#pragma once

#include "CoreMinimal.h"

#include <d3d12.h>

#include "ProceduralMeshComponent.h"
#include "Voxel.h"
#include "Quad.h"

#include "ChunkMesher.generated.h"

USTRUCT(BlueprintType)
struct FUniqueVoxelTypes
{
	GENERATED_BODY()

	/* The vertices of the mesh */
	TArray<FVector> Vertices;

	/* The triangles of the mesh */
	TArray<int32> Triangles;

	TArray<FLinearColor> VertexColors;
	TArray<FVector2D> UVs;

	int32 TriOffset {0};
};


UCLASS()
class PROCEDURALPROJECT_API UChunkMesher : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:
	void ChunkToQuads(TArray<UVoxel*> Voxels, const FIntVector ChunkCoords);

	 UPROPERTY(EditAnywhere,BlueprintReadWrite)
	 UMaterial* VoxelMaterial;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UMaterial* DirtMaterial;

private:
	TMap<EType, FUniqueVoxelTypes> VoxelTypes;

	int32 TriOffset {0};

	void DrawQuad(FQuad* Quad, int Direction, EType VoxelType);

	static int32 VertexAO(bool Side1, bool Side2, bool Corner);

	/* Creates a triangle that connects the given vertices */
	void AddTriangle(int32 V1, int32 V2, int32 V3, TArray<int32>* Triangles) const;
};
