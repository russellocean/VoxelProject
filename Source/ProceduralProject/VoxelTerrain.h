#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FastNoise.h"

#include "VoxelTerrain.generated.h"

class AVoxelChunk;
USTRUCT(BlueprintType)
struct FVoxelTerrainData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunk)
	int32 RenderDistance{6};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterial* VoxelMaterial;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Seed = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Frequency = 0.002f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EInterp Interpolation;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TMap<FIntVector, AVoxelChunk*> VoxelChunks;
};

UCLASS()
class PROCEDURALPROJECT_API AVoxelTerrain final : public AActor
{
	GENERATED_BODY()

public:
	AVoxelTerrain();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunk)
	FVoxelTerrainData TerrainData;

	void InitializeChunk(FIntVector ChunkPosition);

public:
	virtual void Tick(float DeltaTime) override;
};
