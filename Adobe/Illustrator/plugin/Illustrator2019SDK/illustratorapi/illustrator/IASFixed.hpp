/***********************************************************************/
/*                                                                     */
/* IASFixed.hpp                                                        */
/* ASFixed object wrapper class                                        */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2007 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/*                                                                     */
/* Started by Dave Lazarony, 03/10/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IASFixed_hpp__
#define __IASFixed_hpp__

/*
 * Includes
 */
 
#include "ASTypes.h"

/*
 * Types and Defines
 */

// Mac headers define GetItem.  DRL 7/29/96
#ifdef GetItem
#undef GetItem
#endif

#define kASFixedZero		 	((ASFixed) 0x00000000)
#define kASFixedHalf			((ASFixed) 0x00008000)	
#define kASFixedOne				((ASFixed) 0x00010000)
#define kASFixedMin			 	((ASFixed) 0x80000000)
#define kASFixedMax 			((ASFixed) 0x7FFFFFFF)
#define kASFixedUnknown 		((ASFixed) 0x80000000)

typedef long double asdouble_t;

#define _ShortToASFixed(a)		((ASFixed)(a) << 16)

/*
 * Global Suite Pointer
 */

class IASFixed;
inline int operator != (const IASFixed& a, const IASFixed& b);
inline int operator > (const IASFixed& a, const IASFixed& b);
inline int operator >= (const IASFixed& a, const IASFixed& b);
inline int operator <= (const IASFixed& a, const IASFixed& b);

class IASFixed
{

public:
	IASFixed();			
	IASFixed(const ASFixed a);
	IASFixed(const short a);
//#ifndef	__TREAT_ASINT32_AS_INT__
//	IASFixed(const int a);
//#endif
	IASFixed(const float a);
	IASFixed(const double a);

	// conversion operators

	operator ASFixed() const;
	operator short() const;
/*#ifndef	__TREAT_ASINT32_AS_INT__
	operator int() const;
#endif
*/
	operator float() const;
	operator double() const;

	// comparison operators

	friend inline int operator == (const IASFixed& a, const IASFixed& b);
	//friend inline int operator == (short a, const IASFixed& b);
	//friend inline int operator == (const IASFixed& a, short b);
	friend inline int operator == (int a, const IASFixed& b);
	friend inline int operator == (const IASFixed& a, int b);
	friend inline int operator == (const float& a, const IASFixed& b);
	friend inline int operator == (const IASFixed& a, const float& b);
	friend inline int operator == (const double& a, const IASFixed& b);
	friend inline int operator == (const IASFixed& a, const double& b);

	friend inline int operator != (const IASFixed& a, const IASFixed& b);
	//friend inline int operator != (short a, const IASFixed& b);
	//friend inline int operator != (const IASFixed& a, short b);
	friend inline int operator != (int a, const IASFixed& b);
	friend inline int operator != (const IASFixed& a, int b);
	friend inline int operator != (const float& a, const IASFixed& b);
	friend inline int operator != (const IASFixed& a, const float& b);
	friend inline int operator != (const double& a, const IASFixed& b);
	friend inline int operator != (const IASFixed& a, const double& b);

	friend inline int operator > (const IASFixed& a, const IASFixed& b);
	//friend inline int operator > (short a, const IASFixed& b);
	//friend inline int operator > (const IASFixed& a, short b);
	friend inline int operator > (int a, const IASFixed& b);
	friend inline int operator > (const IASFixed& a, int b);
	friend inline int operator > (const float& a, const IASFixed& b);
	friend inline int operator > (const IASFixed& a, const float& b);
	friend inline int operator > (const double& a, const IASFixed& b);
	friend inline int operator > (const IASFixed& a, const double& b);

	friend inline int operator < (const IASFixed& a, const IASFixed& b);
	//friend inline int operator < (short a, const IASFixed& b);
	//friend inline int operator < (const IASFixed& a, short b);
	friend inline int operator < (int a, const IASFixed& b);
	friend inline int operator < (const IASFixed& a, int b);
	friend inline int operator < (const float& a, const IASFixed& b);
	friend inline int operator < (const IASFixed& a, const float& b);
	friend inline int operator < (const double& a, const IASFixed& b);
	friend inline int operator < (const IASFixed& a, const double& b);

	friend inline int operator >= (const IASFixed& a, const IASFixed& b);
	//friend inline int operator >= (short a, const IASFixed& b);
	//friend inline int operator >= (const IASFixed& a, short b);
	friend inline int operator >= (int a, const IASFixed& b);
	friend inline int operator >= (const IASFixed& a, int b);
	friend inline int operator >= (const float& a, const IASFixed& b);
	friend inline int operator >= (const IASFixed& a, const float& b);
	friend inline int operator >= (const double& a, const IASFixed& b);
	friend inline int operator >= (const IASFixed& a, const double& b);

	friend inline int operator <= (const IASFixed& a, const IASFixed& b);
	//friend inline int operator <= (short a, const IASFixed& b);
	//friend inline int operator <= (const IASFixed& a, short b);
	friend inline int operator <= (int a, const IASFixed& b);
	friend inline int operator <= (const IASFixed& a, int b);
	friend inline int operator <= (const float& a, const IASFixed& b);
	friend inline int operator <= (const IASFixed& a, const float& b);
	friend inline int operator <= (const double& a, const IASFixed& b);
	friend inline int operator <= (const IASFixed& a, const double& b);

	// unary minus

	friend inline IASFixed operator - (const IASFixed& a);

	// binary arithmetic operators

	friend inline IASFixed operator + (const IASFixed& a, const IASFixed& b);
	friend inline IASFixed operator - (const IASFixed& a, const IASFixed& b);
	friend inline IASFixed operator * (const IASFixed& a, const IASFixed& b);
	friend inline IASFixed operator / (const IASFixed& a, const IASFixed& b);

	// unary arithmetic opererators

	void operator += (const IASFixed& a);
	void operator -= (const IASFixed& a);
	void operator *= (const IASFixed& a);
	void operator /= (const IASFixed& a);

	friend inline IASFixed operator >> (const IASFixed& a, int amount);
	friend inline IASFixed operator << (const IASFixed& a, int amount);

	friend inline IASFixed abs(const IASFixed& a);

protected:
	ASFixed f;

	static inline asdouble_t FixToX(ASFixed x);
	static inline ASFixed XToFix(asdouble_t x);
	static inline ASFixed FixedMul(ASFixed a, ASFixed b);
	static inline ASFixed FixedDiv(ASFixed x, ASFixed y);
	static inline ASFixed FixedSumChk(ASFixed a, ASFixed b);

};

inline asdouble_t IASFixed::FixToX(ASFixed x)
{
	return ((asdouble_t)x) / 65536.0;
}

inline ASFixed IASFixed::XToFix(asdouble_t x)
{
	ASFixed fx;

	if (x - 1.0 >= (asdouble_t)0x00007fff)
		fx = 0x7fffffff;
	else if (x + 1.0 <= -(asdouble_t)0x00008000)
		fx = 0x80000000;
	else
		fx = (ASFixed)(x * (asdouble_t)0x00010000 + (x > 0.0 ? 0.5 : -0.5));

	return fx;
}

inline ASFixed IASFixed::FixedMul(ASFixed a, ASFixed b)
{
	asdouble_t da, db;
	ASFixed fx;

	da = FixToX(a);
	db = FixToX(b);

	fx = XToFix(da * db);

	return fx;
}

inline ASFixed IASFixed::FixedDiv(ASFixed x, ASFixed y)
{
	if (!y)
		{
		if (x < 0)
			return 0x80000000;
		else
			return 0x7fffffff;
		}

	return XToFix((asdouble_t)x / (asdouble_t)y);
}

inline ASFixed IASFixed::FixedSumChk(ASFixed a, ASFixed b)
{
	if (a == kASFixedMax || b == kASFixedMax)
		return kASFixedMax;
	else if (a == kASFixedMin || b == kASFixedMin)
		return kASFixedMin;
	else
		{
		ASFixed c;
		bool aNeg, bNeg;

		aNeg = a < kASFixedZero;
		bNeg = b < kASFixedZero;
		c = a + b;
		if (aNeg == bNeg && aNeg != (c < kASFixedZero))
			c = aNeg ? kASFixedMin : kASFixedMax;
		return c;
		}
}

inline IASFixed::IASFixed() 			
{ 
}

inline IASFixed::IASFixed(const ASFixed a)
{ 
	f = a;
}

inline IASFixed::IASFixed(const short a)
{ 
	f = ASFixed(a) << 16;
}
//#ifndef	__TREAT_ASINT32_AS_INT__
//inline IASFixed::IASFixed(const int a)
//{ 
//	f = ASFixed(a) << 16;
//}
//#endif
inline IASFixed::IASFixed(const float a)
{ 
	f = long(a * 65536.0);
}

inline IASFixed::IASFixed(const double a)
{ 
	f = long(a * 65536.0);
}

inline IASFixed::operator ASFixed() const 
{
	return f; 
}

inline IASFixed::operator short() const 
{
	return short(f >> 16); 
}
#if 0
#ifndef	__TREAT_ASINT32_AS_INT__
inline IASFixed::operator int() const 
{
	return int(f >> 16); 
}
#endif
#endif

inline IASFixed::operator float() const 
{
	return float(f / 65536.0);
}

inline IASFixed::operator double() const 
{
	return double(f / 65536.0);
}

inline int operator == (const IASFixed& a, const IASFixed& b) 
{
	return a.f == b.f;
}

//inline int operator == (short a, const IASFixed& b) 
//{
//	return IASFixed(a).f != b.f;
//}

//inline int operator == (const IASFixed& a, short b) 
//{
//	return a.f == IASFixed(b).f;
//}

inline int operator == (int a, const IASFixed& b) 
{
	return IASFixed(a).f == b.f;
}

inline int operator == (const IASFixed& a, int b) 
{
	return a.f == IASFixed(b).f;
}

inline int operator == (const float& a, const IASFixed& b) 
{
	return a == float(b);
}

inline int operator == (const IASFixed& a, const float& b) 
{
	return float(a) == b;
}

inline int operator == (const double& a, const IASFixed& b) 
{
	return a == double(b);
}

inline int operator == (const IASFixed& a, const double& b) 
{
	return double(a) == b;
}

inline int operator != (const IASFixed& a, const IASFixed& b) 
{
	return a.f != b.f;
}

//inline int operator != (short a, const IASFixed& b) 
//{
//	return IASFixed(a).f != b.f;
//}

//inline int operator != (const IASFixed& a, short b) 
//{
//	return a.f != IASFixed(b).f;
//}

inline int operator != (int a, const IASFixed& b) 
{
	return IASFixed(a).f != b.f;
}

inline int operator != (const IASFixed& a, int b) 
{
	return a.f != IASFixed(b).f;
}

inline int operator != (const float& a, const IASFixed& b) 
{
	return a != float(b);
}

inline int operator != (const IASFixed& a, const float& b) 
{
	return float(a) != b;
}

inline int operator != (const double& a, const IASFixed& b) 
{
	return a != double(b);
}

inline int operator != (const IASFixed& a, const double& b) 
{
	return double(a) != b;
}

inline int operator > (const IASFixed& a, const IASFixed& b) 
{
	return a.f > b.f;
}

//inline int operator > (short a, const IASFixed& b) 
//{
//	return IASFixed(a).f > b.f;
//}

//inline int operator > (const IASFixed& a, short b) 
//{
//	return a.f > IASFixed(b).f;
//}

inline int operator > (int a, const IASFixed& b) 
{
	return IASFixed(a).f > b.f;
}

inline int operator > (const IASFixed& a, int b) 
{
	return a.f > IASFixed(b).f;
}

inline int operator > (const float& a, const IASFixed& b) 
{
	return a > float(b);
}

inline int operator > (const IASFixed& a, const float& b) 
{
	return float(a) > b;
}

inline int operator > (const double& a, const IASFixed& b) 
{
	return a > double(b);
}

inline int operator > (const IASFixed& a, const double& b) 
{
	return double(a) > b;
}

inline int operator < (const IASFixed& a, const IASFixed& b) 
{
	return a.f < b.f;
}

//inline int operator < (short a, const IASFixed& b) 
//{
//	return IASFixed(a).f < b.f;
//}

//inline int operator < (const IASFixed& a, short b) 
//{
//	return a.f < IASFixed(b).f;
//}

inline int operator < (int a, const IASFixed& b) 
{
	return IASFixed(a).f < b.f;
}

inline int operator < (const IASFixed& a, int b) 
{
	return a.f < IASFixed(b).f;
}

inline int operator < (const float& a, const IASFixed& b) 
{
	return a < float(b);
}

inline int operator < (const IASFixed& a, const float& b) 
{
	return float(a) < b;
}

inline int operator < (const double& a, const IASFixed& b) 
{
	return a < double(b);
}

inline int operator < (const IASFixed& a, const double& b) 
{
	return double(a) < b;
}

inline int operator >= (const IASFixed& a, const IASFixed& b) 
{
	return a.f >= b.f;
}

//inline int operator >= (short a, const IASFixed& b) 
//{
//	return IASFixed(a).f >= b.f;
//}

//inline int operator >= (const IASFixed& a, short b) 
//{
//	return a.f >= IASFixed(b).f;
//}

inline int operator >= (int a, const IASFixed& b) 
{
	return IASFixed(a).f >= b.f;
}

inline int operator >= (const IASFixed& a, int b) 
{
	return a.f >= IASFixed(b).f;
}

inline int operator >= (const float& a, const IASFixed& b) 
{
	return a >= float(b);
}

inline int operator >= (const IASFixed& a, const float& b) 
{
	return float(a) >= b;
}

inline int operator >= (const double& a, const IASFixed& b) 
{
	return a >= double(b);
}

inline int operator >= (const IASFixed& a, const double& b) 
{
	return double(a) >= b;
}

inline int operator <= (const IASFixed& a, const IASFixed& b) 
{
	return a.f <= b.f;
}

//inline int operator <= (short a, const IASFixed& b) 
//{
//	return IASFixed(a).f <= b.f;
//}

//inline int operator <= (const IASFixed& a, short b) 
//{
//	return a.f <= IASFixed(b).f;
//}

inline int operator <= (int a, const IASFixed& b) 
{
	return IASFixed(a).f <= b.f;
}

inline int operator <= (const IASFixed& a, int b) 
{
	return a.f <= IASFixed(b).f;
}

inline int operator <= (const float& a, const IASFixed& b) 
{
	return a <= float(b);
}

inline int operator <= (const IASFixed& a, const float& b) 
{
	return float(a) <= b;
}

inline int operator <= (const double& a, const IASFixed& b) 
{
	return a <= double(b);
}

inline int operator <= (const IASFixed& a, const double& b) 
{
	return double(a) <= b;
}

inline IASFixed operator - (const IASFixed& a)
{
	return -a.f;
}

inline IASFixed operator + (const IASFixed& a, const IASFixed& b)
{
	return a.f + b.f;
}

inline IASFixed operator - (const IASFixed& a, const IASFixed& b)
{
	return a.f - b.f;
}

inline IASFixed operator * (const IASFixed& a, const IASFixed& b)
{
	return IASFixed::FixedMul(a, b);
}

inline IASFixed operator / (const IASFixed& a, const IASFixed& b)
{
	return IASFixed::FixedDiv(a, b);
}

inline void IASFixed::operator += (const IASFixed& a)
{
	*this = *this + a;
}

inline void IASFixed::operator -= (const IASFixed& a)
{
	*this = *this - a;
}

inline void IASFixed::operator *= (const IASFixed& a)
{
	*this = *this * a;
}

inline void IASFixed::operator /= (const IASFixed& a)
{
	*this = *this / a;
}

inline IASFixed operator >> (const IASFixed& a, int amount)
{
	return a.f >> amount;
}

inline IASFixed operator << (const IASFixed& a, int amount)
{
	return a.f << amount;
}

inline IASFixed abs(const IASFixed& a)
{
	if (a.f >= 0)
		return a.f;
	else
		return -a.f; 
}

#endif
