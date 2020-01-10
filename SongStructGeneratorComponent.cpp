#include "SongStructGeneratorComponent.h"

FSongStruct USongStructGeneratorComponent::GenerateStructFromJson(FString Path)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonFullPath(Path));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	FSongStruct SongStruct;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}
		GenerateStructsFromJson(SongStruct, JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}

	return SongStruct;
}

void USongStructGeneratorComponent::GenerateStructFromJson(FSongStruct &SongStruct, TSharedPtr<FJsonObject> JsonObject)
{
    SongStruct.version = JsonObject.GetStringField(TEXT("_version"));

    auto objArray = JsonObject.GetArrayField(TEXT("_notes"));

    for (int i = 0; i < objArray.Num(); i++) {
        TSharedPtr<FJsonValue> value = objArray[i];
		TSharedPtr<FJsonObject> json = value->AsObject();
        FNoteStruct note;

        note.time = json.GetNumberField(TEXT("_time"));
        note.lineIndex = json.GetIntegerField(TEXT("_lineIndex"));
        note.lineLayer = json.GetIntegerField(TEXT("_lineLayer"));
        note.type = json.GetIntergerField(TEXT("_type"));
        note.cutDirection = json.GetIntegerField(TEXT("_cutDirection"));

        SongStruct.notes.Push(note);
    }
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