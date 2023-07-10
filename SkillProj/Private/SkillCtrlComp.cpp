// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillCtrlComp.h"
#include "JsonUtilities.h"

// Sets default values for this component's properties
USkillCtrlComp::USkillCtrlComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
}

// load json file, and initialize.
void USkillCtrlComp::LoadSkillData(FSkillJsonData& InSkillJsonData)
{
	// assume InSkillJsonData.SkillPath = "GameJson.Skills.Dash", translate it to "/Game/GameJson/Skills/Dash.json"
	FString SkillJsonPath = FPaths::ProjectContentDir() + InSkillJsonData.SkillPath.Replace(TEXT("."), TEXT("/")) + FString(".json");

	FString jsonString;
	FFileHelper::LoadFileToString(jsonString, *SkillJsonPath);
	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(jsonString);
	// jsonObject
	TSharedPtr<FJsonObject> jsonObject;
	if (FJsonSerializer::Deserialize(jsonReader, jsonObject))
	{
		// Successfully deserialized JSON data
		UE_LOG(LogTemp, Log, TEXT("Successfully deserialized JSON data"));
	}
	else
	{
		// Failed to deserialize JSON data
		UE_LOG(LogTemp, Log, TEXT("Failed to deserialize JSON data"));
	}
}

// Called when the game starts
void USkillCtrlComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// load all skills, iterate SkillJsonDataMap
	for (auto& SkillJsonData : SkillJsonDataMap)
	{
		LoadSkillData(SkillJsonData);
	}
}


// Called every frame
void USkillCtrlComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

