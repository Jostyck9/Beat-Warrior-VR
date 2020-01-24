// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SongStructGeneratorComponent.generated.h"

USTRUCT(BlueprintType)
struct FSt_Note {
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		float time;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		int32 lineIndex;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		int32 lineLayer;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		int32 type;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		int32 cutDirection;
};

USTRUCT(BlueprintType)
struct FST_SongStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		FString version;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		TArray<FSt_Note> notes;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEATWARRIORVR_API USongStructGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FST_SongStruct music;
public:	
	// Sets default values for this component's properties
	USongStructGeneratorComponent();

	UFUNCTION(BlueprintCallable)
		FST_SongStruct GenerateStructFromJson(FString Path);

private:	
	FST_SongStruct GenerateStructFromJson(FST_SongStruct SongStruct, TSharedPtr<FJsonObject> JsonObject);

	FString JsonFullPath(FString FileName);
};
