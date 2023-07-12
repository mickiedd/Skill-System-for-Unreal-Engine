// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillPhase.h"
#include "SkillNode.h"

// Tick
void USkillPhase::Tick(float DeltaTime)
{
	if (bExit)
	{
		return;
	}
	if (IsFinish())
	{
		Exit();
		return;
	}
	// iterate Nodes
	for (auto& SkillNode : Nodes)
	{
		// Tick Node
		SkillNode->Tick(DeltaTime);
	}
}

// Run
void USkillPhase::Run()
{
	if (IsRunning())
	{
		return;
	}
	if (bExit)
	{
		return;
	}
	// iterate Nodes
	for (auto& SkillNode : Nodes)
	{
		// Check DelayTime
		if (SkillNode->DelayTime > 0)
		{
			// Set A timer
			FTimerHandle TimerHandle;
			TimerHandles.Add(TimerHandle);
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, SkillNode]()
			{
				// Run Node
				SkillNode->Run();
			}, SkillNode->DelayTime, false);
		}
		else
		{
			// Run Node
			SkillNode->Run();
		}
	}
	StartTime = GetWorld()->GetTimeSeconds();
}

// Exit
void USkillPhase::Exit()
{
	bExit = true;
	// iterate Nodes
	for (auto& SkillNode : Nodes)
	{
		SkillNode->Exit();
	}
}

// IsRunning
bool USkillPhase::IsRunning()
{
	return StartTime > 0;
}

// IsPendingRun
bool USkillPhase::IsPendingRun()
{
	return !IsRunning();
}

// IsFinish
bool USkillPhase::IsFinish()
{
	// check StartTime, and Duration
	return StartTime > 0 && StartTime + PhaseDuration < GetWorld()->GetTimeSeconds();
}
