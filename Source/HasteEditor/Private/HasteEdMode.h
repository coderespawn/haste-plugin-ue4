// Copyright 2015-2016 Code Respawn Technologies. MIT License

#pragma once
#include "EdMode.h"

DECLARE_LOG_CATEGORY_EXTERN(LogHasteMode, Log, All);

/**
 * Haste editor mode
 */
class FEdModeHaste : public FEdMode
{
public:

	/** Constructor */
	FEdModeHaste();

	/** Destructor */
	virtual ~FEdModeHaste();

	/** FGCObject interface */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	/** FEdMode: Called when the mode is entered */
	virtual void Enter() override;

	/** FEdMode: Called when the mode is exited */
	virtual void Exit() override;

	/** FEdMode: Called after an Undo operation */
	virtual void PostUndo() override;

	/**
	 * Called when the mouse is moved over the viewport
	 *
	 * @param	InViewportClient	Level editor viewport client that captured the mouse input
	 * @param	InViewport			Viewport that captured the mouse input
	 * @param	InMouseX			New mouse cursor X coordinate
	 * @param	InMouseY			New mouse cursor Y coordinate
	 *
	 * @return	true if input was handled
	 */
	virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 x, int32 y) override;

	/**
	 * FEdMode: Called when the mouse is moved while a window input capture is in effect
	 *
	 * @param	InViewportClient	Level editor viewport client that captured the mouse input
	 * @param	InViewport			Viewport that captured the mouse input
	 * @param	InMouseX			New mouse cursor X coordinate
	 * @param	InMouseY			New mouse cursor Y coordinate
	 *
	 * @return	true if input was handled
	 */
	virtual bool CapturedMouseMove(FEditorViewportClient* InViewportClient, FViewport* InViewport, int32 InMouseX, int32 InMouseY) override;

	/** FEdMode: Called when a mouse button is pressed */
	virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;

	/** FEdMode: Called when a mouse button is released */
	virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;

	/** FEdMode: Called once per frame */
	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;

	/** FEdMode: Called when a key is pressed */
	virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;

	/** FEdMode: Called when mouse drag input it applied */
	virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;

	/** FEdMode: Render elements for the Haste tool */
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;

	/** FEdMode: Render HUD elements for this tool */
	virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;

	/** FEdMode: Handling SelectActor */
	virtual bool Select(AActor* InActor, bool bInSelected) override;

	/** FEdMode: Check to see if an actor can be selected in this mode - no side effects */
	virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;

	/** FEdMode: Called when the currently selected actor has changed */
	virtual void ActorSelectionChangeNotify() override;

	/** Notifies all active modes of mouse click messages. */
	bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click);

	/** Called when the current level changes */
	void NotifyNewCurrentLevel();

	/** Called when the user changes the current tool in the UI */
	void NotifyToolChanged();

	void OnContentBrowserSelectionChanged(const TArray<FAssetData>& NewSelectedAssets, bool bIsPrimaryBrowser);

	/** FEdMode: widget handling */
	virtual FVector GetWidgetLocation() const override;
	virtual bool AllowWidgetMove();
	virtual bool ShouldDrawWidget() const override;
	virtual bool UsesTransformWidget() const override;
	virtual EAxisList::Type GetWidgetAxisToDraw(FWidget::EWidgetMode InWidgetMode) const override;

	virtual bool DisallowMouseDeltaTracking() const override;

	/** Forces real-time perspective viewports */
	void ForceRealTimeViewports(const bool bEnable, const bool bStoreCurrentState);

	/** Trace under the mouse cursor and update brush position */
	void HasteBrushTrace(FEditorViewportClient* ViewportClient, int32 MouseX, int32 MouseY);

	/** Generate start/end points for a random trace inside the sphere brush.
	returns a line segment inside the sphere parallel to the view direction */
	void GetRandomVectorInBrush(FVector& OutStart, FVector& OutEnd);

	/** Apply brush */
	void ApplyBrush(FEditorViewportClient* ViewportClient);

	void ResetBrushMesh();

	void UpdateBrushRotation();

	static FEditorModeID EM_Haste;

private:
	FTransform ApplyTransformers(const FTransform& BaseTransform);

private:
	bool bBrushTraceValid;
	FVector BrushLocation;
	FVector BrushScale;
	FQuat BrushRotation;
	FTransform BrushCursorTransform;
	FIntVector LastMousePosition;

	FVector BrushTraceDirection;
	TArray<UStaticMesh*> SelectedBrushMeshes;
	UStaticMesh* ActiveBrushMesh;
	UStaticMesh* DefaultBrushMesh;
	UStaticMeshComponent* BrushMeshComponent;

	FVector LastHitImpact;

	bool bToolActive;
	bool bCanAltDrag;
	bool bMeshRotating;

	FVector RotationOffset;

	FDelegateHandle ContentBrowserSelectionChangeDelegate;

	class UHasteEdModeSettings* UISettings;

};