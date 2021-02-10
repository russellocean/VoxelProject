// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelGenerator.h"

void UVoxelGenerator::GenerateVoxel(FIntVector VoxelCoords, int32 VoxelIndex)
{
	VoxelCoords *= 100;

	//These are relative locations to the placed Actor in the world
	Vertices.Add(FVector(-50 + VoxelCoords.X, -50 + VoxelCoords.Y, -50 + VoxelCoords.Z)); //lower left - 0
	Vertices.Add(FVector(-50 + VoxelCoords.X, -50 + VoxelCoords.Y, 50 + VoxelCoords.Z)); //upper left - 1
	Vertices.Add(FVector(-50 + VoxelCoords.X, 50 + VoxelCoords.Y, -50 + VoxelCoords.Z)); //lower right - 2 
	Vertices.Add(FVector(-50 + VoxelCoords.X, 50 + VoxelCoords.Y, 50 + VoxelCoords.Z)); //upper right - 3

	Vertices.Add(FVector(50 + VoxelCoords.X, -50 + VoxelCoords.Y, -50 + VoxelCoords.Z)); //lower front left - 4
	Vertices.Add(FVector(50 + VoxelCoords.X, -50 + VoxelCoords.Y, 50 + VoxelCoords.Z)); //upper front left - 5

	Vertices.Add(FVector(50 + VoxelCoords.X, 50 + VoxelCoords.Y, 50 + VoxelCoords.Z)); //upper front right - 6
	Vertices.Add(FVector(50 + VoxelCoords.X, 50 + VoxelCoords.Y, -50 + VoxelCoords.Z)); //lower front right - 7

	//Back face of cube
	AddTriangle(0, 2, 3);
	AddTriangle(3, 1, 0);

	//Left face of cube
	AddTriangle(0, 1, 4);
	AddTriangle(4, 1, 5);

	//Front face of cube
	AddTriangle(4, 5, 7);
	AddTriangle(7, 5, 6);

	//Right face of cube
	AddTriangle(7, 6, 3);
	AddTriangle(3, 2, 7);

	//Top face
	AddTriangle(1, 3, 5);
	AddTriangle(6, 5, 3);

	//bottom face
	AddTriangle(2, 0, 4);
	AddTriangle(4, 7, 2);

	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));
	VertexColors.Add(FLinearColor(1.f, 1.f, 1.f));

	UE_LOG(LogTemp, Warning, TEXT("Current Index: %d"), VoxelIndex);

	CreateMeshSection_LinearColor(VoxelIndex, Vertices, Triangles, TArray<FVector>(), TArray<FVector2D>(), VertexColors,
	                              TArray<FProcMeshTangent>(), true);

	Vertices.Empty();
	Triangles.Empty();
	VertexColors.Empty();
}

void UVoxelGenerator::AddTriangle(const int32 V1, const int32 V2, const int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);
}
