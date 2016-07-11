//$ Copyright 2015 Ali Akbar, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//
#pragma once
#include "HasteTransformLogic.generated.h"

UCLASS(EditInlineNew, DefaultToInstanced, BlueprintType, Blueprintable, HideDropDown, abstract)
class UHasteTransformLogic : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Dungeon")
	void TransformObject(const FTransform& CurrentTransform, FTransform& Offset);
	virtual void TransformObject_Implementation(const FTransform& CurrentTransform, FTransform& Offset);

};
