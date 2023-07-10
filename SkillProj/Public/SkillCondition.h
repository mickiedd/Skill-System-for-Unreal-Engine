// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillCondition.generated.h"

/**
 * 
 */
UCLASS()
class SKILLPROJ_API USkillCondition : public UObject
{
	GENERATED_BODY()

public:
	// Constructor
	USkillCondition();

	// Deconstructor
	~USkillCondition();

	// IsTrue
	UFUNCTION(BlueprintCallable, Category = "SkillCondition")
		virtual bool IsTrue() const;
};
