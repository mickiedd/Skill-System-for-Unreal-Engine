// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillNode.h"
#include "PrintLogSkillNode.generated.h"

/**
 * 
 */
UCLASS()
class SKILLPROJ_API UPrintLogSkillNode : public USkillNode
{
	GENERATED_BODY()

public:

	// Message
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PrintLogSkillNode")
		FString Message;

public:

	// Override Run
	virtual void Run() override;
	
};
