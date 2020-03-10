// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "UScoreFile.generated.h"

USTRUCT(BlueprintType)
struct FSt_Score {
	GENERATED_BODY()

		UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		int32 score;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		int32 maxSerie;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		FString name;
};

USTRUCT(BlueprintType)
struct FSt_ScoreArray {
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
		TArray<FSt_Score> scores;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BEATWARRIORVR_API UScoreFile : public UObject
{
	GENERATED_BODY()
public:
	UScoreFile();
	~UScoreFile();

	UFUNCTION(BlueprintCallable, Category = Actions)
		const FString &getFolderName() const;

	UFUNCTION(BlueprintCallable, Category = Init)
		void setFolderName(FString folderName);
	
	UFUNCTION(BlueprintCallable, Category = Actions)
		const TArray<FSt_Score> &getScoreList();

	UFUNCTION(BlueprintCallable, Category = Actions)
		bool saveScore(const FSt_Score score);

private:
	FString getFullPath();
	bool loadFileContent();
	const FString& getFileContent() const;
	const TArray<FSt_Score> &generateScoreListFromJson(TSharedPtr<FJsonObject> jsonObject);

	bool VerifyFileExist();

private:
	FString _currentFolder;
	FString _fileContent;
	TArray<FSt_Score> _scoreList;
};
