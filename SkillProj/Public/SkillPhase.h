// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillPhase.generated.h"

/**
 * 
 */
UCLASS()
class SKILLPROJ_API USkillPhase : public UObject
{
	GENERATED_BODY()

public:

	// PhaseName
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillPhase")
		FString PhaseName;

	// PhaseDuration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillPhase")
		float PhaseDuration;

	// Nodes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillPhase")
		TArray<class USkillNode*> Nodes;
	
};
