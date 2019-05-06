#pragma once

#include "MessageStruct.generated.h"

UENUM(BlueprintType)
namespace EMessageTypes
{
	enum Type
	{
		Float,
		Int,
		String,
	};
}

UENUM()
namespace ESizes
{
	enum SIZE
	{
		Large,
		Medium,
		Small
	};
}

UENUM()
namespace EStartSides
{
	enum START_SIDE 
	{ 
		Left = 0, 
		Right = 1, 
		Up = 2, 
		Down = 3, 
		None = 20 
	};
}


USTRUCT(BlueprintType)
struct FMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float floatMessage = NAN;

	UPROPERTY(BlueprintReadOnly)
	int intMessage = NAN;

	UPROPERTY(BlueprintReadOnly)
	FString stringMessage = "";

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EMessageTypes::Type> messageType;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ESizes::SIZE> messageAsteroidSize;

	UPROPERTY(BlueprintReadOnly)
	FVector messageCurrentPos;

public:
};