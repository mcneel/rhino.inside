#pragma once

#include "IllustratorSDK.h"
#include "Plugin.hpp"
#include "RhinoInsideID.h"

void FixupReload(Plugin* plugin);

class CRhinoInsidePlugIn : public Plugin
{
  struct ICLRRuntimeHost* m_pRuntimeHost = nullptr;
public:
  CRhinoInsidePlugIn(SPPluginRef pluginRef);

	FIXUP_VTABLE_EX(CRhinoInsidePlugIn, Plugin);

protected:
	ASErr SetGlobal(Plugin *plugin) override;
	ASErr StartupPlugin(SPInterfaceMessage *message) override; 
	ASErr PostStartupPlugin() override;
	ASErr ShutdownPlugin(SPInterfaceMessage* message) override;
	ASErr Notify(AINotifierMessage *message) override;
  ASErr Message(char *caller, char *selector, void *message) override;

	AIErr GetFilterParameters( AIFilterMessage* message ) override;
	AIErr GoFilter( AIFilterMessage* message ) override;

private:
  bool RunRhino();

  // Adds this plug-in's filter to Illustrator.
	AIErr AddFilter(SPInterfaceMessage* message);

	// Adds the listeners for the notifications we are interested in
	ASErr AddNotifiers(SPInterfaceMessage* message);


  AIFilterHandle fFilterHandle;

	// Handle for the apply filter notifier dispatched by the flash UI
	AINotifierHandle fApplyFilterNotifier = nullptr;
	
	// Handle for CSXS plugplug setup complete notifier.
	AINotifierHandle fCSXSPlugPlugSetupCompleteNotifier = nullptr;

  // Handle for resource manager (used to set cursor icon)
  AIResourceManagerHandle fResourceManagerHandle = nullptr;

	// Handle for illustrator shutdown notifier.
	AINotifierHandle fShutdownApplicationNotifier = nullptr;
};

