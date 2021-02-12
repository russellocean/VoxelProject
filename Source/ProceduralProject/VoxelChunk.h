#pragma once

#include "CoreMinimal.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	int32 ChunkID;

	const int32 ChunkSize = 16;
	const int32 ChunkSizeSquared = 256;
	const int32 ChunkSizeCubed = 4096;

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

public:
	AVoxelChunk();
	virtual void Tick(float DeltaTime) override;
	
	void CreateChunk(FIntVector ChunkPosition);
	FIntVector GetChunkPosition() const;
	
	void AddVoxel(UVoxel Voxel);
	
private:
	bool CheckVoxelNeighbors(int32 VoxelIndex);
	static bool CompareQuad(FQuad &Q1, FQuad &Q2);

	static const FIntVector NeighborOffsets[6];
};
