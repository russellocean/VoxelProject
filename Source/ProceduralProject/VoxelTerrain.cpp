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

	for (int32 x = 0; x < RenderDistance; x++)
	{
		for (int32 y = 0; y < RenderDistance; y++)
		{
			AVoxelChunk* Chunk = static_cast<AVoxelChunk*>(GetWorld()->SpawnActor(AVoxelChunk::StaticClass()));
			Chunk->Initialize(FIntVector(x, y, 0), this);
		}
	}
}

void AVoxelTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}