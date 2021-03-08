#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Voxel.generated.h"

UENUM()
enum EType
{
	Air UMETA(DisplayName = "Air"),
	Grass UMETA(DisplayName = "Grass"),
	Dirt UMETA(DisplayName = "Dirt"),
	Stone UMETA(DisplayName = "Stone"),
};

struct FVoxelData
{
	TEnumAsByte<EType> VoxelType;
	
	bool bIsVisible;

	EType Neighbors[6];
};

UCLASS()
class PROCEDURALPROJECT_API UVoxel final : public UObject
{
	GENERATED_BODY()
	FVoxelData Voxel;

public:
	void SetType(TEnumAsByte<EType> Type);
	TEnumAsByte<EType> GetType() const;

	void SetVisibility(bool Visibility);
	bool IsVisible() const;

	void SetNeighbor(TEnumAsByte<EType> Type, int32 Direction);
	EType GetNeighbor(int32 Direction);
};
