#pragma once

#include "CoreMinimal.h"

#include "ChunkMesher.h"

#include "Voxel.h"

#include "GameFramework/Actor.h"
#include "VoxelChunk.generated.h"

struct FVoxelTerrainSettings;
struct FVoxelTerrainData;
USTRUCT(BlueprintType)
struct FChunkData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	FIntVector ChunkPosition;

	//Dont like storing this, must be a better way to detect first time generation, maybe check if already written to disk?
	bool IsNewChunk = true;

	bool IsVisible = false;

	static const int32 ChunkSize = 16;
	static const int32 ChunkSizeSquared = 256;
	static const int32 ChunkSizeCubed = 4096;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	TArray<UVoxel*> Voxels;

	TMap<int32, FChunkData*> NeighborChunks;
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

	//Must be called after chunk constructed
	void Initialize(const FIntVector ChunkCoords, FVoxelTerrainSettings* TerrainSettings);

	FIntVector GetChunkPosition() const;

	UVoxel* GetVoxelAt(FIntVector VoxelLocalPosition);

	FChunkData* GetChunkData();
	
	void SetChunkNeighbor(FChunkData* ChunkData, int32 Direction);
	FChunkData* GetChunkNeighbor(int32 Direction);

	void RefreshChunk(bool bCheckNeighbors);

private:
	void CreateChunkData();
	bool CalculateVoxelNeighbors(int32 VoxelIndex);
	
	FVoxelTerrainSettings* WorldSettings;
};
