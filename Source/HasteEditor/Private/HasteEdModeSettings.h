//$ Copyright 2015 Ali Akbar, Code Respawn Technologies Pvt Ltd - All Rights Reserved $//
#pragma once
#include "Transformer/HasteTransformLogic.h"
#include "HasteEdModeSettings.generated.h"

UCLASS()
class UHasteEdModeSettings : public UObject {
	GENERATED_UCLASS_BODY()

public:

	/** Rules to transform your object when it is placed in the map */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, SimpleDisplay, Category = Haste)
	TArray<UHasteTransformLogic*> Transformers;


	/** Lets you emit your own markers into the scene */
	UPROPERTY(EditAnywhere, Category = Haste)
	bool bRotateOnScroll;
};
