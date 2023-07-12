// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNode.h"
#include "SkillCondition.h"

// Constructor
USkillNode::USkillNode()
{
}

// Destructor
USkillNode::~USkillNode()
{
}

// Exit
void USkillNode::Exit()
{
	// print owner, NodeName
	UE_LOG(LogTemp, Log, TEXT("USkillNode::Exit: %s, %s"), *Owner->GetName(), *NodeName);
}

// SetOwner
void USkillNode::SetOwner(AActor* InOwner)
{
	Owner = InOwner;
}