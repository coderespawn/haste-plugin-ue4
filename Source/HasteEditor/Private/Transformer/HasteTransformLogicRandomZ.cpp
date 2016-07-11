// Copyright 2015-2016 Code Respawn Technologies. MIT License
#include "HasteEditorPrivatePCH.h"
#include "HasteTransformLogicRandomZ.h"

void UHasteTransformLogicRandomZ::TransformObject_Implementation(const FTransform& CurrentTransform, FTransform& Offset)
{
	FQuat Rotation = FQuat::MakeFromEuler(FVector(0, 0, FMath::FRandRange(0, 360)));
	Offset = FTransform::Identity;
	Offset.SetRotation(Rotation);
}
