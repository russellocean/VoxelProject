// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkMesher.h"

void UChunkMesher::ChunkToQuads(TArray<UVoxel*> Voxels)
{
	int32 SectionIndex = 0;
	for(int v = 0; v < Voxels.Num(); v++)
	{
		FVector VertexOffset = FVector(Voxels[v]->GetVoxelPosition()) * 100;
		Vertices.Add(FVector(-50, -50, -50) + VertexOffset); //lower left - 0
		Vertices.Add(FVector(-50, -50, 50) + VertexOffset); //upper left - 1
		Vertices.Add(FVector(-50, 50, -50) + VertexOffset); //lower right - 2 
		Vertices.Add(FVector(-50, 50, 50) + VertexOffset); //upper right - 3
	
		Vertices.Add(FVector(50, -50, -50) + VertexOffset); //lower front left - 4
		Vertices.Add(FVector(50, -50, 50) + VertexOffset); //upper front left - 5

		Vertices.Add(FVector(50, 50, 50) + VertexOffset); //upper front right - 6
		Vertices.Add(FVector(50, 50, -50) + VertexOffset); //lower front right - 7
		if(Voxels[v]->IsVisible())
		{
			for(int n = 0; n < 6; n++)
			{
				if(Voxels[v]->GetNeighbor(n) == nullptr)
				{
					switch(n)
					{
						case(0): {
							//Front face of cube
							AddTriangle(4, 5, 7);
							AddTriangle(7, 5, 6);
						} break;
						case(1): {
							//Back face of cube
							AddTriangle(0, 2, 3);
							AddTriangle(3, 1, 0);				
						} break;
						case(2): {
							//Right face of cube
							AddTriangle(7, 6, 3);
							AddTriangle(3, 2, 7);				
						} break;
						case(3): {
							//Left face of cube
							AddTriangle(0, 1, 4);
							AddTriangle(4, 1, 5);					
						} break;
						case(4): {
							//Top face
							AddTriangle(1, 3, 5);
							AddTriangle(6, 5, 3);					
						} break;
						case(5): {
							//bottom face
							AddTriangle(2, 0, 4);
							AddTriangle(4, 7, 2);
						} break;
					}
					SectionIndex++;
				}

				TArray<FLinearColor> VertexColors;
				VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
				VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
				VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
				VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
				VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
				VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
				VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
				VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));

				CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors, TArray<FProcMeshTangent>(),true);
			}
		}
		Vertices.Empty();
		Triangles.Empty();
	}
}

void UChunkMesher::AddTriangle(const int32 V1, const int32 V2, const int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);
}
