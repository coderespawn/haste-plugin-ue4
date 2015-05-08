#include "HasteEditorPrivatePCH.h"

#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"
#include "LevelEditor.h"
#include "LevelEditorActions.h"

#include "ModuleManager.h"
#include "HasteEdMode.h"

#define LOCTEXT_NAMESPACE "HasteEditorModule" 

const static FEditorModeID EM_Haste(TEXT("EM_Haste"));

class FHasteEditorModule : public IHasteEditorModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override {
		FEditorModeRegistry::Get().RegisterMode<FEdModeHaste>(
			EM_Haste,
			NSLOCTEXT("EditorModes", "HasteMode", "Haste"),
			FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.FoliageMode", "LevelEditor.FoliageMode.Small"),
			true, 400
		);
	}


	virtual void ShutdownModule() override {
		FEditorModeRegistry::Get().UnregisterMode(EM_Haste);
	}
};

IMPLEMENT_MODULE(FHasteEditorModule, HasteEditorModule)


#undef LOCTEXT_NAMESPACE