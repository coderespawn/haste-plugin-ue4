#include "DungeonArchitectEditorPrivatePCH.h"
#include "DungeonArchitectEditor.h"
#include "DungeonAssetTypeActions.h"

#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"
#include "LevelEditor.h"
#include "LevelEditorActions.h"

#include "AssetEditorToolkit.h"
#include "ModuleManager.h"
#include "DungeonArchitectEditorCustomization.h"
#include "DungeonArchitectCommands.h"
#include "Graph/EdGraphNode_DungeonActorBase.h"
#include "Widgets/SGraphNode_DungeonActor.h"
#include "Widgets/GraphPanelNodeFactory_DungeonProp.h"
#include "Widgets/SDungeonEditorViewportToolbar.h"

#define LOCTEXT_NAMESPACE "DungeonArchitectEditorModule" 


class FDungeonArchitectEditorModule : public IDungeonArchitectEditorModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override {
		FDungeonEditorThumbnailPool::Create();

		// Register the details customization
		{
			FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
			PropertyEditorModule.RegisterCustomClassLayout("Dungeon", FOnGetDetailCustomizationInstance::CreateStatic(&FDungeonArchitectEditorCustomization::MakeInstance));
			//PropertyEditorModule.RegisterCustomClassLayout("EdGraphNode_DungeonActorBase", FOnGetDetailCustomizationInstance::CreateStatic(&FDungeonActorNodeCustomization::MakeInstance));
			PropertyEditorModule.NotifyCustomizationModuleChanged();
		}
		
		FDungeonEditorViewportCommands::Register();
		//RegisterToolbar();

		// Register asset types
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		RegisterAssetTypeAction(AssetTools, MakeShareable(new FDungeonAssetTypeActions));

		// Register custom graph nodes
		GraphPanelNodeFactory = MakeShareable(new FGraphPanelNodeFactory_DungeonProp);
		FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory);
		//SGraphNode_DungeonPropMesh
	}

	void RegisterToolbar() {
		// register the level editor commands
		FDungeonArchitectCommands::Register();

		// bind the level editor commands
		GlobalLevelEditorActions = TSharedPtr<FUICommandList>(new FUICommandList);
		FUICommandList& ActionList = *GlobalLevelEditorActions;
		ActionList.MapAction(FDungeonArchitectCommands::Get().OpenDungeonEditor, FExecuteAction::CreateStatic(&FDungeonArchitectEditorModule::OpenDungeonEditor));

		// Register the menu extenders
		{
			FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
			TSharedRef<FExtender> ToolbarExtender(new FExtender);
			ToolbarExtender->AddToolBarExtension(
				"Game",
				EExtensionHook::After,
				GlobalLevelEditorActions,
				FToolBarExtensionDelegate::CreateStatic(&Local::AddToolBarCommands));
			LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
		}

	}

	class Local {
	public:
		static void AddToolBarCommands(FToolBarBuilder& ToolBarBuilder) {
			ToolBarBuilder.AddToolBarButton(FDungeonArchitectCommands::Get().OpenDungeonEditor);
		}
	};

	virtual void ShutdownModule() override {
		// Unregister all the asset types that we registered
		if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
		{
			IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
			for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
			{
				AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
			}
		}
		CreatedAssetTypeActions.Empty();
	}

	static void OpenDungeonEditor() {
	}

	/** Creates a new dungeon editor */
	virtual TSharedRef<IDungeonArchitectEditor> CreateDungeonEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost) override {
		TSharedRef<FDungeonArchitectEditor> NewDungeonEditor(new FDungeonArchitectEditor());
		//NewDungeonEditor->InitDungeonEditor(Mode, InitToolkitHost);
		return NewDungeonEditor;
	}

public:
	TSharedPtr<FUICommandList> GlobalLevelEditorActions;
	TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory; 

private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions(Action);
		CreatedAssetTypeActions.Add(Action);
	}

	/** All created asset type actions.  Cached here so that we can unregister them during shutdown. */
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
};

IMPLEMENT_MODULE(FDungeonArchitectEditorModule, DungeonArchitectEditorModule)


#undef LOCTEXT_NAMESPACE