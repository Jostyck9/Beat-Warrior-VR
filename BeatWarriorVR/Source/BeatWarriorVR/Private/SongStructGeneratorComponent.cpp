// Fill out your copyright notice in the Description page of Project Settings.

#include "SongStructGeneratorComponent.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"

// Sets default values for this component's properties
USongStructGeneratorComponent::USongStructGeneratorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FST_SongStruct USongStructGeneratorComponent::GenerateStructFromJson(FString Path)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonFullPath(Path));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	FST_SongStruct SongStruct;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}
		return GenerateStructFromJson(SongStruct, JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}
	return SongStruct;
}

FST_SongStruct USongStructGeneratorComponent::GenerateStructFromJson(FST_SongStruct SongStruct, TSharedPtr<FJsonObject> jsonObject)
{
	SongStruct.version = jsonObject->GetStringField(TEXT("_version"));

	auto objArray = jsonObject->GetArrayField(TEXT("_notes"));

	for (int i = 0; i < objArray.Num(); i++) {
		TSharedPtr<FJsonValue> value = objArray[i];
		TSharedPtr<FJsonObject> json = value->AsObject();
		FSt_Note note;

		note.time = json->GetNumberField(TEXT("_time"));
		note.lineIndex = json->GetIntegerField(TEXT("_lineIndex"));
		note.lineLayer = json->GetIntegerField(TEXT("_lineLayer"));
		note.type = json->GetIntegerField(TEXT("_type"));
		note.cutDirection = json->GetIntegerField(TEXT("_cutDirection"));

		SongStruct.notes.Push(note);
	}
	return SongStruct;
}

FString USongStructGeneratorComponent::JsonFullPath(FString Path)
{
	// Games/Content/****.json
	FString FullPath = FPaths::GameContentDir();
	FullPath += Path;
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);

	return JsonStr;
}