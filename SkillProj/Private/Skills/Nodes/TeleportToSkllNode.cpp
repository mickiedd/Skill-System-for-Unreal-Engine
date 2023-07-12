// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/Nodes/TeleportToSkillNode.h"

// Run
void UTeleportToSkillNode::Run()
{
	if (GetOwner() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is nullptr"));
		return;
	}
	// Print Owner Location + LocationOffset
	UE_LOG(LogTemp, Log, TEXT("Owner Location: %s, LocationOffset: %s"), *GetOwner()->GetActorLocation().ToString(), *LocationOffset.ToString());
	// Owner Teleport to NewLocation
	GetOwner()->TeleportTo(GetOwner()->GetActorLocation() + LocationOffset, GetOwner()->GetActorRotation());
}