#pragma once

#include "CoreMinimal.h"

#include "ChunkMesher.h"

#include "Voxel.h"
#include "VoxelTerrain.h"
#include "GameFramework/Actor.h"
#include "VoxelChunk.generated.h"

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
};

UCLASS(BlueprintType)
class PROCEDURALPROJECT_API AVoxelChunk final : public AActor
{
	GENERATED_BODY()	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	FChunkData Chunk;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UChunkMesher* ChunkMesh;

public:
	AVoxelChunk();

	//Must be called after voxel constructed
	void Initialize(FIntVector ChunkCoords, AVoxelTerrain* VoxelWorld);

	FIntVector GetChunkPosition() const;

	UVoxel* GetVoxelAt(FIntVector VoxelLocalPosition);

private:
	void CreateChunk(const FIntVector ChunkPosition);
	bool CheckVoxelNeighbors(int32 VoxelIndex);

	static const FIntVector NeighborOffsets[6];

	UPROPERTY()
	AVoxelTerrain* VoxelTerrain;
};
