// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProceduralProjectGameMode.h"
#include "ProceduralProjectHUD.h"
#include "ProceduralProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProceduralProjectGameMode::AProceduralProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AProceduralProjectHUD::StaticClass();
}
