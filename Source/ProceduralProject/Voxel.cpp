#include "Voxel.h"

void UVoxel::SetType(const TEnumAsByte<EType> Type) { Voxel.VoxelType = Type; }

TEnumAsByte<EType> UVoxel::GetType() const { return Voxel.VoxelType;}

void UVoxel::SetVisibility(const bool Visibility) { Voxel.bIsVisible = Visibility; }

bool UVoxel::IsVisible() const { return Voxel.bIsVisible; }

void UVoxel::SetNeighbor(const TEnumAsByte<EType> Type, const int32 Direction) { Voxel.Neighbors[Direction] = Type; }

EType UVoxel::GetNeighbor(const int32 Direction) { return Voxel.Neighbors[Direction]; }