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
		None
	};
}

UENUM()
namespace ESizes
{
	enum SIZE
	{
		Large,
		Medium,
		Small,
		None
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

public:

	UPROPERTY(BlueprintReadOnly)
	float floatMessage;

	UPROPERTY(BlueprintReadWrite)
	int intMessage;

	UPROPERTY(BlueprintReadOnly)
	FString stringMessage;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EMessageTypes::Type> typeMessage;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ESizes::SIZE> asteroidSizeMessage;

	UPROPERTY(BlueprintReadOnly)
	FVector currentPosMessage;

	UPROPERTY(BlueprintReadWrite)
	bool isNewHighScore;
};
