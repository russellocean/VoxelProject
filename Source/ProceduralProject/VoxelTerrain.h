#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FastNoise.h"

#include "VoxelTerrain.generated.h"

UCLASS()
class PROCEDURALPROJECT_API AVoxelTerrain : public AActor
{
	GENERATED_BODY()

public:
	AVoxelTerrain();

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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
