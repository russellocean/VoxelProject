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

USTRUCT(BlueprintType)
struct FVoxelData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Voxel)
	FIntVector VoxelWorldPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Voxel)
	FIntVector VoxelLocalPosition;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Voxel)
	TEnumAsByte<EType> VoxelType;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Voxel)
	bool bIsVisible;

	EType Neighbors[6];
};

UCLASS()
class PROCEDURALPROJECT_API UVoxel final : public UObject
{
	GENERATED_BODY()
	FVoxelData Voxel;

public:
	void Initialize(FIntVector WorldPosition, FIntVector LocalPosition, TEnumAsByte<EType> Type);
	
	void SetWorldPosition(FIntVector Position);
	FIntVector GetWorldPosition() const;

	void SetLocalPosition(FIntVector Position);
	FIntVector GetLocalPosition() const;

	void SetType(TEnumAsByte<EType> Type);
	TEnumAsByte<EType> GetType() const;

	void SetVisibility(bool Visibility);
	bool IsVisible() const;

	void SetNeighbor(TEnumAsByte<EType> Type, int32 Direction);
	EType GetNeighbor(int32 Direction);
};
