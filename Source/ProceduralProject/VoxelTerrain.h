#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FastNoise.h"

#include "VoxelTerrain.generated.h"

class AVoxelChunk;

USTRUCT(BlueprintType)
struct FVoxelTerrainSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunk)
	int32 RenderDistance{2};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterial* VoxelMaterial;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterial* Dirt;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Seed = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Frequency = 0.002f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EInterp Interpolation;
};

UCLASS()
class PROCEDURALPROJECT_API AVoxelTerrain final : public AActor
{
	GENERATED_BODY()

public:
	AVoxelTerrain();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunk)
	//static FVoxelTerrainData VoxelTerrainData;
	static TMap<FIntVector, AVoxelChunk*> VoxelChunks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunk)
	FVoxelTerrainSettings VoxelTerrainSettings;

protected:
	virtual void BeginPlay() override;
	
	void InitializeChunk(FIntVector ChunkPosition);

	void CheckChunks(FVector PlayerChunkPosition) const;

public:
	virtual void Tick(float DeltaTime) override;
};
