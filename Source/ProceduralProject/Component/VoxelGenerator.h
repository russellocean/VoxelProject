// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "VoxelGenerator.generated.h"


UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class PROCEDURALPROJECT_API UVoxelGenerator final : public UProceduralMeshComponent
{
	GENERATED_BODY()
public:
	void GenerateVoxel(FIntVector VoxelCoords, int32 VoxelIndex);

	void AddTriangle(int32 V1, int32 V2, int32 V3);

protected:
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors;
	//TArray<FProcMeshTangent> tangents;
	bool CreateCollision;

	int32 SectionIndex = 0;
};
