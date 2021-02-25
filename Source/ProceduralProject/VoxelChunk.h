#pragma once

#include "CoreMinimal.h"

#include "ChunkMesher.h"

#include "Voxel.h"

#include "GameFramework/Actor.h"
#include "VoxelChunk.generated.h"

struct FVoxelTerrainData;
USTRUCT(BlueprintType)
struct FChunkData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	FIntVector ChunkPosition;

	//Dont like storing this, must be a better way to detect first time generation, maybe check if already written to disk?
	bool IsNewChunk = true;

	static const int32 ChunkSize = 16;
	static const int32 ChunkSizeSquared = 256;
	static const int32 ChunkSizeCubed = 4096;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	TArray<UVoxel*> Voxels;

	FChunkData *NeighborChunks[6];
};

UCLASS(BlueprintType)
class PROCEDURALPROJECT_API AVoxelChunk final : public AActor
{
	GENERATED_BODY()	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	FChunkData Chunk;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UChunkMesher* ChunkMesh;

public:
	AVoxelChunk();

	//Must be called after voxel constructed
	void Initialize(const FIntVector ChunkCoords, FVoxelTerrainData* TerrainData);

	FIntVector GetChunkPosition() const;

	UVoxel* GetVoxelAt(FIntVector VoxelLocalPosition);

	FChunkData* GetChunkData();
	
	void SetChunkNeighbor(FChunkData* ChunkData, FIntVector Direction);
	FChunkData* GetChunkNeighbor(FIntVector Direction);

private:
	void CreateChunk();
	bool CheckVoxelNeighbors(int32 VoxelIndex);

	static const FIntVector NeighborOffsets[6];

	FVoxelTerrainData* WorldData;
};
