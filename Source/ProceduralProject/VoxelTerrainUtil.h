#pragma once

namespace VoxelTerrainUtil
{
	inline FIntVector WorldToChunkCoord(const FIntVector WorldLocation)
	{
		return (WorldLocation / 100) / 16;
	}

	inline FIntVector VoxelIndexToLocalCoords(const int32 VoxelIndex)
	{ // look over this it doesnt work i think
		const int32 x = VoxelIndex % 16;
		const int32 y = (VoxelIndex / 16) % 16;
		const int32 z = VoxelIndex / (16 * 16);
		return FIntVector(x,y,z);
	}

	inline FIntVector VoxelIndexToWorldCoords(const int32 VoxelIndex, const FIntVector ChunkPosition)
	{
		FIntVector WorldCoords;
		WorldCoords.X = VoxelIndexToLocalCoords(VoxelIndex).X + (ChunkPosition.X * 16);
		WorldCoords.Y = VoxelIndexToLocalCoords(VoxelIndex).Y + (ChunkPosition.Y * 16);
		WorldCoords.Z = VoxelIndexToLocalCoords(VoxelIndex).Z + (ChunkPosition.Z * 16);
		return FIntVector(WorldCoords);
	}
}
