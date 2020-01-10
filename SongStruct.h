#pragma once

USTRUCT(BlueprintType)
struct FSongStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    Fstring version;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    FArray<FNoteStruct> notes;
};

USTRUCT(BlueprintType)
struct FNoteStruct
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    double time;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    int lineIndex;

    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    int lineLayer;
   
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    int type;
    
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
    int cutDirection;
}