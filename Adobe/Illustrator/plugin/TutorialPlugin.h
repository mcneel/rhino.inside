#pragma once

#include "IllustratorSDK.h"
#include "Plugin.hpp"
#include "TutorialFilterParameters.h"
#include "TutorialID.h"

void FixupReload(Plugin* plugin);

class TutorialPlugin : public Plugin
{
  class ICLRRuntimeHost* m_pRuntimeHost = nullptr;
public:
	TutorialPlugin(SPPluginRef pluginRef);

	/** Applies this plug-in's filter.
	*/
	AIErr ActuallyGoFilter(TutorialFilterParameters params);

	FIXUP_VTABLE_EX(TutorialPlugin, Plugin);

public:
  AIFilterHandle getFilterHandle(void);

protected:
	ASErr SetGlobal(Plugin *plugin) override;
	ASErr StartupPlugin(SPInterfaceMessage *message) override; 
	ASErr PostStartupPlugin() override;
	ASErr ShutdownPlugin(SPInterfaceMessage* message) override;
  ASErr TrackToolCursor( AIToolMessage* message ) override;
  ASErr DeselectTool( AIToolMessage * message ) override;
	ASErr Notify(AINotifierMessage *message) override;

	/** Handles this plug-in's menu items.
	*/
	AIErr GoMenuItem ( AIMenuMessage* message ) override;

	/** Prompts the user for the parameters used by this plug-in's filter.
	*/
	AIErr GetFilterParameters( AIFilterMessage* message ) override;

	/** Stub method
	*/
	AIErr GoFilter( AIFilterMessage* message ) override;

	/** Handles mouse down messages for this plug-in's tool.
	*/
	AIErr ToolMouseDown( AIToolMessage* message ) override;

	/** Executes this plug-in's filter as an action event.
	*/
	AIErr GoAction( DoActionMessage* message) override;
    
    

private:
	/** Records this plug-in's filter as an action event.
	*/
	AIErr RecordFilterAction(const TutorialFilterParameters& myParameters);

	/** Adds this plug-in's menu items to Illustrator.
	*/
	AIErr AddMenu(SPInterfaceMessage* message);

	/** Adds this plug-in's action event to Illustrator.
	*/
	AIErr AddAction(SPInterfaceMessage* message);

	/** Adds this plug-in's filter to Illustrator.
	*/
	AIErr AddFilter(SPInterfaceMessage* message);

	/** Adds this plug-in's tool to Illustrator.
	*/
	AIErr AddTool(SPInterfaceMessage* message);

	/** Adds the listeners for the notifications we are interested in
	*/
	ASErr AddNotifiers(SPInterfaceMessage* message);

	AIFilterHandle fFilterHandle;
	AIToolHandle fToolHandle;

	/** Menu item handle for this plug-ins About menu.
	*/
	AIMenuItemHandle fAboutPluginMenu;

	/** Handle for the apply filter notifier dispatched by the flash UI
	*/
	AINotifierHandle fApplyFilterNotifier;
	
	/** Handle for CSXS plugplug setup complete notifier.
	*/
	AINotifierHandle fCSXSPlugPlugSetupCompleteNotifier;

	/** The controller for the flash dialog
	*/
	class TutorialPanelController* fPanelController;
    
  /** Handle for resource manager (used to set cursor icon)
   */
  AIResourceManagerHandle fResourceManagerHandle;

	/** Handle for illustrator shutdown notifier.
	*/
	AINotifierHandle fShutdownApplicationNotifier;
};

