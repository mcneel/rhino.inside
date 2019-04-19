#ifndef _AIAGMTYPES_H_
#define _AIAGMTYPES_H_

#include "AITypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _t_AIAGMColrSpace AIAGMColorSpace;
typedef int AIAGMColorSpaceFamily;
typedef struct _t_AIAGMRasterPort AIAGMRasterPort;
typedef struct _t_AIAGMDisplayListPort AIAGMDisplayListPort;
typedef struct _t_AGMBIBPort AIAGMBIBPort; // (aka AGMPort*) can safely pass AIAGMBIBPort across library boundaries.
typedef struct _t_AGMBIBColorSpace AIAGMBIBColorSpace; // (aka AGMColorSpace*) can safely pass AIAGMBIBColorSpace across library boundaries.
typedef struct _t_AIAGMPort AIAGMPort;
typedef AIAGMPort* AIAGMPortPtr;
/** @deprecated Deprecated with the move to CoolType 5. Use \c #AICTText instead. */
typedef struct _t_AIAGMTextRecord AIAGMTextRecord;
typedef struct _t_AICTText AICTText;
typedef struct _t_AIAGMColorConvertOptions AIAGMColorConvertOptions;

/** AGM comment callback procedure template. */
typedef void (*AIAGMCommentProcPtr)( const AIAGMPort* dstPort, ASInt32 comment,
											 void* commentData, ASUInt32 dataLength );

/** AGM option constants. */
typedef enum {
	kAIAGMOptionsGet,
	kAIAGMOptionsSet,
	kAIAGMOptionsEnable,
	kAIAGMOptionsDisable,
	_MAX_AIAGMOptionsOp = 0x40000000  /* force 32 bit enum */
} AIAGMOptionsOp;

/** AGM text option constants. */
enum {
	kAIAGMOptionNone = 0,
	kAIAGMOptionAAText = 1,
	kAIAGMOptionAAGraphics = 2,
	kAIAGMOptionOverscanImage = 4,
	kAIAGMOptionTextAsPaths = 8,
	kAIAGMOptionResampleImage = 0x10,
	kAIAGMOptionHintGlyphLocations = 0x40,
	kAIAGMOptionAANoSubPixelWidths = 0x80,
	kAIAGMOptionEnableOverprint = 0x100,
	kAIAGMOptionAAImages = 0x10000,
	kAIAGMOptionLinearizeAAOnly = 0x2000,
	kAIAGMOptionAATextPreview = 0x8000,
	kAIAGMOptionUnhintedText = 0x40000,
	kAIAGMOptionOverscannedText = 0x80000,
	kAIAGMOptionIllustratorPixelPerfectDrawing = 0x200000,
	kAIAGMOptionUseFloatReducer = 0x8000000
};

// Keep these synchronized with enum AGMBlendingMode!
/** AGM blending option constants. */
enum AIAGMBlendingMode {
	kAIAGMBlendNormal,
	kAIAGMBlendMultiply,
	kAIAGMBlendScreen,
	kAIAGMBlendDifference,
	kAIAGMBlendDarken,
	kAIAGMBlendLighten,
	kAIAGMBlendColorDodge,
	kAIAGMBlendColorBurn,
	kAIAGMBlendExclusion,
	kAIAGMBlendHardLight,
	kAIAGMBlendOverlay,
	kAIAGMBlendSoftLight,
	kAIAGMBlendHue,
	kAIAGMBlendSaturation,
	kAIAGMBlendColor,
	kAIAGMBlendLuminosity,
	kAIAGMNumBlendingModes,
	_MAX_AIAGMBlendingMode = 0x40000000   /* force 32 bit enum */
};

/** Color table structure. */
struct AIAGMColorTab	{
	/** The number of colors in the table. */
	ai::int32	numColors;
	/** Pointer to the color data. */
	void*	theColors;
    
    void Init()
    {
        numColors = 0;
        theColors = nullptr;
    }
};

/** Rectangle structure. */
struct AIAGMInt16Rect {
	/** Left edge.  */
	ai::int16	xMin;
	/** Bottom edge. */
	ai::int16	yMin;
	/** Right edge. */
	ai::int16	xMax;
	/** Top edge. */
	ai::int16	yMax;
    
    void Init()
    {
        xMin = 0;
        yMin = 0;
        xMax = 0;
        yMax = 0;
    }
}
;

/** Image record structure.*/
struct AIAGMImageRecord	{
	/** Bounding box of the image. */
	AIAGMInt16Rect	bounds;
	/** Pointer to the image data. */
	void*			baseAddr;
	/** Width of the image in bytes. The number of bytes
	varies with the bits-per-pixel of the color space. */
	ai::int32			byteWidth;
	/** Color space. */
	ai::int16			colorSpace;
	/** Number of bits per pixel. */
	ai::int16			bitsPerPixel;
	/** Decode array.  */
	AIFloat*		decodeArray;
	/** Color table. */
	AIAGMColorTab	colorTab;
    
    void Init()
    {
        baseAddr = nullptr;
        byteWidth = 0;
        colorSpace = 0;
        bitsPerPixel = 0;
        decodeArray = nullptr;
		bounds.Init();
		colorTab.Init();
    }
};


#ifdef __cplusplus
}
#endif

#endif // _AIAGMTYPES_H_
