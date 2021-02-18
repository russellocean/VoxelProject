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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Voxel)
	bool bIsVisible;
};

UCLASS()
class PROCEDURALPROJECT_API UVoxel final : public UObject
{
	GENERATED_BODY()
	FVoxelData Voxel;

	//References all neighbors. Maybe should move this into VoxelData?
	UVoxel* Neighbors[6] = {nullptr};

public:
	void SetVoxelPosition(FIntVector Position);
	FIntVector GetVoxelPosition() const;
	void SetNeighbor(UVoxel* NeighborVoxel, int32 Direction);
	UVoxel* GetNeighbor(int32 Direction);

	void SetVoxelID(int32 VoxelID);
	int32 GetVoxelID() const;
	bool IsVisible() const;
	void SetVisibility(bool Visibility);
};
