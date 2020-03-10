// Fill out your copyright notice in the Description page of Project Settings.

#include "UScoreFile.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"


UScoreFile::UScoreFile() : _currentFolder("")
{
}

UScoreFile::~UScoreFile()
{
}

const FString &UScoreFile::getFolderName() const
{
	return _currentFolder;
}

void UScoreFile::setFolderName(FString folderName)
{
	_currentFolder = folderName;
}

const TArray<FSt_Score> &UScoreFile::getScoreList()
{
	if (!loadFileContent()) {
		_scoreList = TArray<FSt_Score>();
	}
	else {
		TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(getFileContent());
		TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject);
		if (FJsonSerializer::Deserialize(jsonReader, jsonObject) && jsonObject.IsValid()) {
			generateScoreListFromJson(jsonObject);
		}
		else if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Invalid score file"));
		}
	}
	return _scoreList;
}

bool UScoreFile::saveScore(const FSt_Score score)
{
	getScoreList();
	FSt_ScoreArray scoreArray;
	FString result;

	scoreArray.scores = _scoreList;
	scoreArray.scores.Add(score);
	if (FJsonObjectConverter::UStructToJsonObjectString(scoreArray, result)) {
		FFileHelper::SaveStringToFile(result, *getFullPath());
		return true;
	}
	return false;
}

FString UScoreFile::getFullPath()
{
	FString fullPath = FPaths::GameContentDir();

	fullPath += getFolderName() + "/score.json";
	return fullPath;
}

bool UScoreFile::loadFileContent()
{
	FString fullPath = getFullPath();
	return FFileHelper::LoadFileToString(_fileContent, *fullPath);
}

const FString& UScoreFile::getFileContent() const
{
	return _fileContent;
}

const TArray<FSt_Score>& UScoreFile::generateScoreListFromJson(TSharedPtr<FJsonObject> jsonObject)
{
	auto objArray = jsonObject->GetArrayField(TEXT("scores"));

	_scoreList.Empty();
	for (uint16 i = 0; i < objArray.Num(); i++) {
		TSharedPtr<FJsonValue> value = objArray[i];
		TSharedPtr<FJsonObject> json = value->AsObject();
		FSt_Score scoreToAdd;

		scoreToAdd.score = json->GetNumberField(TEXT("score"));
		scoreToAdd.maxSerie = json->GetNumberField(TEXT("maxSerie"));
		scoreToAdd.name = json->GetStringField(TEXT("name"));
		scoreToAdd.mode = json->GetNumberField(TEXT("mode"));
		scoreToAdd.scoreMode = json->GetNumberField(TEXT("scoreMode"));
		scoreToAdd.weapon = json->GetNumberField(TEXT("weapon"));
		_scoreList.Add(scoreToAdd);
	}
	return (_scoreList);
}