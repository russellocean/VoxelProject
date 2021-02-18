#include "Voxel.h"

void UVoxel::SetVoxelPosition(const FIntVector Position)
{
	Voxel.VoxelPosition = Position;
}

FIntVector UVoxel::GetVoxelPosition() const
{
	return Voxel.VoxelPosition;
}

void UVoxel::SetNeighbor(UVoxel* NeighborVoxel, const int32 Direction)
{
	Neighbors[Direction] = NeighborVoxel;
}

UVoxel* UVoxel::GetNeighbor(const int32 Direction)
{
	return Neighbors[Direction];
}

void UVoxel::SetVoxelID(const int32 VoxelID)
{
	Voxel.VoxelID = VoxelID;
}

int32 UVoxel::GetVoxelID() const
{
	return Voxel.VoxelID;
}

bool UVoxel::IsVisible() const
{
	return Voxel.bIsVisible;
}

void UVoxel::SetVisibility(const bool Visibility)
{
	Voxel.bIsVisible = Visibility;
}
