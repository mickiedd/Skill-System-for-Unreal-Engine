// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillCtrlComp.generated.h"

// struct to store skill json data
USTRUCT(BlueprintType)
struct FSkillJsonData
{
	GENERATED_BODY()

public:
	// key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
		FString SkillName;
	// path
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
		FString SkillPath;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKILLPROJ_API USkillCtrlComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillCtrlComp();

	// load json file, and initialize.
	UFUNCTION(BlueprintCallable, Category = "Skill")
		void LoadSkillData(FSkillJsonData& InSkillJsonData);

	// Skill Json filepath
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
		TArray< FSkillJsonData> SkillJsonDataMap;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// SkillPhase
	TArray<class USkillPhase*> SkillPhases;

private:
	// Clear SkillPhases
	void ClearSkillPhases();
};
