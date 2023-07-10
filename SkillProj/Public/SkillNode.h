// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillNode.generated.h"

/**
 * 
 */
UCLASS()
class SKILLPROJ_API USkillNode : public UObject
{
	GENERATED_BODY()

public:
	// Constructor
	USkillNode();

	// Destructor
	~USkillNode();

	// Condition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillNode")
		class USkillCondition* Condition;
	
	// Is Run on DS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillNode")
		bool bRunOnDS;

	// Is Run on Autonomous
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillNode")
		bool bRunOnAutonomous;

	// Is Run on Simulated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillNode")
		bool bRunOnSimulated;

	// Delay Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SkillNode")
		float DelayTime = 0;
};
