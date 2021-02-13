#include "VoxelChunk.h"

#include "DrawDebugHelpers.h"

AVoxelChunk::AVoxelChunk()
{
	ChunkMesh = CreateDefaultSubobject<UChunkMesher>("Chunk Mesh");
	SetRootComponent(ChunkMesh);
	ChunkMesh->bUseAsyncCooking = true;
}

void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();

	CreateChunk(FIntVector(0,0,0));
}

void AVoxelChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVoxelChunk::CreateChunk(FIntVector ChunkPosition)
{
	int32 Index = 0;
	for(int32 x = 0; x < Chunk.ChunkSize; x++)
	{
		for(int32 y = 0; y < Chunk.ChunkSize; y++)
		{
			for (int32 z = 0; z < Chunk.ChunkSize; z++)
			{
				UVoxel* Voxel;
				Voxel = NewObject<UVoxel>();
				Voxel->SetVoxelPosition(FIntVector(x,y,z));
				Chunk.Voxels.Add(Voxel);
				Index++;
			}
		}
	}
	for(int32 i = 0; i < Chunk.Voxels.Num(); i++)
	{
		Chunk.Voxels[i]->SetVisibility(CheckVoxelNeighbors(i));
		//UE_LOG(LogTemp,Warning,TEXT("Voxel Rendered? %s"), (Chunk.Voxels[i]->IsVisible() ? TEXT("True") : TEXT("False")));
		/*if(Chunk.Voxels[i]->IsVisible())
		{
			DrawDebugBox(GetWorld(), FVector(Chunk.Voxels[i]->GetVoxelPosition().X, Chunk.Voxels[i]->GetVoxelPosition().Y, Chunk.Voxels[i]->GetVoxelPosition().Z) * 100, FVector(50,50,50), FColor::Green, true, -1, 0, 4 );
		}*/
	}
	ChunkMesh->ChunkToQuads(Chunk.Voxels);
}

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

bool AVoxelChunk::CompareQuad(FQuad& Q1, FQuad& Q2)
{
	if(Q1.Y != Q2.Y) return Q1.Y < Q2.Y;
	if(Q1.X != Q2.X) return Q1.X < Q2.X;
	if(Q1.W != Q2.W) return Q1.W < Q2.W;
	return Q1.H >= Q2.H;
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