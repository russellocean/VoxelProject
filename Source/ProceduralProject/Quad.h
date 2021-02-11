#pragma once

struct Quad
{ // X pos, Y pos, Width, Height
	Quad(int X, int Y, int W, int H) : X{X}, Y{Y}, W{W}, H{H}
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
