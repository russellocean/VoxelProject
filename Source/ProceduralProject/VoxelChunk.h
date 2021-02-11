// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Chunk)
	int32 ChunkSize = 16;

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
	void AddVoxel(FIntVector VoxelPosition);
	void RemoveVoxel(FIntVector Position) const;
	
private:
	bool CheckVoxelNeighbors(int32 VoxelIndex);
	bool CompareQuad(const Quad &Q1, const Quad &Q2);

	static const FIntVector NeighborOffsets[6];
};
