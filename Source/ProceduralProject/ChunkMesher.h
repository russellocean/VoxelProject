#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Voxel.h"
#include "Quad.h"

#include "ChunkMesher.generated.h"

UCLASS()
class PROCEDURALPROJECT_API UChunkMesher : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:
	void ChunkToQuads(TArray<UVoxel*> Voxels);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterial* VoxelMaterial;

private:
	/* The vertices of the mesh */
	TArray<FVector> Vertices;

	/* The triangles of the mesh */
	TArray<int32> Triangles;

	TArray<FLinearColor> VertexColors;
	TArray<FVector2D> UVs;

	//int32 SectionIndex = 1;
	int32 TriOffset {0};

	void DrawQuad(FQuad* Quad, int Direction);

	/* Creates a triangle that connects the given vertices */
	void AddTriangle(int32 V1, int32 V2, int32 V3);
};
