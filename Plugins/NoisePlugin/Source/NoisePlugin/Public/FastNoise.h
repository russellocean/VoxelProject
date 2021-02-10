// Copyright 2018 Yaki Studios, Inc. All Rights Reserved.

// FastNoise.h
//
// MIT License
//
// Copyright(c) 2017 Jordan Peck
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FastNoise.generated.h"

class UCurveFloat;

UENUM(BlueprintType)
enum class EInterp : uint8
{
	Linear UMETA(DisplayName = "Linear"),
	Hermite UMETA(DisplayName = "Hermite"),
	Quintic UMETA(DisplayName = "Quintic")
};

UENUM(BlueprintType)
enum class EFractalType : uint8
{
	FBM,
	Billow,
	RidgedMulti
};

UENUM(BlueprintType)
enum class ESelectInterpType : uint8
{
	None,
	CircularIn,
	CircularOut,
	CircularInOut,
	ExponentialIn,
	ExponentialOut,
	ExponentialInOut,
	SineIn,
	SineOut,
	SineInOut,
	Step,
	Linear
};

UCLASS()
class NOISEPLUGIN_API UNoiseBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//2D
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetValue2D(int32 Seed, float Frequency, EInterp Interpolation, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetValueFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves,
	                               EInterp Interpolation, EFractalType FractalType, const FVector2D& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetPerlin2D(int32 Seed, float Frequency, EInterp Interpolation, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetPerlinFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves,
	                                EInterp Interpolation, EFractalType FractalType, const FVector2D& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetSimplex2D(int32 Seed, float Frequency, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetSimplexFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves,
	                                 EFractalType FractalType, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetSimplexFractalBlend(int32 Seed, float Lacunarity, float Gain, int32 Octaves,
	                                    const FVector2D& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetWhiteNoise2D(int32 Seed, const FVector2D& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetCubic2D(int32 Seed, float Frequency, const FVector2D& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetCubicFractal2D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves,
	                               EFractalType FractalType, const FVector2D& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static void GradientPerturb2D(int32 Seed, float Perturb, float Frequency, EInterp Interpolation,
	                              const FVector2D& Coordinates, FVector2D& OutCoordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static void GradientPerturbFractal2D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain,
	                                     int32 Octaves, EInterp Interpolation, const FVector2D& Coordinates,
	                                     FVector2D& OutCoordinates);

	//3D
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetValue3D(int32 Seed, float Frequency, EInterp Interpolation, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetValueFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves,
	                               EInterp Interpolation, EFractalType FractalType, const FVector& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetPerlin3D(int32 Seed, float Frequency, EInterp Interpolation, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetPerlinFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves,
	                                EInterp Interpolation, EFractalType FractalType, const FVector& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetSimplex3D(int32 Seed, float Frequency, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetSimplexFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves,
	                                 EFractalType FractalType, const FVector& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetWhiteNoise3D(int32 Seed, const FVector& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetCubic3D(int32 Seed, float Frequency, const FVector& Coordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetCubicFractal3D(int32 Seed, float Frequency, float Lacunarity, float Gain, int32 Octaves,
	                               EFractalType FractalType, const FVector& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static void GradientPerturb3D(int32 Seed, float Perturb, float Frequency, EInterp Interpolation,
	                              const FVector& Coordinates, FVector& OutCoordinates);
	UFUNCTION(BlueprintPure, Category = "Noise")
	static void GradientPerturbFractal3D(int32 Seed, float Perturb, float Frequency, float Lacunarity, float Gain,
	                                     int32 Octaves, EInterp Interpolation, const FVector& Coordinates,
	                                     FVector& OutCoordinates);

	//4D
	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetSimplex4D(int32 Seed, float Frequency, const FVector4& Coordinates);

	UFUNCTION(BlueprintPure, Category = "Noise")
	static float GetWhiteNoise4D(int32 Seed, FVector4 Cooordinates);


	UFUNCTION(BlueprintPure, Category = "Noise|Utilities")
	static float SelectNoise(float NoiseValue1, float NoiseValue2, float ControlNoise, ESelectInterpType Interpolation,
	                         float Falloff, float Threshold, int32 Steps = 4);

	UFUNCTION(BlueprintPure, Category = "Noise|Utilities")
	static float BlendNoise(float NoiseValue1, float NoiseValue2, float ControlNoise, UCurveFloat* BlendCurve);

	UFUNCTION(BlueprintPure, Category = "Noise|Utilities")
	static float ScaleBiasNoise(float NoiseValue, float Scale, float Bias);

	UFUNCTION(BlueprintPure, Category = "Noise|Utilities")
	static float AddNoise(float NoiseValue1, float NoiseValue2, float MaskNoise, float Threshold);

	UFUNCTION(BlueprintPure, Category = "Noise|Utilities")
	static float Select3Noise(float NoiseValue1, float NoiseValue2, float NoiseValue3, float ControlNoise,
	                          ESelectInterpType Interpolation, float Falloff, float LowerThreshold,
	                          float UpperThreshold, int32 Steps = 4);

	UFUNCTION(BlueprintPure, Category = "Noise|Utilities")
	static float RadialNoise(float NoiseValue1, float NoiseValue2, ESelectInterpType Interpolation, FVector Origin,
	                         float Radius, float Falloff, int32 Steps, const FVector& Coordinates);

private:

	//2D
	static float GetValue(const int32& Seed, const float& Frequency, const EInterp& Interpolation,
	                      const FVector2D& Coordinates);
	static float GetValueFractal(const int32& Seed, const float& Frequency, const float& Lacunarity, const float& Gain,
	                             const int32& Octaves, const EInterp& Interpolation, const EFractalType& FractalType,
	                             const FVector2D& Coordinates);

	static float GetPerlin(const int32& Seed, const float& Frequency, const EInterp& Interpolation,
	                       const FVector2D& Coordinates);
	static float GetPerlinFractal(const int32& Seed, const float& Frequency, const float& Lacunarity, const float& Gain,
	                              const int32& Octaves, const EInterp& Interpolation, const EFractalType& FractalType,
	                              const FVector2D& Coordinates);

	static float GetSimplex(const int32& Seed, const float& Frequency, const FVector2D& Coordinates);
	static float GetSimplexFractal(const int32& Seed, const float& Frequency, const float& Lacunarity,
	                               const float& Gain, const int32& Octaves, const EFractalType& FractalType,
	                               const FVector2D& Coordinates);
	static float SingleSimplexFractalBlend(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                       FVector2D Coordinates);

	static float GetWhiteNoise(const int32& Seed, float x, float y);

	static float GetCubic(const int32& Seed, const float& Frequency, const FVector2D& Coordinates);
	static float GetCubicFractal(const int32& Seed, const float& Frequency, const float& Lacunarity, const float& Gain,
	                             const int32& Octaves, const EFractalType& FractalType, const FVector2D& Coordinates);

	static void GradientPerturb(const int32& Seed, const float& Perturb, const float& Frequency,
	                            const EInterp& Interpolation, FVector2D& Coordinates);
	static void GradientPerturbFractal(int32 Seed, const float& Perturb, const float& Frequency,
	                                   const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                   const EInterp& Interpolation, FVector2D& Coordinates);

	//3D
	static float GetValue(const int32& Seed, const float& Frequency, const EInterp& Interpolation,
	                      const FVector& Coordinates);
	static float GetValueFractal(const int32& Seed, const float& Frequency, const float& Lacunarity, const float& Gain,
	                             const int32& Octaves, const EInterp& Interpolation, const EFractalType& FractalType,
	                             const FVector& Coordinates);

	static float GetPerlin(const int32& Seed, const float& Frequency, const EInterp& Interpolation,
	                       const FVector& Coordinates);
	static float GetPerlinFractal(const int32& Seed, const float& Frequency, const float& Lacunarity, const float& Gain,
	                              const int32& Octaves, const EInterp& Interpolation, const EFractalType& FractalType,
	                              const FVector& Coordinates);

	static float GetSimplex(const int32& Seed, const float& Frequency, const FVector& Coordinates);
	static float GetSimplexFractal(const int32& Seed, const float& Frequency, const float& Lacunarity,
	                               const float& Gain, const int32& Octaves, const EFractalType& FractalType,
	                               const FVector& Coordinates);

	static float GetWhiteNoise(const int32& Seed, float x, float y, float z);

	static float GetCubic(const int32& Seed, const float& Frequency, const FVector& Coordinates);
	static float GetCubicFractal(const int32& Seed, const float& Frequency, const float& Lacunarity, const float& Gain,
	                             const int32& Octaves, const EFractalType& FractalType, const FVector& Coordinates);

	static void GradientPerturb(const int32& Seed, const float& Perturb, const float& Frequency,
	                            const EInterp& Interpolation, FVector& Coordinates);
	static void GradientPerturbFractal(int32 Seed, const float& Perturb, const float& Frequency,
	                                   const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                   const EInterp& Interpolation, FVector& Coordinates);

	//4D
	static float GetSimplex(const int32& Seed, const float& Frequency, const FVector4& Coordinates);

	static float GetWhiteNoise(const int32& Seed, float x, float y, float z, float w);

private:
	//2D
	static float SingleValueFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                   const EInterp& Interpolation, FVector2D Coordinates);
	static float SingleValueFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                      const EInterp& Interpolation, FVector2D Coordinates);
	static float SingleValueFractalRidgedMulti(int32 Seed, const float& Lacunarity, const float& Gain,
	                                           const int32& Octaves, const EInterp& Interpolation,
	                                           FVector2D Coordinates);
	static float SingleValue(const int32& Seed, const EInterp& Interpolation, const FVector2D& Coordinates);

	static float SinglePerlinFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                    const EInterp& Interpolation, FVector2D Coordinates);
	static float SinglePerlinFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                       const EInterp& Interpolation, FVector2D Coordinates);
	static float SinglePerlinFractalRidgedMulti(int32 Seed, const float& Lacunarity, const float& Gain,
	                                            const int32& Octaves, const EInterp& Interpolation,
	                                            FVector2D Coordinates);
	static float SinglePerlin(const int32& Seed, const EInterp& Interpolation, const FVector2D& Coordinates);

	static float SingleSimplexFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                     FVector2D Coordinates);
	static float SingleSimplexFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
	                                        const int32& Octaves, FVector2D Coordinates);
	static float SingleSimplexFractalRidgedMulti(int32 Seed, const float& Lacunarity, const float& Gain,
	                                             const int32& Octaves, FVector2D Coordinates);
	static float SingleSimplex(const int32& Seed, const FVector2D& Coordinates);

	static float SingleCubicFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                   FVector2D Coordinates);
	static float SingleCubicFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                      FVector2D Coordinates);
	static float SingleCubicFractalRidgedMulti(int32 Seed, const float& Lacunarity, const float& Gain,
	                                           const int32& Octaves, FVector2D Coordinates);
	static float SingleCubic(const int32& Seed, const FVector2D& Coordinates);

	static void SingleGradientPerturb(const int32& Seed, const float& Perturb, const float& Frequency,
	                                  const EInterp& Interpolation, FVector2D& Coordinates);

	//3D
	static float SingleValueFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                   const EInterp& Interpolation, FVector Coordinates);
	static float SingleValueFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                      const EInterp& Interpolation, FVector Coordinates);
	static float SingleValueFractalRidgedMulti(int32 Seed, const float& Lacunarity, const float& Gain,
	                                           const int32& Octaves, const EInterp& Interpolation, FVector Coordinates);
	static float SingleValue(const int32& Seed, const EInterp& Interpolation, const FVector& Coordinates);

	static float SinglePerlinFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                    const EInterp& Interpolation, FVector Coordinates);
	static float SinglePerlinFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                       const EInterp& Interpolation, FVector Coordinates);
	static float SinglePerlinFractalRidgedMulti(int32 Seed, const float& Lacunarity, const float& Gain,
	                                            const int32& Octaves, const EInterp& Interpolation,
	                                            FVector Coordinates);
	static float SinglePerlin(const int32& Seed, const EInterp& Interpolation, const FVector& Coordinates);

	static float SingleSimplexFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                     FVector Coordinates);
	static float SingleSimplexFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain,
	                                        const int32& Octaves, FVector Coordinates);
	static float SingleSimplexFractalRidgedMulti(int32 Seed, const float& Lacunarity, const float& Gain,
	                                             const int32& Octaves, FVector Coordinates);
	static float SingleSimplex(const int32& Seed, const FVector& Coordinates);

	static float SingleCubicFractalFBM(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                   FVector Coordinates);
	static float SingleCubicFractalBillow(int32 Seed, const float& Lacunarity, const float& Gain, const int32& Octaves,
	                                      FVector Coordinates);
	static float SingleCubicFractalRidgedMulti(int32 Seed, const float& Lacunarity, const float& Gain,
	                                           const int32& Octaves, FVector Coordinates);
	static float SingleCubic(const int32& Seed, const FVector& Coordinates);

	static void SingleGradientPerturb(const int32& Seed, const float& Perturb, const float& Frequency,
	                                  const EInterp& Interpolation, FVector& Coordinates);

	//4D
	static float SingleSimplex(const int32& Seed, const FVector4& Coordinates);

	static inline int32 Hash2D(int32 Seed, const int32& x, const int32& y);
	static inline int32 Hash3D(int32 Seed, const int32& x, const int32& y, const int32& z);
	static inline int32 Hash4D(int32 Seed, const int32& x, const int32& y, const int32& z, const int32& w);

	static inline float ValCoord2D(int32 Seed, const int32& x, const int32& y);
	static inline float ValCoord3D(int32 Seed, const int32& x, const int32& y, const int32& z);
	static inline float ValCoord4D(int32 Seed, const int32& x, const int32& y, const int32& z, const int32& w);

	static inline float GradCoord2D(int32 Seed, const int32& x, const int32& y, const float& xd, const float& yd);
	static inline float GradCoord3D(int32 Seed, const int32& x, const int32& y, const int32& z, const float& xd,
	                                const float& yd, const float& zd);
	static inline float GradCoord4D(int32 Seed, const int32& x, const int32& y, const int32& z, const int32& w,
	                                const float& xd, const float& yd, const float& zd, const float& wd);
};
