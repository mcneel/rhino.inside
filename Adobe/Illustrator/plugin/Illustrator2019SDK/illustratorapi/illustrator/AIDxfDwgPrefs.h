/*
 *        Name:	AIDxfDwgPrefs.h
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2006-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

//-----------------------------------------------------------------------------

#ifndef __AIDXFDWGPREFS_h__
#define __AIDXFDWGPREFS_h__

// includes
#include "AIHeaderBegin.h"


// ------------------------------------------------------------------
// enumerations


/** AutoCAD file filter preference constants: file format. */
enum DxfDwgAutoCADFileFormat
{
	/** AutoCAD Drawing Exchange Format (.dxf) */
	eFormatDxf = 0,
	/** AutoCAD Drawing Format (.dwg) */
	eFormatDwg
};

/** AutoCAD file filter preference constants: version. */
enum DxfDwgAutoCADVersion
{
	/** AutoCAD version R13/LT95 */
	eR13 = 0,
	/** AutoCAD version R14/LT98/LT97 */
	eR14,
	/** AutoCAD version 2000/LT2000 */
	eR15,
	/** AutoCAD version 2004/2005/2006 */
	eR18,
	/** AutoCAD version 2007/2008/2009 */
	eR21,
	/** AutoCad version 2010/2011/2012(Not all the features of 2012 though) */
	eR24
};

/** AutoCAD file filter preference constants: measurement units. */
enum DxfDwgUnit
{
	ePoints = 0,
	ePicas,
	eInches,
	eMillimeters,
	eCentimeters,
	ePixels,
	eFeets,
	eNumberOfUnits
};

/** AutoCAD file filter preference constants: color depth. */
enum DxfDwgColors
{
	eColors8 = 0,
	eColors16,
	eColors256,
	eColorsTrueColor
};

/** AutoCAD file filter preference constants: scale options. */
enum DxfDwgGlobalScaleOption
{
	/** Do not apply scaling. */
	eOriginalSize = 0,
	/** Scale by optimum amount so as to fit the artboard size. */
	eFitArtboard,
	/** Scale by value specified in \c #DxfDwgExportPrefs::m_unitScaleRatio. */
	eScaleByValue
};

/** AutoCAD file filter preference constants: raster format. */
enum DxfDwgRasterFormat
{
	/** PNG */
	eRasterPNG = 0,
	/** JPEG */
	eRasterJPEG
};

/** AutoCAD file filter preference constants: editability level.*/
enum DxfDwgExportOption
{
	ePreserveAppearance = 0,
	eMaximumEditability
};

// ------------------------------------------------------------------
// constants

/** AutoCAD file filter preference constants: prefix. 	 */
#define kDxfDwgPreferencePrefix						"DxfDwg"

/** AutoCAD file filter preference constants: default AutoCAD name.	 */
#define kFormatAutoCADName							"AutoCAD file"

/** AutoCAD file filter preference constants: DFX format name.	 */
#define kFormatDxfName								"DXF"
#define kDxfExportFileFormatName					"DXF Export"
#define kDxfImportFileFormatName					"DXF Import" 

/** AutoCAD file filter preference constants: DFX format file extension.	 */
#define kFormatDxfExtn								"dxf"

/** AutoCAD file filter preference constants: DWG format name. */
#define kFormatDwgName								"DWG"
#define kDwgExportFileFormatName					"DWG Export"
#define kDwgImportFileFormatName					"DWG Import" 

/** AutoCAD file filter preference constants: DWG format file extension */
#define kFormatDwgExtn								"dwg"

// export related
/** AutoCAD file filter preference constants: file format for export 	 */
#define kDxfDwgExportAutoCADFileFormat				"ExportAutoCADFileFormat"
/** AutoCAD file filter preference constants: default file format for export  	 */
#define kDxfDwgDefaultExportAutoCADFileFormat		eFormatDwg

/** AutoCAD file filter preference constants: AutoCAD version for export */
#define kDxfDwgExportAutoCADVersion					"ExportAutoCADVersion"
/** AutoCAD file filter preference constants: default AutoCAD version for export	 */
#define kDxfDwgDefaultExportAutoCADVersion			eR24

/** AutoCAD file filter preference constants: scale ratio for export  */
#define kDxfDwgExportUnitScaleRatio					"ExportUnitScaleRatio"
/** AutoCAD file filter preference constants: default scale ratio for export, a percentage where 1.0=100%  	 */
#define kDxfDwgDefaultExportUnitScaleRatio			1.0

/** AutoCAD file filter preference constants: measurement units for export	 */
#define kDxfDwgExportUnit							"ExportUnit"
/** AutoCAD file filter preference constants: default measurement units for export	 */
#define kDxfDwgDefaultExportUnit					eMillimeters

/** AutoCAD file filter preference constants: color depth for export	 */
#define kDxfDwgExportColors							"Colors"
/** AutoCAD file filter preference constants: default color depth for export	 */
#define kDxfDwgDefaultExportColors					eColorsTrueColor

/** AutoCAD file filter preference constants: raster format for export (PNG or JPEG)	 */
#define kDxfDwgExportRasterFormat					"ExportRasterFormat"
/** AutoCAD file filter preference constants: default raster format for export	 */
#define kDxfDwgDefaultExportRasterFormat			eRasterPNG

/** AutoCAD file filter preference constants: editability level for export */
#define kDxfDwgExportOption							"ExportOption"
/** AutoCAD file filter preference constants: default editability level for export */
#define kDxfDwgDefaultExportOption					eMaximumEditability

/** AutoCAD file filter preference constants: whether to export only selected art.	 */
#define kDxfDwgExportSelectedArtOnly				"ExportSelectedArtOnly"
/** AutoCAD file filter preference constants: default for whether to export only selected art.  */
#define kDxfDwgDefaultExportSelectedArtOnly			false

/** AutoCAD file filter preference constants: whether to alter paths for appearance   */
#define kDxfDwgExportAlterPathsForAppearance		"ExportAlterPathsForAppearance"
/** AutoCAD file filter preference constants: default for whether to alter paths for appearance   */
#define kDxfDwgDefaultExportAlterPathsForAppearance	false

/** AutoCAD file filter preference constants: whether to export outline text   */
#define kDxfDwgExportOutlineText					"ExportOutlineText"
/** AutoCAD file filter preference constants: default for whether to export outline text  */
#define kDxfDwgDefaultExportOutlineText				false

/** AutoCAD file filter preference constants: whether to scale line weights on export   */
#define kDxfDwgExportScaleLineweights				"ExportScaleLineweights"
/** AutoCAD file filter preference constants: default for whether to scale line weights on export */
#define kDxfDwgDefaultExportScaleLineweights		false

// import related
/** AutoCAD file filter preference constants: scaling type for import   */
#define kDxfDwgImportGlobalScaleOption				"ImportGlobalScaleOption"
/** AutoCAD file filter preference constants: default scaling type for import    */
#define kDxfDwgDefaultImportGlobalScaleOption		eFitArtboard

/** AutoCAD file filter preference constants: global scale value for import   */
#define kDxfDwgImportGlobalScaleValue				"ImportGlobalScaleValue"
/** AutoCAD file filter preference constants: default global scale value for import, a percentage.  */
#define kDxfDwgDefaultImportGlobalScaleValue		100

/** AutoCAD file filter preference constants: scale ratio for import,   */
#define kDxfDwgImportUnitScaleRatio					"ImportUnitScaleRatio"
/** AutoCAD file filter preference constants: default scale ratio for import, a percentage where 1.0=100%   */
#define kDxfDwgDefaultImportUnitScaleRatio			1.0

/** AutoCAD file filter preference constants: measurement units for import   */
#define kDxfDwgImportUnit							"ImportUnit"
/** AutoCAD file filter preference constants: default measurement units for import  */
#define kDxfDwgDefaultImportUnit					eMillimeters

/** AutoCAD file filter preference constants: layout for import, a descriptive string
	defined in the DWG or DXF file.*/
#define kDxfDwgImportLayout							"ImportLayout"
/** AutoCAD file filter preference constants: default layout for import  */
#define kDxfDwgDefaultImportLayout					""

/** AutoCAD file filter preference constants: whether to center art on import.   */
#define kDxfDwgImportCenterArtwork					"ImportCenterArtwork"

/** AutoCAD file filter preference constants: whether to center art on import.   */
#define kDxfDwgImportMergeLayers					"ImportMergeLayers"

/** AutoCAD file filter preference constants: default for whether to center art on import.   */
#define kDxfDwgDefaultImportCenterArtwork			true

/** AutoCAD file filter preference constants: default for whether to merge layers on import.   */
#define kDxfDwgDefaultImportMergeLayers			false

/** AutoCAD file filter preference constants: whether to scale line weights on import.   */
#define kDxfDwgImportScaleLineweights				"ImportScaleLineweights"
/** AutoCAD file filter preference constants: default for whether to scale line weights on import.   */
#define kDxfDwgDefaultImportScaleLineweights		false

// ------------------------------------------------------------------
// structures

/** AutoCAD file filter preferences.   */
struct DxfDwgExportPrefs
{
	/** File format (DXF or DWG). */
	DxfDwgAutoCADFileFormat		m_fileFormat;
	/** AutoCAD version */
	DxfDwgAutoCADVersion		m_version;
	/** Scale ration to use when scale option is \c #eScaleByValue. */
	AIReal						m_unitScaleRatio;
	/** Measurement units. */
	DxfDwgUnit					m_unit;
	/** Color depth. */
	DxfDwgColors				m_colors;
	/** Raster format (PNG or JPEG) */
	DxfDwgRasterFormat			m_rasterFormat;
	/** Editability level of exported file. */
	DxfDwgExportOption			m_exportOption;
	/** Whether to export only selected art. */
	AIBoolean					m_isExportSelectedArtOnly;
	/** Whether to alter path appearance by applying the \c #AIPathfinderData
		options and parameters. */
	AIBoolean					m_isAlterPathForAppearance;
	/** Whether to export text as outline text. */
	AIBoolean					m_isOutlineText;
	/** Whether to scale line weights on export. */
	AIBoolean					m_isScaleLineweights;

};


#include "AIHeaderEnd.h"

#endif //__AIDXFDWGPREFS_h__
