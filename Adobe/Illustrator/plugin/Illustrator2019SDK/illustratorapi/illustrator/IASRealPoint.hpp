#ifndef __IASPoint_hpp__
#define __IASPoint_hpp__

/*
 *        Name:	IASRealPoint.hpp
 *   $Revision: $
 *      Author:	David Holloway 
 *        Date:	
 *     Purpose:	IASRealPoint Wrapper Class.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


/*
 * Includes
 */
 
#ifndef __ASTypes__
#include "ASTypes.h"
#endif

/*
 * Wrapper Class
 */

struct IASRealPoint : public AIRealPoint
{
public:	
	IASRealPoint();
	IASRealPoint(const AIRealPoint &p);
	IASRealPoint(int h, int v);
	IASRealPoint(float h, float v);
	IASRealPoint(AIReal h, AIReal v);
	friend inline ASBoolean operator == (const AIRealPoint &a, const AIRealPoint &b);
	friend inline ASBoolean operator != (const AIRealPoint &a, const AIRealPoint &b);
	
	friend inline AIRealPoint operator + (const AIRealPoint &a, const AIRealPoint& b);
	friend inline AIRealPoint operator - (const AIRealPoint &a, const AIRealPoint& b);

	friend inline AIRealPoint operator * (const AIRealPoint &p, int s);
	friend inline AIRealPoint operator * (int s, const AIRealPoint& p);

	friend inline AIRealPoint operator / (const AIRealPoint &p, int s);

	friend inline AIRealPoint operator - (const AIRealPoint &p);

	void operator = (const AIRealPoint &p);
	void operator += (const AIRealPoint &p);
	void operator -= (const AIRealPoint &p);

	void operator *= (int s);
	void operator /= (int s);
};


inline IASRealPoint::IASRealPoint()
{
}


inline IASRealPoint::IASRealPoint(const AIRealPoint &p)	
{ 
	h = p.h; 
	v = p.v; 
}


inline IASRealPoint::IASRealPoint(int h, int v)
{ 
	this->h = static_cast<ASReal>(h);
	this->v = static_cast<ASReal>(v);
}

inline IASRealPoint::IASRealPoint(float h, float v)
{ 
	this->h = h; this->v = v; 
}

inline IASRealPoint::IASRealPoint(AIReal h, AIReal v)
{ 
	this->h = h; this->v = v; 
}

inline ASBoolean operator == (const AIRealPoint &a, const AIRealPoint &b)
{
	return a.h == b.h && a.v == b.v;
}
	

inline ASBoolean operator != (const AIRealPoint &a, const AIRealPoint &b)
{
	return a.h != b.h || a.v != b.v;
}


inline AIRealPoint operator + (const AIRealPoint &a, const AIRealPoint &b)
{
	return IASRealPoint(a.h + b.h, a.v + b.v);
}


inline AIRealPoint operator - (const AIRealPoint &a, const AIRealPoint &b)
{
	return IASRealPoint(a.h - b.h, a.v - b.v);
}


inline AIRealPoint operator * (const AIRealPoint &p, int s)
{
	return IASRealPoint(p.h * s, p.v * s);
}


inline AIRealPoint operator * (int s, const AIRealPoint &p)
{
	return IASRealPoint(p.h * s, p.v * s);
}


inline AIRealPoint operator / (const AIRealPoint &p, int s)
{
	return IASRealPoint(p.h / s, p.v / s);
}


inline AIRealPoint operator - (const AIRealPoint &p)
{
	return IASRealPoint(-p.h, -p.v);
}


inline void IASRealPoint::operator = (const AIRealPoint& p) 
{
	h = p.h;
	v = p.v;
}


inline void IASRealPoint::operator += (const AIRealPoint& p) 
{ 
	h += p.h;
	v += p.v; 
}


inline void IASRealPoint::operator -= (const AIRealPoint& p) 
{ 
	h -= p.h; 
	v -= p.v; 
}


inline void IASRealPoint::operator *= (int s)
{ 
	h *= s;
	v *= s; 
}


inline void IASRealPoint::operator /= (int s)
{
	h /= s;
	v /= s; 
}


#endif








