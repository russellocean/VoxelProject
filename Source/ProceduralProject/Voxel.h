#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Voxel.generated.h"

USTRUCT(BlueprintType)
struct FVoxelData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Voxel)
	FIntVector VoxelPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Voxel)
	int32 VoxelID;
};
UCLASS()
class PROCEDURALPROJECT_API UVoxel final : public UObject
{
	GENERATED_BODY()
	FVoxelData Voxel;

	UVoxel* Neighbors[6];

public:
	void SetVoxelPosition(FIntVector Position);
	FIntVector GetVoxelPosition() const;
	void SetNeighbor(UVoxel* NeighborVoxel, int32 Direction);
	UVoxel* GetNeighbor(int32 Direction);
	
	bool CompareQuad((const int xPos0, const int ));

	bool bIsVisible;
};
