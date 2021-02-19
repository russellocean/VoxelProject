#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
