#pragma once

#include "CoreMinimal.h"

#include "ChunkMesher.h"
#include "Quad.h"

#include "Voxel.h"
#include "GameFramework/Actor.h"
#include "VoxelChunk.generated.h"

USTRUCT(BlueprintType)
struct FChunkData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	FIntVector ChunkPosition;

	bool IsNewChunk = true;

	int32 ChunkSize = 16;
	int32 ChunkSizeSquared = 256;
	int32 ChunkSizeCubed = 4096;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	TArray<UVoxel*> Voxels;
};

UCLASS(BlueprintType)
class PROCEDURALPROJECT_API AVoxelChunk final : public AActor
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	FChunkData Chunk;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UChunkMesher* ChunkMesh;

public:
	AVoxelChunk();

	void Initialize(FIntVector ChunkCoords);
	
	void CreateChunk(const FIntVector ChunkPosition);
	FIntVector GetChunkPosition() const;
	
	void AddVoxel(UVoxel Voxel);
	
private:
	bool CheckVoxelNeighbors(int32 VoxelIndex);

	static const FIntVector NeighborOffsets[6];
};
