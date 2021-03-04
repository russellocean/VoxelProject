#include "VoxelChunk.h"

#include "VoxelTerrain.h"

AVoxelChunk::AVoxelChunk()
{
	ChunkMesh = CreateDefaultSubobject<UChunkMesher>("Chunk Mesh");
	SetRootComponent(ChunkMesh);
	ChunkMesh->bUseAsyncCooking = true;
}

void AVoxelChunk::Initialize(const FIntVector ChunkCoords, FVoxelTerrainSettings* TerrainSettings)
{
	if (Chunk.IsNewChunk)
	{
		WorldSettings = TerrainSettings;
		Chunk.ChunkPosition = ChunkCoords;
		CreateChunkData();

		Chunk.IsNewChunk = false;
	}
	else
	{
		return;
		// Load chunk from disk
	}
}

// xyz global space | ijk local chunk space

void AVoxelChunk::CreateChunkData()
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

				const double Height = UNoiseBlueprintFunctionLibrary::GetSimplex2D( WorldSettings->Seed, WorldSettings->Frequency, FVector2D(VoxelPosition.X,VoxelPosition.Y)) * 15 * 3;

				 if(VoxelPosition.Z <= Height)
				 {
					Voxel->Initialize(VoxelPosition, FIntVector(i,j,k), Grass);
				 	if(UNoiseBlueprintFunctionLibrary::GetSimplex3D(WorldSettings->Seed, WorldSettings->Frequency * 3, FVector(VoxelPosition.X+1,VoxelPosition.Y,VoxelPosition.Z)) <= 0.1f)
				 	{
				 		Voxel->SetType(Dirt);
				 	}
				 } else
				 {
				 	Voxel->Initialize(VoxelPosition, FIntVector(i,j,k), Air);
				 }
				 Chunk.Voxels.Add(Voxel);
			}
		}
	}
	ChunkMesh->VoxelMaterial = WorldSettings->VoxelMaterial;
	ChunkMesh->DirtMaterial = WorldSettings->Dirt;
}

bool AVoxelChunk::CalculateVoxelNeighbors(const int32 VoxelIndex)
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
	}
	else
	{
		FChunkData* ChunkData = Chunk.NeighborChunks[0];
		const FIntVector& VoxelLocalPosition = Voxel->GetLocalPosition();
		Voxel->SetNeighbor(ChunkData->Voxels[(Chunk.ChunkSizeSquared * VoxelLocalPosition.Z) + 16]->GetType(), 0);
    }

	if(Voxel->GetLocalPosition().X != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 1]->GetType(), 1);
	}
	else
	{
		FChunkData* ChunkData = Chunk.NeighborChunks[1];
		const FIntVector& VoxelLocalPosition = Voxel->GetLocalPosition();
		Voxel->SetNeighbor(ChunkData->Voxels[(Chunk.ChunkSizeSquared * VoxelLocalPosition.Z) + 15]->GetType(), 1);
	}
	if(Voxel->GetLocalPosition().Y != Chunk.ChunkSize - 1)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex + 16]->GetType(), 2);
	}
	if(Voxel->GetLocalPosition().Y != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 16]->GetType(), 3);
	}
	if(Voxel->GetLocalPosition().Z != Chunk.ChunkSize - 1)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex + 256]->GetType(), 4);
	}
	if(Voxel->GetLocalPosition().Z != 0)
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex - 256]->GetType(), 5);
	}

	for(int n = 0; n < 6; n++)
	{
		if(Voxel->GetNeighbor(n) == Air)
		{
			return true;
		}
	}
	return false;
}

void AVoxelChunk::RefreshChunk(const bool bCheckNeighbors)
{
	auto& VoxelChunks = AVoxelTerrain::VoxelChunks;
	//WorldData = &AVoxelTerrain::VoxelTerrainData;
	if(bCheckNeighbors)
	{
		if(VoxelChunks.Contains(FIntVector(GetChunkPosition().X+1, GetChunkPosition().Y, GetChunkPosition().Z)))
		{
			FChunkData* ChunkData = VoxelChunks.FindRef(FIntVector(GetChunkPosition().X+1, GetChunkPosition().Y, GetChunkPosition().Z))->GetChunkData();
			SetChunkNeighbor(ChunkData, 0);
		} 
		if(VoxelChunks.Contains(FIntVector(GetChunkPosition().X-1, GetChunkPosition().Y, GetChunkPosition().Z)))
		{
			FChunkData* ChunkData = VoxelChunks.FindRef(FIntVector(GetChunkPosition().X-1, GetChunkPosition().Y, GetChunkPosition().Z))->GetChunkData();
			SetChunkNeighbor(ChunkData, 1);
		}
		if(VoxelChunks.Contains(FIntVector(GetChunkPosition().X, GetChunkPosition().Y+1, GetChunkPosition().Z)))
		{
			FChunkData* ChunkData = VoxelChunks.FindRef(FIntVector(GetChunkPosition().X, GetChunkPosition().Y+1, GetChunkPosition().Z))->GetChunkData();
			SetChunkNeighbor(ChunkData, 2);
		}
		if(VoxelChunks.Contains(FIntVector(GetChunkPosition().X+1, GetChunkPosition().Y-1, GetChunkPosition().Z)))
		{
			FChunkData* ChunkData = VoxelChunks.FindRef(FIntVector(GetChunkPosition().X, GetChunkPosition().Y-1, GetChunkPosition().Z))->GetChunkData();
			SetChunkNeighbor(ChunkData, 3);
		}
		if(VoxelChunks.Contains(FIntVector(GetChunkPosition().X, GetChunkPosition().Y, GetChunkPosition().Z+1)))
		{
			FChunkData* ChunkData = VoxelChunks.FindRef(FIntVector(GetChunkPosition().X, GetChunkPosition().Y, GetChunkPosition().Z+1))->GetChunkData();
			SetChunkNeighbor(ChunkData, 4);
		}
		if(VoxelChunks.Contains(FIntVector(GetChunkPosition().X, GetChunkPosition().Y, GetChunkPosition().Z-1)))
		{
			FChunkData* ChunkData = VoxelChunks.FindRef(FIntVector(GetChunkPosition().X, GetChunkPosition().Y, GetChunkPosition().Z-1))->GetChunkData();
			SetChunkNeighbor(ChunkData, 5);
		}
	}
	if(Chunk.NeighborChunks.Num() == 6)
	{
		for(int32 v = 0; v < Chunk.Voxels.Num(); v++)
		{		
			Chunk.Voxels[v]->SetVisibility(CalculateVoxelNeighbors(v));
		}
		Chunk.IsVisible = true;
		ChunkMesh->ChunkToQuads(Chunk.Voxels);
	}
}

FIntVector AVoxelChunk::GetChunkPosition() const { return Chunk.ChunkPosition; }

UVoxel* AVoxelChunk::GetVoxelAt(const FIntVector VoxelLocalPosition)
{
	return Chunk.Voxels[VoxelLocalPosition.X + (VoxelLocalPosition.Y * 16) + (VoxelLocalPosition.Z * 256)];
}

FChunkData* AVoxelChunk::GetChunkData() { return &Chunk; }

void AVoxelChunk::SetChunkNeighbor(FChunkData* ChunkData, const int32 Direction) { Chunk.NeighborChunks.Emplace(Direction, ChunkData); }

FChunkData* AVoxelChunk::GetChunkNeighbor(const int32 Direction) { return Chunk.NeighborChunks[Direction]; }

const FIntVector AVoxelChunk::NeighborOffsets[] {
	FIntVector(1, 0, 0),
	FIntVector(-1, 0, 0),
	FIntVector(0, 1, 0),
	FIntVector(0, -1, 0),
	FIntVector(0, 0, 1),
	FIntVector(0, 0, -1)
};
