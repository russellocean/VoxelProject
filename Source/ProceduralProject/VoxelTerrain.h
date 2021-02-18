// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "VoxelTerrain.generated.h"

UCLASS()
class PROCEDURALPROJECT_API AVoxelTerrain : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVoxelTerrain();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chunk)
	int32 RenderDistance{6};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
