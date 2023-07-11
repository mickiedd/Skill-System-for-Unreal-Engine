// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillCtrlComp.h"
#include "JsonUtilities.h"
#include "SkillPhase.h"
#include "SkillNode.h"

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
	// Clear SkillPhases
	ClearSkillPhases();

	// assume InSkillJsonData.SkillPath = "GameJson.Skills.Dash", translate it to "/Game/GameJson/Skills/Dash.json"
	FString SkillJsonPath = FPaths::ProjectContentDir() + InSkillJsonData.SkillPath.Replace(TEXT("."), TEXT("/")) + FString(".json");

	FString jsonString;
	FFileHelper::LoadFileToString(jsonString, *SkillJsonPath);
	TSharedRef<TJsonReader<>> jsonReader = TJsonReaderFactory<>::Create(jsonString);
	// jsonObject
	TSharedPtr<FJsonObject> JsonObject;
	if (FJsonSerializer::Deserialize(jsonReader, JsonObject))
	{
		// Successfully deserialized JSON data
		UE_LOG(LogTemp, Log, TEXT("Successfully deserialized JSON data"));
		// Assume the JsonString is already deserialized to a FJsonObject called JsonObject
		// First, extract the SkillName field from the JsonObject
		FString SkillName;
		if (JsonObject->TryGetStringField("SkillName", SkillName))
		{
			// Then, extract the Phases array from the JsonObject
			const TArray<TSharedPtr<FJsonValue>>* PhasesArray;
			if (JsonObject->TryGetArrayField("Phases", PhasesArray))
			{
				// iterate PhasesArray
				for (auto PhaseValue : *PhasesArray)
				{
					TSharedPtr<FJsonObject> PhaseObject = PhaseValue->AsObject();
					if (PhaseObject.IsValid())
					{
						USkillPhase* SkillPhase = NewObject<USkillPhase>(this, USkillPhase::StaticClass());

						// Extract PhaseName and PhaseDuration
						if (PhaseObject->TryGetStringField("PhaseName", SkillPhase->PhaseName) && PhaseObject->TryGetNumberField("PhaseDuration", SkillPhase->PhaseDuration))
						{
							// Extract Nodes array
							const TArray<TSharedPtr<FJsonValue>>* NodesArray;
							if (PhaseObject->TryGetArrayField("Nodes", NodesArray))
							{
								// Iterate over each element in the Nodes array and extract the NodeName, Class, and Args fields
								for (auto NodeValue : *NodesArray)
								{
									TSharedPtr<FJsonObject> NodeObject = NodeValue->AsObject();
									if (NodeObject.IsValid())
									{
										USkillNode* SkillNode = NewObject<USkillNode>(this, USkillNode::StaticClass());
										SkillNode->SetOwner(GetOwner());

										// Extract NodeName and Class
										FString ClassName;
										if (NodeObject->TryGetStringField("NodeName", SkillNode->NodeName) && NodeObject->TryGetStringField("Class", ClassName))
										{
											// Extract Args object
											TSharedPtr<FJsonObject> ArgsObject = NodeObject->GetObjectField("Args");
											if (ArgsObject.IsValid())
											{
												// todo
											}

											SkillPhase->Nodes.Add(SkillNode);
										}
									}
								}
							}

							SkillPhases.Add(SkillPhase);
						}
					}
				}
			}
		}

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

// ClearSkillPhases
void USkillCtrlComp::ClearSkillPhases()
{
	// Then clear the TArray itself.
	SkillPhases.Empty();
}

