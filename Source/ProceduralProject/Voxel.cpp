#include "Voxel.h"

void UVoxel::SetVoxelPosition(const FIntVector Position)
{
	Voxel.VoxelPosition = Position;
}

FIntVector UVoxel::GetVoxelPosition() const
{
	return Voxel.VoxelPosition;
}

void UVoxel::SetNeighbor(UVoxel* NeighborVoxel, const int32 Direction)
{
	Neighbors[Direction] = NeighborVoxel;
}

UVoxel* UVoxel::GetNeighbor(const int32 Direction)
{
	return Neighbors[Direction];
}

bool UVoxel::IsVisible() const
{
	return Voxel.bIsVisible;
}

void UVoxel::SetVisibility(const bool Visibility)
{
	Voxel.bIsVisible = Visibility;
}

void UVoxel::GenerateQuads()
{
	/*for(int32 n = 0; n < 6 ; n++)
	{
		if(Neighbors[n] == nullptr)
		{
			switch(n)
			{
				case(0): {
					FQuad* Q1 = FQuad {1, 1, 1, 1};
					Quads[n] = Q1;
				}
				case(1): {
											
				}
				case(2): {
											
				}
				case(3): {
												
				}
				case(4): {
												
				}
				case(5): {
												
				}
				default: {
						return;
				}
			}	
		}
	}*/
}
