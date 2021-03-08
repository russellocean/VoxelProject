﻿#include "VoxelTerrain.h"
#include "DrawDebugHelpers.h"
#include "NavigationOctree.h"

#include "VoxelChunk.h"

TMap<FIntVector, AVoxelChunk*> AVoxelTerrain::VoxelChunks;

AVoxelTerrain::AVoxelTerrain()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVoxelTerrain::BeginPlay()
{
	Super::BeginPlay();

	TOctree2<EType, FIntVector> Octree = TOctree2<EType, FIntVector>(FVector(0,0,0), VoxelTerrainSettings.RenderDistance);
	Octree.AddElement(Dirt);
}

void AVoxelTerrain::InitializeChunk(const FIntVector ChunkPosition)
{
	AVoxelChunk* Chunk = static_cast<AVoxelChunk*>(GetWorld()->SpawnActor(AVoxelChunk::StaticClass()));
	Chunk->Initialize(ChunkPosition, &VoxelTerrainSettings);

	VoxelChunks.Add(ChunkPosition, Chunk);
}

void AVoxelTerrain::Tick(float DeltaTime)
{
	const FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() / 100;
	const FVector PlayerChunkPosition = FVector(PlayerPosition.X / 16, PlayerPosition.Y / 16, PlayerPosition.Z / 16);

	for (int32 x = PlayerChunkPosition.X-VoxelTerrainSettings.RenderDistance; x < PlayerChunkPosition.X+VoxelTerrainSettings.RenderDistance; x++)
	{
		for (int32 y = PlayerChunkPosition.Y-VoxelTerrainSettings.RenderDistance; y < PlayerChunkPosition.Y+VoxelTerrainSettings.RenderDistance; y++)
		{
			for (int32 z = -2; z <= 1; z++)
			{
				if(!VoxelChunks.Contains(FIntVector(x,y,z)))
				{
					InitializeChunk(FIntVector(x,y,z));
					//DrawDebugBox(GetWorld(), FVector((x*1600)+800,(y*1600)+800,(z*1600)+800), FVector(800,800,800), FColor::Blue, true, 60.f, ECC_WorldStatic, 5.f);
					
					CheckChunks(PlayerChunkPosition);
				}
			}
		}
	}
	
	Super::Tick(DeltaTime);
}

void AVoxelTerrain::CheckChunks(FVector PlayerChunkPosition)
{
	for(auto& Elem : VoxelChunks)
	{
		AVoxelChunk* Chunk = Elem.Value;
		if(Chunk->GetChunkPosition().X < PlayerChunkPosition.X - VoxelTerrainSettings.RenderDistance || Chunk->GetChunkPosition().X > PlayerChunkPosition.X + VoxelTerrainSettings.RenderDistance)
		{
			VoxelChunks.Remove(Chunk->GetChunkPosition());
			Chunk->Destroy();
		}
		if(Chunk->GetChunkPosition().Y < PlayerChunkPosition.Y - VoxelTerrainSettings.RenderDistance || Chunk->GetChunkPosition().Y > PlayerChunkPosition.Y + VoxelTerrainSettings.RenderDistance)
		{
			VoxelChunks.Remove(Chunk->GetChunkPosition());
			Chunk->Destroy();
		}
		if(!Chunk->GetChunkData()->IsVisible)
		{
			Chunk->RefreshChunk(true);
		}
	}
}