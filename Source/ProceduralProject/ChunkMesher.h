// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Voxel.h"

#include "ChunkMesher.generated.h"

UCLASS()
class PROCEDURALPROJECT_API UChunkMesher : public UProceduralMeshComponent
{
	GENERATED_BODY()

	public:
	void ChunkToQuads(TArray<UVoxel*> Voxels);

	private:
	/* The vertices of the mesh */
	TArray<FVector> Vertices;
 
	/* The triangles of the mesh */
	TArray<int32> Triangles;

	/* Creates a triangle that connects the given vertices */
	void AddTriangle(int32 V1, int32 V2, int32 V3);
};
