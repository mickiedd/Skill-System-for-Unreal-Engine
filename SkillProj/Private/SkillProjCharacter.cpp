// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillProjCharacter.h"
#include "SkillCtrlComp.h"

// Sets default values
ASkillProjCharacter::ASkillProjCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillProjCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillProjCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkillProjCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASkillProjCharacter::GMRunSkill(FString SkillName)
{
	UE_LOG(LogTemp, Log, TEXT("GMRunSkill: %s"), *SkillName);

	// Get SkillCtrlComp
	USkillCtrlComp* SkillCtrlComp = FindComponentByClass<USkillCtrlComp>();
	if (SkillCtrlComp)
	{
		// Run Skill
		SkillCtrlComp->RunSkill(SkillName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GMRunSkill: SkillCtrlComp is null"));
	}
}

