#include "VoxelTerrain.h"

#include "VoxelChunk.h"

AVoxelTerrain::AVoxelTerrain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AVoxelTerrain::BeginPlay()
{
	Super::BeginPlay();
}

void AVoxelTerrain::InitializeChunk(const FIntVector ChunkPosition)
{
	AVoxelChunk* Chunk = static_cast<AVoxelChunk*>(GetWorld()->SpawnActor(AVoxelChunk::StaticClass()));
	Chunk->Initialize(ChunkPosition, &TerrainData);

	TerrainData.VoxelChunks.Add(ChunkPosition, Chunk);
}

void AVoxelTerrain::Tick(float DeltaTime)
{
	const FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() / 100;
	const FVector PlayerChunkPosition = FVector(PlayerPosition.X / 16, PlayerPosition.Y / 16, PlayerPosition.Z / 16);
	/*if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Player Position: %f, %f, %f"), PlayerPosition.X, PlayerPosition.Y, PlayerPosition.Z));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Current Player Chunk Position: %f, %f, %f"), PlayerChunkPosition.X, PlayerChunkPosition.Y, PlayerChunkPosition.Z));
	}*/

	for (int32 x = PlayerChunkPosition.X-TerrainData.RenderDistance; x < PlayerChunkPosition.X+TerrainData.RenderDistance; x++)
	{
		for (int32 y = PlayerChunkPosition.Y-TerrainData.RenderDistance; y < PlayerChunkPosition.Y+TerrainData.RenderDistance; y++)
		{
			for (int32 z = -2; z <= 1; z++)
			{
				if(!TerrainData.VoxelChunks.Contains(FIntVector(x,y,z)))
				{
					InitializeChunk(FIntVector(x,y,z));
				}
			}
		}
	}
	
	Super::Tick(DeltaTime);
}

