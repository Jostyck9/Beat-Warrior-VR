// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Paths.h"
#include "HAL/FileManagerGeneric.h"
#include "MusicClassComponent.generated.h"

USTRUCT(BlueprintType)
struct FDifficultyBeatmapStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString difficulty;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        uint8 difficultyRank;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString beatmapFilename;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        float noteJumpMovementSpeed;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        float noteJumpStartBeatOffset;
};

USTRUCT(BlueprintType)
struct FDifficultyBeatmapSetsStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString beatmapCharacteristicName;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        TArray<FDifficultyBeatmapStruct> difficultyBeatmaps;
};

USTRUCT(BlueprintType)
struct FInfoStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString version;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString songName;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString songAuthorName;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString levelAuthorName;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        float beatsPerMinute;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        float songTimeOffset;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString songFilename;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString coverImageFilename;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        FString environmentName;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
        TArray<FDifficultyBeatmapSetsStruct> difficultyBeatmapSets;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEATWARRIORVR_API UMusicClassComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    TMap<FString, FInfoStruct> musics;

public:
	// Sets default values for this component's properties
	UMusicClassComponent();

private:
	UFUNCTION(BlueprintCallable)
		void readFolders(FString Directory);

	UFUNCTION(BlueprintCallable)
		TMap<FString, FInfoStruct> getMusics();

    FInfoStruct GenerateStructFromJson(FString Path, FString SongFolder);

    FInfoStruct GenerateStructFromJson(FInfoStruct InfoStruct, TSharedPtr<FJsonObject> JsonObject, FString SongFolder);

    FString JsonFullPath(FString FileName);
};