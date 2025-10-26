#include "SQR_TDEditor.h"

#define LOCTEXT_NAMESPACE "FSQR_TDEditorModule"

void FSQR_TDEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file
}

void FSQR_TDEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSQR_TDEditorModule, SQR_TDEditor)
