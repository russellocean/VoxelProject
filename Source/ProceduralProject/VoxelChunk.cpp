#include "VoxelChunk.h"

#include "DrawDebugHelpers.h"

AVoxelChunk::AVoxelChunk()
{
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
		UVoxel* CurrentVoxel = Chunk.Voxels[i];
		FIntVector VoxelPosition = CurrentVoxel->GetVoxelPosition();
		Chunk.Voxels[i]->bIsVisible = CheckVoxelNeighbors(i);
		UE_LOG(LogTemp,Warning,TEXT("Voxel Rendered? %s"), (Chunk.Voxels[i]->bIsVisible ? TEXT("True") : TEXT("False")));
		if(Chunk.Voxels[i]->bIsVisible)
		{
			DrawDebugBox(GetWorld(), FVector(Chunk.Voxels[i]->GetVoxelPosition().X, Chunk.Voxels[i]->GetVoxelPosition().Y, Chunk.Voxels[i]->GetVoxelPosition().Z) * 100, FVector(50,50,50), FColor::Green, true, -1, 0, 4 );
		}

		/*if(Chunk.Voxels[i]->bIsVisible)
		{
			Quad Q1(VoxelPosition.X, VoxelPosition.Y, 1,1);
			Quad Q2(VoxelPosition.X + 1, VoxelPosition.Y + 1, 1,1);
			if(CompareQuad(Q1, Q2));
			{
				Q1.W += Q2.W;
			}
		}*/
	}
	
}

bool AVoxelChunk::CheckVoxelNeighbors(const int32 VoxelIndex)
{
	int32 TotalNeighbors = 0;
	UVoxel* Voxel = Chunk.Voxels[VoxelIndex];
	if(Chunk.Voxels.IsValidIndex(VoxelIndex+256))
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex+256], 0);
		TotalNeighbors++;
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex-256))
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex-256], 1);
		TotalNeighbors++;
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex+16))
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex+16], 2);
		TotalNeighbors++;
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex-16))
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex-16], 3);
		TotalNeighbors++;
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex+1))
	{
		Voxel->SetNeighbor(Chunk.Voxels[VoxelIndex+1], 4);
		TotalNeighbors++;
	}
	if(Chunk.Voxels.IsValidIndex(VoxelIndex-1))
	{
		Voxel->SetNeighbor(Chunk.Voxels[-1], 5);
		TotalNeighbors++;
	}
	if(TotalNeighbors == 6)
	{
		return false; //Voxel should be culled
	}
	return true;
}

bool AVoxelChunk::CompareQuad(Quad& Q1, Quad& Q2)
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

void AVoxelChunk::AddVoxel(const FIntVector VoxelPosition)
{
	UVoxel Voxel;
	Voxel.SetVoxelPosition(VoxelPosition);
	Chunk.Voxels.Add(&Voxel);
}

void AVoxelChunk::RemoveVoxel(FIntVector Position) const
{
	for(int32 i = 0; i < Chunk.Voxels.Num(); i++)
	{
		/*if(Chunk.Voxels[i].GetVoxelPosition() == Position)
		{
			//Remove voxel from Chunk.Voxels[i] and rebuild chunk.
		}*/
	}
}

const FIntVector AVoxelChunk::NeighborOffsets[] {
	FIntVector(1,0,0),
	FIntVector(-1,0,0),
	FIntVector(0,1,0),
	FIntVector(0,-1,0),
	FIntVector(0,0,1),
	FIntVector(0,0,-1)
};