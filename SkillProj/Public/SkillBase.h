// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

/**
 * 
 */
UCLASS()
class SKILLPROJ_API USkillBase : public UObject
{
	GENERATED_BODY()

public:

	void SetArgsJson(class TSharedPtr<FJsonObject>& InArgsJson);

private:

	
};
