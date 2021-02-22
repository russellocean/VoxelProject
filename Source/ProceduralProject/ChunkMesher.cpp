#include "ChunkMesher.h"

void UChunkMesher::ChunkToQuads(TArray<UVoxel*> Voxels)
{
	for (int v = 0; v < Voxels.Num(); v++)
	{
		if (Voxels[v]->IsVisible())
		{
			const FVector QuadOffset = FVector(Voxels[v]->GetWorldPosition()) * 100;

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
		}
	}

	CreateMeshSection_LinearColor(0, Vertices, Triangles, TArray<FVector>(), UVs, VertexColors,
                      TArray<FProcMeshTangent>(), true);

	SetMaterial(0, VoxelMaterial);

	Vertices.Empty();
	Triangles.Empty();
	UVs.Empty();
	VertexColors.Empty();
}

void UChunkMesher::DrawQuad(FQuad* Quad, const int Direction)
{;
	const FIntVector QOrigin = FIntVector(Quad->X, Quad->Y, Quad->Z);

	Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z));
	
	switch (Direction)
	{
	case(0):
		{
			//Front
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z)); //Right
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z + (Quad->H * 100))); //Up Right
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100))); // Up
		} break;
	case(1):
		{
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z)); //Right
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z + (Quad->H * 100))); //Up Right
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100))); // Up
		} break;
	case(2):
		{
			//Right
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));//Up
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z + (Quad->H * 100))); //Up Forward
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z)); // Forward
		} break;
	case(3):
		{
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));//1
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z + (Quad->H * 100)));//2
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z));//3
		} break;
	case(4):
		{
			//Top
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z)); // Forward
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y + (Quad->W * 100), QOrigin.Z)); // Forward Up
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z)); // Up
		} break;
	case(5):
		{
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y + (Quad->W * 100), QOrigin.Z));
			Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z));
		} break;
	default:
		{
			return;
		};
	}

	if(Direction % 2 == 0)
	{
		AddTriangle(2,1,0);
		AddTriangle(3,2,0);
	} else
	{
		AddTriangle(0,1,2);
		AddTriangle(0,2,3);
	}

	//SectionIndex++;
	TriOffset += 4;
	
	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(1, 0));
	UVs.Add(FVector2D(1, 1));
	UVs.Add(FVector2D(0, 1));
	/*VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));*/
	

	VertexColors.Add(FLinearColor::MakeRandomColor());
	VertexColors.Add(FLinearColor::MakeRandomColor());
	VertexColors.Add(FLinearColor::MakeRandomColor());
	VertexColors.Add(FLinearColor::MakeRandomColor());
}

void UChunkMesher::AddTriangle(const int32 V1, const int32 V2, const int32 V3)
{
	Triangles.Add(V1 + TriOffset);
	Triangles.Add(V2 + TriOffset);
	Triangles.Add(V3 + TriOffset);
}