#include "VoxelChunk.h"

AVoxelChunk::AVoxelChunk()
{
	ChunkMesh = CreateDefaultSubobject<UChunkMesher>("Chunk Mesh");
	SetRootComponent(ChunkMesh);
	ChunkMesh->bUseAsyncCooking = true;
}

void AVoxelChunk::Initialize(const FIntVector ChunkCoords, AVoxelTerrain* VoxelWorld)
{
	if (Chunk.IsNewChunk)
	{
		VoxelTerrain = VoxelWorld;
		CreateChunk(FIntVector(ChunkCoords));
		Chunk.IsNewChunk = false;
	}
	else
	{
		// Load chunk from disk
	}
}

// xyz global space | ijk local chunk space

void AVoxelChunk::CreateChunk(const FIntVector ChunkPosition)
{
	//Loop from bottom to top
	for (int32 k = 0; k < Chunk.ChunkSize; k++)
	{
		for (int32 j = 0; j < Chunk.ChunkSize; j++)
		{
			for (int32 i = 0; i < Chunk.ChunkSize; i++)
			{
				UVoxel* Voxel;
				Voxel = NewObject<UVoxel>();
				const FIntVector VoxelPosition = FIntVector{
					i + (Chunk.ChunkSize * ChunkPosition.X),
					j + (Chunk.ChunkSize * ChunkPosition.Y),
					k + (Chunk.ChunkSize * ChunkPosition.Z)
				};
				Voxel->Initialize(VoxelPosition, Grass);
				Chunk.Voxels.Add(Voxel);
			}
		}
	}
	for(int32 v = 0; v < Chunk.Voxels.Num(); v++)
	{
		Chunk.Voxels[v]->SetVisibility(CheckVoxelNeighbors(v));
	}
	ChunkMesh->ChunkToQuads(Chunk.Voxels);
}

bool AVoxelChunk::CheckVoxelNeighbors(const int32 VoxelIndex)
{
	int32 TotalNeighbors = 0;
	UVoxel* Voxel = Chunk.Voxels[VoxelIndex];
	if(Voxel->GetType() == Air)
	{
		return false;
	}
	if(Voxel->GetWorldPosition().X % Chunk.ChunkSize != Chunk.ChunkSize-1)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex + 1]->GetType(), 0);
		TotalNeighbors++;
	}
	if(Voxel->GetWorldPosition().X % Chunk.ChunkSize != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 1]->GetType(), 1);
		TotalNeighbors++;
	}
	if(Voxel->GetWorldPosition().Y % Chunk.ChunkSize != Chunk.ChunkSize-1)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex + 16]->GetType(), 2);
		TotalNeighbors++;
	}
	if(Voxel->GetWorldPosition().Y % Chunk.ChunkSize != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 16]->GetType(), 3);
		TotalNeighbors++;
	}
	if(Voxel->GetWorldPosition().Z % Chunk.ChunkSize != Chunk.ChunkSize-1)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex + 256]->GetType(), 4);
		TotalNeighbors++;
	}
	if(Voxel->GetWorldPosition().Z % Chunk.ChunkSize != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 256]->GetType(), 5);
		TotalNeighbors++;
	}
	if(TotalNeighbors == 6)
	{
		return false; //Voxel should be culled
	}
	return true;
}

FIntVector AVoxelChunk::GetChunkPosition() const
{
	return Chunk.ChunkPosition;
}

UVoxel* AVoxelChunk::GetVoxelAt(const FIntVector VoxelLocalPosition)
{
	return Chunk.Voxels[VoxelLocalPosition.X + (VoxelLocalPosition.Y * 16) + (VoxelLocalPosition.Z * 256)];
}


const FIntVector AVoxelChunk::NeighborOffsets[]{
	FIntVector(1, 0, 0),
	FIntVector(-1, 0, 0),
	FIntVector(0, 1, 0),
	FIntVector(0, -1, 0),
	FIntVector(0, 0, 1),
	FIntVector(0, 0, -1)
};
