#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SQR_TD/UI/SQR_TDWidgetBase.generated.h"

/**
 * SQR_TDWidgetBase - Base class for all UI widgets
 * Provides common functionality for UI elements
 */
UCLASS()
class SQR_TD_API USQR_TDWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	USQR_TDWidgetBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	// UI functions (to be implemented)
	// UpdateDisplay, BindEvents, etc.
};
