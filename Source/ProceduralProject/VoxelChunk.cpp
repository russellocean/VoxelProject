#include "VoxelChunk.h"
#include "VoxelTerrain.h"

AVoxelChunk::AVoxelChunk()
{
	ChunkMesh = CreateDefaultSubobject<UChunkMesher>("Chunk Mesh");
	SetRootComponent(ChunkMesh);
	ChunkMesh->bUseAsyncCooking = true;
}

void AVoxelChunk::Initialize(const FIntVector ChunkCoords, FVoxelTerrainData* TerrainData)
{
	if (Chunk.IsNewChunk)
	{
		WorldData = TerrainData;
		Chunk.ChunkPosition = ChunkCoords;
		CreateChunk();
		Chunk.IsNewChunk = false;
	}
	else
	{
		return;
		// Load chunk from disk
	}
}

// xyz global space | ijk local chunk space

void AVoxelChunk::CreateChunk()
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
					i + (Chunk.ChunkSize * Chunk.ChunkPosition.X),
					j + (Chunk.ChunkSize * Chunk.ChunkPosition.Y),
					k + (Chunk.ChunkSize * Chunk.ChunkPosition.Z)
				};

				const double Height = UNoiseBlueprintFunctionLibrary::GetSimplex2D( WorldData->Seed, WorldData->Frequency, FVector2D(VoxelPosition.X,VoxelPosition.Y))
				* 15 * 3;

				if(VoxelPosition.Z <= Height)
				{
					Voxel->Initialize(VoxelPosition, FIntVector(i,j,k), Grass);
				} else
				{
					Voxel->Initialize(VoxelPosition, FIntVector(i,j,k), Air);
				}

				Chunk.Voxels.Add(Voxel);
			}
		}
	}
	for(int32 v = 0; v < Chunk.Voxels.Num(); v++)
	{		
		Chunk.Voxels[v]->SetVisibility(CheckVoxelNeighbors(v));
	}
	
	ChunkMesh->VoxelMaterial = WorldData->VoxelMaterial;
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
	if(Voxel->GetLocalPosition().X != Chunk.ChunkSize - 1)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex + 1]->GetType(), 0);
		if(Voxel->GetNeighbor(0) != Air)
		{
			TotalNeighbors++;
		}
	}
	if(Voxel->GetLocalPosition().X != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 1]->GetType(), 1);
		if(Voxel->GetNeighbor(1) != Air)
		{
			TotalNeighbors++;
		}
	}
	if(Voxel->GetLocalPosition().Y != Chunk.ChunkSize - 1)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex + 16]->GetType(), 2);
		if(Voxel->GetNeighbor(2) != Air)
		{
			TotalNeighbors++;
		}
	}
	if(Voxel->GetLocalPosition().Y != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 16]->GetType(), 3);
		if(Voxel->GetNeighbor(3) != Air)
		{
			TotalNeighbors++;
		} 
	}
	if(Voxel->GetLocalPosition().Z != Chunk.ChunkSize - 1)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex + 256]->GetType(), 4);
		if(Voxel->GetNeighbor(4) != Air)
		{
			TotalNeighbors++;
		} 
	}
	if(Voxel->GetLocalPosition().Z != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 256]->GetType(), 5);
		if(Voxel->GetNeighbor(5) != Air)
		{
			TotalNeighbors++;
		} 
	}
	
	if(TotalNeighbors == 6)
	{
		return false; //Voxel should be culled
	}
	return true;
}

FIntVector AVoxelChunk::GetChunkPosition() const { return Chunk.ChunkPosition; }

UVoxel* AVoxelChunk::GetVoxelAt(const FIntVector VoxelLocalPosition)
{
	return Chunk.Voxels[VoxelLocalPosition.X + (VoxelLocalPosition.Y * 16) + (VoxelLocalPosition.Z * 256)];
}

FChunkData* AVoxelChunk::GetChunkData() { return &Chunk; }

void AVoxelChunk::SetChunkNeighbor(FChunkData* ChunkData, const int32 Direction) { Chunk.NeighborChunks[Direction] = ChunkData; }

FChunkData* AVoxelChunk::GetChunkNeighbor(const int32 Direction) { return Chunk.NeighborChunks[Direction]; }

const FIntVector AVoxelChunk::NeighborOffsets[]{
	FIntVector(1, 0, 0),
	FIntVector(-1, 0, 0),
	FIntVector(0, 1, 0),
	FIntVector(0, -1, 0),
	FIntVector(0, 0, 1),
	FIntVector(0, 0, -1)
};
