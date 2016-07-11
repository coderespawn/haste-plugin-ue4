//$ Copyright 2015 Ali Akbar, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//
#pragma once
#include "HasteTransformLogicRandomZ.generated.h"

UCLASS(EditInlineNew, DefaultToInstanced, BlueprintType, Blueprintable)
class UHasteTransformLogicRandomZ : public UHasteTransformLogic
{
	GENERATED_BODY()

public:
	virtual void TransformObject_Implementation(const FTransform& CurrentTransform, FTransform& Offset) override;
};
