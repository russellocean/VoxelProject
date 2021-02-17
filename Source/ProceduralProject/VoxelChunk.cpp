#include "VoxelChunk.h"

AVoxelChunk::AVoxelChunk()
{
	ChunkMesh = CreateDefaultSubobject<UChunkMesher>("Chunk Mesh");
	SetRootComponent(ChunkMesh);
	ChunkMesh->bUseAsyncCooking = true;
}

void AVoxelChunk::Initialize(const FIntVector ChunkCoords)
{
	if(Chunk.IsNewChunk)
	{
		CreateChunk(FIntVector(ChunkCoords));
		Chunk.IsNewChunk = false;
	} else
	{
		// Load chunk from disk
	}
}

void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
}

// xyz global space | ijk local chunk space

void AVoxelChunk::CreateChunk(const FIntVector ChunkPosition)
{
	int32 Index = 0;
	//Loop through all axis in the chunk by Chunk size and create a new voxel there. Add to our chunk array.
	for(int32 i = 0; i < Chunk.ChunkSize; i++)
	{
		for(int32 j = 0; j < Chunk.ChunkSize; j++)
		{
			for (int32 k = 0; k < Chunk.ChunkSize; k++)
			{
				UVoxel* Voxel;
				Voxel = NewObject<UVoxel>();
				const FIntVector VoxelPosition = FIntVector{i + (Chunk.ChunkSize * ChunkPosition.X),j + (Chunk.ChunkSize * ChunkPosition.Y),k + (Chunk.ChunkSize * ChunkPosition.Z)};
				Voxel->SetVoxelPosition(VoxelPosition);
				Chunk.Voxels.Add(Voxel);
				Index++;
			}
		}
	}
	for(int32 i = 0; i < Chunk.Voxels.Num(); i++)
	{
		Chunk.Voxels[i]->SetVisibility(CheckVoxelNeighbors(i));
	}
	ChunkMesh->ChunkToQuads(Chunk.Voxels);
}

//I really dont like the check system here TODO find another method to detect neighbors
bool AVoxelChunk::CheckVoxelNeighbors(const int32 VoxelIndex)
{
	int32 TotalNeighbors = 0;
	UVoxel* Voxel = Chunk.Voxels[VoxelIndex];
	if(Chunk.Voxels.IsValidIndex(VoxelIndex+256))
	{
		if(Chunk.Voxels[VoxelIndex]->GetVoxelPosition().X +1 == Chunk.Voxels[VoxelIndex+256]->GetVoxelPosition().X)
		{
			Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex+256], 0);
			TotalNeighbors++;
		}
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex-256))
	{
		if(Chunk.Voxels[VoxelIndex]->GetVoxelPosition().X -1 == Chunk.Voxels[VoxelIndex-256]->GetVoxelPosition().X)
		{
			Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex-256], 1);
			TotalNeighbors++;
		}
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex+16))
	{
		if(Chunk.Voxels[VoxelIndex]->GetVoxelPosition().Y +1 == Chunk.Voxels[VoxelIndex+16]->GetVoxelPosition().Y)
		{
			Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex+16], 2);
			TotalNeighbors++;
		}
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex-16))
	{
		if(Chunk.Voxels[VoxelIndex]->GetVoxelPosition().Y -1 == Chunk.Voxels[VoxelIndex-16]->GetVoxelPosition().Y)
		{
			Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex-16], 3);
			TotalNeighbors++;
		}
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex+1))
	{
		if(Chunk.Voxels[VoxelIndex]->GetVoxelPosition().Z +1 == Chunk.Voxels[VoxelIndex+1]->GetVoxelPosition().Z)
		{
			Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex+1], 4);
			TotalNeighbors++;
		}
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex-1))
	{
		if(Chunk.Voxels[VoxelIndex]->GetVoxelPosition().Z -1 == Chunk.Voxels[VoxelIndex-1]->GetVoxelPosition().Z)
		{
			Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex-1], 5);
			TotalNeighbors++;
		}
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

void AVoxelChunk::AddVoxel(UVoxel Voxel)
{
	Chunk.Voxels.Add(&Voxel);
}

const FIntVector AVoxelChunk::NeighborOffsets[] {
	FIntVector(1,0,0),
	FIntVector(-1,0,0),
	FIntVector(0,1,0),
	FIntVector(0,-1,0),
	FIntVector(0,0,1),
	FIntVector(0,0,-1)
};