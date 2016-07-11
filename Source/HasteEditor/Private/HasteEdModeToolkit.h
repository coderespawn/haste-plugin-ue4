// Copyright 2015-2016 Code Respawn Technologies. MIT License
#pragma once

#include "Toolkits/BaseToolkit.h"

class SWidget;
class FEdMode;

class FHasteEdModeToolkit : public FModeToolkit
{
public:
	/** Initializes the dungeon mode toolkit */
	virtual void Init(const TSharedPtr< class IToolkitHost >& InitToolkitHost);

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FEdMode* GetEditorMode() const override;
	virtual TSharedPtr<SWidget> GetInlineContent() const override;

	void SetInlineContent(TSharedPtr<SWidget> Widget);

private:
	TSharedPtr<SWidget> HasteEdWidget;
};


class SHasteEditor : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SHasteEditor) {}
	SLATE_END_ARGS()


public:
	/** SCompoundWidget functions */
	void Construct(const FArguments& InArgs);
	
	void SetSettingsObject(UObject* Object, bool bForceRefresh = false);

private:
	TSharedPtr<class IDetailsView> DetailsPanel;

};