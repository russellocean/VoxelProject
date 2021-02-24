#include "Voxel.h"

void UVoxel::Initialize(const FIntVector WorldPosition, const FIntVector LocalPosition, const TEnumAsByte<EType> Type)
{
	SetWorldPosition(WorldPosition);
	SetLocalPosition(LocalPosition);
	SetType(Type);
}

void UVoxel::SetWorldPosition(const FIntVector Position) { Voxel.VoxelWorldPosition = Position; }

FIntVector UVoxel::GetWorldPosition() const { return Voxel.VoxelWorldPosition; }

void UVoxel::SetLocalPosition(const FIntVector Position) { Voxel.VoxelLocalPosition = Position; }

FIntVector UVoxel::GetLocalPosition() const { return Voxel.VoxelLocalPosition; }

void UVoxel::SetType(const TEnumAsByte<EType> Type) { Voxel.VoxelType = Type; }

TEnumAsByte<EType> UVoxel::GetType() const { return Voxel.VoxelType;}

void UVoxel::SetVisibility(const bool Visibility) { Voxel.bIsVisible = Visibility; }

bool UVoxel::IsVisible() const { return Voxel.bIsVisible; }

void UVoxel::SetNeighbor(const TEnumAsByte<EType> Type, const int32 Direction) { Voxel.Neighbors[Direction] = Type; }

EType UVoxel::GetNeighbor(const int32 Direction) { return Voxel.Neighbors[Direction]; }