/** Structure that defines a power up table entry */
#pragma once

#include "Engine/DataTable.h"
#include "PowerUpDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FPowerUpData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FPowerUpData()
		: Points(0)
	{}

	/** Extra HitPoints gained at this level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	int32 Points;
};