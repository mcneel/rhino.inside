#ifndef __AIMenuCommandString__
#define __AIMenuCommandString__

/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2014 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 * 
 **************************************************************************/

/** @file AIMenuCommandString.h */




#include "AIHeaderBegin.h"

/*******************************************************************************
 **
 **	Constants
 **
 **/

/** @ingroup MenuCommand
	File:New */
#define kNewCommandStr                                               "new"                                                          

/** @ingroup MenuCommand
	File:New from Template */
#define kNewFromTemplateCommandStr                                   "newFromTemplate"                                              

/** @ingroup MenuCommand
	File:Open */
#define kOpenCommandStr                                              "open"                                                         

/** @ingroup MenuCommand
	File:Browse in Bridge */
#define kAdobeBridgeBrowseCommandStr                                 "Adobe Bridge Browse"                                          

/** @ingroup MenuCommand
	File:Device Central */
#define kAdobeAIDeviceCenterCommandStr                               "Adobe AI Device center"                                       

/** @ingroup MenuCommand
	File:Close */
#define kCloseCommandStr                                             "close"                                                        

/** @ingroup MenuCommand
	File:Save */
#define kSaveCommandStr                                              "save"                                                         

/** @ingroup MenuCommand
	File:Save As */
#define kSaveasCommandStr                                            "saveas"                                                       

/** @ingroup MenuCommand
	File:Save a Copy */
#define kSaveacopyCommandStr                                         "saveacopy"                                                    

/** @ingroup MenuCommand
	File:Save as Template */
#define kSaveastemplateCommandStr                                    "saveastemplate"                                               

/** @ingroup MenuCommand
	File:Save for Web & Devices */
#define kAdobeAISaveForWebCommandStr                                 "Adobe AI Save For Web"                                        

/** @ingroup MenuCommand
	File:Save Selected Slices */
#define kAdobeAISaveSelectedSlicesCommandStr                         "Adobe AI Save Selected Slices"                                

/** @ingroup MenuCommand
	File:Revert */
#define kRevertCommandStr                                            "revert"                                                       

/** @ingroup MenuCommand
	File:Place */
#define kAIPlaceCommandStr                                           "AI Place"                                                     

/** @ingroup MenuCommand
	File:Export */
#define kExportCommandStr                                            "export"          

/** @ingroup MenuCommand
	File:Export Selection */
#define kExportSelectionCommandStr                                   "exportSelection"  

/** @ingroup MenuCommand
	File:Export/Export For Screens */
#define kExportForScreensCommandStr                                  "exportForScreens"  

/** @ingroup MenuCommand
	File:Scripts:Other Script */
#define kAiBrowseForScriptCommandStr                                 "ai_browse_for_script"                                         

/** @ingroup MenuCommand
	File:Document Setup */
#define kDocumentCommandStr                                          "document"                                                     

/** @ingroup MenuCommand
	File:Document Color Mode:CMYK Color */
#define kDocColorCmykCommandStr                                      "doc-color-cmyk"                                               

/** @ingroup MenuCommand
	File:Document Color Mode:RGB Color */
#define kDocColorRgbCommandStr                                       "doc-color-rgb"                                                

/** @ingroup MenuCommand
	File:File Info */
#define kFileInfoCommandStr                                          "File Info"                                                    

/** @ingroup MenuCommand
	File:Print */
#define kPrintCommandStr                                             "Print"                                                        

/** @ingroup MenuCommand
	File:Exit */
#define kQuitCommandStr                                              "quit"                                                         

/** @ingroup MenuCommand
	Edit:Undo */
#define kUndoCommandStr                                              "undo"                                                         

/** @ingroup MenuCommand
	Edit:Redo */
#define kRedoCommandStr                                              "redo"                                                         

/** @ingroup MenuCommand
	Edit:Cut */
#define kCutCommandStr                                               "cut"                                                          

/** @ingroup MenuCommand
	Edit:Copy */
#define kCopyCommandStr                                              "copy"                                                         

/** @ingroup MenuCommand
	Edit:Paste */
#define kPasteCommandStr                                             "paste"                                                        

/** @ingroup MenuCommand
	Edit:Paste in Front */
#define kPasteFrontCommandStr                                        "pasteFront"                                                   

/** @ingroup MenuCommand
	Edit:Paste in Back */
#define kPasteBackCommandStr                                         "pasteBack"                                                    

/** @ingroup MenuCommand
	Edit:Paste in Place */
#define kPasteInPlaceCommandStr                                      "pasteInPlace"                                                 

/** @ingroup MenuCommand
	Edit:Paste on All Artboards */
#define kPasteInAllArtboardCommandStr                                "pasteInAllArtboard"                                           

/** @ingroup MenuCommand
	Edit:Clear */
#define kClearCommandStr                                             "clear"                                                        

/** @ingroup MenuCommand
	Edit:Find & Replace */
#define kFindAndReplaceCommandStr									 "Find and Replace"												

/** @ingroup MenuCommand
	Edit:Find Next */
#define kFindNextCommandStr											 "Find Next"													

/** @ingroup MenuCommand
	Edit:Check Spelling */
#define kCheckSpellingCommandStr                                     "Check Spelling"                                               

/** @ingroup MenuCommand
	Edit:Edit Custom Dictionary */
#define kEditCustomDictionaryCommandStr                              "Edit Custom Dictionary..."                                    

/** @ingroup MenuCommand
	Edit:Define Pattern */
#define kDefinePatternMenuItemCommandStr                             "Define Pattern Menu Item"                                     

/** @ingroup MenuCommand
	Edit:Edit Colors:Recolor Artwork */
#define kRecolorArtDialogCommandStr                                  "Recolor Art Dialog"                                           

/** @ingroup MenuCommand
	Edit:Edit Colors:Adjust Color Balance */
#define kAdjust3CommandStr                                           "Adjust3"                                                      

/** @ingroup MenuCommand
	Edit:Edit Colors:Blend Front to Back */
#define kColors3CommandStr                                           "Colors3"                                                      

/** @ingroup MenuCommand
	Edit:Edit Colors:Blend Horizontally */
#define kColors4CommandStr                                           "Colors4"                                                      

/** @ingroup MenuCommand
	Edit:Edit Colors:Blend Vertically */
#define kColors5CommandStr                                           "Colors5"                                                      

/** @ingroup MenuCommand
	Edit:Edit Colors:Convert to CMYK */
#define kColors8CommandStr                                           "Colors8"                                                      

/** @ingroup MenuCommand
	Edit:Edit Colors:Convert to Grayscale */
#define kColors7CommandStr                                           "Colors7"                                                      

/** @ingroup MenuCommand
	Edit:Edit Colors:Convert to RGB */
#define kColors9CommandStr                                           "Colors9"                                                      

/** @ingroup MenuCommand
	Edit:Edit Colors:Invert Colors */
#define kColors6CommandStr                                           "Colors6"                                                      

/** @ingroup MenuCommand
	Edit:Edit Colors:Overprint Black */
#define kOverprint2CommandStr                                        "Overprint2"                                                   

/** @ingroup MenuCommand
	Edit:Edit Colors:Saturate */
#define kSaturate3CommandStr                                         "Saturate3"                                                    

/** @ingroup MenuCommand
	Edit:Edit Original */
#define kEditOriginalMenuItemCommandStr                              "EditOriginal Menu Item"                                       

/** @ingroup MenuCommand
	Edit:Transparency Flattener Presets */
#define kTransparencyPresetsCommandStr                               "Transparency Presets"                                         

/** @ingroup MenuCommand
	Edit:Tracing Presets */
#define kTracingPresetsCommandStr                                    "TracingPresets"                                               

/** @ingroup MenuCommand
	Edit:Print Presets */
#define kPrintPresetsCommandStr                                      "Print Presets"                                                

/** @ingroup MenuCommand
	Edit:Adobe PDF Presets */
#define kPDFPresetsCommandStr                                        "PDF Presets"                                                  

/** @ingroup MenuCommand
	Edit:SWF Presets */
#define kSWFPresetsCommandStr                                        "SWFPresets"                                                   

/** @ingroup MenuCommand
	Edit:Perspective Grid Presets */
#define kPerspectiveGridPresetsCommandStr                            "PerspectiveGridPresets"                                       

/** @ingroup MenuCommand
	Edit:Color Settings */
#define kColorCommandStr                                             "color"                                                        

/** @ingroup MenuCommand
	Edit:Assign Profile */
#define kAssignprofileCommandStr                                     "assignprofile"                                                

/** @ingroup MenuCommand
	Edit:Keyboard Shortcuts */
#define kKBSCMenuItemCommandStr                                      "KBSC Menu Item"                                               

/** @ingroup MenuCommand
	Edit:Run AAT Test */
#define kAATMenuItemCommandStr                                       "AAT Menu Item"                                                

/** @ingroup MenuCommand
	Edit:Edit AAT Script */
#define kLastAATMenuItemCommandStr                                   "Last AAT Menu Item"                                           

/** @ingroup MenuCommand
	Edit:Abort AAT Script */
#define kAbortAATMenuItemCommandStr                                  "Abort AAT Menu Item"                                          

/** @ingroup MenuCommand
	Edit:Preferences:General */
#define kPreferenceCommandStr                                        "preference"                                                   

/** @ingroup MenuCommand
	Edit:Preferences:Selection & Anchor Display */
#define kSelectPrefCommandStr                                        "selectPref"			                                        

/** @ingroup MenuCommand
	Edit:Preferences:Type */
#define kKeyboardPrefCommandStr                                      "keyboardPref"                                                 

/** @ingroup MenuCommand
	Edit:Preferences:Units */
#define kUnitundoPrefCommandStr                                      "unitundoPref"                                                 

/** @ingroup MenuCommand
	Edit:Preferences:Guides & Grid */
#define kGuidegridPrefCommandStr                                     "guidegridPref"                                                

/** @ingroup MenuCommand
	Edit:Preferences:Smart Guides */
#define kSnapPrefCommandStr                                          "snapPref"                                                     

/** @ingroup MenuCommand
	Edit:Preferences:Slices */
#define kSlicePrefCommandStr                                         "slicePref"                                                    

/** @ingroup MenuCommand
	Edit:Preferences:Hyphenation */
#define kHyphenPrefCommandStr                                        "hyphenPref"                                                   

/** @ingroup MenuCommand
	Edit:Preferences:Plug-ins & Scratch Disks */
#define kPluginPrefCommandStr                                        "pluginPref"                                                   

/** @ingroup MenuCommand
	Edit:Preferences:User Interface */
#define kUIPrefCommandStr											 "UIPref"														

/** @ingroup MenuCommand
	Edit:Preferences:File Handling & Clipboard */
#define kFileClipboardPrefCommandStr                                 "FileClipboardPref"                                            

/** @ingroup MenuCommand
	Edit:Preferences:Appearance of Black */
#define kBlackPrefCommandStr                                         "BlackPref"                                                    

/** @ingroup MenuCommand
	Object:Transform:Transform Again */
#define kTransformagainCommandStr                                    "transformagain"                                               

/** @ingroup MenuCommand
	Object:Transform:Move */
#define kTransformmoveCommandStr                                     "transformmove"                                                

/** @ingroup MenuCommand
	Object:Transform:Rotate */
#define kTransformrotateCommandStr                                   "transformrotate"                                              

/** @ingroup MenuCommand
	Object:Transform:Reflect */
#define kTransformreflectCommandStr                                  "transformreflect"                                             

/** @ingroup MenuCommand
	Object:Transform:Scale */
#define kTransformscaleCommandStr                                    "transformscale"                                               

/** @ingroup MenuCommand
	Object:Transform:Shear */
#define kTransformshearCommandStr                                    "transformshear"                                               

/** @ingroup MenuCommand
	Object:Transform Each */
#define kTransformEachCommandStr									 "Transform v23"												

/** @ingroup MenuCommand
	Object:Transform:Reset Bounding Box */
#define kAIResetBoundingBoxCommandStr                                "AI Reset Bounding Box"                                        

/** @ingroup MenuCommand
	Object:Arrange:Bring to Front */
#define kSendToFrontCommandStr                                       "sendToFront"                                                  

/** @ingroup MenuCommand
	Object:Arrange:Bring Forward */
#define kSendForwardCommandStr                                       "sendForward"                                                  

/** @ingroup MenuCommand
	Object:Arrange:Send Backward */
#define kSendBackwardCommandStr                                      "sendBackward"                                                 

/** @ingroup MenuCommand
	Object:Arrange:Send to Back */
#define kSendToBackCommandStr                                        "sendToBack"                                                   

/** @ingroup MenuCommand
	Object:Arrange:Send to Current Layer */
#define kSelectionHat2CommandStr                                     "Selection Hat 2"                                              

/** @ingroup MenuCommand
	Object:Group */
#define kGroupCommandStr                                             "group"                                                        

/** @ingroup MenuCommand
	Object:Ungroup */
#define kUngroupCommandStr                                           "ungroup"                                                      

/** @ingroup MenuCommand
	Object:Lock:Selection */
#define kLockCommandStr                                              "lock"                                                         

/** @ingroup MenuCommand
	Object:Lock:All Artwork Above */
#define kSelectionHat5CommandStr                                     "Selection Hat 5"                                              

/** @ingroup MenuCommand
	Object:Lock:Other Layers */
#define kSelectionHat7CommandStr                                     "Selection Hat 7"                                              

/** @ingroup MenuCommand
	Object:Unlock All */
#define kUnlockAllCommandStr                                         "unlockAll"                                                    

/** @ingroup MenuCommand
	Object:Hide:Selection */
#define kHideCommandStr                                              "hide"                                                         

/** @ingroup MenuCommand
	Object:Hide:All Artwork Above */
#define kSelectionHat4CommandStr                                     "Selection Hat 4"                                              

/** @ingroup MenuCommand
	Object:Hide:Other Layers */
#define kSelectionHat6CommandStr                                     "Selection Hat 6"                                              

/** @ingroup MenuCommand
	Object:Show All */
#define kShowAllCommandStr                                           "showAll"                                                      

/** @ingroup MenuCommand
	Object:Expand */
#define kExpand3CommandStr                                           "Expand3"                                                      

/** @ingroup MenuCommand
	Object:Expand Appearance */
#define kExpandStyleCommandStr                                       "expandStyle"                                                  

/** @ingroup MenuCommand
	Object:Flatten Transparency */
#define kFlattenTransparency1CommandStr                              "FlattenTransparency1"                                         

/** @ingroup MenuCommand
	Object:Rasterize */
#define kRasterize8MenuItemCommandStr                                "Rasterize 8 menu item"                                        

/** @ingroup MenuCommand
	Object:Create Gradient Mesh */
#define kCreateGradientMeshCommandStr								 "make mesh"													

/** @ingroup MenuCommand
	Object:Create Object Mosaic */
#define kAIObjectMosaicPlugIn4CommandStr                             "AI Object Mosaic Plug-in4"                                    

/** @ingroup MenuCommand
	Object:Create Trim Marks */
#define kTrimMarkV25CommandStr                                       "TrimMark v25"                                                 

/** @ingroup MenuCommand
	Object:Slice:Make */
#define kAISliceMakeSliceCommandStr                                  "AISlice Make Slice"                                           

/** @ingroup MenuCommand
	Object:Slice:Release */
#define kAISliceReleaseSliceCommandStr                               "AISlice Release Slice"                                        

/** @ingroup MenuCommand
	Object:Slice:Create from Guides */
#define kAISliceCreateFromGuidesCommandStr                           "AISlice Create from Guides"                                   

/** @ingroup MenuCommand
	Object:Slice:Create from Selection */
#define kAISliceCreateFromSelectionCommandStr                        "AISlice Create from Selection"                                

/** @ingroup MenuCommand
	Object:Slice:Duplicate Slice */
#define kAISliceDuplicateCommandStr                                  "AISlice Duplicate"                                            

/** @ingroup MenuCommand
	Object:Slice:Combine Slices */
#define kAISliceCombineCommandStr                                    "AISlice Combine"                                              

/** @ingroup MenuCommand
	Object:Slice:Divide Slices */
#define kAISliceDivideCommandStr                                     "AISlice Divide"                                               

/** @ingroup MenuCommand
	Object:Slice:Delete All */
#define kAISliceDeleteAllSlicesCommandStr                            "AISlice Delete All Slices"                                    

/** @ingroup MenuCommand
	Object:Slice:Slice Options */
#define kAISliceSliceOptionsCommandStr                               "AISlice Slice Options"                                        

/** @ingroup MenuCommand
	Object:Slice:Clip to Artboard */
#define kAISliceClipToArtboardCommandStr                             "AISlice Clip to Artboard"                                     

/** @ingroup MenuCommand
	Object:Path:Join */
#define kJoinCommandStr                                              "join"                                                         

/** @ingroup MenuCommand
	Object:Path:Average */
#define kAverageCommandStr                                           "average"                                                      

/** @ingroup MenuCommand
	Object:Path:Outline Stroke */
#define kOffsetPathV22CommandStr                                     "OffsetPath v22"                                               

/** @ingroup MenuCommand
	Object:Path:Offset Path */
#define kOffsetPathV23CommandStr                                     "OffsetPath v23"                                               

/** @ingroup MenuCommand
	Object:Path:Simplify */
#define kSimplifyCommandStr											 "simplify menu item"											

/** @ingroup MenuCommand
	Object:Path:Add Anchor Points */
#define kAddAnchorPoints2CommandStr                                  "Add Anchor Points2"                                           

/** @ingroup MenuCommand
	Object:Path:Remove Anchor Points */
#define kRemoveAnchorPointsMenuCommandStr                            "Remove Anchor Points menu"                                    

/** @ingroup MenuCommand
	Object:Path:Divide Objects Below */
#define kKnifeTool2CommandStr                                        "Knife Tool2"                                                  

/** @ingroup MenuCommand
	Object:Path:Split Into Grid */
#define kRowsAndColumnsCommandStr                                    "Rows and Columns...."                                         

/** @ingroup MenuCommand
	Object:Path:Clean Up */
#define kCleanupMenuItemCommandStr                                   "cleanup menu item"                                            

/** @ingroup MenuCommand
	Object:Blend:Make */
#define kBlendMakeCommandStr										 "Path Blend Make"												

/** @ingroup MenuCommand
	Object:Blend:Release */
#define kBlendReleaseCommandStr										 "Path Blend Release"											

/** @ingroup MenuCommand
	Object:Blend:Expand */
#define kBlendExpandCommndStr										 "Path Blend Expand"											

/** @ingroup MenuCommand
	Object:Blend:Blend Options */
#define kBlendOptionsCommandStr										 "Path Blend Options"											

/** @ingroup MenuCommand
	Object:Blend:Replace Spine */
#define kBlendReplaceSpineCommandStr								 "Path Blend Replace Spine"										

/** @ingroup MenuCommand
	Object:Blend:Reverse Spine */
#define kBlendReverseSpineCommandStr								 "Path Blend Reverse Spine"										

/** @ingroup MenuCommand
	Object:Blend:Reverse Front to Back */
#define kBlendReverseStackCommandStr								 "Path Blend Reverse Stack"										

/** @ingroup MenuCommand
	Object:Envelope Distort:Make with Warp */
#define kMakeWarpCommandStr                                          "Make Warp"                                                    

/** @ingroup MenuCommand
	Object:Envelope Distort:Make with Mesh */
#define kCreateEnvelopeGridCommandStr                                "Create Envelope Grid"                                         

/** @ingroup MenuCommand
	Object:Envelope Distort:Make with Top Object  */
#define kMakeEnvelopeCommandStr                                      "Make Envelope"                                                

/** @ingroup MenuCommand
	Object:Envelope Distort:Release */
#define kReleaseEnvelopeCommandStr                                   "Release Envelope"                                             

/** @ingroup MenuCommand
	Object:Envelope Distort:Envelope Options */
#define kEnvelopeOptionsCommandStr                                   "Envelope Options"                                             

/** @ingroup MenuCommand
	Object:Envelope Distort:Expand */
#define kExpandEnvelopeCommandStr                                    "Expand Envelope"                                              

/** @ingroup MenuCommand
	Object:Envelope Distort:Edit Contents  */
#define kEditEnvelopeContentsCommandStr                              "Edit Envelope Contents"                                       

/** @ingroup MenuCommand
	Object:Perspective:Attach to Active Plane */
#define kAttachToActivePlaneCommandStr                               "Attach to Active Plane"                                       

/** @ingroup MenuCommand
	Object:Perspective:Release with Perspective */
#define kReleaseWithPerspectiveCommandStr                            "Release with Perspective"                                     

/** @ingroup MenuCommand
	Object:Perspective:Move Plane to Match Object */
#define kShowObjectGridPlaneCommandStr                               "Show Object Grid Plane"                                       

/** @ingroup MenuCommand
	Object:Perspective:Edit Text */
#define kEditOriginalObjectCommandStr                                "Edit Original Object"                                         

/** @ingroup MenuCommand
	Object:Live Paint:Make  */
#define kMakePlanetXCommandStr                                       "Make Planet X"                                                

/** @ingroup MenuCommand
	Object:Live Paint:Merge */
#define kMargePlanetXCommandStr                                      "Marge Planet X"                                               

/** @ingroup MenuCommand
	Object:Live Paint:Release */
#define kReleasePlanetXCommandStr                                    "Release Planet X"                                             

/** @ingroup MenuCommand
	Object:Live Paint:Gap Options */
#define kPlanetXOptionsCommandStr                                    "Planet X Options"                                             

/** @ingroup MenuCommand
	Object:Live Paint:Expand */
#define kExpandPlanetXCommandStr                                     "Expand Planet X"                                              

/** @ingroup MenuCommand
	Object:Live Trace:Make */
#define kMakeTracingCommandStr                                       "Make Tracing"                                                 

/** @ingroup MenuCommand
	Object:Live Trace:Make and Expand */
#define kMakeAndExpandCommandStr                                     "Make and Expand"                                              

/** @ingroup MenuCommand
	Object:Live Trace:Make and Convert to Live Paint */
#define kMakeAndConvertToLivePaintCommandStr                         "Make and Convert to Live Paint"                               

/** @ingroup MenuCommand
	Object:Live Trace:Release */
#define kReleaseTracingCommandStr                                    "Release Tracing"                                              

/** @ingroup MenuCommand
	Object:Live Trace:Tracing Options */
#define kTracingOptionsCommandStr                                    "Tracing Options"                                              

/** @ingroup MenuCommand
	Object:Live Trace:Expand */
#define kExpandTracingCommandStr                                     "Expand Tracing"                                               

/** @ingroup MenuCommand
	Object:Live Trace:Expand as Viewed */
#define kExpandAsViewedCommandStr                                    "Expand as Viewed"                                             

/** @ingroup MenuCommand
	Object:Live Trace:Convert to Live Paint */
#define kPaintTracingCommandStr                                      "Paint Tracing"                                                

/** @ingroup MenuCommand
	Object:Live Trace:Show No Image */
#define kShowNoImageCommandStr                                       "ShowNoImage"                                                  

/** @ingroup MenuCommand
	Object:Live Trace:Show Original Image */
#define kShowOriginalImageCommandStr                                 "ShowOriginalImage"                                            

/** @ingroup MenuCommand
	Object:Live Trace:Show Adjusted Image */
#define kShowPreprocessedImageCommandStr                             "Show Preprocessed Image"                                      

/** @ingroup MenuCommand
	Object:Live Trace:Show Transparent Image */
#define kShowTransparentImageCommandStr                              "ShowTransparentImage"                                         

/** @ingroup MenuCommand
	Object:Live Trace:Show No Tracing Result */
#define kShowNoArtworkCommandStr                                     "ShowNoArtwork"                                                

/** @ingroup MenuCommand
	Object:Live Trace:Show Tracing Result */
#define kShowArtworkCommandStr                                       "ShowArtwork"                                                  

/** @ingroup MenuCommand
	Object:Live Trace:Show Outlines */
#define kShowPathsCommandStr                                         "ShowPaths"                                                    

/** @ingroup MenuCommand
	Object:Live Trace:Show Outlines with Tracing */
#define kShowPathsAndTransparentArtworkCommandStr                    "ShowPathsAndTransparentArtwork"                               

/** @ingroup MenuCommand
	Object:Text Wrap:Make */
#define kMakeTextWrapCommandStr                                      "Make Text Wrap"                                               

/** @ingroup MenuCommand
	Object:Text Wrap:Release */
#define kReleaseTextWrapCommandStr                                   "Release Text Wrap"                                            

/** @ingroup MenuCommand
	Object:Text Wrap:Text Wrap Options */
#define kTextWrapOptionsCommandStr                                   "Text Wrap Options..."                                         

/** @ingroup MenuCommand
	Object:Clipping Mask:Make */
#define kMakeMaskCommandStr                                          "makeMask"                                                     

/** @ingroup MenuCommand
	Object:Clipping Mask:Release */
#define kReleaseMaskCommandStr                                       "releaseMask"                                                  

/** @ingroup MenuCommand
	Object:Clipping Mask:Edit Contents */
#define kEditMaskCommandStr                                          "editMask"                                                     

/** @ingroup MenuCommand
	Object:Compound Path:Make */
#define kCompoundPathCommandStr                                      "compoundPath"                                                 

/** @ingroup MenuCommand
	Object:Compound Path:Release */
#define kNoCompoundPathCommandStr                                    "noCompoundPath"                                               

/** @ingroup MenuCommand
	Object:Artboards:Convert to Artboards */
#define kSetCropMarksCommandStr                                      "setCropMarks"                                                 

/** @ingroup MenuCommand
	Object:Artboards:Rearrange */
#define kReArrangeArtboardsCommandStr                                "ReArrange Artboards"                                          

/** @ingroup MenuCommand
	Object:Artboards:Fit to Artwork Bounds */
#define kFitArtboardToArtworkBoundsCommandStr                        "Fit Artboard to artwork bounds"                               

/** @ingroup MenuCommand
	Object:Artboards:Fit to Selected Art */
#define kFitArtboardToSelectedArtCommandStr                          "Fit Artboard to selected Art"                                 

/** @ingroup MenuCommand
	Object:Graph:Type */
#define kSetGraphStyleCommandStr                                     "setGraphStyle"                                                

/** @ingroup MenuCommand
	Object:Graph:Data */
#define kEditGraphDataCommandStr                                     "editGraphData"                                                

/** @ingroup MenuCommand
	Object:Graph:Design */
#define kGraphDesignsCommandStr                                      "graphDesigns"                                                 

/** @ingroup MenuCommand
	Object:Graph:Column */
#define kSetBarDesignCommandStr                                      "setBarDesign"                                                 

/** @ingroup MenuCommand
	Object:Graph:Marker */
#define kSetIconDesignCommandStr                                     "setIconDesign"                                                

/** @ingroup MenuCommand
	Type:Glyphs */
#define kAlternateGlyphPalettePluginCommandStr                       "alternate glyph palette plugin"                               

/** @ingroup MenuCommand
	Type:Area Type Options */
#define kAreaTypeOptionsCommandStr                                   "area-type-options"                                            

/** @ingroup MenuCommand
	Type:Type on a Path:Rainbow */
#define kRainbowTOPCommandStr										 "Rainbow"														

/** @ingroup MenuCommand
	Type:Type on a Path:3D Ribbon */
#define k3DRibbonTOPCommandStr										 "3D ribbon"													

/** @ingroup MenuCommand
	Type:Type on a Path:Skew */
#define kSkewTOPCommandStr											 "Skew"															

/** @ingroup MenuCommand
	Type:Type on a Path:Stair Step */
#define kStairTOPCommandStr											 "Stair Step"													

/** @ingroup MenuCommand
	Type:Type on a Path:Gravity */
#define kGravityTOPCommandStr										 "Gravity"														

/** @ingroup MenuCommand
	Type:Type on a Path:Type on a path Options */
#define kTOPOptionsCommandStr										 "typeOnPathOptions"											

/** @ingroup MenuCommand
	Type:Type on a Path:Update Legacy Type on a Path */
#define kUpdateLegacyTOPCommandStr                                   "updateLegacyTOP"                                              

/** @ingroup MenuCommand
	Type:Threaded Text:Create */
#define kThreadTextCreateCommandStr                                  "threadTextCreate"                                             

/** @ingroup MenuCommand
	Type:Threaded Text:Release Selection */
#define kReleaseThreadedTextSelectionCommandStr                      "releaseThreadedTextSelection"                                 

/** @ingroup MenuCommand
	Type:Threaded Text:Remove Threading */
#define kRemoveThreadingCommandStr                                   "removeThreading"                                              

/** @ingroup MenuCommand
	Type:Composite Fonts */
#define kAdobeInternalCompositeFontPluginCommandStr                  "Adobe internal composite font plugin"                         

/** @ingroup MenuCommand
	Type:Kinsoku Shori Settings */
#define kAdobeKinsokuSettingsCommandStr                              "Adobe Kinsoku Settings"                                       

/** @ingroup MenuCommand
	Type:Mojikumi Settings */
#define kAdobeMojiKumiSettingsCommandStr                             "Adobe MojiKumi Settings"                                      

/** @ingroup MenuCommand
	Type:Fit Headline */
#define kFitHeadlineCommandStr                                       "fitHeadline"                                                  

/** @ingroup MenuCommand
	Type:Create Outlines */
#define kOutlineCommandStr                                           "outline"                                                      

/** @ingroup MenuCommand
	Type:Find Font */
#define kAdobeIllustratorFindFontMenuItemCommandStr                  "Adobe Illustrator Find Font Menu Item"                        

/** @ingroup MenuCommand
	Type:Change Case:UPPERCASE */
#define kUpperCaseChangeCaseItemCommandStr                           "UpperCase Change Case Item"                                   

/** @ingroup MenuCommand
	Type:Change Case:lowercase */
#define kLowerCaseChangeCaseItemCommandStr                           "LowerCase Change Case Item"                                   

/** @ingroup MenuCommand
	Type:Change Case:Title Case */
#define kTitleCaseChangeCaseItemCommandStr                           "Title Case Change Case Item"                                  

/** @ingroup MenuCommand
	Type:Change Case:Sentence case */
#define kSentenceCaseChangeCaseItemCommandStr                        "Sentence case Change Case Item"                               

/** @ingroup MenuCommand
	Type:Smart Punctuation */
#define kAdobeIllustratorSmartPunctuationMenuItemCommandStr          "Adobe Illustrator Smart Punctuation Menu Item"                

/** @ingroup MenuCommand
	Type:Optical Margin Alignment */
#define kAdobeOpticalAlignmentItemCommandStr                         "Adobe Optical Alignment Item"                                 

/** @ingroup MenuCommand
	Type:Show Hidden Characters */
#define kShowHiddenCharCommandStr                                    "showHiddenChar"                                               

/** @ingroup MenuCommand
	Type:Type Orientation:Horizontal */
#define kTypeHorizontalCommandStr                                    "type-horizontal"                                              

/** @ingroup MenuCommand
	Type:Type Orientation:Vertical */
#define kTypeVerticalCommandStr                                      "type-vertical"                                                

/** @ingroup MenuCommand
	Select:All */
#define kSelectallCommandStr                                         "selectall"                                                    

/** @ingroup MenuCommand
	Select:All on Active Artboard */
#define kSelectallinartboardCommandStr                               "selectallinartboard"                                          

/** @ingroup MenuCommand
	Select:Deselect */
#define kDeselectallCommandStr                                       "deselectall"                                                  

/** @ingroup MenuCommand
	Select:Reselect  */
#define kFindReselectMenuItemCommandStr                              "Find Reselect menu item"                                      

/** @ingroup MenuCommand
	Select:Inverse */
#define kInverseMenuItemCommandStr                                   "Inverse menu item"                                            

/** @ingroup MenuCommand
	Select:Next Object Above  */
#define kSelectionHat8CommandStr                                     "Selection Hat 8"                                              

/** @ingroup MenuCommand
	Select:Next Object Below  */
#define kSelectionHat9CommandStr                                     "Selection Hat 9"                                              

/** @ingroup MenuCommand
	Select:Same:Appearance */
#define kFindAppearanceMenuItemCommandStr                            "Find Appearance menu item"                                    

/** @ingroup MenuCommand
	Select:Same:Appearance Attribute */
#define kFindAppearanceAttributesMenuItemCommandStr                  "Find Appearance Attributes menu item"                         

/** @ingroup MenuCommand
	Select:Same:Blending Mode */
#define kFindBlendingModeMenuItemCommandStr                          "Find Blending Mode menu item"                                 

/** @ingroup MenuCommand
	Select:Same:Fill & Stroke */
#define kFindFillStrokeMenuItemCommandStr                            "Find Fill & Stroke menu item"                                 

/** @ingroup MenuCommand
	Select:Same:Fill Color */
#define kFindFillColorMenuItemCommandStr                             "Find Fill Color menu item"                                    

/** @ingroup MenuCommand
	Select:Same:Opacity */
#define kFindOpacityMenuItemCommandStr                               "Find Opacity menu item"                                       

/** @ingroup MenuCommand
	Select:Same:Stroke Color */
#define kFindStrokeColorMenuItemCommandStr                           "Find Stroke Color menu item"                                  

/** @ingroup MenuCommand
	Select:Same:Stroke Weight */
#define kFindStrokeWeightMenuItemCommandStr                          "Find Stroke Weight menu item"                                 

/** @ingroup MenuCommand
	Select:Same:Graphic Style */
#define kFindStyleMenuItemCommandStr                                 "Find Style menu item"                                         

/** @ingroup MenuCommand
	Select:Same:Symbol Instance */
#define kFindSymbolInstanceMenuItemCommandStr                        "Find Symbol Instance menu item"                               

/** @ingroup MenuCommand
	Select:Same:Link Block Series */
#define kFindLinkBlockSeriesMenuItemCommandStr                       "Find Link Block Series menu item"                             

/** @ingroup MenuCommand
	Select:Object:All on Same Layers */
#define kSelectionHat3CommandStr                                     "Selection Hat 3"                                              

/** @ingroup MenuCommand
	Select:Object:Direction Handles */
#define kSelectionHat1CommandStr                                     "Selection Hat 1"                                              

/** @ingroup MenuCommand
	Select:Object:Not Aligned to Pixel Grid */
#define kSelectionHat12CommandStr                                    "Selection Hat 12"                                             

/** @ingroup MenuCommand
	Select:Object:Bristle Brush Strokes */
#define kBristleBrushStrokesMenuItemCommandStr                       "Bristle Brush Strokes menu item"                              

/** @ingroup MenuCommand
	Select:Object:Brush Strokes */
#define kBrushStrokesMenuItemCommandStr                              "Brush Strokes menu item"                                      

/** @ingroup MenuCommand
	Select:Object:Clipping Masks */
#define kClippingMasksMenuItemCommandStr                             "Clipping Masks menu item"                                     

/** @ingroup MenuCommand
	Select:Object:Stray Points */
#define kStrayPointsMenuItemCommandStr                               "Stray Points menu item"                                       

/** @ingroup MenuCommand
	Select:Object:Text Objects */
#define kTextObjectsMenuItemCommandStr                               "Text Objects menu item"                                       

/** @ingroup MenuCommand
	Select:Object:Flash Dynamic Text */
#define kDynamicTextCommandStr                                       "Dynamic Text"                                                 

/** @ingroup MenuCommand
	Select:Object:Flash Input Text */
#define kInputTextCommandStr                                         "Input Text"                                                   

/** @ingroup MenuCommand
	Select:Save Selection */
#define kSelectionHat10CommandStr                                    "Selection Hat 10"                                             

/** @ingroup MenuCommand
	Select:Edit Selection */
#define kSelectionHat11CommandStr                                    "Selection Hat 11"                                             

/** @ingroup MenuCommand
	Effect:Apply Last Effect  */
#define kAdobeApplyLastEffectCommandStr                              "Adobe Apply Last Effect"                                      

/** @ingroup MenuCommand
	Effect:Last Effect  */
#define kAdobeLastEffectCommandStr                                   "Adobe Last Effect"                                            

/** @ingroup MenuCommand
	Effect:Document Raster Effects Settings */
#define kLiveRasterizeEffectSettingCommandStr                        "Live Rasterize Effect Setting"                                

/** @ingroup MenuCommand
	Effect:3D:Extrude & Bevel */
#define kLive3DExtrudeCommandStr                                     "Live 3DExtrude"                                               

/** @ingroup MenuCommand
	Effect:3D:Revolve */
#define kLive3DRevolveCommandStr                                     "Live 3DRevolve"                                               

/** @ingroup MenuCommand
	Effect:3D:Rotate */
#define kLive3DRotateCommandStr                                      "Live 3DRotate"                                                

/** @ingroup MenuCommand
	Effect:Convert to Shape:Rectangle */
#define kLiveRectangleCommandStr                                     "Live Rectangle"                                               

/** @ingroup MenuCommand
	Effect:Convert to Shape:Rounded Rectangle */
#define kLiveRoundedRectangleCommandStr                              "Live Rounded Rectangle"                                       

/** @ingroup MenuCommand
	Effect:Convert to Shape:Ellipse */
#define kLiveEllipseCommandStr                                       "Live Ellipse"                                                 

/** @ingroup MenuCommand
	Effect:Crop Marks */
#define kLiveTrimMarksCommandStr                                     "Live Trim Marks"                                              

/** @ingroup MenuCommand
	Effect:Distort & Transform:Free Distort */
#define kLiveFreeDistortCommandStr                                   "Live Free Distort"                                            

/** @ingroup MenuCommand
	Effect:Distort & Transform:Pucker & Bloat */
#define kLivePuckerBloatCommandStr                                   "Live Pucker & Bloat"                                          

/** @ingroup MenuCommand
	Effect:Distort & Transform:Roughen */
#define kLiveRoughenCommandStr                                       "Live Roughen"                                                 

/** @ingroup MenuCommand
	Effect:Distort & Transform:Transform */
#define kLiveTransformCommandStr									 "Live Transform"												

/** @ingroup MenuCommand
	Effect:Distort & Transform:Tweak */
#define kLiveScribbleAndTweakCommandStr                              "Live Scribble and Tweak"                                      

/** @ingroup MenuCommand
	Effect:Distort & Transform:Twist */
#define kLiveTwistCommandStr                                         "Live Twist"                                                   

/** @ingroup MenuCommand
	Effect:Distort & Transform:Zig Zag */
#define kLiveZigZagCommandStr                                        "Live Zig Zag"                                                 

/** @ingroup MenuCommand
	Effect:Path:Offset Path */
#define kLiveOffsetPathCommandStr                                    "Live Offset Path"                                             

/** @ingroup MenuCommand
	Effect:Path:Outline Object */
#define kLiveOutlineObjectCommandStr                                 "Live Outline Object"                                          

/** @ingroup MenuCommand
	Effect:Path:Outline Stroke */
#define kLiveOutlineStrokeCommandStr                                 "Live Outline Stroke"                                          

/** @ingroup MenuCommand
	Effect:Pathfinder:Add */
#define kLivePathfinderAddCommandStr                                 "Live Pathfinder Add"                                          

/** @ingroup MenuCommand
	Effect:Pathfinder:Intersect */
#define kLivePathfinderIntersectCommandStr                           "Live Pathfinder Intersect"                                    

/** @ingroup MenuCommand
	Effect:Pathfinder:Exclude */
#define kLivePathfinderExcludeCommandStr                             "Live Pathfinder Exclude"                                      

/** @ingroup MenuCommand
	Effect:Pathfinder:Subtract */
#define kLivePathfinderSubtractCommandStr                            "Live Pathfinder Subtract"                                     

/** @ingroup MenuCommand
	Effect:Pathfinder:Minus Back */
#define kLivePathfinderMinusBackCommandStr                           "Live Pathfinder Minus Back"                                   

/** @ingroup MenuCommand
	Effect:Pathfinder:Divide */
#define kLivePathfinderDivideCommandStr                              "Live Pathfinder Divide"                                       

/** @ingroup MenuCommand
	Effect:Pathfinder:Trim */
#define kLivePathfinderTrimCommandStr                                "Live Pathfinder Trim"                                         

/** @ingroup MenuCommand
	Effect:Pathfinder:Merge */
#define kLivePathfinderMergeCommandStr                               "Live Pathfinder Merge"                                        

/** @ingroup MenuCommand
	Effect:Pathfinder:Crop */
#define kLivePathfinderCropCommandStr                                "Live Pathfinder Crop"                                         

/** @ingroup MenuCommand
	Effect:Pathfinder:Outline */
#define kLivePathfinderOutlineCommandStr                             "Live Pathfinder Outline"                                      

/** @ingroup MenuCommand
	Effect:Pathfinder:Hard Mix */
#define kLivePathfinderHardMixCommandStr                             "Live Pathfinder Hard Mix"                                     

/** @ingroup MenuCommand
	Effect:Pathfinder:Soft Mix */
#define kLivePathfinderSoftMixCommandStr                             "Live Pathfinder Soft Mix"                                     

/** @ingroup MenuCommand
	Effect:Pathfinder:Trap */
#define kLivePathfinderTrapCommandStr                                "Live Pathfinder Trap"                                         

/** @ingroup MenuCommand
	Effect:Rasterize */
#define kLiveRasterizeCommandStr                                     "Live Rasterize"                                               

/** @ingroup MenuCommand
	Effect:Stylize:Drop Shadow */
#define kLiveDropShadowCommandStr									 "Live Adobe Drop Shadow"										

/** @ingroup MenuCommand
	Effect:Stylize:Feather */
#define kLiveFeatherCommandStr                                       "Live Feather"                                                 

/** @ingroup MenuCommand
	Effetc:Stylize:Inner Glow */
#define kLiveInnerGlowCommandStr									 "Live Inner Glow"												

/** @ingroup MenuCommand
	Effect:Stylize:outer Glow */
#define kLiveOuterGlowCommandStr									 "Live Outer Glow"												

/** @ingroup MenuCommand
	Effect:Stylize:Round Corners */
#define kLiveAdobeRoundCornersCommandStr                             "Live Adobe Round Corners"                                     

/** @ingroup MenuCommand
	Effect:Stylize:Scribble */
#define kLiveScribbleFillCommandStr                                  "Live Scribble Fill"                                           

/** @ingroup MenuCommand
	Effect:SVG Filters:Apply SVG Filter */
#define kLiveSVGFiltersCommandStr                                    "Live SVG Filters"                                             

/** @ingroup MenuCommand
	Effect:SVG Filters:Import SVG Filter */
#define kSVGFilterImportCommandStr                                   "SVG Filter Import"                                            

/** @ingroup MenuCommand
	Effect:Warp:Arc */
#define kLiveDeformArcCommandStr                                     "Live Deform Arc"                                              

/** @ingroup MenuCommand
	Effect:Warp:Arc Lower */
#define kLiveDeformArcLowerCommandStr                                "Live Deform Arc Lower"                                        

/** @ingroup MenuCommand
	Effect:Warp:Arc Upper */
#define kLiveDeformArcUpperCommandStr                                "Live Deform Arc Upper"                                        

/** @ingroup MenuCommand
	Effect:Warp:Arch */
#define kLiveDeformArchCommandStr                                    "Live Deform Arch"                                             

/** @ingroup MenuCommand
	Effect:Warp:Bulge */
#define kLiveDeformBulgeCommandStr                                   "Live Deform Bulge"                                            

/** @ingroup MenuCommand
	Effect:Warp:Shell Lower */
#define kLiveDeformShellLowerCommandStr                              "Live Deform Shell Lower"                                      

/** @ingroup MenuCommand
	Effect:Warp:Shell Upper */
#define kLiveDeformShellUpperCommandStr                              "Live Deform Shell Upper"                                      

/** @ingroup MenuCommand
	Effect:Warp:Flag */
#define kLiveDeformFlagCommandStr                                    "Live Deform Flag"                                             

/** @ingroup MenuCommand
	Effect:Warp:Wave */
#define kLiveDeformWaveCommandStr                                    "Live Deform Wave"                                             

/** @ingroup MenuCommand
	Effect:Warp:Fish */
#define kLiveDeformFishCommandStr                                    "Live Deform Fish"                                             

/** @ingroup MenuCommand
	Effect:Warp:Rise */
#define kLiveDeformRiseCommandStr                                    "Live Deform Rise"                                             

/** @ingroup MenuCommand
	Effect:Warp:Fisheye */
#define kLiveDeformFisheyeCommandStr                                 "Live Deform Fisheye"                                          

/** @ingroup MenuCommand
	Effect:Warp:Inflate */
#define kLiveDeformInflateCommandStr                                 "Live Deform Inflate"                                          

/** @ingroup MenuCommand
	Effect:Warp:Squeeze */
#define kLiveDeformSqueezeCommandStr                                 "Live Deform Squeeze"                                          

/** @ingroup MenuCommand
	Effect:Warp:Twist */
#define kLiveDeformTwistCommandStr                                   "Live Deform Twist"                                            

/** @ingroup MenuCommand
	Effect:Effect Gallery */
#define kLivePSAdapterPluginGEfcCommandStr                           "Live PSAdapter_plugin_GEfc"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Colored Pencil */
#define kLivePSAdapterPluginClrPCommandStr                           "Live PSAdapter_plugin_ClrP"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Cutout */
#define kLivePSAdapterPluginCtCommandStr                             "Live PSAdapter_plugin_Ct  "                                   

/** @ingroup MenuCommand
	Effect:Artistic:Dry Brush */
#define kLivePSAdapterPluginDryBCommandStr                           "Live PSAdapter_plugin_DryB"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Film Grain */
#define kLivePSAdapterPluginFlmGCommandStr                           "Live PSAdapter_plugin_FlmG"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Fresco */
#define kLivePSAdapterPluginFrscCommandStr                           "Live PSAdapter_plugin_Frsc"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Neon Glow */
#define kLivePSAdapterPluginNGlwCommandStr                           "Live PSAdapter_plugin_NGlw"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Paint Daubs */
#define kLivePSAdapterPluginPntDCommandStr                           "Live PSAdapter_plugin_PntD"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Palette Knife */
#define kLivePSAdapterPluginPltKCommandStr                           "Live PSAdapter_plugin_PltK"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Plastic Wrap */
#define kLivePSAdapterPluginPlsWCommandStr                           "Live PSAdapter_plugin_PlsW"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Poster Edges */
#define kLivePSAdapterPluginPstECommandStr                           "Live PSAdapter_plugin_PstE"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Rough Pastels */
#define kLivePSAdapterPluginRghPCommandStr                           "Live PSAdapter_plugin_RghP"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Smudge Stick */
#define kLivePSAdapterPluginSmdSCommandStr                           "Live PSAdapter_plugin_SmdS"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Sponge */
#define kLivePSAdapterPluginSpngCommandStr                           "Live PSAdapter_plugin_Spng"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Underpainting */
#define kLivePSAdapterPluginUndrCommandStr                           "Live PSAdapter_plugin_Undr"                                   

/** @ingroup MenuCommand
	Effect:Artistic:Watercolor */
#define kLivePSAdapterPluginWtrcCommandStr                           "Live PSAdapter_plugin_Wtrc"                                   

/** @ingroup MenuCommand
	Effect:Blur:Gaussian Blur */
#define kLivePSAdapterPluginGblRCommandStr                           "Live PSAdapter_plugin_GblR"                                   

/** @ingroup MenuCommand
	Effect:Blur:Radial Blur */
#define kLivePSAdapterPluginRdlBCommandStr                           "Live PSAdapter_plugin_RdlB"                                   

/** @ingroup MenuCommand
	Effect:Blur:Smart Blur */
#define kLivePSAdapterPluginSmrBCommandStr                           "Live PSAdapter_plugin_SmrB"                                   

/** @ingroup MenuCommand
	Effect:Brush Strokes:Accented Edges */
#define kLivePSAdapterPluginAccECommandStr                           "Live PSAdapter_plugin_AccE"                                   

/** @ingroup MenuCommand
	Effect:Brush Strokes:Angled Strokes */
#define kLivePSAdapterPluginAngSCommandStr                           "Live PSAdapter_plugin_AngS"                                   

/** @ingroup MenuCommand
	Effect:Brush Strokes:Crosshatch */
#define kLivePSAdapterPluginCrshCommandStr                           "Live PSAdapter_plugin_Crsh"                                   

/** @ingroup MenuCommand
	Effect:Brush Strokes:Dark Strokes */
#define kLivePSAdapterPluginDrkSCommandStr                           "Live PSAdapter_plugin_DrkS"                                   

/** @ingroup MenuCommand
	Effect:Brush Strokes:Ink Outlines */
#define kLivePSAdapterPluginInkOCommandStr                           "Live PSAdapter_plugin_InkO"                                   

/** @ingroup MenuCommand
	Effect:Brush Strokes:Spatter */
#define kLivePSAdapterPluginSptCommandStr                            "Live PSAdapter_plugin_Spt "                                   

/** @ingroup MenuCommand
	Effect:Brush Strokes:Sprayed Strokes */
#define kLivePSAdapterPluginSprSCommandStr                           "Live PSAdapter_plugin_SprS"                                   

/** @ingroup MenuCommand
	Effect:Brush Strokes:Sumi-e */
#define kLivePSAdapterPluginSmieCommandStr                           "Live PSAdapter_plugin_Smie"                                   

/** @ingroup MenuCommand
	Effect:Distort:Diffuse Glow */
#define kLivePSAdapterPluginDfsGCommandStr                           "Live PSAdapter_plugin_DfsG"                                   

/** @ingroup MenuCommand
	Effect:Distort:Glass */
#define kLivePSAdapterPluginGlsCommandStr                            "Live PSAdapter_plugin_Gls "                                   

/** @ingroup MenuCommand
	Effect:Distort:Ocean Ripple */
#define kLivePSAdapterPluginOcnRCommandStr                           "Live PSAdapter_plugin_OcnR"                                   

/** @ingroup MenuCommand
	Effect:Pixelate:Color Halftone */
#define kLivePSAdapterPluginClrHCommandStr                           "Live PSAdapter_plugin_ClrH"                                   

/** @ingroup MenuCommand
	Effect:Pixelate:Crystallize */
#define kLivePSAdapterPluginCrstCommandStr                           "Live PSAdapter_plugin_Crst"                                   

/** @ingroup MenuCommand
	Effect:Pixelate:Mezzotint */
#define kLivePSAdapterPluginMztnCommandStr                           "Live PSAdapter_plugin_Mztn"                                   

/** @ingroup MenuCommand
	Effect:Pixelate:Pointillize */
#define kLivePSAdapterPluginPntlCommandStr                           "Live PSAdapter_plugin_Pntl"                                   

/** @ingroup MenuCommand
	Effect:Sharpen:Unsharp Mask */
#define kLivePSAdapterPluginUSMkCommandStr                           "Live PSAdapter_plugin_USMk"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Bas Relief */
#define kLivePSAdapterPluginBsRlCommandStr                           "Live PSAdapter_plugin_BsRl"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Chalk & Charcoal */
#define kLivePSAdapterPluginChlCCommandStr                           "Live PSAdapter_plugin_ChlC"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Charcoal */
#define kLivePSAdapterPluginChrcCommandStr                           "Live PSAdapter_plugin_Chrc"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Chrome */
#define kLivePSAdapterPluginChrmCommandStr                           "Live PSAdapter_plugin_Chrm"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Cont￩ Crayon */
#define kLivePSAdapterPluginCntCCommandStr                           "Live PSAdapter_plugin_CntC"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Graphic Pen */
#define kLivePSAdapterPluginGraPCommandStr                           "Live PSAdapter_plugin_GraP"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Halftone Pattern */
#define kLivePSAdapterPluginHlfSCommandStr                           "Live PSAdapter_plugin_HlfS"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Note Paper */
#define kLivePSAdapterPluginNtPrCommandStr                           "Live PSAdapter_plugin_NtPr"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Photocopy */
#define kLivePSAdapterPluginPhtcCommandStr                           "Live PSAdapter_plugin_Phtc"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Plaster */
#define kLivePSAdapterPluginPlstCommandStr                           "Live PSAdapter_plugin_Plst"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Reticulation */
#define kLivePSAdapterPluginRtclCommandStr                           "Live PSAdapter_plugin_Rtcl"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Stamp */
#define kLivePSAdapterPluginStmpCommandStr                           "Live PSAdapter_plugin_Stmp"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Torn Edges */
#define kLivePSAdapterPluginTrnECommandStr                           "Live PSAdapter_plugin_TrnE"                                   

/** @ingroup MenuCommand
	Effect:Sketch:Water Paper */
#define kLivePSAdapterPluginWtrPCommandStr                           "Live PSAdapter_plugin_WtrP"                                   

/** @ingroup MenuCommand
	Effect:Stylize:Glowing Edges */
#define kLivePSAdapterPluginGlwECommandStr                           "Live PSAdapter_plugin_GlwE"                                   

/** @ingroup MenuCommand
	Effect:Texture:Craquelure */
#define kLivePSAdapterPluginCrqlCommandStr                           "Live PSAdapter_plugin_Crql"                                   

/** @ingroup MenuCommand
	Effect:Texture:Grain */
#define kLivePSAdapterPluginGrnCommandStr                            "Live PSAdapter_plugin_Grn "                                   

/** @ingroup MenuCommand
	Effect:Texture:Mosaic Tiles */
#define kLivePSAdapterPluginMscTCommandStr                           "Live PSAdapter_plugin_MscT"                                   

/** @ingroup MenuCommand
	Effect:Texture:Patchwork */
#define kLivePSAdapterPluginPtchCommandStr                           "Live PSAdapter_plugin_Ptch"                                   

/** @ingroup MenuCommand
	Effect:Texture:Stained Glass */
#define kLivePSAdapterPluginStnGCommandStr                           "Live PSAdapter_plugin_StnG"                                   

/** @ingroup MenuCommand
	Effect:Texture:Texturizer */
#define kLivePSAdapterPluginTxtzCommandStr                           "Live PSAdapter_plugin_Txtz"                                   

/** @ingroup MenuCommand
	Effect:Video:De-Interlace */
#define kLivePSAdapterPluginDntrCommandStr                           "Live PSAdapter_plugin_Dntr"                                   

/** @ingroup MenuCommand
	Effect:Video:NTSC Colors */
#define kLivePSAdapterPluginNTSCCommandStr                           "Live PSAdapter_plugin_NTSC"                                   

/** @ingroup MenuCommand
	View:Preview */
#define kPreviewCommandStr                                           "preview"                                                      

/** @ingroup MenuCommand
	View:Overprint Preview */
#define kInkCommandStr                                               "ink"                                                          

/** @ingroup MenuCommand
	View:Pixel Preview */
#define kRasterCommandStr                                            "raster"                                                       

/** @ingroup MenuCommand
	View:Proof Setup:Document CMYK:  */
#define kProofDocumentCommandStr                                     "proof-document"                                               

/** @ingroup MenuCommand
	View:Proof Setup:Legacy Macintosh RGB (Gamma 1.8) */
#define kProofMacRgbCommandStr                                       "proof-mac-rgb"                                                

/** @ingroup MenuCommand
	View:Proof Setup:Internet Standard RGB (sRGB) */
#define kProofWinRgbCommandStr                                       "proof-win-rgb"                                                

/** @ingroup MenuCommand
	View:Proof Setup:Monitor RGB */
#define kProofMonitorRgbCommandStr                                   "proof-monitor-rgb"                                            

/** @ingroup MenuCommand
	View:Proof Setup:Color blindness - Protanopia-type */
#define kProofColorblindpCommandStr                                  "proof-colorblindp"                                            

/** @ingroup MenuCommand
	View:Proof Setup:Color blindness - Deuteranopia-type */
#define kProofColorblinddCommandStr                                  "proof-colorblindd"                                            

/** @ingroup MenuCommand
	View:Proof Setup:Customize */
#define kProofCustomCommandStr                                       "proof-custom"                                                 

/** @ingroup MenuCommand
	View:Proof Colors */
#define kProofColorsCommandStr                                       "proofColors"                                                  

/** @ingroup MenuCommand
	View:Zoom In */
#define kZoominCommandStr                                            "zoomin"                                                       

/** @ingroup MenuCommand
	View:Zoom Out */
#define kZoomoutCommandStr                                           "zoomout"                                                      

/** @ingroup MenuCommand
	View:Fit Artboard in Window	 */
#define kFitArtboardCommandStr										 "fitin"														

/** @ingroup MenuCommand
	View:Fit All in Window */
#define kFitallCommandStr                                            "fitall"                                                       

/** @ingroup MenuCommand
	View:Actual Size */
#define kActualsizeCommandStr                                        "actualsize"                                                   

/** @ingroup MenuCommand
	View:Hide Edges */
#define kEdgeCommandStr                                              "edge"                                                         

/** @ingroup MenuCommand
	View:Hide Artboards */
#define kArtboardCommandStr                                          "artboard"                                                     

/** @ingroup MenuCommand
	View:Hide Print Tiling */
#define kPagetilingCommandStr                                        "pagetiling"                                                   

/** @ingroup MenuCommand
	View:Show Slices */
#define kAISliceFeedbackMenuCommandStr                               "AISlice Feedback Menu"                                        

/** @ingroup MenuCommand
	View:Lock Slices */
#define kAISliceLockMenuCommandStr                                   "AISlice Lock Menu"                                            

/** @ingroup MenuCommand
	View:Show Template */
#define kShowtemplateCommandStr                                      "showtemplate"                                                 

/** @ingroup MenuCommand
	View:Rulers:Show Rulers */
#define kRulerCommandStr                                             "ruler"                                                        

/** @ingroup MenuCommand
	View:Rulers:Show Video Rulers */
#define kVideorulerCommandStr                                        "videoruler"                                                   

/** @ingroup MenuCommand
	View:Rulers:Change to Global Rulers */
#define kSwitchRulerCommandStr										 "rulerCoordinateSystem"										

/** @ingroup MenuCommand
	View:Hide Bounding Box  */
#define kAIBoundingBoxToggleCommandStr                               "AI Bounding Box Toggle"                                       

/** @ingroup MenuCommand
	View:Show Transparency Grid  */
#define kTransparencyGridMenuItemCommandStr                          "TransparencyGrid Menu Item"                                   

/** @ingroup MenuCommand
	View:Show Text Threads */
#define kTextthreadsCommandStr                                       "textthreads"                                                  

/** @ingroup MenuCommand
	View:Hide Gradient Annotator */
#define kGradientFeedbackCommandStr                                  "Gradient Feedback"                                            

/** @ingroup MenuCommand
	View:Show Live Paint Gaps */
#define kShowGapsPlanetXCommandStr                                   "Show Gaps Planet X"                                           

/** @ingroup MenuCommand
	View:Guides:Hide Guides */
#define kShowguideCommandStr                                         "showguide"                                                    

/** @ingroup MenuCommand
	View:Guides:Lock Guides */
#define kLockguideCommandStr                                         "lockguide"                                                    

/** @ingroup MenuCommand
	View:Guides:Make Guides */
#define kMakeguideCommandStr                                         "makeguide"                                                    

/** @ingroup MenuCommand
	View:Guides:Release Guides */
#define kReleaseguideCommandStr                                      "releaseguide"                                                 

/** @ingroup MenuCommand
	View:Guides:Clear Guides */
#define kClearguideCommandStr                                        "clearguide"                                                   

/** @ingroup MenuCommand
	View:Smart Guides  */
#define kSnapomaticOnOffMenuItemCommandStr                           "Snapomatic on-off menu item"                                  

/** @ingroup MenuCommand
	View:Perspective Grid:Show Grid  */
#define kShowPerspectiveGridCommandStr                               "Show Perspective Grid"                                        

/** @ingroup MenuCommand
	View:Perspective Grid:Show Rulers */
#define kShowRulerCommandStr                                         "Show Ruler"                                                   

/** @ingroup MenuCommand
	View:Perspective Grid:Snap to Grid */
#define kSnapToGridCommandStr                                        "Snap to Grid"                                                 

/** @ingroup MenuCommand
	View:Perspective Grid:Lock Grid */
#define kLockPerspectiveGridCommandStr                               "Lock Perspective Grid"                                        

/** @ingroup MenuCommand
	View:Perspective Grid:Lock Station Point */
#define kLockStationPointCommandStr                                  "Lock Station Point"                                           

/** @ingroup MenuCommand
	View:Perspective Grid:Define Grid */
#define kDefinePerspectiveGridCommandStr                             "Define Perspective Grid"                                      

/** @ingroup MenuCommand
	View:Perspective Grid:Save Grid as Preset */
#define kSavePerspectiveGridAsPresetCommandStr                       "Save Perspective Grid as Preset"                              

/** @ingroup MenuCommand
	View:Show Grid */
#define kShowgridCommandStr                                          "showgrid"                                                     

/** @ingroup MenuCommand
	View:Snap to Grid */
#define kSnapgridCommandStr                                          "snapgrid"                                                     

/** @ingroup MenuCommand
	View:Snap to Point */
#define kSnappointCommandStr                                         "snappoint"                                                    

/** @ingroup MenuCommand
	View:New View */
#define kNewviewCommandStr                                           "newview"                                                      

/** @ingroup MenuCommand
	View:Edit Views */
#define kEditviewCommandStr                                          "editview"                                                     

/** @ingroup MenuCommand
	Window:New Window */
#define kNewwindowCommandStr                                         "newwindow"                                                    

/** @ingroup MenuCommand
	Window:Arrange:Cascade */
#define kCascadeCommandStr                                           "cascade"                                                      

/** @ingroup MenuCommand
	Window:Arrange:Tile */
#define kTileCommandStr                                              "tile"                                                         

/** @ingroup MenuCommand
	Window:Arrange:Float in Window */
#define kFloatInWindowCommandStr                                     "floatInWindow"                                                

/** @ingroup MenuCommand
	Window:Arrange:Float All in Windows */
#define kFloatAllInWindowsCommandStr                                 "floatAllInWindows"                                            

/** @ingroup MenuCommand
	Window:Arrange:Consolidate All Windows */
#define kConsolidateAllWindowsCommandStr                             "consolidateAllWindows"                                        

/** @ingroup MenuCommand
	Window:Workspace:Save Workspace */
#define kAdobeSaveWorkspaceCommandStr                                "Adobe Save Workspace"                                         

/** @ingroup MenuCommand
	Window:Workspace:New Workspace */
#define kAdobeNewWorkspaceCommandStr								 "Adobe New Workspace"											

/** @ingroup MenuCommand
	Window:Workspace:Manage Workspaces */
#define kAdobeManageWorkspaceCommandStr                              "Adobe Manage Workspace"                                       

/** @ingroup MenuCommand
	Window:Control */
#define kControlPalettePluginCommandStr                              "control palette plugin"                                       

/** @ingroup MenuCommand
	Window:Tools */
#define kAdobeBuiltInToolbox1CommandStr                              "AdobeBuiltInToolbox1"                                         

/** @ingroup MenuCommand
	Window:Actions */
#define kAdobeActionPaletteCommandStr                                "Adobe Action Palette"                                         

/** @ingroup MenuCommand
	Window:Align */
#define kAdobeAlignPaletteCommandStr								 "AdobeAlignObjects2"											

/** @ingroup MenuCommand
	Window:Appearance  */
#define kStylePaletteCommandStr                                      "Style Palette"                                                

/** @ingroup MenuCommand
	Window:Artboards */
#define kAdobeArtboardPaletteCommandStr                              "Adobe Artboard Palette"                                       

/** @ingroup MenuCommand
	Window:Attributes  */
#define kInternalPalettesPosingAsPlugInMenusAttributesCommandStr     "internal palettes posing as plug-in menus-attributes"         

/** @ingroup MenuCommand
	Window:Brushes  */
#define kAdobeBrushManagerMenuItemCommandStr                         "Adobe BrushManager Menu Item"                                 

/** @ingroup MenuCommand
	Window:Color  */
#define kAdobeColorPaletteCommandStr                                 "Adobe Color Palette"                                          

/** @ingroup MenuCommand
	Window:Color Guide */
#define kAdobeHarmonyPaletteCommandStr                               "Adobe Harmony Palette"                                        

/** @ingroup MenuCommand
	Window:Document Info */
#define kDocInfo1CommandStr                                          "DocInfo1"                                                     

/** @ingroup MenuCommand
	Window:Flattener Preview */
#define kAdobeFlatteningPreviewCommandStr                            "Adobe Flattening Preview"                                     

/** @ingroup MenuCommand
	Window:Gradient  */
#define kAdobeGradientPaletteCommandStr                              "Adobe Gradient Palette"                                       

/** @ingroup MenuCommand
	Window:Graphic Styles  */
#define kAdobeStylePaletteCommandStr                                 "Adobe Style Palette"                                          

/** @ingroup MenuCommand
	Window:Info */
#define kInternalPalettesPosingAsPlugInMenusInfoCommandStr           "internal palettes posing as plug-in menus-info"               

/** @ingroup MenuCommand
	Window:Layers  */
#define kAdobeLayerPalette1CommandStr                                "AdobeLayerPalette1"                                           

/** @ingroup MenuCommand
	Window:Links */
#define kAdobeLinkPaletteMenuItemCommandStr                          "Adobe LinkPalette Menu Item"                                  

/** @ingroup MenuCommand
	Window:Magic Wand */
#define kAIMagicWandCommandStr                                       "AI Magic Wand"                                                

/** @ingroup MenuCommand
	Window:Navigator */
#define kAdobeNavigator1CommandStr                                   "AdobeNavigator"                                               

/** @ingroup MenuCommand
	Window:Pathfinder  */
#define kAdobePathfinderPalette1CommandStr                           "Adobe PathfinderUI"											

/** @ingroup MenuCommand
	Window:Separations Preview */
#define kAdobeSeparationPreviewPaletteCommandStr                     "Adobe Separation Preview Panel"                               

/** @ingroup MenuCommand
	Window:Stroke  */
#define kAdobeStrokePaletteCommandStr                                "Adobe Stroke Palette"                                         

/** @ingroup MenuCommand
	Window:SVG Interactivity */
#define kAdobeSVGInteractivityPaletteCommandStr                      "Adobe SVG Interactivity Palette"                              

/** @ingroup MenuCommand
	Window:Swatches */
#define kAdobeSwatchesMenuItemCommandStr                             "Adobe Swatches Menu Item"                                     

/** @ingroup MenuCommand
	Window:Symbols  */
#define kAdobeSymbolPaletteCommandStr                                "Adobe Symbol Palette"                                         

/** @ingroup MenuCommand
	Window:Transform  */
#define kAdobeTransformObjects1CommandStr                            "AdobeTransformObjects1"                                       

/** @ingroup MenuCommand
	Window:Transparency  */
#define kAdobeTransparencyPaletteMenuItemCommandStr                  "Adobe Transparency Palette Menu Item"                         

/** @ingroup MenuCommand
	Window:Type:Character */
#define kInternalPalettesPosingAsPlugInMenusCharacterCommandStr      "internal palettes posing as plug-in menus-character"          

/** @ingroup MenuCommand
	Window:Type:Character Styles */
#define kCharacterStylesCommandStr                                   "Character Styles"                                             

/** @ingroup MenuCommand
	Window:Type:Flash Text */
#define kFlashTextCommandStr                                         "Flash Text"                                                   

/** @ingroup MenuCommand
	Window:Type:Glyphs */
#define kAlternateGlyphPalettePlugin2CommandStr                      "alternate glyph palette plugin 2"                             

/** @ingroup MenuCommand
	Window:Type:OpenType */
#define kInternalPalettesPosingAsPlugInMenusOpentypeCommandStr       "internal palettes posing as plug-in menus-opentype"           

/** @ingroup MenuCommand
	Window:Type:Paragraph */
#define kInternalPalettesPosingAsPlugInMenusParagraphCommandStr      "internal palettes posing as plug-in menus-paragraph"          

/** @ingroup MenuCommand
	Window:Type:Paragraph Styles */
#define kAdobeParagraphStylesPaletteCommandStr                       "Adobe Paragraph Styles Palette"                               

/** @ingroup MenuCommand
	Window:Type:Tabs */
#define kInternalPalettesPosingAsPlugInMenusTabCommandStr            "internal palettes posing as plug-in menus-tab"                

/** @ingroup MenuCommand
	Window:Variables */
#define kAdobeVariablesPaletteMenuItemCommandStr                     "Adobe Variables Palette Menu Item"                            

/** @ingroup MenuCommand
	Window:Brush Libraries:No Libraries found */
#define kAdobeBrushMgrNoLibrariesMenuItemCommandStr                  "AdobeBrushMgr No libraries menu item"                         

/** @ingroup MenuCommand
	Window:Brush Libraries:Other Library */
#define kAdobeBrushMgrOtherLibrariesMenuItemCommandStr               "AdobeBrushMgr Other libraries menu item"                      

/** @ingroup MenuCommand
	Window:Graphic Style Libraries:No Libraries found */
#define kAdobeArtStylePluginNoLibrariesMenuItemCommandStr            "Adobe Art Style Plugin No libraries menu item"                

/** @ingroup MenuCommand
	Window:Graphic Style Libraries:Other Library */
#define kAdobeArtStylePluginOtherLibrariesMenuItemCommandStr         "Adobe Art Style Plugin Other libraries menu item"             

/** @ingroup MenuCommand
	Window:Symbol Libraries:No Libraries found */
#define kAdobeSymbolPalettePluginNoLibrariesMenuItemCommandStr       "Adobe Symbol Palette Plugin No libraries menu item"           

/** @ingroup MenuCommand
	Window:Symbol Libraries:Other Library */
#define kAdobeSymbolPalettePluginOtherLibrariesMenuItemCommandStr    "Adobe Symbol Palette Plugin Other libraries menu item"        

/** @ingroup MenuCommand
	Help:Illustrator Help */
#define kHelpcontentCommandStr                                       "helpcontent"                                                  

/** @ingroup MenuCommand
	Help:Welcome Screen */
#define kWelcomeScreenMenuItemCommandStr                             "Welcome screen menu item"                                     

/** @ingroup MenuCommand
	Help:Debug:Memory Use Checkpoint */
#define kMemoryUseCheckpointCommandStr                               "Memory Use Checkpoint"                                        

/** @ingroup MenuCommand
	Help:Debug:Save Memory Use */
#define kSaveMemoryUseCommandStr                                     "Save Memory Use"                                              

/** @ingroup MenuCommand
	Help:Debug:Count Objects */
#define kCountObjectsCommandStr                                      "Count Objects"                                                

/** @ingroup MenuCommand
	Help:Debug:Object Counts */
#define kObjectCountsCommandStr                                      "Object Counts"                                                

/** @ingroup MenuCommand
	Help:Debug:Track API Refs */
#define kTrackAPIRefsCommandStr                                      "Track API Refs"                                               

/** @ingroup MenuCommand
	Help:Debug:Enable New Rendering */
#define kEnableNewRenderingCommandStr                                "Enable New Rendering"                                         

/** @ingroup MenuCommand
	Help:Debug:Enable Rendering Timer */
#define kEnableRenderingTimerCommandStr                              "Enable Rendering Timer"                                       

/** @ingroup MenuCommand
	Help:Debug:Purge Rendering Cache */
#define kPurgeRenderingCacheCommandStr                               "Purge Rendering Cache"                                        

/** @ingroup MenuCommand
	Help:Debug:Redraw */
#define kRedrawCommandStr                                            "Redraw"                                                       

/** @ingroup MenuCommand
	Help:Debug:Dump Application Heap Used */
#define kDumpApplicationHeapUsedCommandStr                           "Dump Application Heap Used"                                   

/** @ingroup MenuCommand
	Help:Debug:Disable Greeking for New Rendering */
#define kDisableGreekingForNewRenderingCommandStr                    "Disable Greeking for New Rendering"                           

/** @ingroup MenuCommand
	Help:Debug:Enable Threaded Rendering */
#define kEnableThreadedRenderingCommandStr                           "Enable Threaded Rendering"                                    

/** @ingroup MenuCommand
	Help:Debug:Enable AGM Threading */
#define kEnableAGMThreadingCommandStr                                "Enable AGM Threading"                                         

/** @ingroup MenuCommand
	Help:Debug:Enable Hyper Threading */
#define kEnableHyperThreadingCommandStr								 "Enable Hyper Threading"										

/** @ingroup MenuCommand
	Help:Debug:Enable AGM Internal Memory Pool */
#define kEnableAGMInternalMemoryPoolCommandStr                       "Enable AGM Internal Memory Pool"                              

/** @ingroup MenuCommand
	Help:Debug:Enable QuickPort Quartz */
#define kEnableQuickPortQuartzCommandStr                             "Enable QuickPort Quartz"                                      

/** @ingroup MenuCommand
	Help:Debug:Heap Check Running */
#define kHeapCheckRunningCommandStr                                  "Heap Check Running"                                           

/** @ingroup MenuCommand
	Help:Debug:Crash */
#define kCrashCommandStr                                             "Crash"                                                        

/** @ingroup MenuCommand
	Help:Debug:Enable PGF Recovery */
#define kEnablePGFRecoveryCommandStr                                 "Enable PGF Recovery"                                          

/** @ingroup MenuCommand
	Help:Debug:Enable ATE Read Recovery */
#define kEnableATEReadRecoveryCommandStr                             "Enable ATE Read Recovery"                                     

/** @ingroup MenuCommand
	Help:Debug:Enable ATE Write Recovery */
#define kEnableATEWriteRecoveryCommandStr                            "Enable ATE Write Recovery"                                    

/** @ingroup MenuCommand
	Help:Debug:Trace Counted Object Refs */
#define kTraceCountedObjectRefsCommandStr                            "Trace Counted Object Refs"                                    

/** @ingroup MenuCommand
	Help:Debug:Check Heap */
#define kCheckHeapCommandStr                                         "Check Heap"                                                   

/** @ingroup MenuCommand
	Help:Debug:Track Blocks */
#define kTrackBlocksCommandStr                                       "Track Blocks"                                                 

/** @ingroup MenuCommand
	Help:Debug:Defer Freeing */
#define kDeferFreeingCommandStr                                      "Defer Freeing"                                                

/** @ingroup MenuCommand
	Help:Debug:Debug Window */
#define kDebugWindowCommandStr                                       "Debug Window"                                                 

/** @ingroup MenuCommand
	Help:Debug:Flush Preference to File */
#define kFlushPreferenceToFileCommandStr                             "Flush Preference to File"                                     

/** @ingroup MenuCommand
	Help:Debug:Reinterpret Grayscale Image Color Space */
#define kReinterpretGrayscaleImageColorSpaceCommandStr               "Reinterpret Grayscale Image Color Space"                      

/** @ingroup MenuCommand
	Help:Debug:Split and Interleave Raster Channels */
#define kSplitAndInterleaveRasterChannelsCommandStr                  "Split and Interleave Raster Channels"                         

/** @ingroup MenuCommand
	Help:Debug:Populate Live Effect Graphic Styles */
#define kPopulateLiveEffectGraphicStylesCommandStr                   "Populate Live Effect Graphic Styles"                          

/** @ingroup MenuCommand
	Help:Debug:Use ContainsTransparency Flag */
#define kUseContainsTransparencyFlagCommandStr                       "Use ContainsTransparency Flag"                                

/** @ingroup MenuCommand
	Help:Debug:Add Known Style */
#define kAddKnownStyleCommandStr                                     "Add Known Style"                                              

/** @ingroup MenuCommand
	Help:Debug:Mark Logs */
#define kMarkLogsCommandStr                                          "Mark Logs"                                                    

/** @ingroup MenuCommand
	Help:Debug:Clear Logs */
#define kClearLogsCommandStr                                         "Clear Logs"                                                   

/** @ingroup MenuCommand
	Help:Debug:Run UnicodeString testbed */
#define kRunUnicodeStringTestbedCommandStr                           "Run UnicodeString testbed"                                    

/** @ingroup MenuCommand
	Help:Debug:Enable Gradient Feedback */
#define kGradientFeedbackDebugCommandStr                             "Gradient Feedback Debug"                                      

/** @ingroup MenuCommand
	Help:Debug:Unit Testing */
#define kAdobeUnitTestingCommandStr                                  "Adobe Unit testing"                                           

/** @ingroup MenuCommand
	Help:Create Eve Dialog */
#define kAdamEveDialogMenuCommandStr                                 "Adam Eve dialog menu"                                         

/** @ingroup MenuCommand
	Help:About Illustrator */
#define kAboutCommandStr                                             "about"                                                        

/** @ingroup MenuCommand
	Help:System Info */
#define kSystemInfoStr												 "System Info"													

/** @ingroup MenuCommand
	Other Panel:New Symbol  */
#define kAdobeNewSymbolShortcutCommandStr                            "Adobe New Symbol Shortcut"                                    

/** @ingroup MenuCommand
	Other Panel:Show Color Panel (Secondary) */
#define kAdobeColorPaletteSecondaryCommandStr                        "Adobe Color Palette Secondary"                                

/** @ingroup MenuCommand
	Other Panel:Actions Batch */
#define kAdobeActionsBatchCommandStr                                 "Adobe Actions Batch"                                          

/** @ingroup MenuCommand
	Other Panel:Add New Fill  */
#define kAdobeNewFillShortcutCommandStr                              "Adobe New Fill Shortcut"                                      

/** @ingroup MenuCommand
	Other Panel:Add New Stroke  */
#define kAdobeNewStrokeShortcutCommandStr                            "Adobe New Stroke Shortcut"                                    

/** @ingroup MenuCommand
	Other Panel:New Graphic Style */
#define kAdobeNewStyleShortcutCommandStr                             "Adobe New Style Shortcut"                                     

/** @ingroup MenuCommand
	Other Panel:New Layer  */
#define kAdobeLayerPalette2CommandStr                                "AdobeLayerPalette2"                                           

/** @ingroup MenuCommand
	Other Panel:New Layer with Dialog  */
#define kAdobeLayerPalette3CommandStr                                "AdobeLayerPalette3"                                           

/** @ingroup MenuCommand
	Other Panel:Update Link */
#define kAdobeUpdateLinkShortcutCommandStr                           "Adobe Update Link Shortcut"                                   

/** @ingroup MenuCommand
	Other Panel:Navigator Options */
#define kAdobeNavigator2CommandStr                                   "AdobeNavigator2"                                              

/** @ingroup MenuCommand
	Other Panel:New Swatch */
#define kAdobeNewSwatchShortcutMenuCommandStr                        "Adobe New Swatch Shortcut Menu"

#include "AIHeaderEnd.h"

#endif // __AIMenuCommandString__

