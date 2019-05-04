#ifndef __SloTextdomTypes___
#define __SloTextdomTypes___


// error codes
#define kNoErr					0
#define kOutOfMemoryErr			'!MEM'
#define kBadParameterErr		'PARM'
#define kNotImplementedErr		'!IMP'
#define kCantHappenErr			'CANT'

namespace ATETextDOM
{

#ifdef WINDOWS
    typedef __int32 Int32;
#endif

#ifdef MACINTOSH
    typedef int32_t Int32;
#endif

#ifdef WINDOWS
    typedef __int32 ATETextDomErr;
#endif
#ifdef MACINTOSH
    typedef int32_t ATETextDomErr;
#endif

	typedef unsigned short Unicode;

	typedef float Float;
	typedef double Real;

	typedef struct _t_FloatMatrix {
		Float a, b, c, d, tx, ty;
	} FloatMatrix;

	typedef struct _t_FloatPoint {
		Float h, v;
	} FloatPoint;

	typedef struct _t_RealMatrix {
		Real a, b, c, d, tx, ty;
	} RealMatrix;

	typedef struct _t_RealPoint {
		Real h, v;
	} RealPoint;
	
}
#endif