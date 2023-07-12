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
							// Extract SkillPhase's Properties
							SkillPhase->SetArgsJson(PhaseObject);

							// Extract Nodes array
							const TArray<TSharedPtr<FJsonValue>>* NodesArray;
							if (PhaseObject->TryGetArrayField("Nodes", NodesArray))
							{
								// Iterate over each element in the Nodes array and extract the NodeName, Class, and Args fields
								for (auto NodeValue : *NodesArray)
								{
									TSharedPtr<FJsonObject> NodeObject = NodeValue->AsObject();
									FString ClassName;
									if (NodeObject.IsValid() && NodeObject->TryGetStringField("Class", ClassName))
									{
										UClass* ClassObj = StaticLoadClass(UObject::StaticClass(), nullptr, *ClassName);
										if (ClassObj)
										{
											USkillNode* SkillNode = NewObject<USkillNode>(this, ClassObj);
											SkillNode->SetOwner(GetOwner());

											// Extract NodeName and Class
											if (NodeObject->TryGetStringField("NodeName", SkillNode->NodeName))
											{
												// Extract Args object
												TSharedPtr<FJsonObject> ArgsObject = NodeObject->GetObjectField("Args");
												if (ArgsObject.IsValid())
												{
													SkillNode->SetArgsJson(ArgsObject);
												}

												SkillPhase->Nodes.Add(SkillNode);
											}
										}
									}
								}
							}

							// Add SkillPhase to SkillPhases
							InSkillJsonData.SkillPhases.Add(SkillPhase);
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

// RunSkill
void USkillCtrlComp::RunSkill(FString SkillName)
{
	for (auto& SkillJsonData : SkillJsonDataMap)
	{
		if (SkillJsonData.SkillName == SkillName)
		{
			SkillJsonData.bRun = true;
		}
	}
}


// Called every frame
void USkillCtrlComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// iterate SkillJsonDataMap, and find the SkillJsonData with SkillName
	for (auto& SkillJsonData : SkillJsonDataMap)
	{
		if (SkillJsonData.bRun)
		{
			// iterate SkillPhases
			for (auto& SkillPhase : SkillJsonData.SkillPhases)
			{
				// check IsFinish
				if (SkillPhase->IsFinish())
				{
					continue;
				}
				// Run Phase
				SkillPhase->Run();
				break;
			}
		}
	}

	// iterate SkillJsonDataMap
	for (auto& SkillJsonData : SkillJsonDataMap)
	{
		// iterate SkillPhases
		for (auto& SkillPhase : SkillJsonData.SkillPhases)
		{
			// Tick Phase
			SkillPhase->Tick(DeltaTime);
		}
	}
}

// ClearSkillPhases
void USkillCtrlComp::ClearSkillPhases()
{
	// iterate SkillJsonDataMap
	for (auto& SkillJsonData : SkillJsonDataMap)
	{
		SkillJsonData.SkillPhases.Empty();
	}
}

