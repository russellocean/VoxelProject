// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelTerrain.h"

#include "VoxelChunk.h"


// Sets default values
AVoxelTerrain::AVoxelTerrain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVoxelTerrain::BeginPlay()
{
	Super::BeginPlay();

	for(int32 x = 0; x < RenderDistance; x++)
	{
		for(int32 y = 0; y < RenderDistance; y++)
		{
			AVoxelChunk* Chunk = static_cast<AVoxelChunk*>(GetWorld()->SpawnActor(AVoxelChunk::StaticClass()));
			Chunk->Initialize(FIntVector(x,y,0));
		}
	}
}

// Called every frame
void AVoxelTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

