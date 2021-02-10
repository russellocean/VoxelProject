// Fill out your copyright notice in the Description page of Project Settings.


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
