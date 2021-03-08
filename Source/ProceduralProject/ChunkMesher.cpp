#include "ChunkMesher.h"

#include "VoxelTerrainUtil.h"

void UChunkMesher::ChunkToQuads(TArray<UVoxel*> Voxels, const FIntVector ChunkCoords)
{
	for (int v = 0; v < Voxels.Num(); v++)
	{
		if (Voxels[v]->IsVisible())
		{
			if(!VoxelTypes.Contains(Voxels[v]->GetType()))
			{
				VoxelTypes.Add(Voxels[v]->GetType());
			}

			const FVector VoxelWorldPosition = FVector(VoxelTerrainUtil::VoxelIndexToWorldCoords(v, ChunkCoords));
			const FVector QuadOffset = VoxelWorldPosition * 100;

			for (int n = 0; n < 6; n++)
			{
				if (Voxels[v]->GetNeighbor(n) == Air)
				{
					switch (n)
					{
					case(0):
						{
							FQuad Quad(QuadOffset.X+100, QuadOffset.Y, QuadOffset.Z, 1, 1, 0);
							DrawQuad(&Quad, 0, Voxels[v]->GetType());
							//Front face of cube
						}
						break;
					case(1):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y, QuadOffset.Z, 1, 1, 0);
							DrawQuad(&Quad, 1, Voxels[v]->GetType());
							//Back face of cube
						}
						break;
					case(2):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y+100, QuadOffset.Z, 0, 1, 1);
							DrawQuad(&Quad, 2, Voxels[v]->GetType());
							//Right face of cube
						}
						break;
					case(3):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y, QuadOffset.Z, 0, 1, 1);
							DrawQuad(&Quad, 3, Voxels[v]->GetType());
							//Left face of cube
						}
						break;
					case(4):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y, QuadOffset.Z+100, 1, 0, 1);
							DrawQuad(&Quad, 4, Voxels[v]->GetType());
							//Top face
						}
						break;
					case(5):
						{
							FQuad Quad(QuadOffset.X, QuadOffset.Y, QuadOffset.Z, 1, 0, 1);
							DrawQuad(&Quad, 5, Voxels[v]->GetType());
							//bottom face
						}
						break;
					}
				}
			}
		}
	}

	int32 SectionIndex = 0;
	for(auto& Elem : VoxelTypes)
	{
		//FUniqueVoxelTypes* UniqueVoxelSection = Elem.Value;
		CreateMeshSection_LinearColor(SectionIndex, Elem.Value.Vertices, Elem.Value.Triangles, TArray<FVector>(), Elem.Value.UVs, Elem.Value.VertexColors,
                              TArray<FProcMeshTangent>(), true);

		if(Elem.Key == Grass)
		{
			SetMaterial(SectionIndex, VoxelMaterial);
		}
		else
		{
			SetMaterial(SectionIndex, DirtMaterial);
		}
		SectionIndex++;
	}

	VoxelTypes.Empty();
}

void UChunkMesher::DrawQuad(FQuad* Quad, const int Direction, const EType VoxelType)
{;
	const FIntVector QOrigin = FIntVector(Quad->X, Quad->Y, Quad->Z);
	
	FUniqueVoxelTypes* VoxelSection = VoxelTypes.Find(VoxelType);
	
	VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z));
	
	switch (Direction)
	{
	case(0):
		{
			//Front
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z)); //Right
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z + (Quad->H * 100))); //Up Right
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100))); // Up
		} break;
	case(1):
		{
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z)); //Right
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z + (Quad->H * 100))); //Up Right
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100))); // Up
		} break;
	case(2):
		{
			//Right
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));//Up
			VoxelSection->Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z + (Quad->H * 100))); //Up Forward
			VoxelSection->Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z)); // Forward
		} break;
	case(3):
		{
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y, QOrigin.Z + (Quad->H * 100)));//1
			VoxelSection->Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z + (Quad->H * 100)));//2
			VoxelSection->Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z));//3
		} break;
	case(4):
		{
			//Top
			VoxelSection->Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z)); // Forward
			VoxelSection->Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y + (Quad->W * 100), QOrigin.Z)); // Forward Up
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z)); // Up
		} break;
	case(5):
		{
			VoxelSection->Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y, QOrigin.Z));
			VoxelSection->Vertices.Add(FVector(QOrigin.X + (Quad->D * 100), QOrigin.Y + (Quad->W * 100), QOrigin.Z));
			VoxelSection->Vertices.Add(FVector(QOrigin.X, QOrigin.Y + (Quad->W * 100), QOrigin.Z));
		} break;
	default:
		{
			return;
		};
	}

	TriOffset = VoxelSection->TriOffset;
	
	if(Direction % 2 == 0)
	{
		AddTriangle(2,1,0, &VoxelSection->Triangles);
		AddTriangle(3,2,0, &VoxelSection->Triangles);
	} else
	{
		AddTriangle(0,1,2, &VoxelSection->Triangles);
		AddTriangle(0,2,3, &VoxelSection->Triangles);
	}

	VoxelSection->TriOffset += 4;

	
	VoxelSection->UVs.Add(FVector2D(0, 0));
	VoxelSection->UVs.Add(FVector2D(1, 0));
	VoxelSection->UVs.Add(FVector2D(1, 1));
	VoxelSection->UVs.Add(FVector2D(0, 1));

	VoxelSection->VertexColors.Add(FLinearColor::MakeRandomColor());
	VoxelSection->VertexColors.Add(FLinearColor::MakeRandomColor());
	VoxelSection->VertexColors.Add(FLinearColor::MakeRandomColor());
	VoxelSection->VertexColors.Add(FLinearColor::MakeRandomColor());

}

int32 UChunkMesher::VertexAO(const bool Side1, const bool Side2, const bool Corner)
{
	if(Side1 && Side2) {
		return 0;
      }
	return 3 - (Side1 + Side2 + Corner);
}

void UChunkMesher::AddTriangle(const int32 V1, const int32 V2, const int32 V3, TArray<int32>* Triangles) const
{
	Triangles->Add(V1 + TriOffset);
	Triangles->Add(V2 + TriOffset);
	Triangles->Add(V3 + TriOffset);
}
