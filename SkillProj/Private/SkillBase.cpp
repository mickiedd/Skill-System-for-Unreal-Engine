// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBase.h"
#include "JsonUtilities.h"



// SetArgsJson
void USkillBase::SetArgsJson(TSharedPtr<FJsonObject>& InArgsJson)
{

	// iterate Property in this Class
	for (TFieldIterator<UProperty> It(GetClass()); It; ++It)
	{
		// get Property
		UProperty* Property = *It;
		// get Property Name
		FString PropertyName = Property->GetName();
		// First check field exists
		if (!InArgsJson->HasField(PropertyName))
		{
			continue;
		}
		// check is FString
		if (Property->IsA(UStrProperty::StaticClass()))
		{
			// get Property Value
			FString PropertyValue = InArgsJson->GetStringField(PropertyName);
			// get the Pointer of this Property
			void* PropertyPtr = Property->ContainerPtrToValuePtr<void>(this);
			// PropertyPtr to FString
			UStrProperty* StrProperty = Cast<UStrProperty>(Property);
			StrProperty->SetPropertyValue(PropertyPtr, PropertyValue);
		}
		// float
		else if (Property->IsA(UFloatProperty::StaticClass()))
		{
			// get Property Value
			float PropertyValue = InArgsJson->GetNumberField(PropertyName);
			// get the Pointer of this Property
			void* PropertyPtr = Property->ContainerPtrToValuePtr<void>(this);
			// PropertyPtr to float
			UFloatProperty* FloatProperty = Cast<UFloatProperty>(Property);
			FloatProperty->SetPropertyValue(PropertyPtr, PropertyValue);
		}
		// int
		else if (Property->IsA(UIntProperty::StaticClass()))
		{
			// get Property Value
			int32 PropertyValue = InArgsJson->GetIntegerField(PropertyName);
			// get the Pointer of this Property
			void* PropertyPtr = Property->ContainerPtrToValuePtr<void>(this);
			// PropertyPtr to int
			UIntProperty* IntProperty = Cast<UIntProperty>(Property);
			IntProperty->SetPropertyValue(PropertyPtr, PropertyValue);
		}
		// Struct
		else if (Property->IsA(UStructProperty::StaticClass()))
		{
			// get Property Value
			TSharedPtr<FJsonObject> PropertyValue = InArgsJson->GetObjectField(PropertyName);
			// get the Pointer of this Property
			void* PropertyPtr = Property->ContainerPtrToValuePtr<void>(this);
			// PropertyPtr to Struct
			UStructProperty* StructProperty = Cast<UStructProperty>(Property);
			// Set Struct
			FJsonObjectConverter::JsonObjectToUStruct(PropertyValue.ToSharedRef(), StructProperty->Struct, PropertyPtr, 0, 0);
		}

	}
}