// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkillProjGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SKILLPROJ_API ASkillProjGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASkillProjGameModeBase();

	// BeginPlay
	virtual void BeginPlay() override;
	
};
