// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillNode.h"
#include "TeleportToSkillNode.generated.h"

/**
 * 
 */
UCLASS()
class SKILLPROJ_API UTeleportToSkillNode : public USkillNode
{
	GENERATED_BODY()

public:

	// LocationOffset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeleportToSkillNode")
		FVector LocationOffset;

public:

	// Override Run
	virtual void Run() override;
	
};
