// Fill out your copyright notice in the Description page of Project Settings.


#include "Skills/Nodes/PrintLogSkillNode.h"

// Run
void UPrintLogSkillNode::Run()
{
	// Print Message
	UE_LOG(LogTemp, Log, TEXT("PrintLogSkillNode: %s"), *Message);
}