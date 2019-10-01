#ifndef AIMenuCommandNotifiers_h__
#define AIMenuCommandNotifiers_h__

/*
 *        Name:	AIMenuCommandNotifiers.h
 *     Purpose:	
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1995-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

/** @file AIMenuCommandNotifiers.h */

/**	@ingroup Notifiers
	Menu identifiers for pre- and post- notification
	See source code and \c #AIMenuSuite. */

#define kAINewCommandPreNotifierStr                                  "AI Command Notifier: Before New"                              //File:New
#define kAINewCommandPostNotifierStr                                 "AI Command Notifier: After New"                               //File:New
#define kAINewFromTemplateCommandPreNotifierStr                      "AI Command Notifier: Before New From Template"                //File:New from Template
#define kAINewFromTemplateCommandPostNotifierStr                     "AI Command Notifier: After New From Template"                 //File:New from Template
#define kAIOpenCommandPreNotifierStr                                 "AI Command Notifier: Before Open"                             //File:Open
#define kAIOpenCommandPostNotifierStr                                "AI Command Notifier: After Open"                              //File:Open
#define kAICloseCommandPreNotifierStr                                "AI Command Notifier: Before Close"                            //File:Close
#define kAICloseCommandPostNotifierStr                               "AI Command Notifier: After Close"                             //File:Close
#define kAISaveCommandPreNotifierStr                                 "AI Command Notifier: Before Save"                             //File:Save
#define kAISaveCommandPostNotifierStr                                "AI Command Notifier: After Save"                              //File:Save
#define kAISaveAsCommandPreNotifierStr                               "AI Command Notifier: Before Save As"                          //File:Save As
#define kAISaveAsCommandPostNotifierStr                              "AI Command Notifier: After Save As"                           //File:Save As
#define kAISaveACopyAsCommandPreNotifierStr                          "AI Command Notifier: Before Save A Copy As"                   //File:Save a Copy
#define kAISaveACopyAsCommandPostNotifierStr                         "AI Command Notifier: After Save A Copy As"                    //File:Save a Copy
#define kAISaveAsTemplateCommandPreNotifierStr                       "AI Command Notifier: Before Save As Template"                 //File:Save as Template
#define kAISaveAsTemplateCommandPostNotifierStr                      "AI Command Notifier: After Save As Template"                  //File:Save as Template
#define kAIAdobeAISaveForWebCommandPreNotifierStr                    "AI Command Notifier: Before Adobe AI Save For Web"            //File:Save for Web & Devices
#define kAIAdobeAISaveForWebCommandPostNotifierStr                   "AI Command Notifier: After Adobe AI Save For Web"             //File:Save for Web & Devices
#define kAIAdobeAISaveSelectedSlicesCommandPreNotifierStr            "AI Command Notifier: Before Adobe AI Save Selected Slices"    //File:Save Selected Slices
#define kAIAdobeAISaveSelectedSlicesCommandPostNotifierStr           "AI Command Notifier: After Adobe AI Save Selected Slices"     //File:Save Selected Slices
#define kAIRevertToSavedCommandPreNotifierStr                        "AI Command Notifier: Before Revert To Saved"                  //File:Revert
#define kAIRevertToSavedCommandPostNotifierStr                       "AI Command Notifier: After Revert To Saved"                   //File:Revert
#define kAIAIPlaceCommandPreNotifierStr                              "AI Command Notifier: Before AI Place"                         //File:Place
#define kAIAIPlaceCommandPostNotifierStr                             "AI Command Notifier: After AI Place"                          //File:Place
#define kAISaveForOfficeCommandPreNotifierStr                        "AI Command Notifier: Before Save for Office"                  //File:Save for Microsoft Office
#define kAISaveForOfficeCommandPostNotifierStr                       "AI Command Notifier: After Save for Office"                   //File:Save for Microsoft Office
#define kAIExportCommandPreNotifierStr                               "AI Command Notifier: Before Export"                           //File:Export
#define kAIExportCommandPostNotifierStr                              "AI Command Notifier: After Export"                            //File:Export
#define kAIAiBrowseForScriptCommandPreNotifierStr                    "AI Command Notifier: Before ai_browse_for_script"             //File:Scripts:Other Script
#define kAIAiBrowseForScriptCommandPostNotifierStr                   "AI Command Notifier: After ai_browse_for_script"              //File:Scripts:Other Script
#define kAIArtSetupCommandPreNotifierStr                             "AI Command Notifier: Before Art Setup"                        //File:Document Setup
#define kAIArtSetupCommandPostNotifierStr                            "AI Command Notifier: After Art Setup"                         //File:Document Setup
#define kAIColorModeCMYKCommandPreNotifierStr                        "AI Command Notifier: Before Color Mode CMYK"                  //File:Document Color Mode:CMYK Color
#define kAIColorModeCMYKCommandPostNotifierStr                       "AI Command Notifier: After Color Mode CMYK"                   //File:Document Color Mode:CMYK Color
#define kAIColorModeRGBCommandPreNotifierStr                         "AI Command Notifier: Before Color Mode RGB"                   //File:Document Color Mode:RGB Color
#define kAIColorModeRGBCommandPostNotifierStr                        "AI Command Notifier: After Color Mode RGB"                    //File:Document Color Mode:RGB Color
#define kAIFileInfoCommandPreNotifierStr                             "AI Command Notifier: Before File Info"                        //File:File Info
#define kAIFileInfoCommandPostNotifierStr                            "AI Command Notifier: After File Info"                         //File:File Info
#define kAIPrintCommandPreNotifierStr                                "AI Command Notifier: Before Print"                            //File:Print
#define kAIPrintCommandPostNotifierStr                               "AI Command Notifier: After Print"                             //File:Print
#define kAIQuitCommandPreNotifierStr                                 "AI Command Notifier: Before Quit"                             //File:Exit
#define kAIQuitCommandPostNotifierStr                                "AI Command Notifier: After Quit"                              //File:Exit
#define kAIUndoCommandPreNotifierStr                                 "AI Command Notifier: Before Undo"                             //Edit:Undo
#define kAIUndoCommandPostNotifierStr                                "AI Command Notifier: After Undo"                              //Edit:Undo
#define kAIRedoCommandPreNotifierStr                                 "AI Command Notifier: Before Redo"                             //Edit:Redo
#define kAIRedoCommandPostNotifierStr                                "AI Command Notifier: After Redo"                              //Edit:Redo
#define kAICutCommandPreNotifierStr                                  "AI Command Notifier: Before Cut"                              //Edit:Cut
#define kAICutCommandPostNotifierStr                                 "AI Command Notifier: After Cut"                               //Edit:Cut
#define kAICopyCommandPreNotifierStr                                 "AI Command Notifier: Before Copy"                             //Edit:Copy
#define kAICopyCommandPostNotifierStr                                "AI Command Notifier: After Copy"                              //Edit:Copy
#define kAIPasteCommandPreNotifierStr                                "AI Command Notifier: Before Paste"                            //Edit:Paste
#define kAIPasteCommandPostNotifierStr                               "AI Command Notifier: After Paste"                             //Edit:Paste
#define kAIPasteInFrontCommandPreNotifierStr                         "AI Command Notifier: Before Paste in Front"                   //Edit:Paste in Front
#define kAIPasteInFrontCommandPostNotifierStr                        "AI Command Notifier: After Paste in Front"                    //Edit:Paste in Front
#define kAIPasteInBackCommandPreNotifierStr                          "AI Command Notifier: Before Paste in Back"                    //Edit:Paste in Back
#define kAIPasteInBackCommandPostNotifierStr                         "AI Command Notifier: After Paste in Back"                     //Edit:Paste in Back
#define kAIPasteInPlaceCommandPreNotifierStr                         "AI Command Notifier: Before Paste in Place"                   //Edit:Paste in Place
#define kAIPasteInPlaceCommandPostNotifierStr                        "AI Command Notifier: After Paste in Place"                    //Edit:Paste in Place
#define kAIPasteInAllArtboardsCommandPreNotifierStr                  "AI Command Notifier: Before Paste in All Artboards"           //Edit:Paste on All Artboards
#define kAIPasteInAllArtboardsCommandPostNotifierStr                 "AI Command Notifier: After Paste in All Artboards"            //Edit:Paste on All Artboards
#define kAIClearCommandPreNotifierStr                                "AI Command Notifier: Before Clear"                            //Edit:Clear
#define kAIClearCommandPostNotifierStr                               "AI Command Notifier: After Clear"                             //Edit:Clear
#define kAIFindAndReplaceCommandPreNotifierStr                       "AI Command Notifier: Before Find and Replace"                 //Edit:Find and Replace
#define kAIFindAndReplaceCommandPostNotifierStr                      "AI Command Notifier: After Find and Replace"                  //Edit:Find and Replace
#define kAIFindNextCommandPreNotifierStr                             "AI Command Notifier: Before Find Next"                        //Edit:Find Next
#define kAIFindNextCommandPostNotifierStr                            "AI Command Notifier: After Find Next"                         //Edit:Find Next
#define kAICheckSpellingCommandPreNotifierStr                        "AI Command Notifier: Before Check Spelling"                   //Edit:Check Spelling
#define kAICheckSpellingCommandPostNotifierStr                       "AI Command Notifier: After Check Spelling"                    //Edit:Check Spelling
#define kAIEditCustomDictionaryCommandPreNotifierStr                 "AI Command Notifier: Before Edit Custom Dictionary..."        //Edit:Edit Custom Dictionary
#define kAIEditCustomDictionaryCommandPostNotifierStr                "AI Command Notifier: After Edit Custom Dictionary..."         //Edit:Edit Custom Dictionary
#define kAIDefinePatternMenuItemCommandPreNotifierStr                "AI Command Notifier: Before Define Pattern Menu Item"         //Edit:Define Pattern
#define kAIDefinePatternMenuItemCommandPostNotifierStr               "AI Command Notifier: After Define Pattern Menu Item"          //Edit:Define Pattern
#define kAIRecolorArtDialogCommandPreNotifierStr                     "AI Command Notifier: Before Recolor Art Dialog"               //Edit:Edit Colors:Recolor Artwork
#define kAIRecolorArtDialogCommandPostNotifierStr                    "AI Command Notifier: After Recolor Art Dialog"                //Edit:Edit Colors:Recolor Artwork
#define kAIAdjust3CommandPreNotifierStr                              "AI Command Notifier: Before Adjust3"                          //Edit:Edit Colors:Adjust Color Balance
#define kAIAdjust3CommandPostNotifierStr                             "AI Command Notifier: After Adjust3"                           //Edit:Edit Colors:Adjust Color Balance
#define kAIColors3CommandPreNotifierStr                              "AI Command Notifier: Before Colors3"                          //Edit:Edit Colors:Blend Front to Back
#define kAIColors3CommandPostNotifierStr                             "AI Command Notifier: After Colors3"                           //Edit:Edit Colors:Blend Front to Back
#define kAIColors4CommandPreNotifierStr                              "AI Command Notifier: Before Colors4"                          //Edit:Edit Colors:Blend Horizontally
#define kAIColors4CommandPostNotifierStr                             "AI Command Notifier: After Colors4"                           //Edit:Edit Colors:Blend Horizontally
#define kAIColors5CommandPreNotifierStr                              "AI Command Notifier: Before Colors5"                          //Edit:Edit Colors:Blend Vertically
#define kAIColors5CommandPostNotifierStr                             "AI Command Notifier: After Colors5"                           //Edit:Edit Colors:Blend Vertically
#define kAIColors8CommandPreNotifierStr                              "AI Command Notifier: Before Colors8"                          //Edit:Edit Colors:Convert to CMYK
#define kAIColors8CommandPostNotifierStr                             "AI Command Notifier: After Colors8"                           //Edit:Edit Colors:Convert to CMYK
#define kAIColors7CommandPreNotifierStr                              "AI Command Notifier: Before Colors7"                          //Edit:Edit Colors:Convert to Grayscale
#define kAIColors7CommandPostNotifierStr                             "AI Command Notifier: After Colors7"                           //Edit:Edit Colors:Convert to Grayscale
#define kAIColors9CommandPreNotifierStr                              "AI Command Notifier: Before Colors9"                          //Edit:Edit Colors:Convert to RGB
#define kAIColors9CommandPostNotifierStr                             "AI Command Notifier: After Colors9"                           //Edit:Edit Colors:Convert to RGB
#define kAIColors6CommandPreNotifierStr                              "AI Command Notifier: Before Colors6"                          //Edit:Edit Colors:Invert Colors
#define kAIColors6CommandPostNotifierStr                             "AI Command Notifier: After Colors6"                           //Edit:Edit Colors:Invert Colors
#define kAIOverprint2CommandPreNotifierStr                           "AI Command Notifier: Before Overprint2"                       //Edit:Edit Colors:Overprint Black
#define kAIOverprint2CommandPostNotifierStr                          "AI Command Notifier: After Overprint2"                        //Edit:Edit Colors:Overprint Black
#define kAISaturate3CommandPreNotifierStr                            "AI Command Notifier: Before Saturate3"                        //Edit:Edit Colors:Saturate
#define kAISaturate3CommandPostNotifierStr                           "AI Command Notifier: After Saturate3"                         //Edit:Edit Colors:Saturate
#define kAIEditOriginalMenuItemCommandPreNotifierStr                 "AI Command Notifier: Before EditOriginal Menu Item"           //Edit:Edit Original
#define kAIEditOriginalMenuItemCommandPostNotifierStr                "AI Command Notifier: After EditOriginal Menu Item"            //Edit:Edit Original
#define kAITransparencyPresetsCommandPreNotifierStr                  "AI Command Notifier: Before Transparency Presets"             //Edit:Transparency Flattener Presets
#define kAITransparencyPresetsCommandPostNotifierStr                 "AI Command Notifier: After Transparency Presets"              //Edit:Transparency Flattener Presets
#define kAITracingPresetsCommandPreNotifierStr                       "AI Command Notifier: Before TracingPresets"                   //Edit:Tracing Presets
#define kAITracingPresetsCommandPostNotifierStr                      "AI Command Notifier: After TracingPresets"                    //Edit:Tracing Presets
#define kAIPrintPresetsCommandPreNotifierStr                         "AI Command Notifier: Before Print Presets"                    //Edit:Print Presets
#define kAIPrintPresetsCommandPostNotifierStr                        "AI Command Notifier: After Print Presets"                     //Edit:Print Presets
#define kAIPDFPresetsCommandPreNotifierStr                           "AI Command Notifier: Before PDF Presets"                      //Edit:Adobe PDF Presets
#define kAIPDFPresetsCommandPostNotifierStr                          "AI Command Notifier: After PDF Presets"                       //Edit:Adobe PDF Presets
#define kAISWFPresetsCommandPreNotifierStr                           "AI Command Notifier: Before SWFPresets"                       //Edit:SWF Presets
#define kAISWFPresetsCommandPostNotifierStr                          "AI Command Notifier: After SWFPresets"                        //Edit:SWF Presets
#define kAIPerspectiveGridPresetsCommandPreNotifierStr               "AI Command Notifier: Before PerspectiveGridPresets"           //Edit:Perspective Grid Presets
#define kAIPerspectiveGridPresetsCommandPostNotifierStr              "AI Command Notifier: After PerspectiveGridPresets"            //Edit:Perspective Grid Presets
#define kAIColorMatchingPreferencesCommandPreNotifierStr             "AI Command Notifier: Before Color Matching Preferences"       //Edit:Color Settings
#define kAIColorMatchingPreferencesCommandPostNotifierStr            "AI Command Notifier: After Color Matching Preferences"        //Edit:Color Settings
#define kAIAssignProfileCommandPreNotifierStr                        "AI Command Notifier: Before Assign Profile"                   //Edit:Assign Profile
#define kAIAssignProfileCommandPostNotifierStr                       "AI Command Notifier: After Assign Profile"                    //Edit:Assign Profile
#define kAIKBSCMenuItemCommandPreNotifierStr                         "AI Command Notifier: Before KBSC Menu Item"                   //Edit:Keyboard Shortcuts
#define kAIKBSCMenuItemCommandPostNotifierStr                        "AI Command Notifier: After KBSC Menu Item"                    //Edit:Keyboard Shortcuts
#define kAIPreferencesCommandPreNotifierStr                          "AI Command Notifier: Before Preferences"                      //Edit:Preferences:General
#define kAIPreferencesCommandPostNotifierStr                         "AI Command Notifier: After Preferences"                       //Edit:Preferences:General
#define kAISelectionPreferencesCommandPreNotifierStr                 "AI Command Notifier: Before Selection Preferences"            //Edit:Preferences:Selection & Anchor Display
#define kAISelectionPreferencesCommandPostNotifierStr                "AI Command Notifier: After Selection Preferences"             //Edit:Preferences:Selection & Anchor Display
#define kAIKeyboardPreferencesCommandPreNotifierStr                  "AI Command Notifier: Before Keyboard Preferences"             //Edit:Preferences:Type
#define kAIKeyboardPreferencesCommandPostNotifierStr                 "AI Command Notifier: After Keyboard Preferences"              //Edit:Preferences:Type
#define kAIUnitUndoPreferencesCommandPreNotifierStr                  "AI Command Notifier: Before Unit Undo Preferences"            //Edit:Preferences:Units
#define kAIUnitUndoPreferencesCommandPostNotifierStr                 "AI Command Notifier: After Unit Undo Preferences"             //Edit:Preferences:Units
#define kAIGridPreferencesCommandPreNotifierStr                      "AI Command Notifier: Before Grid Preferences"                 //Edit:Preferences:Guides & Grid
#define kAIGridPreferencesCommandPostNotifierStr                     "AI Command Notifier: After Grid Preferences"                  //Edit:Preferences:Guides & Grid
#define kAISnapomaticPreferencesCommandPreNotifierStr                "AI Command Notifier: Before Snapomatic Preferences"           //Edit:Preferences:Smart Guides
#define kAISnapomaticPreferencesCommandPostNotifierStr               "AI Command Notifier: After Snapomatic Preferences"            //Edit:Preferences:Smart Guides
#define kAISlicePreferencesCommandPreNotifierStr                     "AI Command Notifier: Before Slice Preferences"                //Edit:Preferences:Slices
#define kAISlicePreferencesCommandPostNotifierStr                    "AI Command Notifier: After Slice Preferences"                 //Edit:Preferences:Slices
#define kAIHyphenationPreferencesCommandPreNotifierStr               "AI Command Notifier: Before Hyphenation Preferences"          //Edit:Preferences:Hyphenation
#define kAIHyphenationPreferencesCommandPostNotifierStr              "AI Command Notifier: After Hyphenation Preferences"           //Edit:Preferences:Hyphenation
#define kAIPluginsFolderPreferencesCommandPreNotifierStr             "AI Command Notifier: Before Plugins Folder Preferences"       //Edit:Preferences:Plug-ins & Scratch Disks
#define kAIPluginsFolderPreferencesCommandPostNotifierStr            "AI Command Notifier: After Plugins Folder Preferences"        //Edit:Preferences:Plug-ins & Scratch Disks
#define kAIUserInterfacePreferencesCommandPreNotifierStr             "AI Command Notifier: Before User Interface Preferences"       //Edit:Preferences:User Interface
#define kAIUserInterfacePreferencesCommandPostNotifierStr            "AI Command Notifier: After User Interface Preferences"        //Edit:Preferences:User Interface
#define kAIFileClipboardPrefCommandPreNotifierStr                    "AI Command Notifier: Before FileClipboardPref"                //Edit:Preferences:File Handling & Clipboard
#define kAIFileClipboardPrefCommandPostNotifierStr                   "AI Command Notifier: After FileClipboardPref"                 //Edit:Preferences:File Handling & Clipboard
#define kAIBlackPrefCommandPreNotifierStr                            "AI Command Notifier: Before BlackPref"                        //Edit:Preferences:Appearance of Black
#define kAIBlackPrefCommandPostNotifierStr                           "AI Command Notifier: After BlackPref"                         //Edit:Preferences:Appearance of Black
#define kAITransformAgainCommandPreNotifierStr                       "AI Command Notifier: Before Transform Again"                  //Object:Transform:Transform Again
#define kAITransformAgainCommandPostNotifierStr                      "AI Command Notifier: After Transform Again"                   //Object:Transform:Transform Again
#define kAIMoveObjectsCommandPreNotifierStr                          "AI Command Notifier: Before Move Objects"                     //Object:Transform:Move
#define kAIMoveObjectsCommandPostNotifierStr                         "AI Command Notifier: After Move Objects"                      //Object:Transform:Move
#define kAITransformRotateCommandPreNotifierStr                      "AI Command Notifier: Before Transform - Rotate"               //Object:Transform:Rotate
#define kAITransformRotateCommandPostNotifierStr                     "AI Command Notifier: After Transform - Rotate"                //Object:Transform:Rotate
#define kAITransformReflectCommandPreNotifierStr                     "AI Command Notifier: Before Transform - Reflect"              //Object:Transform:Reflect
#define kAITransformReflectCommandPostNotifierStr                    "AI Command Notifier: After Transform - Reflect"               //Object:Transform:Reflect
#define kAITransformScaleCommandPreNotifierStr                       "AI Command Notifier: Before Transform - Scale"                //Object:Transform:Scale
#define kAITransformScaleCommandPostNotifierStr                      "AI Command Notifier: After Transform - Scale"                 //Object:Transform:Scale
#define kAITransformShearCommandPreNotifierStr                       "AI Command Notifier: Before Transform - Shear"                //Object:Transform:Shear
#define kAITransformShearCommandPostNotifierStr                      "AI Command Notifier: After Transform - Shear"                 //Object:Transform:Shear
#define kAITransformV23CommandPreNotifierStr                         "AI Command Notifier: Before Transform v23"                    //Object:Transform:Transform Each
#define kAITransformV23CommandPostNotifierStr                        "AI Command Notifier: After Transform v23"                     //Object:Transform:Transform Each
#define kAIAIResetBoundingBoxCommandPreNotifierStr                   "AI Command Notifier: Before AI Reset Bounding Box"            //Object:Transform:Reset Bounding Box
#define kAIAIResetBoundingBoxCommandPostNotifierStr                  "AI Command Notifier: After AI Reset Bounding Box"             //Object:Transform:Reset Bounding Box
#define kAISendToFrontCommandPreNotifierStr                          "AI Command Notifier: Before Send to Front"                    //Object:Arrange:Bring to Front
#define kAISendToFrontCommandPostNotifierStr                         "AI Command Notifier: After Send to Front"                     //Object:Arrange:Bring to Front
#define kAISendForwardCommandPreNotifierStr                          "AI Command Notifier: Before Send Forward"                     //Object:Arrange:Bring Forward
#define kAISendForwardCommandPostNotifierStr                         "AI Command Notifier: After Send Forward"                      //Object:Arrange:Bring Forward
#define kAISendBackwardCommandPreNotifierStr                         "AI Command Notifier: Before Send Backward"                    //Object:Arrange:Send Backward
#define kAISendBackwardCommandPostNotifierStr                        "AI Command Notifier: After Send Backward"                     //Object:Arrange:Send Backward
#define kAISendToBackCommandPreNotifierStr                           "AI Command Notifier: Before Send to Back"                     //Object:Arrange:Send to Back
#define kAISendToBackCommandPostNotifierStr                          "AI Command Notifier: After Send to Back"                      //Object:Arrange:Send to Back
#define kAISelectionHat2CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 2"                  //Object:Arrange:Send to Current Layer
#define kAISelectionHat2CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 2"                   //Object:Arrange:Send to Current Layer
#define kAIGroupCommandPreNotifierStr                                "AI Command Notifier: Before Group"                            //Object:Group
#define kAIGroupCommandPostNotifierStr                               "AI Command Notifier: After Group"                             //Object:Group
#define kAIUngroupCommandPreNotifierStr                              "AI Command Notifier: Before Ungroup"                          //Object:Ungroup
#define kAIUngroupCommandPostNotifierStr                             "AI Command Notifier: After Ungroup"                           //Object:Ungroup
#define kAILockCommandPreNotifierStr                                 "AI Command Notifier: Before Lock"                             //Object:Lock:Selection
#define kAILockCommandPostNotifierStr                                "AI Command Notifier: After Lock"                              //Object:Lock:Selection
#define kAISelectionHat5CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 5"                  //Object:Lock:All Artwork Above
#define kAISelectionHat5CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 5"                   //Object:Lock:All Artwork Above
#define kAISelectionHat7CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 7"                  //Object:Lock:Other Layers
#define kAISelectionHat7CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 7"                   //Object:Lock:Other Layers
#define kAIUnlockAllCommandPreNotifierStr                            "AI Command Notifier: Before Unlock All"                       //Object:Unlock All
#define kAIUnlockAllCommandPostNotifierStr                           "AI Command Notifier: After Unlock All"                        //Object:Unlock All
#define kAIHideCommandPreNotifierStr                                 "AI Command Notifier: Before Hide"                             //Object:Hide:Selection
#define kAIHideCommandPostNotifierStr                                "AI Command Notifier: After Hide"                              //Object:Hide:Selection
#define kAISelectionHat4CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 4"                  //Object:Hide:All Artwork Above
#define kAISelectionHat4CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 4"                   //Object:Hide:All Artwork Above
#define kAISelectionHat6CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 6"                  //Object:Hide:Other Layers
#define kAISelectionHat6CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 6"                   //Object:Hide:Other Layers
#define kAIUnhideAllCommandPreNotifierStr                            "AI Command Notifier: Before Unhide All"                       //Object:Show All
#define kAIUnhideAllCommandPostNotifierStr                           "AI Command Notifier: After Unhide All"                        //Object:Show All
#define kAIExpand3CommandPreNotifierStr                              "AI Command Notifier: Before Expand3"                          //Object:Expand
#define kAIExpand3CommandPostNotifierStr                             "AI Command Notifier: After Expand3"                           //Object:Expand
#define kAIExpandStyleCommandPreNotifierStr                          "AI Command Notifier: Before Expand Style"                     //Object:Expand Appearance
#define kAIExpandStyleCommandPostNotifierStr                         "AI Command Notifier: After Expand Style"                      //Object:Expand Appearance
#define kAIFlattenTransparency1CommandPreNotifierStr                 "AI Command Notifier: Before FlattenTransparency1"             //Object:Flatten Transparency
#define kAIFlattenTransparency1CommandPostNotifierStr                "AI Command Notifier: After FlattenTransparency1"              //Object:Flatten Transparency
#define kAIRasterize8MenuItemCommandPreNotifierStr                   "AI Command Notifier: Before Rasterize 8 menu item"            //Object:Rasterize
#define kAIRasterize8MenuItemCommandPostNotifierStr                  "AI Command Notifier: After Rasterize 8 menu item"             //Object:Rasterize
#define kAIMakeMeshCommandPreNotifierStr                             "AI Command Notifier: Before make mesh"                        //Object:Create Gradient Mesh
#define kAIMakeMeshCommandPostNotifierStr                            "AI Command Notifier: After make mesh"                         //Object:Create Gradient Mesh
#define kAIAIObjectMosaicPlugIn4CommandPreNotifierStr                "AI Command Notifier: Before AI Object Mosaic Plug-in4"        //Object:Create Object Mosaic
#define kAIAIObjectMosaicPlugIn4CommandPostNotifierStr               "AI Command Notifier: After AI Object Mosaic Plug-in4"         //Object:Create Object Mosaic
#define kAITrimMarkV25CommandPreNotifierStr                          "AI Command Notifier: Before TrimMark v25"                     //Object:Create Trim Marks
#define kAITrimMarkV25CommandPostNotifierStr                         "AI Command Notifier: After TrimMark v25"                      //Object:Create Trim Marks
#define kAIAISliceMakeSliceCommandPreNotifierStr                     "AI Command Notifier: Before AISlice Make Slice"               //Object:Slice:Make
#define kAIAISliceMakeSliceCommandPostNotifierStr                    "AI Command Notifier: After AISlice Make Slice"                //Object:Slice:Make
#define kAIAISliceReleaseSliceCommandPreNotifierStr                  "AI Command Notifier: Before AISlice Release Slice"            //Object:Slice:Release
#define kAIAISliceReleaseSliceCommandPostNotifierStr                 "AI Command Notifier: After AISlice Release Slice"             //Object:Slice:Release
#define kAIAISliceCreateFromGuidesCommandPreNotifierStr              "AI Command Notifier: Before AISlice Create from Guides"       //Object:Slice:Create from Guides
#define kAIAISliceCreateFromGuidesCommandPostNotifierStr             "AI Command Notifier: After AISlice Create from Guides"        //Object:Slice:Create from Guides
#define kAIAISliceCreateFromSelectionCommandPreNotifierStr           "AI Command Notifier: Before AISlice Create from Selection"    //Object:Slice:Create from Selection
#define kAIAISliceCreateFromSelectionCommandPostNotifierStr          "AI Command Notifier: After AISlice Create from Selection"     //Object:Slice:Create from Selection
#define kAIAISliceDuplicateCommandPreNotifierStr                     "AI Command Notifier: Before AISlice Duplicate"                //Object:Slice:Duplicate Slice
#define kAIAISliceDuplicateCommandPostNotifierStr                    "AI Command Notifier: After AISlice Duplicate"                 //Object:Slice:Duplicate Slice
#define kAIAISliceCombineCommandPreNotifierStr                       "AI Command Notifier: Before AISlice Combine"                  //Object:Slice:Combine Slices
#define kAIAISliceCombineCommandPostNotifierStr                      "AI Command Notifier: After AISlice Combine"                   //Object:Slice:Combine Slices
#define kAIAISliceDivideCommandPreNotifierStr                        "AI Command Notifier: Before AISlice Divide"                   //Object:Slice:Divide Slices
#define kAIAISliceDivideCommandPostNotifierStr                       "AI Command Notifier: After AISlice Divide"                    //Object:Slice:Divide Slices
#define kAIAISliceDeleteAllSlicesCommandPreNotifierStr               "AI Command Notifier: Before AISlice Delete All Slices"        //Object:Slice:Delete All
#define kAIAISliceDeleteAllSlicesCommandPostNotifierStr              "AI Command Notifier: After AISlice Delete All Slices"         //Object:Slice:Delete All
#define kAIAISliceSliceOptionsCommandPreNotifierStr                  "AI Command Notifier: Before AISlice Slice Options"            //Object:Slice:Slice Options
#define kAIAISliceSliceOptionsCommandPostNotifierStr                 "AI Command Notifier: After AISlice Slice Options"             //Object:Slice:Slice Options
#define kAIAISliceClipToArtboardCommandPreNotifierStr                "AI Command Notifier: Before AISlice Clip to Artboard"         //Object:Slice:Clip to Artboard
#define kAIAISliceClipToArtboardCommandPostNotifierStr               "AI Command Notifier: After AISlice Clip to Artboard"          //Object:Slice:Clip to Artboard
#define kAIJoinCommandPreNotifierStr                                 "AI Command Notifier: Before Join"                             //Object:Path:Join
#define kAIJoinCommandPostNotifierStr                                "AI Command Notifier: After Join"                              //Object:Path:Join
#define kAIAverageCommandPreNotifierStr                              "AI Command Notifier: Before Average"                          //Object:Path:Average
#define kAIAverageCommandPostNotifierStr                             "AI Command Notifier: After Average"                           //Object:Path:Average
#define kAIOffsetPathV22CommandPreNotifierStr                        "AI Command Notifier: Before OffsetPath v22"                   //Object:Path:Outline Stroke
#define kAIOffsetPathV22CommandPostNotifierStr                       "AI Command Notifier: After OffsetPath v22"                    //Object:Path:Outline Stroke
#define kAIOffsetPathV23CommandPreNotifierStr                        "AI Command Notifier: Before OffsetPath v23"                   //Object:Path:Offset Path
#define kAIOffsetPathV23CommandPostNotifierStr                       "AI Command Notifier: After OffsetPath v23"                    //Object:Path:Offset Path
#define kAISimplifyMenuItemCommandPreNotifierStr                     "AI Command Notifier: Before simplify menu item"               //Object:Path:Simplify
#define kAISimplifyMenuItemCommandPostNotifierStr                    "AI Command Notifier: After simplify menu item"                //Object:Path:Simplify
#define kAIAddAnchorPoints2CommandPreNotifierStr                     "AI Command Notifier: Before Add Anchor Points2"               //Object:Path:Add Anchor Points
#define kAIAddAnchorPoints2CommandPostNotifierStr                    "AI Command Notifier: After Add Anchor Points2"                //Object:Path:Add Anchor Points
#define kAIRemoveAnchorPointsMenuCommandPreNotifierStr               "AI Command Notifier: Before Remove Anchor Points menu"        //Object:Path:Remove Anchor Points
#define kAIRemoveAnchorPointsMenuCommandPostNotifierStr              "AI Command Notifier: After Remove Anchor Points menu"         //Object:Path:Remove Anchor Points
#define kAIKnifeTool2CommandPreNotifierStr                           "AI Command Notifier: Before Knife Tool2"                      //Object:Path:Divide Objects Below
#define kAIKnifeTool2CommandPostNotifierStr                          "AI Command Notifier: After Knife Tool2"                       //Object:Path:Divide Objects Below
#define kAIRowsAndColumnsCommandPreNotifierStr                       "AI Command Notifier: Before Rows and Columns...."             //Object:Path:Split Into Grid
#define kAIRowsAndColumnsCommandPostNotifierStr                      "AI Command Notifier: After Rows and Columns...."              //Object:Path:Split Into Grid
#define kAICleanupMenuItemCommandPreNotifierStr                      "AI Command Notifier: Before cleanup menu item"                //Object:Path:Clean Up
#define kAICleanupMenuItemCommandPostNotifierStr                     "AI Command Notifier: After cleanup menu item"                 //Object:Path:Clean Up
#define kAIPathBlendMakeCommandPreNotifierStr                        "AI Command Notifier: Before Path Blend Make"                  //Object:Blend:Make 
#define kAIPathBlendMakeCommandPostNotifierStr                       "AI Command Notifier: After Path Blend Make"                   //Object:Blend:Make 
#define kAIPathBlendReleaseCommandPreNotifierStr                     "AI Command Notifier: Before Path Blend Release"               //Object:Blend:Release 
#define kAIPathBlendReleaseCommandPostNotifierStr                    "AI Command Notifier: After Path Blend Release"                //Object:Blend:Release 
#define kAIPathBlendOptionsCommandPreNotifierStr                     "AI Command Notifier: Before Path Blend Options"               //Object:Blend:Blend Options
#define kAIPathBlendOptionsCommandPostNotifierStr                    "AI Command Notifier: After Path Blend Options"                //Object:Blend:Blend Options
#define kAIPathBlendExpandCommandPreNotifierStr                      "AI Command Notifier: Before Path Blend Expand"                //Object:Blend:Expand
#define kAIPathBlendExpandCommandPostNotifierStr                     "AI Command Notifier: After Path Blend Expand"                 //Object:Blend:Expand
#define kAIPathBlendReplaceSpineCommandPreNotifierStr                "AI Command Notifier: Before Path Blend Replace Spine"         //Object:Blend:Replace Spine
#define kAIPathBlendReplaceSpineCommandPostNotifierStr               "AI Command Notifier: After Path Blend Replace Spine"          //Object:Blend:Replace Spine
#define kAIPathBlendReverseSpineCommandPreNotifierStr                "AI Command Notifier: Before Path Blend Reverse Spine"         //Object:Blend:Reverse Spine
#define kAIPathBlendReverseSpineCommandPostNotifierStr               "AI Command Notifier: After Path Blend Reverse Spine"          //Object:Blend:Reverse Spine
#define kAIPathBlendReverseStackCommandPreNotifierStr                "AI Command Notifier: Before Path Blend Reverse Stack"         //Object:Blend:Reverse Front to Back
#define kAIPathBlendReverseStackCommandPostNotifierStr               "AI Command Notifier: After Path Blend Reverse Stack"          //Object:Blend:Reverse Front to Back
#define kAIMakeWarpCommandPreNotifierStr                             "AI Command Notifier: Before Make Warp"                        //Object:Envelope Distort:Make with Warp
#define kAIMakeWarpCommandPostNotifierStr                            "AI Command Notifier: After Make Warp"                         //Object:Envelope Distort:Make with Warp
#define kAICreateEnvelopeGridCommandPreNotifierStr                   "AI Command Notifier: Before Create Envelope Grid"             //Object:Envelope Distort:Make with Mesh
#define kAICreateEnvelopeGridCommandPostNotifierStr                  "AI Command Notifier: After Create Envelope Grid"              //Object:Envelope Distort:Make with Mesh
#define kAIMakeEnvelopeCommandPreNotifierStr                         "AI Command Notifier: Before Make Envelope"                    //Object:Envelope Distort:Make with Top Object 
#define kAIMakeEnvelopeCommandPostNotifierStr                        "AI Command Notifier: After Make Envelope"                     //Object:Envelope Distort:Make with Top Object 
#define kAIReleaseEnvelopeCommandPreNotifierStr                      "AI Command Notifier: Before Release Envelope"                 //Object:Envelope Distort:Release
#define kAIReleaseEnvelopeCommandPostNotifierStr                     "AI Command Notifier: After Release Envelope"                  //Object:Envelope Distort:Release
#define kAIEnvelopeOptionsCommandPreNotifierStr                      "AI Command Notifier: Before Envelope Options"                 //Object:Envelope Distort:Envelope Options
#define kAIEnvelopeOptionsCommandPostNotifierStr                     "AI Command Notifier: After Envelope Options"                  //Object:Envelope Distort:Envelope Options
#define kAIExpandEnvelopeCommandPreNotifierStr                       "AI Command Notifier: Before Expand Envelope"                  //Object:Envelope Distort:Expand
#define kAIExpandEnvelopeCommandPostNotifierStr                      "AI Command Notifier: After Expand Envelope"                   //Object:Envelope Distort:Expand
#define kAIEditEnvelopeContentsCommandPreNotifierStr                 "AI Command Notifier: Before Edit Envelope Contents"           //Object:Envelope Distort:Edit Contents 
#define kAIEditEnvelopeContentsCommandPostNotifierStr                "AI Command Notifier: After Edit Envelope Contents"            //Object:Envelope Distort:Edit Contents 
#define kAIAttachToActivePlaneCommandPreNotifierStr                  "AI Command Notifier: Before Attach to Active Plane"           //Object:Perspective:Attach to Active Plane
#define kAIAttachToActivePlaneCommandPostNotifierStr                 "AI Command Notifier: After Attach to Active Plane"            //Object:Perspective:Attach to Active Plane
#define kAIReleaseWithPerspectiveCommandPreNotifierStr               "AI Command Notifier: Before Release with Perspective"         //Object:Perspective:Release with Perspective
#define kAIReleaseWithPerspectiveCommandPostNotifierStr              "AI Command Notifier: After Release with Perspective"          //Object:Perspective:Release with Perspective
#define kAIShowObjectGridPlaneCommandPreNotifierStr                  "AI Command Notifier: Before Show Object Grid Plane"           //Object:Perspective:Move Plane to Match Object
#define kAIShowObjectGridPlaneCommandPostNotifierStr                 "AI Command Notifier: After Show Object Grid Plane"            //Object:Perspective:Move Plane to Match Object
#define kAIEditOriginalObjectCommandPreNotifierStr                   "AI Command Notifier: Before Edit Original Object"             //Object:Perspective:Edit Text
#define kAIEditOriginalObjectCommandPostNotifierStr                  "AI Command Notifier: After Edit Original Object"              //Object:Perspective:Edit Text
#define kAIMakePlanetXCommandPreNotifierStr                          "AI Command Notifier: Before Make Planet X"                    //Object:Live Paint:Make 
#define kAIMakePlanetXCommandPostNotifierStr                         "AI Command Notifier: After Make Planet X"                     //Object:Live Paint:Make 
#define kAIMargePlanetXCommandPreNotifierStr                         "AI Command Notifier: Before Marge Planet X"                   //Object:Live Paint:Merge
#define kAIMargePlanetXCommandPostNotifierStr                        "AI Command Notifier: After Marge Planet X"                    //Object:Live Paint:Merge
#define kAIReleasePlanetXCommandPreNotifierStr                       "AI Command Notifier: Before Release Planet X"                 //Object:Live Paint:Release
#define kAIReleasePlanetXCommandPostNotifierStr                      "AI Command Notifier: After Release Planet X"                  //Object:Live Paint:Release
#define kAIPlanetXOptionsCommandPreNotifierStr                       "AI Command Notifier: Before Planet X Options"                 //Object:Live Paint:Gap Options
#define kAIPlanetXOptionsCommandPostNotifierStr                      "AI Command Notifier: After Planet X Options"                  //Object:Live Paint:Gap Options
#define kAIExpandPlanetXCommandPreNotifierStr                        "AI Command Notifier: Before Expand Planet X"                  //Object:Live Paint:Expand
#define kAIExpandPlanetXCommandPostNotifierStr                       "AI Command Notifier: After Expand Planet X"                   //Object:Live Paint:Expand
#define kAIMakeTracingCommandPreNotifierStr                          "AI Command Notifier: Before Make Tracing"                     //Object:Live Trace:Make
#define kAIMakeTracingCommandPostNotifierStr                         "AI Command Notifier: After Make Tracing"                      //Object:Live Trace:Make
#define kAIMakeAndExpandCommandPreNotifierStr                        "AI Command Notifier: Before Make and Expand"                  //Object:Live Trace:Make and Expand
#define kAIMakeAndExpandCommandPostNotifierStr                       "AI Command Notifier: After Make and Expand"                   //Object:Live Trace:Make and Expand
#define kAIMakeAndConvertToLivePaintCommandPreNotifierStr            "AI Command Notifier: Before Make and Convert to Live Paint"   //Object:Live Trace:Make and Convert to Live Paint
#define kAIMakeAndConvertToLivePaintCommandPostNotifierStr           "AI Command Notifier: After Make and Convert to Live Paint"    //Object:Live Trace:Make and Convert to Live Paint
#define kAIReleaseTracingCommandPreNotifierStr                       "AI Command Notifier: Before Release Tracing"                  //Object:Live Trace:Release
#define kAIReleaseTracingCommandPostNotifierStr                      "AI Command Notifier: After Release Tracing"                   //Object:Live Trace:Release
#define kAITracingOptionsCommandPreNotifierStr                       "AI Command Notifier: Before Tracing Options"                  //Object:Live Trace:Tracing Options
#define kAITracingOptionsCommandPostNotifierStr                      "AI Command Notifier: After Tracing Options"                   //Object:Live Trace:Tracing Options
#define kAIExpandTracingCommandPreNotifierStr                        "AI Command Notifier: Before Expand Tracing"                   //Object:Live Trace:Expand
#define kAIExpandTracingCommandPostNotifierStr                       "AI Command Notifier: After Expand Tracing"                    //Object:Live Trace:Expand
#define kAIExpandAsViewedCommandPreNotifierStr                       "AI Command Notifier: Before Expand as Viewed"                 //Object:Live Trace:Expand as Viewed
#define kAIExpandAsViewedCommandPostNotifierStr                      "AI Command Notifier: After Expand as Viewed"                  //Object:Live Trace:Expand as Viewed
#define kAIPaintTracingCommandPreNotifierStr                         "AI Command Notifier: Before Paint Tracing"                    //Object:Live Trace:Convert to Live Paint
#define kAIPaintTracingCommandPostNotifierStr                        "AI Command Notifier: After Paint Tracing"                     //Object:Live Trace:Convert to Live Paint
#define kAIShowNoImageCommandPreNotifierStr                          "AI Command Notifier: Before ShowNoImage"                      //Object:Live Trace:Show No Image
#define kAIShowNoImageCommandPostNotifierStr                         "AI Command Notifier: After ShowNoImage"                       //Object:Live Trace:Show No Image
#define kAIShowOriginalImageCommandPreNotifierStr                    "AI Command Notifier: Before ShowOriginalImage"                //Object:Live Trace:Show Original Image
#define kAIShowOriginalImageCommandPostNotifierStr                   "AI Command Notifier: After ShowOriginalImage"                 //Object:Live Trace:Show Original Image
#define kAIShowPreprocessedImageCommandPreNotifierStr                "AI Command Notifier: Before Show Preprocessed Image"          //Object:Live Trace:Show Adjusted Image
#define kAIShowPreprocessedImageCommandPostNotifierStr               "AI Command Notifier: After Show Preprocessed Image"           //Object:Live Trace:Show Adjusted Image
#define kAIShowTransparentImageCommandPreNotifierStr                 "AI Command Notifier: Before ShowTransparentImage"             //Object:Live Trace:Show Transparent Image
#define kAIShowTransparentImageCommandPostNotifierStr                "AI Command Notifier: After ShowTransparentImage"              //Object:Live Trace:Show Transparent Image
#define kAIShowNoArtworkCommandPreNotifierStr                        "AI Command Notifier: Before ShowNoArtwork"                    //Object:Live Trace:Show No Tracing Result
#define kAIShowNoArtworkCommandPostNotifierStr                       "AI Command Notifier: After ShowNoArtwork"                     //Object:Live Trace:Show No Tracing Result
#define kAIShowArtworkCommandPreNotifierStr                          "AI Command Notifier: Before ShowArtwork"                      //Object:Live Trace:Show Tracing Result
#define kAIShowArtworkCommandPostNotifierStr                         "AI Command Notifier: After ShowArtwork"                       //Object:Live Trace:Show Tracing Result
#define kAIShowPathsCommandPreNotifierStr                            "AI Command Notifier: Before ShowPaths"                        //Object:Live Trace:Show Outlines
#define kAIShowPathsCommandPostNotifierStr                           "AI Command Notifier: After ShowPaths"                         //Object:Live Trace:Show Outlines
#define kAIShowPathsAndTransparentArtworkCommandPreNotifierStr       "AI Command Notifier: Before ShowPathsAndTransparentArtwork"   //Object:Live Trace:Show Outlines with Tracing
#define kAIShowPathsAndTransparentArtworkCommandPostNotifierStr      "AI Command Notifier: After ShowPathsAndTransparentArtwork"    //Object:Live Trace:Show Outlines with Tracing
#define kAIMakeTextWrapCommandPreNotifierStr                         "AI Command Notifier: Before Make Text Wrap"                   //Object:Text Wrap:Make
#define kAIMakeTextWrapCommandPostNotifierStr                        "AI Command Notifier: After Make Text Wrap"                    //Object:Text Wrap:Make
#define kAIReleaseTextWrapCommandPreNotifierStr                      "AI Command Notifier: Before Release Text Wrap"                //Object:Text Wrap:Release
#define kAIReleaseTextWrapCommandPostNotifierStr                     "AI Command Notifier: After Release Text Wrap"                 //Object:Text Wrap:Release
#define kAITextWrapOptionsCommandPreNotifierStr                      "AI Command Notifier: Before Text Wrap Options..."             //Object:Text Wrap:Text Wrap Options
#define kAITextWrapOptionsCommandPostNotifierStr                     "AI Command Notifier: After Text Wrap Options..."              //Object:Text Wrap:Text Wrap Options
#define kAIMakeMaskCommandPreNotifierStr                             "AI Command Notifier: Before Make Mask"                        //Object:Clipping Mask:Make
#define kAIMakeMaskCommandPostNotifierStr                            "AI Command Notifier: After Make Mask"                         //Object:Clipping Mask:Make
#define kAIReleaseMaskCommandPreNotifierStr                          "AI Command Notifier: Before Release Mask"                     //Object:Clipping Mask:Release
#define kAIReleaseMaskCommandPostNotifierStr                         "AI Command Notifier: After Release Mask"                      //Object:Clipping Mask:Release
#define kAIEditMaskCommandPreNotifierStr                             "AI Command Notifier: Before Edit Mask"                        //Object:Clipping Mask:Edit Contents
#define kAIEditMaskCommandPostNotifierStr                            "AI Command Notifier: After Edit Mask"                         //Object:Clipping Mask:Edit Contents
#define kAIMakeCompoundPathCommandPreNotifierStr                     "AI Command Notifier: Before Make Compound Path"               //Object:Compound Path:Make
#define kAIMakeCompoundPathCommandPostNotifierStr                    "AI Command Notifier: After Make Compound Path"                //Object:Compound Path:Make
#define kAIReleaseCompoundPathCommandPreNotifierStr                  "AI Command Notifier: Before Release Compound Path"            //Object:Compound Path:Release
#define kAIReleaseCompoundPathCommandPostNotifierStr                 "AI Command Notifier: After Release Compound Path"             //Object:Compound Path:Release
#define kAIMakeCropMarksCommandPreNotifierStr                        "AI Command Notifier: Before Make Crop Marks"                  //Object:Artboards:Convert to Artboards
#define kAIMakeCropMarksCommandPostNotifierStr                       "AI Command Notifier: After Make Crop Marks"                   //Object:Artboards:Convert to Artboards
#define kAIReArrangeArtboardsCommandPreNotifierStr                   "AI Command Notifier: Before ReArrange Artboards"              //Object:Artboards:Rearrange
#define kAIReArrangeArtboardsCommandPostNotifierStr                  "AI Command Notifier: After ReArrange Artboards"               //Object:Artboards:Rearrange
#define kAIFitArtboardToArtworkBoundsCommandPreNotifierStr           "AI Command Notifier: Before Fit Artboard to artwork bounds"   //Object:Artboards:Fit to Artwork Bounds
#define kAIFitArtboardToArtworkBoundsCommandPostNotifierStr          "AI Command Notifier: After Fit Artboard to artwork bounds"    //Object:Artboards:Fit to Artwork Bounds
#define kAIFitArtboardToSelectedArtCommandPreNotifierStr             "AI Command Notifier: Before Fit Artboard to selected Art"     //Object:Artboards:Fit to Selected Art
#define kAIFitArtboardToSelectedArtCommandPostNotifierStr            "AI Command Notifier: After Fit Artboard to selected Art"      //Object:Artboards:Fit to Selected Art
#define kAISetGraphStyleCommandPreNotifierStr                        "AI Command Notifier: Before Set Graph Style"                  //Object:Graph:Type
#define kAISetGraphStyleCommandPostNotifierStr                       "AI Command Notifier: After Set Graph Style"                   //Object:Graph:Type
#define kAIEditGraphDataCommandPreNotifierStr                        "AI Command Notifier: Before Edit Graph Data"                  //Object:Graph:Data
#define kAIEditGraphDataCommandPostNotifierStr                       "AI Command Notifier: After Edit Graph Data"                   //Object:Graph:Data
#define kAIDefineGraphDesignCommandPreNotifierStr                    "AI Command Notifier: Before Define Graph Design"              //Object:Graph:Design
#define kAIDefineGraphDesignCommandPostNotifierStr                   "AI Command Notifier: After Define Graph Design"               //Object:Graph:Design
#define kAISetBarDesignCommandPreNotifierStr                         "AI Command Notifier: Before Set Bar Design"                   //Object:Graph:Column
#define kAISetBarDesignCommandPostNotifierStr                        "AI Command Notifier: After Set Bar Design"                    //Object:Graph:Column
#define kAISetIconDesignCommandPreNotifierStr                        "AI Command Notifier: Before Set Icon Design"                  //Object:Graph:Marker
#define kAISetIconDesignCommandPostNotifierStr                       "AI Command Notifier: After Set Icon Design"                   //Object:Graph:Marker
#define kAIAlternateGlyphPalettePluginCommandPreNotifierStr          "AI Command Notifier: Before alternate glyph palette plugin"   //Type:Glyphs
#define kAIAlternateGlyphPalettePluginCommandPostNotifierStr         "AI Command Notifier: After alternate glyph palette plugin"    //Type:Glyphs
#define kAIAreaTextOptionsCommandPreNotifierStr                      "AI Command Notifier: Before Area Text Options"                //Type:Area Type Options
#define kAIAreaTextOptionsCommandPostNotifierStr                     "AI Command Notifier: After Area Text Options"                 //Type:Area Type Options
#define kAITextPathTypeRainbowCommandPreNotifierStr                  "AI Command Notifier: Before Text Path Type Rainbow"           //Type:Type on a Path:Rainbow
#define kAITextPathTypeRainbowCommandPostNotifierStr                 "AI Command Notifier: After Text Path Type Rainbow"            //Type:Type on a Path:Rainbow
#define kAITextPathTypeSkewCommandPreNotifierStr                     "AI Command Notifier: Before Text Path Type Skew"              //Type:Type on a Path:Skew
#define kAITextPathTypeSkewCommandPostNotifierStr                    "AI Command Notifier: After Text Path Type Skew"               //Type:Type on a Path:Skew
#define kAITextPathType3dCommandPreNotifierStr                       "AI Command Notifier: Before Text Path Type 3d"                //Type:Type on a Path:3D Ribbon
#define kAITextPathType3dCommandPostNotifierStr                      "AI Command Notifier: After Text Path Type 3d"                 //Type:Type on a Path:3D Ribbon
#define kAITextPathTypeStairsCommandPreNotifierStr                   "AI Command Notifier: Before Text Path Type Stairs"            //Type:Type on a Path:Stair Step
#define kAITextPathTypeStairsCommandPostNotifierStr                  "AI Command Notifier: After Text Path Type Stairs"             //Type:Type on a Path:Stair Step
#define kAITextPathTypeGravityCommandPreNotifierStr                  "AI Command Notifier: Before Text Path Type Gravity"           //Type:Type on a Path:Gravity
#define kAITextPathTypeGravityCommandPostNotifierStr                 "AI Command Notifier: After Text Path Type Gravity"            //Type:Type on a Path:Gravity
#define kAITextPathTypeOptionsCommandPreNotifierStr                  "AI Command Notifier: Before Text Path Type Options"           //Type:Type on a Path:Type on a Path Options
#define kAITextPathTypeOptionsCommandPostNotifierStr                 "AI Command Notifier: After Text Path Type Options"            //Type:Type on a Path:Type on a Path Options
#define kAIUpdateSelectedTypeOnPathCommandPreNotifierStr             "AI Command Notifier: Before Update Selected Type On Path"     //Type:Type on a Path:Update Legacy Type on a Path
#define kAIUpdateSelectedTypeOnPathCommandPostNotifierStr            "AI Command Notifier: After Update Selected Type On Path"      //Type:Type on a Path:Update Legacy Type on a Path
#define kAICreateThreadedTextCommandPreNotifierStr                   "AI Command Notifier: Before Create Threaded Text"             //Type:Threaded Text:Create
#define kAICreateThreadedTextCommandPostNotifierStr                  "AI Command Notifier: After Create Threaded Text"              //Type:Threaded Text:Create
#define kAIReleaseThreadedTextSelectionCommandPreNotifierStr         "AI Command Notifier: Before Release Threaded Text Selection"  //Type:Threaded Text:Release Selection
#define kAIReleaseThreadedTextSelectionCommandPostNotifierStr        "AI Command Notifier: After Release Threaded Text Selection"   //Type:Threaded Text:Release Selection
#define kAIRemoveThreadingCommandPreNotifierStr                      "AI Command Notifier: Before Remove Threading"                 //Type:Threaded Text:Remove Threading
#define kAIRemoveThreadingCommandPostNotifierStr                     "AI Command Notifier: After Remove Threading"                  //Type:Threaded Text:Remove Threading
#define kAIAdobeInternalCompositeFontPluginCommandPreNotifierStr     "AI Command Notifier: Before Adobe internal composite font plugin" //Type:Composite Fonts
#define kAIAdobeInternalCompositeFontPluginCommandPostNotifierStr    "AI Command Notifier: After Adobe internal composite font plugin" //Type:Composite Fonts
#define kAIAdobeKinsokuSettingsCommandPreNotifierStr                 "AI Command Notifier: Before Adobe Kinsoku Settings"           //Type:Kinsoku Shori Settings
#define kAIAdobeKinsokuSettingsCommandPostNotifierStr                "AI Command Notifier: After Adobe Kinsoku Settings"            //Type:Kinsoku Shori Settings
#define kAIAdobeMojiKumiSettingsCommandPreNotifierStr                "AI Command Notifier: Before Adobe MojiKumi Settings"          //Type:Mojikumi Settings
#define kAIAdobeMojiKumiSettingsCommandPostNotifierStr               "AI Command Notifier: After Adobe MojiKumi Settings"           //Type:Mojikumi Settings
#define kAIFitHeadlineCommandPreNotifierStr                          "AI Command Notifier: Before Fit Headline"                     //Type:Fit Headline
#define kAIFitHeadlineCommandPostNotifierStr                         "AI Command Notifier: After Fit Headline"                      //Type:Fit Headline
#define kAITypeOutlinesCommandPreNotifierStr                         "AI Command Notifier: Before Type Outlines"                    //Type:Create Outlines
#define kAITypeOutlinesCommandPostNotifierStr                        "AI Command Notifier: After Type Outlines"                     //Type:Create Outlines
#define kAIAdobeIllustratorFindFontMenuItemCommandPreNotifierStr     "AI Command Notifier: Before Adobe Illustrator Find Font Menu Item" //Type:Find Font
#define kAIAdobeIllustratorFindFontMenuItemCommandPostNotifierStr    "AI Command Notifier: After Adobe Illustrator Find Font Menu Item" //Type:Find Font
#define kAIUpperCaseChangeCaseItemCommandPreNotifierStr              "AI Command Notifier: Before UpperCase Change Case Item"       //Type:Change Case:UPPERCASE
#define kAIUpperCaseChangeCaseItemCommandPostNotifierStr             "AI Command Notifier: After UpperCase Change Case Item"        //Type:Change Case:UPPERCASE
#define kAILowerCaseChangeCaseItemCommandPreNotifierStr              "AI Command Notifier: Before LowerCase Change Case Item"       //Type:Change Case:lowercase
#define kAILowerCaseChangeCaseItemCommandPostNotifierStr             "AI Command Notifier: After LowerCase Change Case Item"        //Type:Change Case:lowercase
#define kAITitleCaseChangeCaseItemCommandPreNotifierStr              "AI Command Notifier: Before Title Case Change Case Item"      //Type:Change Case:Title Case
#define kAITitleCaseChangeCaseItemCommandPostNotifierStr             "AI Command Notifier: After Title Case Change Case Item"       //Type:Change Case:Title Case
#define kAISentenceCaseChangeCaseItemCommandPreNotifierStr           "AI Command Notifier: Before Sentence case Change Case Item"   //Type:Change Case:Sentence case
#define kAISentenceCaseChangeCaseItemCommandPostNotifierStr          "AI Command Notifier: After Sentence case Change Case Item"    //Type:Change Case:Sentence case
#define kAIAdobeIllustratorSmartPunctuationMenuItemCommandPreNotifierStr "AI Command Notifier: Before Adobe Illustrator Smart Punctuation Menu Item" //Type:Smart Punctuation
#define kAIAdobeIllustratorSmartPunctuationMenuItemCommandPostNotifierStr "AI Command Notifier: After Adobe Illustrator Smart Punctuation Menu Item" //Type:Smart Punctuation
#define kAIAdobeOpticalAlignmentItemCommandPreNotifierStr            "AI Command Notifier: Before Adobe Optical Alignment Item"     //Type:Optical Margin Alignment
#define kAIAdobeOpticalAlignmentItemCommandPostNotifierStr           "AI Command Notifier: After Adobe Optical Alignment Item"      //Type:Optical Margin Alignment
#define kAIShowHiddenCharactersCommandPreNotifierStr                 "AI Command Notifier: Before Show Hidden Characters"           //Type:Show Hidden Characters
#define kAIShowHiddenCharactersCommandPostNotifierStr                "AI Command Notifier: After Show Hidden Characters"            //Type:Show Hidden Characters
#define kAITypeOrientationHorizontalCommandPreNotifierStr            "AI Command Notifier: Before Type Orientation Horizontal"      //Type:Type Orientation:Horizontal
#define kAITypeOrientationHorizontalCommandPostNotifierStr           "AI Command Notifier: After Type Orientation Horizontal"       //Type:Type Orientation:Horizontal
#define kAITypeOrientationVerticalCommandPreNotifierStr              "AI Command Notifier: Before Type Orientation Vertical"        //Type:Type Orientation:Vertical
#define kAITypeOrientationVerticalCommandPostNotifierStr             "AI Command Notifier: After Type Orientation Vertical"         //Type:Type Orientation:Vertical
#define kAIConvertToNativeTextCommandPreNotifierStr                  "AI Command Notifier: Before Convert To Native Text"           //Type:Legacy Text:Update All Legacy Text
#define kAIConvertToNativeTextCommandPostNotifierStr                 "AI Command Notifier: After Convert To Native Text"            //Type:Legacy Text:Update All Legacy Text
#define kAIConvertSelectedTextToNativeTextCommandPreNotifierStr      "AI Command Notifier: Before Convert Selected Text To Native Text" //Type:Legacy Text:Update Selected Legacy Text
#define kAIConvertSelectedTextToNativeTextCommandPostNotifierStr     "AI Command Notifier: After Convert Selected Text To Native Text" //Type:Legacy Text:Update Selected Legacy Text
#define kAIShowHideLegacyTextCopiesCommandPreNotifierStr             "AI Command Notifier: Before Show/Hide Legacy Text Copies"     //Type:Legacy Text:Hide Copies
#define kAIShowHideLegacyTextCopiesCommandPostNotifierStr            "AI Command Notifier: After Show/Hide Legacy Text Copies"      //Type:Legacy Text:Hide Copies
#define kAIDeleteLegacyTextCopiesCommandPreNotifierStr               "AI Command Notifier: Before Delete Legacy Text Copies"        //Type:Legacy Text:Delete Copies
#define kAIDeleteLegacyTextCopiesCommandPostNotifierStr              "AI Command Notifier: After Delete Legacy Text Copies"         //Type:Legacy Text:Delete Copies
#define kAISelectLegacyTextCopiesCommandPreNotifierStr               "AI Command Notifier: Before Select Legacy Text Copies"        //Type:Legacy Text:Select Copies
#define kAISelectLegacyTextCopiesCommandPostNotifierStr              "AI Command Notifier: After Select Legacy Text Copies"         //Type:Legacy Text:Select Copies
#define kAISelectAllCommandPreNotifierStr                            "AI Command Notifier: Before Select All"                       //Select:All
#define kAISelectAllCommandPostNotifierStr                           "AI Command Notifier: After Select All"                        //Select:All
#define kAISelectAllInArtboardCommandPreNotifierStr                  "AI Command Notifier: Before Select All In Artboard"           //Select:All on Active Artboard
#define kAISelectAllInArtboardCommandPostNotifierStr                 "AI Command Notifier: After Select All In Artboard"            //Select:All on Active Artboard
#define kAIDeselectAllCommandPreNotifierStr                          "AI Command Notifier: Before Deselect All"                     //Select:Deselect
#define kAIDeselectAllCommandPostNotifierStr                         "AI Command Notifier: After Deselect All"                      //Select:Deselect
#define kAIFindReselectMenuItemCommandPreNotifierStr                 "AI Command Notifier: Before Find Reselect menu item"          //Select:Reselect 
#define kAIFindReselectMenuItemCommandPostNotifierStr                "AI Command Notifier: After Find Reselect menu item"           //Select:Reselect 
#define kAIInverseMenuItemCommandPreNotifierStr                      "AI Command Notifier: Before Inverse menu item"                //Select:Inverse
#define kAIInverseMenuItemCommandPostNotifierStr                     "AI Command Notifier: After Inverse menu item"                 //Select:Inverse
#define kAISelectionHat8CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 8"                  //Select:Next Object Above 
#define kAISelectionHat8CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 8"                   //Select:Next Object Above 
#define kAISelectionHat9CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 9"                  //Select:Next Object Below 
#define kAISelectionHat9CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 9"                   //Select:Next Object Below 
#define kAIFindAppearanceMenuItemCommandPreNotifierStr               "AI Command Notifier: Before Find Appearance menu item"        //Select:Same:Appearance
#define kAIFindAppearanceMenuItemCommandPostNotifierStr              "AI Command Notifier: After Find Appearance menu item"         //Select:Same:Appearance
#define kAIFindAppearanceAttributesMenuItemCommandPreNotifierStr     "AI Command Notifier: Before Find Appearance Attributes menu item" //Select:Same:Appearance Attribute
#define kAIFindAppearanceAttributesMenuItemCommandPostNotifierStr    "AI Command Notifier: After Find Appearance Attributes menu item" //Select:Same:Appearance Attribute
#define kAIFindBlendingModeMenuItemCommandPreNotifierStr             "AI Command Notifier: Before Find Blending Mode menu item"     //Select:Same:Blending Mode
#define kAIFindBlendingModeMenuItemCommandPostNotifierStr            "AI Command Notifier: After Find Blending Mode menu item"      //Select:Same:Blending Mode
#define kAIFindFillStrokeMenuItemCommandPreNotifierStr               "AI Command Notifier: Before Find Fill & Stroke menu item"     //Select:Same:Fill & Stroke
#define kAIFindFillStrokeMenuItemCommandPostNotifierStr              "AI Command Notifier: After Find Fill & Stroke menu item"      //Select:Same:Fill & Stroke
#define kAIFindFillColorMenuItemCommandPreNotifierStr                "AI Command Notifier: Before Find Fill Color menu item"        //Select:Same:Fill Color
#define kAIFindFillColorMenuItemCommandPostNotifierStr               "AI Command Notifier: After Find Fill Color menu item"         //Select:Same:Fill Color
#define kAIFindOpacityMenuItemCommandPreNotifierStr                  "AI Command Notifier: Before Find Opacity menu item"           //Select:Same:Opacity
#define kAIFindOpacityMenuItemCommandPostNotifierStr                 "AI Command Notifier: After Find Opacity menu item"            //Select:Same:Opacity
#define kAIFindStrokeColorMenuItemCommandPreNotifierStr              "AI Command Notifier: Before Find Stroke Color menu item"      //Select:Same:Stroke Color
#define kAIFindStrokeColorMenuItemCommandPostNotifierStr             "AI Command Notifier: After Find Stroke Color menu item"       //Select:Same:Stroke Color
#define kAIFindStrokeWeightMenuItemCommandPreNotifierStr             "AI Command Notifier: Before Find Stroke Weight menu item"     //Select:Same:Stroke Weight
#define kAIFindStrokeWeightMenuItemCommandPostNotifierStr            "AI Command Notifier: After Find Stroke Weight menu item"      //Select:Same:Stroke Weight
#define kAIFindStyleMenuItemCommandPreNotifierStr                    "AI Command Notifier: Before Find Style menu item"             //Select:Same:Graphic Style
#define kAIFindStyleMenuItemCommandPostNotifierStr                   "AI Command Notifier: After Find Style menu item"              //Select:Same:Graphic Style
#define kAIFindSymbolInstanceMenuItemCommandPreNotifierStr           "AI Command Notifier: Before Find Symbol Instance menu item"   //Select:Same:Symbol Instance
#define kAIFindSymbolInstanceMenuItemCommandPostNotifierStr          "AI Command Notifier: After Find Symbol Instance menu item"    //Select:Same:Symbol Instance
#define kAIFindLinkBlockSeriesMenuItemCommandPreNotifierStr          "AI Command Notifier: Before Find Link Block Series menu item" //Select:Same:Link Block Series
#define kAIFindLinkBlockSeriesMenuItemCommandPostNotifierStr         "AI Command Notifier: After Find Link Block Series menu item"  //Select:Same:Link Block Series
#define kAISelectionHat3CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 3"                  //Select:Object:All on Same Layers
#define kAISelectionHat3CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 3"                   //Select:Object:All on Same Layers
#define kAISelectionHat1CommandPreNotifierStr                        "AI Command Notifier: Before Selection Hat 1"                  //Select:Object:Direction Handles
#define kAISelectionHat1CommandPostNotifierStr                       "AI Command Notifier: After Selection Hat 1"                   //Select:Object:Direction Handles
#define kAISelectionHat12CommandPreNotifierStr                       "AI Command Notifier: Before Selection Hat 12"                 //Select:Object:Not Aligned to Pixel Grid
#define kAISelectionHat12CommandPostNotifierStr                      "AI Command Notifier: After Selection Hat 12"                  //Select:Object:Not Aligned to Pixel Grid
#define kAIBristleBrushStrokesMenuItemCommandPreNotifierStr          "AI Command Notifier: Before Bristle Brush Strokes menu item"  //Select:Object:Bristle Brush Strokes
#define kAIBristleBrushStrokesMenuItemCommandPostNotifierStr         "AI Command Notifier: After Bristle Brush Strokes menu item"   //Select:Object:Bristle Brush Strokes
#define kAIBrushStrokesMenuItemCommandPreNotifierStr                 "AI Command Notifier: Before Brush Strokes menu item"          //Select:Object:Brush Strokes
#define kAIBrushStrokesMenuItemCommandPostNotifierStr                "AI Command Notifier: After Brush Strokes menu item"           //Select:Object:Brush Strokes
#define kAIClippingMasksMenuItemCommandPreNotifierStr                "AI Command Notifier: Before Clipping Masks menu item"         //Select:Object:Clipping Masks
#define kAIClippingMasksMenuItemCommandPostNotifierStr               "AI Command Notifier: After Clipping Masks menu item"          //Select:Object:Clipping Masks
#define kAIStrayPointsMenuItemCommandPreNotifierStr                  "AI Command Notifier: Before Stray Points menu item"           //Select:Object:Stray Points
#define kAIStrayPointsMenuItemCommandPostNotifierStr                 "AI Command Notifier: After Stray Points menu item"            //Select:Object:Stray Points
#define kAITextObjectsMenuItemCommandPreNotifierStr                  "AI Command Notifier: Before Text Objects menu item"           //Select:Object:Text Objects
#define kAITextObjectsMenuItemCommandPostNotifierStr                 "AI Command Notifier: After Text Objects menu item"            //Select:Object:Text Objects
#define kAIDynamicTextCommandPreNotifierStr                          "AI Command Notifier: Before Dynamic Text"                     //Select:Object:Flash Dynamic Text
#define kAIDynamicTextCommandPostNotifierStr                         "AI Command Notifier: After Dynamic Text"                      //Select:Object:Flash Dynamic Text
#define kAIInputTextCommandPreNotifierStr                            "AI Command Notifier: Before Input Text"                       //Select:Object:Flash Input Text
#define kAIInputTextCommandPostNotifierStr                           "AI Command Notifier: After Input Text"                        //Select:Object:Flash Input Text
#define kAISelectionHat10CommandPreNotifierStr                       "AI Command Notifier: Before Selection Hat 10"                 //Select:Save Selection
#define kAISelectionHat10CommandPostNotifierStr                      "AI Command Notifier: After Selection Hat 10"                  //Select:Save Selection
#define kAISelectionHat11CommandPreNotifierStr                       "AI Command Notifier: Before Selection Hat 11"                 //Select:Edit Selection
#define kAISelectionHat11CommandPostNotifierStr                      "AI Command Notifier: After Selection Hat 11"                  //Select:Edit Selection
#define kAIAdobeApplyLastEffectCommandPreNotifierStr                 "AI Command Notifier: Before Adobe Apply Last Effect"          //Effect:Apply Last Effect 
#define kAIAdobeApplyLastEffectCommandPostNotifierStr                "AI Command Notifier: After Adobe Apply Last Effect"           //Effect:Apply Last Effect 
#define kAIAdobeLastEffectCommandPreNotifierStr                      "AI Command Notifier: Before Adobe Last Effect"                //Effect:Last Effect 
#define kAIAdobeLastEffectCommandPostNotifierStr                     "AI Command Notifier: After Adobe Last Effect"                 //Effect:Last Effect 
#define kAILiveRasterizeEffectSettingCommandPreNotifierStr           "AI Command Notifier: Before Live Rasterize Effect Setting"    //Effect:Document Raster Effects Settings
#define kAILiveRasterizeEffectSettingCommandPostNotifierStr          "AI Command Notifier: After Live Rasterize Effect Setting"     //Effect:Document Raster Effects Settings
#define kAILive3DExtrudeCommandPreNotifierStr                        "AI Command Notifier: Before Live 3DExtrude"                   //Effect:3D:Extrude & Bevel
#define kAILive3DExtrudeCommandPostNotifierStr                       "AI Command Notifier: After Live 3DExtrude"                    //Effect:3D:Extrude & Bevel
#define kAILive3DRevolveCommandPreNotifierStr                        "AI Command Notifier: Before Live 3DRevolve"                   //Effect:3D:Revolve
#define kAILive3DRevolveCommandPostNotifierStr                       "AI Command Notifier: After Live 3DRevolve"                    //Effect:3D:Revolve
#define kAILive3DRotateCommandPreNotifierStr                         "AI Command Notifier: Before Live 3DRotate"                    //Effect:3D:Rotate
#define kAILive3DRotateCommandPostNotifierStr                        "AI Command Notifier: After Live 3DRotate"                     //Effect:3D:Rotate
#define kAILiveRectangleCommandPreNotifierStr                        "AI Command Notifier: Before Live Rectangle"                   //Effect:Convert to Shape:Rectangle
#define kAILiveRectangleCommandPostNotifierStr                       "AI Command Notifier: After Live Rectangle"                    //Effect:Convert to Shape:Rectangle
#define kAILiveRoundedRectangleCommandPreNotifierStr                 "AI Command Notifier: Before Live Rounded Rectangle"           //Effect:Convert to Shape:Rounded Rectangle
#define kAILiveRoundedRectangleCommandPostNotifierStr                "AI Command Notifier: After Live Rounded Rectangle"            //Effect:Convert to Shape:Rounded Rectangle
#define kAILiveEllipseCommandPreNotifierStr                          "AI Command Notifier: Before Live Ellipse"                     //Effect:Convert to Shape:Ellipse
#define kAILiveEllipseCommandPostNotifierStr                         "AI Command Notifier: After Live Ellipse"                      //Effect:Convert to Shape:Ellipse
#define kAILiveTrimMarksCommandPreNotifierStr                        "AI Command Notifier: Before Live Trim Marks"                  //Effect:Crop Marks
#define kAILiveTrimMarksCommandPostNotifierStr                       "AI Command Notifier: After Live Trim Marks"                   //Effect:Crop Marks
#define kAILiveFreeDistortCommandPreNotifierStr                      "AI Command Notifier: Before Live Free Distort"                //Effect:Distort & Transform:Free Distort
#define kAILiveFreeDistortCommandPostNotifierStr                     "AI Command Notifier: After Live Free Distort"                 //Effect:Distort & Transform:Free Distort
#define kAILivePuckerBloatCommandPreNotifierStr                      "AI Command Notifier: Before Live Pucker & Bloat"              //Effect:Distort & Transform:Pucker & Bloat
#define kAILivePuckerBloatCommandPostNotifierStr                     "AI Command Notifier: After Live Pucker & Bloat"               //Effect:Distort & Transform:Pucker & Bloat
#define kAILiveRoughenCommandPreNotifierStr                          "AI Command Notifier: Before Live Roughen"                     //Effect:Distort & Transform:Roughen
#define kAILiveRoughenCommandPostNotifierStr                         "AI Command Notifier: After Live Roughen"                      //Effect:Distort & Transform:Roughen
#define kAILiveTransformCommandPreNotifierStr                        "AI Command Notifier: Before Live Transform"                   //Effect:Distort & Transform:Transform
#define kAILiveTransformCommandPostNotifierStr                       "AI Command Notifier: After Live Transform"                    //Effect:Distort & Transform:Transform
#define kAILiveScribbleAndTweakCommandPreNotifierStr                 "AI Command Notifier: Before Live Scribble and Tweak"          //Effect:Distort & Transform:Tweak
#define kAILiveScribbleAndTweakCommandPostNotifierStr                "AI Command Notifier: After Live Scribble and Tweak"           //Effect:Distort & Transform:Tweak
#define kAILiveTwistCommandPreNotifierStr                            "AI Command Notifier: Before Live Twist"                       //Effect:Distort & Transform:Twist
#define kAILiveTwistCommandPostNotifierStr                           "AI Command Notifier: After Live Twist"                        //Effect:Distort & Transform:Twist
#define kAILiveZigZagCommandPreNotifierStr                           "AI Command Notifier: Before Live Zig Zag"                     //Effect:Distort & Transform:Zig Zag
#define kAILiveZigZagCommandPostNotifierStr                          "AI Command Notifier: After Live Zig Zag"                      //Effect:Distort & Transform:Zig Zag
#define kAILiveOffsetPathCommandPreNotifierStr                       "AI Command Notifier: Before Live Offset Path"                 //Effect:Path:Offset Path
#define kAILiveOffsetPathCommandPostNotifierStr                      "AI Command Notifier: After Live Offset Path"                  //Effect:Path:Offset Path
#define kAILiveOutlineObjectCommandPreNotifierStr                    "AI Command Notifier: Before Live Outline Object"              //Effect:Path:Outline Object
#define kAILiveOutlineObjectCommandPostNotifierStr                   "AI Command Notifier: After Live Outline Object"               //Effect:Path:Outline Object
#define kAILiveOutlineStrokeCommandPreNotifierStr                    "AI Command Notifier: Before Live Outline Stroke"              //Effect:Path:Outline Stroke
#define kAILiveOutlineStrokeCommandPostNotifierStr                   "AI Command Notifier: After Live Outline Stroke"               //Effect:Path:Outline Stroke
#define kAILivePathfinderAddCommandPreNotifierStr                    "AI Command Notifier: Before Live Pathfinder Add"              //Effect:Pathfinder:Add
#define kAILivePathfinderAddCommandPostNotifierStr                   "AI Command Notifier: After Live Pathfinder Add"               //Effect:Pathfinder:Add
#define kAILivePathfinderIntersectCommandPreNotifierStr              "AI Command Notifier: Before Live Pathfinder Intersect"        //Effect:Pathfinder:Intersect
#define kAILivePathfinderIntersectCommandPostNotifierStr             "AI Command Notifier: After Live Pathfinder Intersect"         //Effect:Pathfinder:Intersect
#define kAILivePathfinderExcludeCommandPreNotifierStr                "AI Command Notifier: Before Live Pathfinder Exclude"          //Effect:Pathfinder:Exclude
#define kAILivePathfinderExcludeCommandPostNotifierStr               "AI Command Notifier: After Live Pathfinder Exclude"           //Effect:Pathfinder:Exclude
#define kAILivePathfinderSubtractCommandPreNotifierStr               "AI Command Notifier: Before Live Pathfinder Subtract"         //Effect:Pathfinder:Subtract
#define kAILivePathfinderSubtractCommandPostNotifierStr              "AI Command Notifier: After Live Pathfinder Subtract"          //Effect:Pathfinder:Subtract
#define kAILivePathfinderMinusBackCommandPreNotifierStr              "AI Command Notifier: Before Live Pathfinder Minus Back"       //Effect:Pathfinder:Minus Back
#define kAILivePathfinderMinusBackCommandPostNotifierStr             "AI Command Notifier: After Live Pathfinder Minus Back"        //Effect:Pathfinder:Minus Back
#define kAILivePathfinderDivideCommandPreNotifierStr                 "AI Command Notifier: Before Live Pathfinder Divide"           //Effect:Pathfinder:Divide
#define kAILivePathfinderDivideCommandPostNotifierStr                "AI Command Notifier: After Live Pathfinder Divide"            //Effect:Pathfinder:Divide
#define kAILivePathfinderTrimCommandPreNotifierStr                   "AI Command Notifier: Before Live Pathfinder Trim"             //Effect:Pathfinder:Trim
#define kAILivePathfinderTrimCommandPostNotifierStr                  "AI Command Notifier: After Live Pathfinder Trim"              //Effect:Pathfinder:Trim
#define kAILivePathfinderMergeCommandPreNotifierStr                  "AI Command Notifier: Before Live Pathfinder Merge"            //Effect:Pathfinder:Merge
#define kAILivePathfinderMergeCommandPostNotifierStr                 "AI Command Notifier: After Live Pathfinder Merge"             //Effect:Pathfinder:Merge
#define kAILivePathfinderCropCommandPreNotifierStr                   "AI Command Notifier: Before Live Pathfinder Crop"             //Effect:Pathfinder:Crop
#define kAILivePathfinderCropCommandPostNotifierStr                  "AI Command Notifier: After Live Pathfinder Crop"              //Effect:Pathfinder:Crop
#define kAILivePathfinderOutlineCommandPreNotifierStr                "AI Command Notifier: Before Live Pathfinder Outline"          //Effect:Pathfinder:Outline
#define kAILivePathfinderOutlineCommandPostNotifierStr               "AI Command Notifier: After Live Pathfinder Outline"           //Effect:Pathfinder:Outline
#define kAILivePathfinderHardMixCommandPreNotifierStr                "AI Command Notifier: Before Live Pathfinder Hard Mix"         //Effect:Pathfinder:Hard Mix
#define kAILivePathfinderHardMixCommandPostNotifierStr               "AI Command Notifier: After Live Pathfinder Hard Mix"          //Effect:Pathfinder:Hard Mix
#define kAILivePathfinderSoftMixCommandPreNotifierStr                "AI Command Notifier: Before Live Pathfinder Soft Mix"         //Effect:Pathfinder:Soft Mix
#define kAILivePathfinderSoftMixCommandPostNotifierStr               "AI Command Notifier: After Live Pathfinder Soft Mix"          //Effect:Pathfinder:Soft Mix
#define kAILivePathfinderTrapCommandPreNotifierStr                   "AI Command Notifier: Before Live Pathfinder Trap"             //Effect:Pathfinder:Trap
#define kAILivePathfinderTrapCommandPostNotifierStr                  "AI Command Notifier: After Live Pathfinder Trap"              //Effect:Pathfinder:Trap
#define kAILiveRasterizeCommandPreNotifierStr                        "AI Command Notifier: Before Live Rasterize"                   //Effect:Rasterize
#define kAILiveRasterizeCommandPostNotifierStr                       "AI Command Notifier: After Live Rasterize"                    //Effect:Rasterize
#define kAILiveAdobeDropShadowCommandPreNotifierStr                  "AI Command Notifier: Before Live Adobe Drop Shadow"           //Effect:Stylize:Drop Shadow
#define kAILiveAdobeDropShadowCommandPostNotifierStr                 "AI Command Notifier: After Live Adobe Drop Shadow"            //Effect:Stylize:Drop Shadow
#define kAILiveFeatherCommandPreNotifierStr                          "AI Command Notifier: Before Live Feather"                     //Effect:Stylize:Feather
#define kAILiveFeatherCommandPostNotifierStr                         "AI Command Notifier: After Live Feather"                      //Effect:Stylize:Feather
#define kAILiveInnerGlowCommandPreNotifierStr                        "AI Command Notifier: Before Live Inner Glow"                  //Effect:Stylize:Inner Glow
#define kAILiveInnerGlowCommandPostNotifierStr                       "AI Command Notifier: After Live Inner Glow"                   //Effect:Stylize:Inner Glow
#define kAILiveOuterGlowCommandPreNotifierStr                        "AI Command Notifier: Before Live Outer Glow"                  //Effect:Stylize:Outer Glow
#define kAILiveOuterGlowCommandPostNotifierStr                       "AI Command Notifier: After Live Outer Glow"                   //Effect:Stylize:Outer Glow
#define kAILiveAdobeRoundCornersCommandPreNotifierStr                "AI Command Notifier: Before Live Adobe Round Corners"         //Effect:Stylize:Round Corners
#define kAILiveAdobeRoundCornersCommandPostNotifierStr               "AI Command Notifier: After Live Adobe Round Corners"          //Effect:Stylize:Round Corners
#define kAILiveScribbleFillCommandPreNotifierStr                     "AI Command Notifier: Before Live Scribble Fill"               //Effect:Stylize:Scribble
#define kAILiveScribbleFillCommandPostNotifierStr                    "AI Command Notifier: After Live Scribble Fill"                //Effect:Stylize:Scribble
#define kAILiveSVGFiltersCommandPreNotifierStr                       "AI Command Notifier: Before Live SVG Filters"                 //Effect:SVG Filters:Apply SVG Filter
#define kAILiveSVGFiltersCommandPostNotifierStr                      "AI Command Notifier: After Live SVG Filters"                  //Effect:SVG Filters:Apply SVG Filter
#define kAISVGFilterImportCommandPreNotifierStr                      "AI Command Notifier: Before SVG Filter Import"                //Effect:SVG Filters:Import SVG Filter
#define kAISVGFilterImportCommandPostNotifierStr                     "AI Command Notifier: After SVG Filter Import"                 //Effect:SVG Filters:Import SVG Filter
#define kAILiveDeformArcCommandPreNotifierStr                        "AI Command Notifier: Before Live Deform Arc"                  //Effect:Warp:Arc
#define kAILiveDeformArcCommandPostNotifierStr                       "AI Command Notifier: After Live Deform Arc"                   //Effect:Warp:Arc
#define kAILiveDeformArcLowerCommandPreNotifierStr                   "AI Command Notifier: Before Live Deform Arc Lower"            //Effect:Warp:Arc Lower
#define kAILiveDeformArcLowerCommandPostNotifierStr                  "AI Command Notifier: After Live Deform Arc Lower"             //Effect:Warp:Arc Lower
#define kAILiveDeformArcUpperCommandPreNotifierStr                   "AI Command Notifier: Before Live Deform Arc Upper"            //Effect:Warp:Arc Upper
#define kAILiveDeformArcUpperCommandPostNotifierStr                  "AI Command Notifier: After Live Deform Arc Upper"             //Effect:Warp:Arc Upper
#define kAILiveDeformArchCommandPreNotifierStr                       "AI Command Notifier: Before Live Deform Arch"                 //Effect:Warp:Arch
#define kAILiveDeformArchCommandPostNotifierStr                      "AI Command Notifier: After Live Deform Arch"                  //Effect:Warp:Arch
#define kAILiveDeformBulgeCommandPreNotifierStr                      "AI Command Notifier: Before Live Deform Bulge"                //Effect:Warp:Bulge
#define kAILiveDeformBulgeCommandPostNotifierStr                     "AI Command Notifier: After Live Deform Bulge"                 //Effect:Warp:Bulge
#define kAILiveDeformShellLowerCommandPreNotifierStr                 "AI Command Notifier: Before Live Deform Shell Lower"          //Effect:Warp:Shell Lower
#define kAILiveDeformShellLowerCommandPostNotifierStr                "AI Command Notifier: After Live Deform Shell Lower"           //Effect:Warp:Shell Lower
#define kAILiveDeformShellUpperCommandPreNotifierStr                 "AI Command Notifier: Before Live Deform Shell Upper"          //Effect:Warp:Shell Upper
#define kAILiveDeformShellUpperCommandPostNotifierStr                "AI Command Notifier: After Live Deform Shell Upper"           //Effect:Warp:Shell Upper
#define kAILiveDeformFlagCommandPreNotifierStr                       "AI Command Notifier: Before Live Deform Flag"                 //Effect:Warp:Flag
#define kAILiveDeformFlagCommandPostNotifierStr                      "AI Command Notifier: After Live Deform Flag"                  //Effect:Warp:Flag
#define kAILiveDeformWaveCommandPreNotifierStr                       "AI Command Notifier: Before Live Deform Wave"                 //Effect:Warp:Wave
#define kAILiveDeformWaveCommandPostNotifierStr                      "AI Command Notifier: After Live Deform Wave"                  //Effect:Warp:Wave
#define kAILiveDeformFishCommandPreNotifierStr                       "AI Command Notifier: Before Live Deform Fish"                 //Effect:Warp:Fish
#define kAILiveDeformFishCommandPostNotifierStr                      "AI Command Notifier: After Live Deform Fish"                  //Effect:Warp:Fish
#define kAILiveDeformRiseCommandPreNotifierStr                       "AI Command Notifier: Before Live Deform Rise"                 //Effect:Warp:Rise
#define kAILiveDeformRiseCommandPostNotifierStr                      "AI Command Notifier: After Live Deform Rise"                  //Effect:Warp:Rise
#define kAILiveDeformFisheyeCommandPreNotifierStr                    "AI Command Notifier: Before Live Deform Fisheye"              //Effect:Warp:Fisheye
#define kAILiveDeformFisheyeCommandPostNotifierStr                   "AI Command Notifier: After Live Deform Fisheye"               //Effect:Warp:Fisheye
#define kAILiveDeformInflateCommandPreNotifierStr                    "AI Command Notifier: Before Live Deform Inflate"              //Effect:Warp:Inflate
#define kAILiveDeformInflateCommandPostNotifierStr                   "AI Command Notifier: After Live Deform Inflate"               //Effect:Warp:Inflate
#define kAILiveDeformSqueezeCommandPreNotifierStr                    "AI Command Notifier: Before Live Deform Squeeze"              //Effect:Warp:Squeeze
#define kAILiveDeformSqueezeCommandPostNotifierStr                   "AI Command Notifier: After Live Deform Squeeze"               //Effect:Warp:Squeeze
#define kAILiveDeformTwistCommandPreNotifierStr                      "AI Command Notifier: Before Live Deform Twist"                //Effect:Warp:Twist
#define kAILiveDeformTwistCommandPostNotifierStr                     "AI Command Notifier: After Live Deform Twist"                 //Effect:Warp:Twist
#define kAILivePSAdapterPluginGEfcCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_GEfc"       //Effect:Effect Gallery
#define kAILivePSAdapterPluginGEfcCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_GEfc"        //Effect:Effect Gallery
#define kAILivePSAdapterPluginClrPCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_ClrP"       //Effect:Artistic:Colored Pencil
#define kAILivePSAdapterPluginClrPCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_ClrP"        //Effect:Artistic:Colored Pencil
#define kAILivePSAdapterPluginCtCommandPreNotifierStr                "AI Command Notifier: Before Live PSAdapter_plugin_Ct  "       //Effect:Artistic:Cutout
#define kAILivePSAdapterPluginCtCommandPostNotifierStr               "AI Command Notifier: After Live PSAdapter_plugin_Ct  "        //Effect:Artistic:Cutout
#define kAILivePSAdapterPluginDryBCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_DryB"       //Effect:Artistic:Dry Brush
#define kAILivePSAdapterPluginDryBCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_DryB"        //Effect:Artistic:Dry Brush
#define kAILivePSAdapterPluginFlmGCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_FlmG"       //Effect:Artistic:Film Grain
#define kAILivePSAdapterPluginFlmGCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_FlmG"        //Effect:Artistic:Film Grain
#define kAILivePSAdapterPluginFrscCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Frsc"       //Effect:Artistic:Fresco
#define kAILivePSAdapterPluginFrscCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Frsc"        //Effect:Artistic:Fresco
#define kAILivePSAdapterPluginNGlwCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_NGlw"       //Effect:Artistic:Neon Glow
#define kAILivePSAdapterPluginNGlwCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_NGlw"        //Effect:Artistic:Neon Glow
#define kAILivePSAdapterPluginPntDCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_PntD"       //Effect:Artistic:Paint Daubs
#define kAILivePSAdapterPluginPntDCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_PntD"        //Effect:Artistic:Paint Daubs
#define kAILivePSAdapterPluginPltKCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_PltK"       //Effect:Artistic:Palette Knife
#define kAILivePSAdapterPluginPltKCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_PltK"        //Effect:Artistic:Palette Knife
#define kAILivePSAdapterPluginPlsWCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_PlsW"       //Effect:Artistic:Plastic Wrap
#define kAILivePSAdapterPluginPlsWCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_PlsW"        //Effect:Artistic:Plastic Wrap
#define kAILivePSAdapterPluginPstECommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_PstE"       //Effect:Artistic:Poster Edges
#define kAILivePSAdapterPluginPstECommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_PstE"        //Effect:Artistic:Poster Edges
#define kAILivePSAdapterPluginRghPCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_RghP"       //Effect:Artistic:Rough Pastels
#define kAILivePSAdapterPluginRghPCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_RghP"        //Effect:Artistic:Rough Pastels
#define kAILivePSAdapterPluginSmdSCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_SmdS"       //Effect:Artistic:Smudge Stick
#define kAILivePSAdapterPluginSmdSCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_SmdS"        //Effect:Artistic:Smudge Stick
#define kAILivePSAdapterPluginSpngCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Spng"       //Effect:Artistic:Sponge
#define kAILivePSAdapterPluginSpngCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Spng"        //Effect:Artistic:Sponge
#define kAILivePSAdapterPluginUndrCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Undr"       //Effect:Artistic:Underpainting
#define kAILivePSAdapterPluginUndrCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Undr"        //Effect:Artistic:Underpainting
#define kAILivePSAdapterPluginWtrcCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Wtrc"       //Effect:Artistic:Watercolor
#define kAILivePSAdapterPluginWtrcCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Wtrc"        //Effect:Artistic:Watercolor
#define kAILivePSAdapterPluginGblRCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_GblR"       //Effect:Blur:Gaussian Blur
#define kAILivePSAdapterPluginGblRCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_GblR"        //Effect:Blur:Gaussian Blur
#define kAILivePSAdapterPluginRdlBCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_RdlB"       //Effect:Blur:Radial Blur
#define kAILivePSAdapterPluginRdlBCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_RdlB"        //Effect:Blur:Radial Blur
#define kAILivePSAdapterPluginSmrBCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_SmrB"       //Effect:Blur:Smart Blur
#define kAILivePSAdapterPluginSmrBCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_SmrB"        //Effect:Blur:Smart Blur
#define kAILivePSAdapterPluginAccECommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_AccE"       //Effect:Brush Strokes:Accented Edges
#define kAILivePSAdapterPluginAccECommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_AccE"        //Effect:Brush Strokes:Accented Edges
#define kAILivePSAdapterPluginAngSCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_AngS"       //Effect:Brush Strokes:Angled Strokes
#define kAILivePSAdapterPluginAngSCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_AngS"        //Effect:Brush Strokes:Angled Strokes
#define kAILivePSAdapterPluginCrshCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Crsh"       //Effect:Brush Strokes:Crosshatch
#define kAILivePSAdapterPluginCrshCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Crsh"        //Effect:Brush Strokes:Crosshatch
#define kAILivePSAdapterPluginDrkSCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_DrkS"       //Effect:Brush Strokes:Dark Strokes
#define kAILivePSAdapterPluginDrkSCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_DrkS"        //Effect:Brush Strokes:Dark Strokes
#define kAILivePSAdapterPluginInkOCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_InkO"       //Effect:Brush Strokes:Ink Outlines
#define kAILivePSAdapterPluginInkOCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_InkO"        //Effect:Brush Strokes:Ink Outlines
#define kAILivePSAdapterPluginSptCommandPreNotifierStr               "AI Command Notifier: Before Live PSAdapter_plugin_Spt "       //Effect:Brush Strokes:Spatter
#define kAILivePSAdapterPluginSptCommandPostNotifierStr              "AI Command Notifier: After Live PSAdapter_plugin_Spt "        //Effect:Brush Strokes:Spatter
#define kAILivePSAdapterPluginSprSCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_SprS"       //Effect:Brush Strokes:Sprayed Strokes
#define kAILivePSAdapterPluginSprSCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_SprS"        //Effect:Brush Strokes:Sprayed Strokes
#define kAILivePSAdapterPluginSmieCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Smie"       //Effect:Brush Strokes:Sumi-e
#define kAILivePSAdapterPluginSmieCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Smie"        //Effect:Brush Strokes:Sumi-e
#define kAILivePSAdapterPluginDfsGCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_DfsG"       //Effect:Distort:Diffuse Glow
#define kAILivePSAdapterPluginDfsGCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_DfsG"        //Effect:Distort:Diffuse Glow
#define kAILivePSAdapterPluginGlsCommandPreNotifierStr               "AI Command Notifier: Before Live PSAdapter_plugin_Gls "       //Effect:Distort:Glass
#define kAILivePSAdapterPluginGlsCommandPostNotifierStr              "AI Command Notifier: After Live PSAdapter_plugin_Gls "        //Effect:Distort:Glass
#define kAILivePSAdapterPluginOcnRCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_OcnR"       //Effect:Distort:Ocean Ripple
#define kAILivePSAdapterPluginOcnRCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_OcnR"        //Effect:Distort:Ocean Ripple
#define kAILivePSAdapterPluginClrHCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_ClrH"       //Effect:Pixelate:Color Halftone
#define kAILivePSAdapterPluginClrHCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_ClrH"        //Effect:Pixelate:Color Halftone
#define kAILivePSAdapterPluginCrstCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Crst"       //Effect:Pixelate:Crystallize
#define kAILivePSAdapterPluginCrstCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Crst"        //Effect:Pixelate:Crystallize
#define kAILivePSAdapterPluginMztnCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Mztn"       //Effect:Pixelate:Mezzotint
#define kAILivePSAdapterPluginMztnCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Mztn"        //Effect:Pixelate:Mezzotint
#define kAILivePSAdapterPluginPntlCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Pntl"       //Effect:Pixelate:Pointillize
#define kAILivePSAdapterPluginPntlCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Pntl"        //Effect:Pixelate:Pointillize
#define kAILivePSAdapterPluginUSMkCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_USMk"       //Effect:Sharpen:Unsharp Mask
#define kAILivePSAdapterPluginUSMkCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_USMk"        //Effect:Sharpen:Unsharp Mask
#define kAILivePSAdapterPluginBsRlCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_BsRl"       //Effect:Sketch:Bas Relief
#define kAILivePSAdapterPluginBsRlCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_BsRl"        //Effect:Sketch:Bas Relief
#define kAILivePSAdapterPluginChlCCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_ChlC"       //Effect:Sketch:Chalk & Charcoal
#define kAILivePSAdapterPluginChlCCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_ChlC"        //Effect:Sketch:Chalk & Charcoal
#define kAILivePSAdapterPluginChrcCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Chrc"       //Effect:Sketch:Charcoal
#define kAILivePSAdapterPluginChrcCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Chrc"        //Effect:Sketch:Charcoal
#define kAILivePSAdapterPluginChrmCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Chrm"       //Effect:Sketch:Chrome
#define kAILivePSAdapterPluginChrmCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Chrm"        //Effect:Sketch:Chrome
#define kAILivePSAdapterPluginCntCCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_CntC"       //Effect:Sketch:Cont￩ Crayon
#define kAILivePSAdapterPluginCntCCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_CntC"        //Effect:Sketch:Cont￩ Crayon
#define kAILivePSAdapterPluginGraPCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_GraP"       //Effect:Sketch:Graphic Pen
#define kAILivePSAdapterPluginGraPCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_GraP"        //Effect:Sketch:Graphic Pen
#define kAILivePSAdapterPluginHlfSCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_HlfS"       //Effect:Sketch:Halftone Pattern
#define kAILivePSAdapterPluginHlfSCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_HlfS"        //Effect:Sketch:Halftone Pattern
#define kAILivePSAdapterPluginNtPrCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_NtPr"       //Effect:Sketch:Note Paper
#define kAILivePSAdapterPluginNtPrCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_NtPr"        //Effect:Sketch:Note Paper
#define kAILivePSAdapterPluginPhtcCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Phtc"       //Effect:Sketch:Photocopy
#define kAILivePSAdapterPluginPhtcCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Phtc"        //Effect:Sketch:Photocopy
#define kAILivePSAdapterPluginPlstCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Plst"       //Effect:Sketch:Plaster
#define kAILivePSAdapterPluginPlstCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Plst"        //Effect:Sketch:Plaster
#define kAILivePSAdapterPluginRtclCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Rtcl"       //Effect:Sketch:Reticulation
#define kAILivePSAdapterPluginRtclCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Rtcl"        //Effect:Sketch:Reticulation
#define kAILivePSAdapterPluginStmpCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Stmp"       //Effect:Sketch:Stamp
#define kAILivePSAdapterPluginStmpCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Stmp"        //Effect:Sketch:Stamp
#define kAILivePSAdapterPluginTrnECommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_TrnE"       //Effect:Sketch:Torn Edges
#define kAILivePSAdapterPluginTrnECommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_TrnE"        //Effect:Sketch:Torn Edges
#define kAILivePSAdapterPluginWtrPCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_WtrP"       //Effect:Sketch:Water Paper
#define kAILivePSAdapterPluginWtrPCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_WtrP"        //Effect:Sketch:Water Paper
#define kAILivePSAdapterPluginGlwECommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_GlwE"       //Effect:Stylize:Glowing Edges
#define kAILivePSAdapterPluginGlwECommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_GlwE"        //Effect:Stylize:Glowing Edges
#define kAILivePSAdapterPluginCrqlCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Crql"       //Effect:Texture:Craquelure
#define kAILivePSAdapterPluginCrqlCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Crql"        //Effect:Texture:Craquelure
#define kAILivePSAdapterPluginGrnCommandPreNotifierStr               "AI Command Notifier: Before Live PSAdapter_plugin_Grn "       //Effect:Texture:Grain
#define kAILivePSAdapterPluginGrnCommandPostNotifierStr              "AI Command Notifier: After Live PSAdapter_plugin_Grn "        //Effect:Texture:Grain
#define kAILivePSAdapterPluginMscTCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_MscT"       //Effect:Texture:Mosaic Tiles
#define kAILivePSAdapterPluginMscTCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_MscT"        //Effect:Texture:Mosaic Tiles
#define kAILivePSAdapterPluginPtchCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Ptch"       //Effect:Texture:Patchwork
#define kAILivePSAdapterPluginPtchCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Ptch"        //Effect:Texture:Patchwork
#define kAILivePSAdapterPluginStnGCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_StnG"       //Effect:Texture:Stained Glass
#define kAILivePSAdapterPluginStnGCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_StnG"        //Effect:Texture:Stained Glass
#define kAILivePSAdapterPluginTxtzCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Txtz"       //Effect:Texture:Texturizer
#define kAILivePSAdapterPluginTxtzCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Txtz"        //Effect:Texture:Texturizer
#define kAILivePSAdapterPluginDntrCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_Dntr"       //Effect:Video:De-Interlace
#define kAILivePSAdapterPluginDntrCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_Dntr"        //Effect:Video:De-Interlace
#define kAILivePSAdapterPluginNTSCCommandPreNotifierStr              "AI Command Notifier: Before Live PSAdapter_plugin_NTSC"       //Effect:Video:NTSC Colors
#define kAILivePSAdapterPluginNTSCCommandPostNotifierStr             "AI Command Notifier: After Live PSAdapter_plugin_NTSC"        //Effect:Video:NTSC Colors
#define kAIPreviewModeCommandPreNotifierStr                          "AI Command Notifier: Before Preview Mode"                     //View:Preview
#define kAIPreviewModeCommandPostNotifierStr                         "AI Command Notifier: After Preview Mode"                      //View:Preview
#define kAIInkPreviewCommandPreNotifierStr                           "AI Command Notifier: Before Ink Preview"                      //View:Overprint Preview
#define kAIInkPreviewCommandPostNotifierStr                          "AI Command Notifier: After Ink Preview"                       //View:Overprint Preview
#define kAIPixelViewCommandPreNotifierStr                            "AI Command Notifier: Before Pixel View"                       //View:Pixel Preview
#define kAIPixelViewCommandPostNotifierStr                           "AI Command Notifier: After Pixel View"                        //View:Pixel Preview
#define kAIProofSetupDocumentCommandPreNotifierStr                   "AI Command Notifier: Before Proof Setup Document"             //View:Proof Setup:Document CMYK: 
#define kAIProofSetupDocumentCommandPostNotifierStr                  "AI Command Notifier: After Proof Setup Document"              //View:Proof Setup:Document CMYK: 
#define kAIProofSetupMacRGBCommandPreNotifierStr                     "AI Command Notifier: Before Proof Setup Mac RGB"              //View:Proof Setup:Legacy Macintosh RGB (Gamma 1.8)
#define kAIProofSetupMacRGBCommandPostNotifierStr                    "AI Command Notifier: After Proof Setup Mac RGB"               //View:Proof Setup:Legacy Macintosh RGB (Gamma 1.8)
#define kAIProofSetupWinRGBCommandPreNotifierStr                     "AI Command Notifier: Before Proof Setup Win RGB"              //View:Proof Setup:Internet Standard RGB (sRGB)
#define kAIProofSetupWinRGBCommandPostNotifierStr                    "AI Command Notifier: After Proof Setup Win RGB"               //View:Proof Setup:Internet Standard RGB (sRGB)
#define kAIProofSetupMonitorRGBCommandPreNotifierStr                 "AI Command Notifier: Before Proof Setup Monitor RGB"          //View:Proof Setup:Monitor RGB
#define kAIProofSetupMonitorRGBCommandPostNotifierStr                "AI Command Notifier: After Proof Setup Monitor RGB"           //View:Proof Setup:Monitor RGB
#define kAIProofSetupColorBlindPCommandPreNotifierStr                "AI Command Notifier: Before Proof Setup Color Blind P"        //View:Proof Setup:Color blindness - Protanopia-type
#define kAIProofSetupColorBlindPCommandPostNotifierStr               "AI Command Notifier: After Proof Setup Color Blind P"         //View:Proof Setup:Color blindness - Protanopia-type
#define kAIProofSetupColorBlindDCommandPreNotifierStr                "AI Command Notifier: Before Proof Setup Color Blind D"        //View:Proof Setup:Color blindness - Deuteranopia-type
#define kAIProofSetupColorBlindDCommandPostNotifierStr               "AI Command Notifier: After Proof Setup Color Blind D"         //View:Proof Setup:Color blindness - Deuteranopia-type
#define kAIProofSetupCustomCommandPreNotifierStr                     "AI Command Notifier: Before Proof Setup Custom"               //View:Proof Setup:Customize
#define kAIProofSetupCustomCommandPostNotifierStr                    "AI Command Notifier: After Proof Setup Custom"                //View:Proof Setup:Customize
#define kAIProofColorsCommandPreNotifierStr                          "AI Command Notifier: Before Proof Colors"                     //View:Proof Colors
#define kAIProofColorsCommandPostNotifierStr                         "AI Command Notifier: After Proof Colors"                      //View:Proof Colors
#define kAIZoomInCommandPreNotifierStr                               "AI Command Notifier: Before Zoom In"                          //View:Zoom In
#define kAIZoomInCommandPostNotifierStr                              "AI Command Notifier: After Zoom In"                           //View:Zoom In
#define kAIZoomOutCommandPreNotifierStr                              "AI Command Notifier: Before Zoom Out"                         //View:Zoom Out
#define kAIZoomOutCommandPostNotifierStr                             "AI Command Notifier: After Zoom Out"                          //View:Zoom Out
#define kAIReduceToFitCommandPreNotifierStr                          "AI Command Notifier: Before Reduce To Fit"                    //View:Fit Artboard in Window
#define kAIReduceToFitCommandPostNotifierStr                         "AI Command Notifier: After Reduce To Fit"                     //View:Fit Artboard in Window
#define kAIReduceToFitAllCommandPreNotifierStr                       "AI Command Notifier: Before Reduce To Fit All"                //View:Fit All in Window
#define kAIReduceToFitAllCommandPostNotifierStr                      "AI Command Notifier: After Reduce To Fit All"                 //View:Fit All in Window
#define kAIActualSizeCommandPreNotifierStr                           "AI Command Notifier: Before Actual Size"                      //View:Actual Size
#define kAIActualSizeCommandPostNotifierStr                          "AI Command Notifier: After Actual Size"                       //View:Actual Size
#define kAIShowHideEdgesCommandPreNotifierStr                        "AI Command Notifier: Before Show/Hide Edges"                  //View:Hide Edges
#define kAIShowHideEdgesCommandPostNotifierStr                       "AI Command Notifier: After Show/Hide Edges"                   //View:Hide Edges
#define kAIShowHideArtboardCommandPreNotifierStr                     "AI Command Notifier: Before Show/Hide Artboard"               //View:Hide Artboards
#define kAIShowHideArtboardCommandPostNotifierStr                    "AI Command Notifier: After Show/Hide Artboard"                //View:Hide Artboards
#define kAIShowHidePageTilingCommandPreNotifierStr                   "AI Command Notifier: Before Show/Hide Page Tiling"            //View:Hide Print Tiling
#define kAIShowHidePageTilingCommandPostNotifierStr                  "AI Command Notifier: After Show/Hide Page Tiling"             //View:Hide Print Tiling
#define kAIAISliceFeedbackMenuCommandPreNotifierStr                  "AI Command Notifier: Before AISlice Feedback Menu"            //View:Show Slices
#define kAIAISliceFeedbackMenuCommandPostNotifierStr                 "AI Command Notifier: After AISlice Feedback Menu"             //View:Show Slices
#define kAIAISliceLockMenuCommandPreNotifierStr                      "AI Command Notifier: Before AISlice Lock Menu"                //View:Lock Slices
#define kAIAISliceLockMenuCommandPostNotifierStr                     "AI Command Notifier: After AISlice Lock Menu"                 //View:Lock Slices
#define kAIShowHideTemplateCommandPreNotifierStr                     "AI Command Notifier: Before Show/Hide Template"               //View:Show Template
#define kAIShowHideTemplateCommandPostNotifierStr                    "AI Command Notifier: After Show/Hide Template"                //View:Show Template
#define kAIShowHideRulersCommandPreNotifierStr                       "AI Command Notifier: Before Show/Hide Rulers"                 //View:Rulers:Show Rulers
#define kAIShowHideRulersCommandPostNotifierStr                      "AI Command Notifier: After Show/Hide Rulers"                  //View:Rulers:Show Rulers
#define kAISwitchRulerCoordinateSystemCommandPreNotifierStr          "AI Command Notifier: Before Switch Ruler Coordinate System"   //View:Rulers:Change to Artboard Rulers
#define kAISwitchRulerCoordinateSystemCommandPostNotifierStr         "AI Command Notifier: After Switch Ruler Coordinate System"    //View:Rulers:Change to Artboard Rulers
#define kAIShowHideVideoRulersCommandPreNotifierStr                  "AI Command Notifier: Before Show/Hide Video Rulers"           //View:Rulers:Show Video Rulers
#define kAIShowHideVideoRulersCommandPostNotifierStr                 "AI Command Notifier: After Show/Hide Video Rulers"            //View:Rulers:Show Video Rulers
#define kAIAIBoundingBoxToggleCommandPreNotifierStr                  "AI Command Notifier: Before AI Bounding Box Toggle"           //View:Hide Bounding Box 
#define kAIAIBoundingBoxToggleCommandPostNotifierStr                 "AI Command Notifier: After AI Bounding Box Toggle"            //View:Hide Bounding Box 
#define kAITransparencyGridMenuItemCommandPreNotifierStr             "AI Command Notifier: Before TransparencyGrid Menu Item"       //View:Show Transparency Grid 
#define kAITransparencyGridMenuItemCommandPostNotifierStr            "AI Command Notifier: After TransparencyGrid Menu Item"        //View:Show Transparency Grid 
#define kAIShowHideTextThreadsCommandPreNotifierStr                  "AI Command Notifier: Before Show/Hide Text Threads"           //View:Show Text Threads
#define kAIShowHideTextThreadsCommandPostNotifierStr                 "AI Command Notifier: After Show/Hide Text Threads"            //View:Show Text Threads
#define kAIGradientFeedbackCommandPreNotifierStr                     "AI Command Notifier: Before Gradient Feedback"                //View:Hide Gradient Annotator
#define kAIGradientFeedbackCommandPostNotifierStr                    "AI Command Notifier: After Gradient Feedback"                 //View:Hide Gradient Annotator
#define kAIShowGapsPlanetXCommandPreNotifierStr                      "AI Command Notifier: Before Show Gaps Planet X"               //View:Show Live Paint Gaps
#define kAIShowGapsPlanetXCommandPostNotifierStr                     "AI Command Notifier: After Show Gaps Planet X"                //View:Show Live Paint Gaps
#define kAIShowHideGuidesCommandPreNotifierStr                       "AI Command Notifier: Before Show/Hide Guides"                 //View:Guides:Hide Guides
#define kAIShowHideGuidesCommandPostNotifierStr                      "AI Command Notifier: After Show/Hide Guides"                  //View:Guides:Hide Guides
#define kAILockUnlockGuidesCommandPreNotifierStr                     "AI Command Notifier: Before Lock/Unlock Guides"               //View:Guides:Lock Guides
#define kAILockUnlockGuidesCommandPostNotifierStr                    "AI Command Notifier: After Lock/Unlock Guides"                //View:Guides:Lock Guides
#define kAIMakeGuidesCommandPreNotifierStr                           "AI Command Notifier: Before Make Guides"                      //View:Guides:Make Guides
#define kAIMakeGuidesCommandPostNotifierStr                          "AI Command Notifier: After Make Guides"                       //View:Guides:Make Guides
#define kAIReleaseGuidesCommandPreNotifierStr                        "AI Command Notifier: Before Release Guides"                   //View:Guides:Release Guides
#define kAIReleaseGuidesCommandPostNotifierStr                       "AI Command Notifier: After Release Guides"                    //View:Guides:Release Guides
#define kAIClearGuideCommandPreNotifierStr                           "AI Command Notifier: Before Clear Guide"                      //View:Guides:Clear Guides
#define kAIClearGuideCommandPostNotifierStr                          "AI Command Notifier: After Clear Guide"                       //View:Guides:Clear Guides
#define kAISnapomaticOnOffMenuItemCommandPreNotifierStr              "AI Command Notifier: Before Snapomatic on-off menu item"      //View:Smart Guides 
#define kAISnapomaticOnOffMenuItemCommandPostNotifierStr             "AI Command Notifier: After Snapomatic on-off menu item"       //View:Smart Guides 
#define kAIShowPerspectiveGridCommandPreNotifierStr                  "AI Command Notifier: Before Show Perspective Grid"            //View:Perspective Grid:Show Grid 
#define kAIShowPerspectiveGridCommandPostNotifierStr                 "AI Command Notifier: After Show Perspective Grid"             //View:Perspective Grid:Show Grid 
#define kAIShowRulerCommandPreNotifierStr                            "AI Command Notifier: Before Show Ruler"                       //View:Perspective Grid:Show Rulers
#define kAIShowRulerCommandPostNotifierStr                           "AI Command Notifier: After Show Ruler"                        //View:Perspective Grid:Show Rulers
#define kAISnapToGridCommandPreNotifierStr                           "AI Command Notifier: Before Snap to Grid"                     //View:Perspective Grid:Snap to Grid
#define kAISnapToGridCommandPostNotifierStr                          "AI Command Notifier: After Snap to Grid"                      //View:Perspective Grid:Snap to Grid
#define kAILockPerspectiveGridCommandPreNotifierStr                  "AI Command Notifier: Before Lock Perspective Grid"            //View:Perspective Grid:Lock Grid
#define kAILockPerspectiveGridCommandPostNotifierStr                 "AI Command Notifier: After Lock Perspective Grid"             //View:Perspective Grid:Lock Grid
#define kAILockStationPointCommandPreNotifierStr                     "AI Command Notifier: Before Lock Station Point"               //View:Perspective Grid:Lock Station Point
#define kAILockStationPointCommandPostNotifierStr                    "AI Command Notifier: After Lock Station Point"                //View:Perspective Grid:Lock Station Point
#define kAIDefinePerspectiveGridCommandPreNotifierStr                "AI Command Notifier: Before Define Perspective Grid"          //View:Perspective Grid:Define Grid
#define kAIDefinePerspectiveGridCommandPostNotifierStr               "AI Command Notifier: After Define Perspective Grid"           //View:Perspective Grid:Define Grid
#define kAISavePerspectiveGridAsPresetCommandPreNotifierStr          "AI Command Notifier: Before Save Perspective Grid as Preset"  //View:Perspective Grid:Save Grid as Preset
#define kAISavePerspectiveGridAsPresetCommandPostNotifierStr         "AI Command Notifier: After Save Perspective Grid as Preset"   //View:Perspective Grid:Save Grid as Preset
#define kAIShowHideGridCommandPreNotifierStr                         "AI Command Notifier: Before Show/Hide Grid"                   //View:Show Grid
#define kAIShowHideGridCommandPostNotifierStr                        "AI Command Notifier: After Show/Hide Grid"                    //View:Show Grid
#define kAIEnableDisableGridSnapCommandPreNotifierStr                "AI Command Notifier: Before Enable/Disable Grid Snap"         //View:Snap to Grid
#define kAIEnableDisableGridSnapCommandPostNotifierStr               "AI Command Notifier: After Enable/Disable Grid Snap"          //View:Snap to Grid
#define kAISnapPointCommandPreNotifierStr                            "AI Command Notifier: Before Snap Point"                       //View:Snap to Point
#define kAISnapPointCommandPostNotifierStr                           "AI Command Notifier: After Snap Point"                        //View:Snap to Point
#define kAINewViewSnapCommandPreNotifierStr                          "AI Command Notifier: Before New View Snap"                    //View:New View
#define kAINewViewSnapCommandPostNotifierStr                         "AI Command Notifier: After New View Snap"                     //View:New View
#define kAIEditViewSnapCommandPreNotifierStr                         "AI Command Notifier: Before Edit View Snap"                   //View:Edit Views
#define kAIEditViewSnapCommandPostNotifierStr                        "AI Command Notifier: After Edit View Snap"                    //View:Edit Views
#define kAIView1CommandPreNotifierStr                                "AI Command Notifier: Before View1"                            //View:Custom View 1
#define kAIView1CommandPostNotifierStr                               "AI Command Notifier: After View1"                             //View:Custom View 1
#define kAIView2CommandPreNotifierStr                                "AI Command Notifier: Before View2"                            //View:Custom View 2
#define kAIView2CommandPostNotifierStr                               "AI Command Notifier: After View2"                             //View:Custom View 2
#define kAIView3CommandPreNotifierStr                                "AI Command Notifier: Before View3"                            //View:Custom View 3
#define kAIView3CommandPostNotifierStr                               "AI Command Notifier: After View3"                             //View:Custom View 3
#define kAIView4CommandPreNotifierStr                                "AI Command Notifier: Before View4"                            //View:Custom View 4
#define kAIView4CommandPostNotifierStr                               "AI Command Notifier: After View4"                             //View:Custom View 4
#define kAIView5CommandPreNotifierStr                                "AI Command Notifier: Before View5"                            //View:Custom View 5
#define kAIView5CommandPostNotifierStr                               "AI Command Notifier: After View5"                             //View:Custom View 5
#define kAIView6CommandPreNotifierStr                                "AI Command Notifier: Before View6"                            //View:Custom View 6
#define kAIView6CommandPostNotifierStr                               "AI Command Notifier: After View6"                             //View:Custom View 6
#define kAIView7CommandPreNotifierStr                                "AI Command Notifier: Before View7"                            //View:Custom View 7
#define kAIView7CommandPostNotifierStr                               "AI Command Notifier: After View7"                             //View:Custom View 7
#define kAIView8CommandPreNotifierStr                                "AI Command Notifier: Before View8"                            //View:Custom View 8
#define kAIView8CommandPostNotifierStr                               "AI Command Notifier: After View8"                             //View:Custom View 8
#define kAIView9CommandPreNotifierStr                                "AI Command Notifier: Before View9"                            //View:Custom View 9
#define kAIView9CommandPostNotifierStr                               "AI Command Notifier: After View9"                             //View:Custom View 9
#define kAIView10CommandPreNotifierStr                               "AI Command Notifier: Before View10"                           //View:Custom View 10
#define kAIView10CommandPostNotifierStr                              "AI Command Notifier: After View10"                            //View:Custom View 10
#define kAINewViewCommandPreNotifierStr                              "AI Command Notifier: Before New View"                         //Window:New Window
#define kAINewViewCommandPostNotifierStr                             "AI Command Notifier: After New View"                          //Window:New Window
#define kAIArrangeWindowsCascadeCommandPreNotifierStr                "AI Command Notifier: Before Arrange Windows - Cascade"        //Window:Arrange:Cascade
#define kAIArrangeWindowsCascadeCommandPostNotifierStr               "AI Command Notifier: After Arrange Windows - Cascade"         //Window:Arrange:Cascade
#define kAIArrangeWindowsVerticalCommandPreNotifierStr               "AI Command Notifier: Before Arrange Windows - Vertical"       //Window:Arrange:Tile
#define kAIArrangeWindowsVerticalCommandPostNotifierStr              "AI Command Notifier: After Arrange Windows - Vertical"        //Window:Arrange:Tile
#define kAIArrangeWindowsFloatInWindowCommandPreNotifierStr          "AI Command Notifier: Before Arrange Windows - Float in Window" //Window:Arrange:Float in Window
#define kAIArrangeWindowsFloatInWindowCommandPostNotifierStr         "AI Command Notifier: After Arrange Windows - Float in Window" //Window:Arrange:Float in Window
#define kAIArrangeWindowsFloatAllInWindowsCommandPreNotifierStr      "AI Command Notifier: Before Arrange Windows - Float All in Windows" //Window:Arrange:Float All in Windows
#define kAIArrangeWindowsFloatAllInWindowsCommandPostNotifierStr     "AI Command Notifier: After Arrange Windows - Float All in Windows" //Window:Arrange:Float All in Windows
#define kAIArrangeWindowsConsolidateAllWindowsCommandPreNotifierStr  "AI Command Notifier: Before Arrange Windows - Consolidate AllWindows" //Window:Arrange:Consolidate All Windows
#define kAIArrangeWindowsConsolidateAllWindowsCommandPostNotifierStr "AI Command Notifier: After Arrange Windows - Consolidate AllWindows" //Window:Arrange:Consolidate All Windows
#define kAIAdobeSaveWorkspaceCommandPreNotifierStr                   "AI Command Notifier: Before Adobe Save Workspace"             //Window:Workspace:Save Workspace
#define kAIAdobeSaveWorkspaceCommandPostNotifierStr                  "AI Command Notifier: After Adobe Save Workspace"              //Window:Workspace:Save Workspace
#define kAIAdobeManageWorkspaceCommandPreNotifierStr                 "AI Command Notifier: Before Adobe Manage Workspace"           //Window:Workspace:Manage Workspaces
#define kAIAdobeManageWorkspaceCommandPostNotifierStr                "AI Command Notifier: After Adobe Manage Workspace"            //Window:Workspace:Manage Workspaces
#define kAIControlPalettePluginCommandPreNotifierStr                 "AI Command Notifier: Before control palette plugin"           //Window:Control
#define kAIControlPalettePluginCommandPostNotifierStr                "AI Command Notifier: After control palette plugin"            //Window:Control
#define kAIAdobeBuiltInToolbox1CommandPreNotifierStr                 "AI Command Notifier: Before AdobeBuiltInToolbox1"             //Window:Tools
#define kAIAdobeBuiltInToolbox1CommandPostNotifierStr                "AI Command Notifier: After AdobeBuiltInToolbox1"              //Window:Tools
#define kAIAdobeActionPaletteCommandPreNotifierStr                   "AI Command Notifier: Before Adobe Action Palette"             //Window:Actions
#define kAIAdobeActionPaletteCommandPostNotifierStr                  "AI Command Notifier: After Adobe Action Palette"              //Window:Actions
#define kAIAdobeAlignObjects2CommandPreNotifierStr                   "AI Command Notifier: Before AdobeAlignObjects2"               //Window:Align 
#define kAIAdobeAlignObjects2CommandPostNotifierStr                  "AI Command Notifier: After AdobeAlignObjects2"                //Window:Align 
#define kAIStylePaletteCommandPreNotifierStr                         "AI Command Notifier: Before Style Palette"                    //Window:Appearance 
#define kAIStylePaletteCommandPostNotifierStr                        "AI Command Notifier: After Style Palette"                     //Window:Appearance 
#define kAIAdobeArtboardPaletteCommandPreNotifierStr                 "AI Command Notifier: Before Adobe Artboard Palette"           //Window:Artboards
#define kAIAdobeArtboardPaletteCommandPostNotifierStr                "AI Command Notifier: After Adobe Artboard Palette"            //Window:Artboards
#define kAIInternalPalettesPosingAsPlugInMenusAttributesCommandPreNotifierStr "AI Command Notifier: Before internal palettes posing as plug-in menus-attributes" //Window:Attributes 
#define kAIInternalPalettesPosingAsPlugInMenusAttributesCommandPostNotifierStr "AI Command Notifier: After internal palettes posing as plug-in menus-attributes" //Window:Attributes 
#define kAIAdobeBrushManagerMenuItemCommandPreNotifierStr            "AI Command Notifier: Before Adobe BrushManager Menu Item"     //Window:Brushes 
#define kAIAdobeBrushManagerMenuItemCommandPostNotifierStr           "AI Command Notifier: After Adobe BrushManager Menu Item"      //Window:Brushes 
#define kAIAdobeColorPaletteCommandPreNotifierStr                    "AI Command Notifier: Before Adobe Color Palette"              //Window:Color 
#define kAIAdobeColorPaletteCommandPostNotifierStr                   "AI Command Notifier: After Adobe Color Palette"               //Window:Color 
#define kAIAdobeHarmonyPaletteCommandPreNotifierStr                  "AI Command Notifier: Before Adobe Harmony Palette"            //Window:Color Guide
#define kAIAdobeHarmonyPaletteCommandPostNotifierStr                 "AI Command Notifier: After Adobe Harmony Palette"             //Window:Color Guide
#define kAIDocInfo1CommandPreNotifierStr                             "AI Command Notifier: Before DocInfo1"                         //Window:Document Info
#define kAIDocInfo1CommandPostNotifierStr                            "AI Command Notifier: After DocInfo1"                          //Window:Document Info
#define kAIAdobeFlatteningPreviewCommandPreNotifierStr               "AI Command Notifier: Before Adobe Flattening Preview"         //Window:Flattener Preview
#define kAIAdobeFlatteningPreviewCommandPostNotifierStr              "AI Command Notifier: After Adobe Flattening Preview"          //Window:Flattener Preview
#define kAIAdobeGradientPaletteCommandPreNotifierStr                 "AI Command Notifier: Before Adobe Gradient Palette"           //Window:Gradient 
#define kAIAdobeGradientPaletteCommandPostNotifierStr                "AI Command Notifier: After Adobe Gradient Palette"            //Window:Gradient 
#define kAIAdobeStylePaletteCommandPreNotifierStr                    "AI Command Notifier: Before Adobe Style Palette"              //Window:Graphic Styles 
#define kAIAdobeStylePaletteCommandPostNotifierStr                   "AI Command Notifier: After Adobe Style Palette"               //Window:Graphic Styles 
#define kAIInternalPalettesPosingAsPlugInMenusInfoCommandPreNotifierStr "AI Command Notifier: Before internal palettes posing as plug-in menus-info" //Window:Info
#define kAIInternalPalettesPosingAsPlugInMenusInfoCommandPostNotifierStr "AI Command Notifier: After internal palettes posing as plug-in menus-info" //Window:Info
#define kAIAdobeLayerPalette1CommandPreNotifierStr                   "AI Command Notifier: Before AdobeLayerPalette1"               //Window:Layers 
#define kAIAdobeLayerPalette1CommandPostNotifierStr                  "AI Command Notifier: After AdobeLayerPalette1"                //Window:Layers 
#define kAIAdobeLinkPaletteMenuItemCommandPreNotifierStr             "AI Command Notifier: Before Adobe LinkPalette Menu Item"      //Window:Links
#define kAIAdobeLinkPaletteMenuItemCommandPostNotifierStr            "AI Command Notifier: After Adobe LinkPalette Menu Item"       //Window:Links
#define kAIAIMagicWandCommandPreNotifierStr                          "AI Command Notifier: Before AI Magic Wand"                    //Window:Magic Wand
#define kAIAIMagicWandCommandPostNotifierStr                         "AI Command Notifier: After AI Magic Wand"                     //Window:Magic Wand
#define kAIAdobeNavigator1CommandPreNotifierStr                      "AI Command Notifier: Before AdobeNavigator1"                  //Window:Navigator
#define kAIAdobeNavigator1CommandPostNotifierStr                     "AI Command Notifier: After AdobeNavigator1"                   //Window:Navigator
#define kAIAdobePathfinderPalette1CommandPreNotifierStr              "AI Command Notifier: Before AdobePathfinderPalette1"          //Window:Pathfinder 
#define kAIAdobePathfinderPalette1CommandPostNotifierStr             "AI Command Notifier: After AdobePathfinderPalette1"           //Window:Pathfinder 
#define kAIAdobeSeparationPreviewPaletteCommandPreNotifierStr        "AI Command Notifier: Before Adobe Separation Preview Palette" //Window:Separations Preview
#define kAIAdobeSeparationPreviewPaletteCommandPostNotifierStr       "AI Command Notifier: After Adobe Separation Preview Palette"  //Window:Separations Preview
#define kAIAdobeStrokePaletteCommandPreNotifierStr                   "AI Command Notifier: Before Adobe Stroke Palette"             //Window:Stroke 
#define kAIAdobeStrokePaletteCommandPostNotifierStr                  "AI Command Notifier: After Adobe Stroke Palette"              //Window:Stroke 
#define kAIAdobeSVGInteractivityPaletteCommandPreNotifierStr         "AI Command Notifier: Before Adobe SVG Interactivity Palette"  //Window:SVG Interactivity
#define kAIAdobeSVGInteractivityPaletteCommandPostNotifierStr        "AI Command Notifier: After Adobe SVG Interactivity Palette"   //Window:SVG Interactivity
#define kAIAdobeSwatchesMenuItemCommandPreNotifierStr                "AI Command Notifier: Before Adobe Swatches Menu Item"         //Window:Swatches
#define kAIAdobeSwatchesMenuItemCommandPostNotifierStr               "AI Command Notifier: After Adobe Swatches Menu Item"          //Window:Swatches
#define kAIAdobeSymbolPaletteCommandPreNotifierStr                   "AI Command Notifier: Before Adobe Symbol Palette"             //Window:Symbols 
#define kAIAdobeSymbolPaletteCommandPostNotifierStr                  "AI Command Notifier: After Adobe Symbol Palette"              //Window:Symbols 
#define kAIAdobeTransformObjects1CommandPreNotifierStr               "AI Command Notifier: Before AdobeTransformObjects1"           //Window:Transform 
#define kAIAdobeTransformObjects1CommandPostNotifierStr              "AI Command Notifier: After AdobeTransformObjects1"            //Window:Transform 
#define kAIAdobeTransparencyPaletteMenuItemCommandPreNotifierStr     "AI Command Notifier: Before Adobe Transparency Palette Menu Item" //Window:Transparency 
#define kAIAdobeTransparencyPaletteMenuItemCommandPostNotifierStr    "AI Command Notifier: After Adobe Transparency Palette Menu Item" //Window:Transparency 
#define kAIInternalPalettesPosingAsPlugInMenusCharacterCommandPreNotifierStr "AI Command Notifier: Before internal palettes posing as plug-in menus-character" //Window:Type:Character
#define kAIInternalPalettesPosingAsPlugInMenusCharacterCommandPostNotifierStr "AI Command Notifier: After internal palettes posing as plug-in menus-character" //Window:Type:Character
#define kAICharacterStylesCommandPreNotifierStr                      "AI Command Notifier: Before Character Styles"                 //Window:Type:Character Styles
#define kAICharacterStylesCommandPostNotifierStr                     "AI Command Notifier: After Character Styles"                  //Window:Type:Character Styles
#define kAIFlashTextCommandPreNotifierStr                            "AI Command Notifier: Before Flash Text"                       //Window:Type:Flash Text
#define kAIFlashTextCommandPostNotifierStr                           "AI Command Notifier: After Flash Text"                        //Window:Type:Flash Text
#define kAIAlternateGlyphPalettePlugin2CommandPreNotifierStr         "AI Command Notifier: Before alternate glyph palette plugin 2" //Window:Type:Glyphs
#define kAIAlternateGlyphPalettePlugin2CommandPostNotifierStr        "AI Command Notifier: After alternate glyph palette plugin 2"  //Window:Type:Glyphs
#define kAIInternalPalettesPosingAsPlugInMenusOpentypeCommandPreNotifierStr "AI Command Notifier: Before internal palettes posing as plug-in menus-opentype" //Window:Type:OpenType
#define kAIInternalPalettesPosingAsPlugInMenusOpentypeCommandPostNotifierStr "AI Command Notifier: After internal palettes posing as plug-in menus-opentype" //Window:Type:OpenType
#define kAIInternalPalettesPosingAsPlugInMenusParagraphCommandPreNotifierStr "AI Command Notifier: Before internal palettes posing as plug-in menus-paragraph" //Window:Type:Paragraph
#define kAIInternalPalettesPosingAsPlugInMenusParagraphCommandPostNotifierStr "AI Command Notifier: After internal palettes posing as plug-in menus-paragraph" //Window:Type:Paragraph
#define kAIAdobeParagraphStylesPaletteCommandPreNotifierStr          "AI Command Notifier: Before Adobe Paragraph Styles Palette"   //Window:Type:Paragraph Styles
#define kAIAdobeParagraphStylesPaletteCommandPostNotifierStr         "AI Command Notifier: After Adobe Paragraph Styles Palette"    //Window:Type:Paragraph Styles
#define kAIInternalPalettesPosingAsPlugInMenusTabCommandPreNotifierStr "AI Command Notifier: Before internal palettes posing as plug-in menus-tab" //Window:Type:Tabs
#define kAIInternalPalettesPosingAsPlugInMenusTabCommandPostNotifierStr "AI Command Notifier: After internal palettes posing as plug-in menus-tab" //Window:Type:Tabs
#define kAIAdobeVariablesPaletteMenuItemCommandPreNotifierStr        "AI Command Notifier: Before Adobe Variables Palette Menu Item" //Window:Variables
#define kAIAdobeVariablesPaletteMenuItemCommandPostNotifierStr       "AI Command Notifier: After Adobe Variables Palette Menu Item" //Window:Variables
#define kAIWelcomeScreenMenuItemCommandPreNotifierStr                "AI Command Notifier: Before Welcome screen menu item"         //Help:Welcome Screen
#define kAIWelcomeScreenMenuItemCommandPostNotifierStr               "AI Command Notifier: After Welcome screen menu item"          //Help:Welcome Screen
#define kAIAboutIllustratorCommandPreNotifierStr                     "AI Command Notifier: Before About Illustrator"                //Help:About Illustrator
#define kAIAboutIllustratorCommandPostNotifierStr                    "AI Command Notifier: After About Illustrator"                 //Help:About Illustrator
#define kAISystemInformationCommandPreNotifierStr                    "AI Command Notifier: Before System Information"               //Help:System Info
#define kAISystemInformationCommandPostNotifierStr                   "AI Command Notifier: After System Information"                //Help:System Info
#define kAITextSizeCommandPreNotifierStr                             "AI Command Notifier: Before Text Size"                        //Other Text:Point Size Up/Down
#define kAITextSizeCommandPostNotifierStr                            "AI Command Notifier: After Text Size"                         //Other Text:Point Size Up/Down
#define kAITextAlignmentCommandPreNotifierStr                        "AI Command Notifier: Before Text Alignment"                   //Other Text:Left Align Text
#define kAITextAlignmentCommandPostNotifierStr                       "AI Command Notifier: After Text Alignment"                    //Other Text:Left Align Text
#define kAITrackingKerningCommandPreNotifierStr                      "AI Command Notifier: Before Tracking/Kerning"                 //Other Text:Kern Looser
#define kAITrackingKerningCommandPostNotifierStr                     "AI Command Notifier: After Tracking/Kerning"                  //Other Text:Kern Looser
#define kAIWordSpacingCommandPreNotifierStr                          "AI Command Notifier: Before Word Spacing"                     //Other Text:Spacing
#define kAIWordSpacingCommandPostNotifierStr                         "AI Command Notifier: After Word Spacing"                      //Other Text:Spacing
#define kAIDiscretionaryHyphenCommandPreNotifierStr                  "AI Command Notifier: Before Discretionary Hyphen"             //Other Text:Insert Hyphen
#define kAIDiscretionaryHyphenCommandPostNotifierStr                 "AI Command Notifier: After Discretionary Hyphen"              //Other Text:Insert Hyphen
#define kAIClearTrackCommandPreNotifierStr                           "AI Command Notifier: Before Clear Track"                      //Other Text:Clear Tracking
#define kAIClearTrackCommandPostNotifierStr                          "AI Command Notifier: After Clear Track"                       //Other Text:Clear Tracking
#define kAIClearTypeScaleCommandPreNotifierStr                       "AI Command Notifier: Before Clear Type Scale"                 //Other Text:Uniform Type
#define kAIClearTypeScaleCommandPostNotifierStr                      "AI Command Notifier: After Clear Type Scale"                  //Other Text:Uniform Type
#define kAIHighlightFontCommandPreNotifierStr                        "AI Command Notifier: Before Highlight Font"                   //Other Text:Highlight Font
#define kAIHighlightFontCommandPostNotifierStr                       "AI Command Notifier: After Highlight Font"                    //Other Text:Highlight Font
#define kAICenterAlignCommandPreNotifierStr                          "AI Command Notifier: Before Center Align"                     //Other Text:Center Text
#define kAICenterAlignCommandPostNotifierStr                         "AI Command Notifier: After Center Align"                      //Other Text:Center Text
#define kAIRightAlignCommandPreNotifierStr                           "AI Command Notifier: Before Right Align"                      //Other Text:Right Align Text
#define kAIRightAlignCommandPostNotifierStr                          "AI Command Notifier: After Right Align"                       //Other Text:Right Align Text
#define kAIJustifyCommandPreNotifierStr                              "AI Command Notifier: Before Justify"                          //Other Text:Justify Text Left
#define kAIJustifyCommandPostNotifierStr                             "AI Command Notifier: After Justify"                           //Other Text:Justify Text Left
#define kAIJustifyCenterCommandPreNotifierStr                        "AI Command Notifier: Before Justify Center"                   //Other Text:Justify Text Center
#define kAIJustifyCenterCommandPostNotifierStr                       "AI Command Notifier: After Justify Center"                    //Other Text:Justify Text Center
#define kAIJustifyRightCommandPreNotifierStr                         "AI Command Notifier: Before Justify Right"                    //Other Text:Justify Text Right
#define kAIJustifyRightCommandPostNotifierStr                        "AI Command Notifier: After Justify Right"                     //Other Text:Justify Text Right
#define kAIJustifyAllCommandPreNotifierStr                           "AI Command Notifier: Before Justify All"                      //Other Text:Justify All Lines
#define kAIJustifyAllCommandPostNotifierStr                          "AI Command Notifier: After Justify All"                       //Other Text:Justify All Lines
#define kAIToggleAutoHyphenationCommandPreNotifierStr                "AI Command Notifier: Before Toggle Auto Hyphenation"          //Other Text:Toggle Auto Hyphenation
#define kAIToggleAutoHyphenationCommandPostNotifierStr               "AI Command Notifier: After Toggle Auto Hyphenation"           //Other Text:Toggle Auto Hyphenation
#define kAIToggleLineComposerCommandPreNotifierStr                   "AI Command Notifier: Before Toggle Line Composer"             //Other Text:Toggle Line Composer
#define kAIToggleLineComposerCommandPostNotifierStr                  "AI Command Notifier: After Toggle Line Composer"              //Other Text:Toggle Line Composer
#define kAISwitchSelectionToolCommandPreNotifierStr                  "AI Command Notifier: Before Switch Selection Tool"            //Other Select:Switch Selection Tools
#define kAISwitchSelectionToolCommandPostNotifierStr                 "AI Command Notifier: After Switch Selection Tool"             //Other Select:Switch Selection Tools

//Old Menu Command Notifiers
#define kAIPageSetupCommandPreNotifierStr                            "AI Command Notifier: Before Page Setup"
#define kAIPageSetupCommandPostNotifierStr                           "AI Command Notifier: After Page Setup"
#define kAIUnlinkTextCommandPreNotifierStr                           "AI Command Notifier: Before Unlink Text"
#define kAIUnlinkTextCommandPostNotifierStr                          "AI Command Notifier: After Unlink Text"
#define kAIArtworkModeCommandPreNotifierStr                          "AI Command Notifier: Before Artwork Mode"
#define kAIArtworkModeCommandPostNotifierStr                         "AI Command Notifier: After Artwork Mode"
#define kAIShowHideArtboardRulersCommandPreNotifierStr               "AI Command Notifier: Before Show/Hide Artboard Rulers"
#define kAIShowHideArtboardRulersCommandPostNotifierStr              "AI Command Notifier: After Show/Hide Artboard Rulers"
#define kAISelectWindowCommandPreNotifierStr                         "AI Command Notifier: Before Select Window"
#define kAISelectWindowCommandPostNotifierStr                        "AI Command Notifier: After Select Window"
#define kAITextFontCommandPreNotifierStr                             "AI Command Notifier: Before Text Font"
#define kAITextFontCommandPostNotifierStr                            "AI Command Notifier: After Text Font"
#define kAILinkTextCommandPreNotifierStr                             "AI Command Notifier: Before Link Text" 
#define kAILinkTextCommandPostNotifierStr                            "AI Command Notifier: After Link Text" 
#define kAILineSpacingCommandPreNotifierStr                          "AI Command Notifier: Before Line Spacing"
#define kAILineSpacingCommandPostNotifierStr                         "AI Command Notifier: After Line Spacing"
#define kAIReleaseCropMarksCommandPreNotifierStr                     "AI Command Notifier: Before Release Crop Marks"
#define kAIReleaseCropMarksCommandPostNotifierStr                    "AI Command Notifier: After Release Crop Marks"
#define kAINewMultipleMasterInstanceCommandPreNotifierStr            "AI Command Notifier: Before New Multiple Master Instance"
#define kAINewMultipleMasterInstanceCommandPostNotifierStr           "AI Command Notifier: After New Multiple Master Instance"
#define kAICutPictureCommandPreNotifierStr                           "AI Command Notifier: Before Cut Picture"
#define kAICutPictureCommandPostNotifierStr                          "AI Command Notifier: After Cut Picture"
#define kAICopyPictureCommandPreNotifierStr                          "AI Command Notifier: Before Copy Picture"
#define kAICopyPictureCommandPostNotifierStr                         "AI Command Notifier: After Copy Picture"
#define kAISetNoteCommandPreNotifierStr                              "AI Command Notifier: Before Set Note"
#define kAISetNoteCommandPostNotifierStr                             "AI Command Notifier: After Set Note"
#define kAISeparationSetupCommandPreNotifierStr                      "AI Command Notifier: Before Separation Setup"
#define kAISeparationSetupCommandPostNotifierStr                     "AI Command Notifier: After Separation Setup"
#define kAIArrangeWindowsHorizontalCommandPreNotifierStr             "AI Command Notifier: Before Arrange Windows - Horizontal"
#define kAIArrangeWindowsHorizontalCommandPostNotifierStr            "AI Command Notifier: After Arrange Windows - Horizontal"
#define kAIArrangeIconsCommandPreNotifierStr                         "AI Command Notifier: Before Arrange Icons"
#define kAIArrangeIconsCommandPostNotifierStr                        "AI Command Notifier: After Arrange Icons"
#define kAISelecteFile1CommandPreNotifierStr                         "AI Command Notifier: Before Selecte File 1"
#define kAISelecteFile1CommandPostNotifierStr                        "AI Command Notifier: After Selecte File 1"
#define kAISelecteFile2CommandPreNotifierStr                         "AI Command Notifier: Before Selecte File 2"
#define kAISelecteFile2CommandPostNotifierStr                        "AI Command Notifier: After Selecte File 2"
#define kAISelecteFile3CommandPreNotifierStr                         "AI Command Notifier: Before Selecte File 3"
#define kAISelecteFile3CommandPostNotifierStr                        "AI Command Notifier: After Selecte File 3"
#define kAISelecteFile4CommandPreNotifierStr                         "AI Command Notifier: Before Selecte File 4"
#define kAISelecteFile4CommandPostNotifierStr                        "AI Command Notifier: After Selecte File 4"
#define kAITextOrientationCommandPreNotifierStr                      "AI Command Notifier: Before Text Orientation"
#define kAITextOrientationCommandPostNotifierStr                     "AI Command Notifier: After Text Orientation"
#define kAIGlyphSubstitutionOptionsCommandPreNotifierStr             "AI Command Notifier: Before Glyph Substitution Options"
#define kAIGlyphSubstitutionOptionsCommandPostNotifierStr            "AI Command Notifier: After Glyph Substitution Options"
#define kAIAfterAltOptionDragCopyCommandPostNotifierStr				 "AI Command Notifier: After Alt/Option Drag Copy"

#endif // AIMenuCommandNotifiers_h__