#include "ChunkMesher.h"

void UChunkMesher::ChunkToQuads(TArray<UVoxel*> Voxels)
{
	for (int v = 0; v < Voxels.Num(); v++)
	{
		if (Voxels[v]->IsVisible())
		{
			const FVector QuadOffset = FVector(Voxels[v]->GetWorldPosition()) * 100;
			/*Vertices.Add(FVector(-50, -50, -50) + VertexOffset); //lower left - 0
			Vertices.Add(FVector(-50, -50, 50) + VertexOffset); //upper left - 1
			Vertices.Add(FVector(-50, 50, -50) + VertexOffset); //lower right - 2 
			Vertices.Add(FVector(-50, 50, 50) + VertexOffset); //upper right - 3

			Vertices.Add(FVector(50, -50, -50) + VertexOffset); //lower front left - 4
			Vertices.Add(FVector(50, -50, 50) + VertexOffset); //upper front left - 5

			Vertices.Add(FVector(50, 50, 50) + VertexOffset); //upper front right - 6
			Vertices.Add(FVector(50, 50, -50) + VertexOffset); //lower front right - 7*/
			TArray<FQuad*> Quads;

			for (int n = 0; n < 6; n++)
			{
				if (Voxels[v]->GetNeighbor(n) == Air)
				{
					switch (n)
					{
					case(0):
						{
							FQuad Quad(QuadOffset.X+100, QuadOffset.Y, QuadOffset.Z, 1, 1, 0);
							DrawQuad(&Quad, 0);
							//Front face of cube
						}
						break;
					case(1):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y, QuadOffset.Z, 1, 1, 0);
							DrawQuad(&Quad, 1);
							//Back face of cube
						}
						break;
					case(2):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y+100, QuadOffset.Z, 0, 1, 1);
							DrawQuad(&Quad, 2);
							//Right face of cube
						}
						break;
					case(3):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y, QuadOffset.Z, 0, 1, 1);
							DrawQuad(&Quad, 3);
							//Left face of cube
						}
						break;
					case(4):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y, QuadOffset.Z+100, 1, 0, 1);
							DrawQuad(&Quad, 4);
							//Top face
						}
						break;
					case(5):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y, QuadOffset.Z, 1, 0, 1);
							DrawQuad(&Quad, 5);
							//bottom face
						}
						break;
					}
				}
			}

			SectionIndex++;

			SetMaterial(SectionIndex, VoxelMaterial);
			
			Quads.Empty();
		}
	}
}

void UChunkMesher::DrawQuad(FQuad* Quad, int Direction)
{;
	const FIntVector QOrigin = FIntVector(Quad->X, Quad->Y, Quad->Z);
	switch (Direction)
	{
	case(0):
		{
			//Front
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z + (Quad->H * 100)));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z));
		} break;
	case(1):
		{
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z + (Quad->H * 100)));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z));
		} break;
	case(2):
		{

			//2 1 0
			//3 2 0
			//Right
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z));//0
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));//1
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z + (Quad->H * 100)));//2
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z));//3
		} break;
	case(3):
		{
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z + (Quad->H * 100)));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z));
		} break;
	case(4):
		{
			//Top
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y + (Quad->W * 100), QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z));
		} break;
	case(5):
		{
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z + (Quad->H * 100)));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z));
		} break;
	}

	
	AddTriangle(2,1,0);
	AddTriangle(3,2,0);

	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(1, 0));
	UVs.Add(FVector2D(1, 1));
	UVs.Add(FVector2D(0, 1));

	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));

	CreateMeshSection_LinearColor(SectionIndex, Vertices, Triangles, TArray<FVector>(), UVs, VertexColors,
                          TArray<FProcMeshTangent>(), true);

	SectionIndex++;

	Vertices.Empty();
	Triangles.Empty();
	UVs.Empty();
	VertexColors.Empty();
}

void UChunkMesher::AddTriangle(const int32 V1, const int32 V2, const int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);
}
