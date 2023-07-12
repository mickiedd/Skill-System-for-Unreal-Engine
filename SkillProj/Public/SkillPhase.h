// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.h"
#include "SkillPhase.generated.h"

/**
 * 
 */
UCLASS()
class SKILLPROJ_API USkillPhase : public USkillBase
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

public:

	void Tick(float DeltaTime);

	void Run();

	void Exit();

	bool IsFinish();

	bool IsRunning();

	bool IsPendingRun();

private:

	// start run time
	float StartTime = 0.0f;

	// Cache the Timers
	TArray<FTimerHandle> TimerHandles;

	bool bExit = false;
	
};
