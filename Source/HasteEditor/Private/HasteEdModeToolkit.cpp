// Copyright 2015-2016 Code Respawn Technologies. MIT License
#include "HasteEditorPrivatePCH.h"
#include "HasteEdModeToolkit.h"
#include "HasteEdMode.h"
#include "PropertyEditorModule.h"
#include "ModuleManager.h"
#include "IDetailsView.h"

#define LOCTEXT_NAMESPACE "HasteEditMode"

void FHasteEdModeToolkit::Init(const TSharedPtr< class IToolkitHost >& InitToolkitHost)
{
	FModeToolkit::Init(InitToolkitHost);
}

FName FHasteEdModeToolkit::GetToolkitFName() const
{
	return FName("HasteEditMode");
}

FText FHasteEdModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("ToolkitName", "Haste Edit Mode");
}

FEdMode* FHasteEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FEdModeHaste::EM_Haste);
}

TSharedPtr<SWidget> FHasteEdModeToolkit::GetInlineContent() const
{
	return HasteEdWidget;
}

void FHasteEdModeToolkit::SetInlineContent(TSharedPtr<SWidget> Widget)
{
	HasteEdWidget = Widget;
}

void SHasteEditor::Construct(const FArguments& InArgs)
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(false, false, false, FDetailsViewArgs::HideNameArea);

	DetailsPanel = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	this->ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			DetailsPanel.ToSharedRef()
		]
	];
}

void SHasteEditor::SetSettingsObject(UObject* Object, bool bForceRefresh /*= false*/)
{
	if (DetailsPanel.IsValid()) {
		DetailsPanel->SetObject(Object, bForceRefresh);
	}
}

#undef LOCTEXT_NAMESPACE