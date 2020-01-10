#pragma once

#include "Components/ActorComponent.h"
#include "SongStruct.h"
#include "SongStructGeneratorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class USongStructGeneratorComponent : public UActorComponent
{
   GENERATED_BODY()

public:	
  USongStructGeneratorComponent();

private:
  void GenerateStructFromJson(FSongStruct SongStruct, TSharedPtr<FJsonObject> JsonObject);

  FString JsonFullPath(FString FileName);
}