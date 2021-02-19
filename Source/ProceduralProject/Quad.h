#pragma once

struct FQuad
{
	// X pos, Y pos, Width, Height
	FQuad(const int X, const int Y, const int Z, const int W, const int H, const int D) : X{X}, Y{Y}, Z{Z}, W{W}, H{H}, D{D}
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
		this->W = W;
		this->H = H;
		this->D = D;
	}

	int X;
	int Y;
	int Z;
	int W;
	int H;
	int D;
};
