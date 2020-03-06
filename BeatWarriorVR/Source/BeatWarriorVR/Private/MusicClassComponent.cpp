// Fill out your copyright notice in the Description page of Project Settings.

#include "MusicClassComponent.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"

// Sets default values for this component's properties
UMusicClassComponent::UMusicClassComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

TMap<FString, FInfoStruct> UMusicClassComponent::getMusics()
{
    return this->musics;
}

void UMusicClassComponent::readFolders(FString Directory)
{
    FString FullPath = FPaths::GameContentDir();
    FullPath += Directory;
    TArray<FString> output;
    output.Empty();
    if (FPaths::DirectoryExists(FullPath))
    {
        FFileManagerGeneric::Get().FindFiles(output, *(FullPath + "*"), false, true);
        for (int i = 0; i < output.Num(); i++) {
            FString MusicPath = FullPath;
            MusicPath += output[i];
            MusicPath += TEXT("/info.dat");
            this->musics.Add(output[i], GenerateStructFromJson(MusicPath, output[i]));
        }
    }
}

FInfoStruct UMusicClassComponent::GenerateStructFromJson(FString Path, FString SongFolder)
{
    TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonFullPath(Path));
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    FInfoStruct InfoStruct;

    if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
    {
        //if (GEngine) {
        //    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
        //}
        return GenerateStructFromJson(InfoStruct, JsonObject, SongFolder);
    }
    //else {
    //    if (GEngine) {
    //        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
    //    }
    //}
    return InfoStruct;
}

FInfoStruct UMusicClassComponent::GenerateStructFromJson(FInfoStruct InfoStruct, TSharedPtr<FJsonObject> JsonObject, FString SongFolder)
{
    InfoStruct.version = JsonObject->GetStringField(TEXT("_version"));
    InfoStruct.songName = JsonObject->GetStringField(TEXT("_songName"));
    InfoStruct.songAuthorName = JsonObject->GetStringField(TEXT("_songAuthorName"));
    InfoStruct.levelAuthorName = JsonObject->GetStringField(TEXT("_levelAuthorName"));
    InfoStruct.beatsPerMinute = JsonObject->GetNumberField(TEXT("_beatsPerMinute"));
    InfoStruct.songTimeOffset = JsonObject->GetNumberField(TEXT("_songTimeOffset"));
    InfoStruct.songFilename += "SoundsMaps/" + SongFolder + "/";
    InfoStruct.songFilename += JsonObject->GetStringField(TEXT("_songFilename"));
    InfoStruct.coverImageFilename = FPaths::GameContentDir();
    InfoStruct.coverImageFilename += "SoundsMaps/" + SongFolder + "/";
    InfoStruct.coverImageFilename += JsonObject->GetStringField(TEXT("_coverImageFilename"));
    InfoStruct.environmentName = JsonObject->GetStringField(TEXT("_environmentName"));

    auto objArray = JsonObject->GetArrayField(TEXT("_difficultyBeatmapSets"));

    for (int i = 0; i < objArray.Num(); i++) {
        TSharedPtr<FJsonValue> value = objArray[i];
        TSharedPtr<FJsonObject> json = value->AsObject();
        FDifficultyBeatmapSetsStruct DifficultyBeatmapSets;

        DifficultyBeatmapSets.beatmapCharacteristicName = json->GetStringField(TEXT("_beatmapCharacteristicName"));

        auto objArray2 = json->GetArrayField(TEXT("_difficultyBeatmaps"));

        for (int i = 0; i < objArray2.Num(); i++) {
            TSharedPtr<FJsonValue> value2 = objArray2[i];
            TSharedPtr<FJsonObject> json2 = value2->AsObject();
            FDifficultyBeatmapStruct DifficultyBeatmaps;

            DifficultyBeatmaps.difficulty = json2->GetStringField(TEXT("_difficulty"));
            DifficultyBeatmaps.difficultyRank = json2->GetIntegerField(TEXT("_difficultyRank"));
            DifficultyBeatmaps.beatmapFilename = "SoundsMaps/" + SongFolder + "/";
            DifficultyBeatmaps.beatmapFilename += json2->GetStringField(TEXT("_beatmapFilename"));
            DifficultyBeatmaps.noteJumpMovementSpeed = json2->GetNumberField(TEXT("_noteJumpMovementSpeed"));
            DifficultyBeatmaps.noteJumpStartBeatOffset = json2->GetNumberField(TEXT("_noteJumpStartBeatOffset"));

            DifficultyBeatmapSets.difficultyBeatmaps.Push(DifficultyBeatmaps);
        }
        InfoStruct.difficultyBeatmapSets.Push(DifficultyBeatmapSets);
    }
    return InfoStruct;
}

FString UMusicClassComponent::JsonFullPath(FString Path)
{
    // Games/Content/****.json
    FString JsonStr;
    FFileHelper::LoadFileToString(JsonStr, *Path);

    return JsonStr;
}