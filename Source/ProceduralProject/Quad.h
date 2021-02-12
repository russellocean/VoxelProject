#pragma once

struct FQuad
{ // X pos, Y pos, Width, Height
	FQuad(const int X, const int Y, const int W, const int H) : X{X}, Y{Y}, W{W}, H{H}
	{
		this->X = X;
		this->Y = Y;
		this->W = W;
		this->H = H;
	}
	int X;
	int Y;
	int W;
	int H;
};
