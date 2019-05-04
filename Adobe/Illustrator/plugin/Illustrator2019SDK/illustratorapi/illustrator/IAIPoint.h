/*
*        Name:	IAIPoint.h
*   $Revision:	1 $
*      Author:	 
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2008 Adobe Systems Incorporated
* All rights reserved.
*
* NOTICE:  Adobe permits you to use, modify, and distribute this file 
* in accordance with the terms of the Adobe license agreement 
* accompanying it. If you have received this file from a source other 
* than Adobe, then your use, modification, or distribution of it 
* requires the prior written permission of Adobe.
*
*/

#ifndef __IAIPoint__
#define __IAIPoint__

/*
* Includes
*/

#include "AITypes.h"
#include <cmath>
#include <cfloat>

namespace ai
{
	namespace PointTraits
	{
		template<typename S>
		struct PointStruct_Traits
		{

		};
		template<>
		struct PointStruct_Traits <AIPoint>
		{
			//current implementation is compatible with ADMPoint, 
			//but we plan to make is same for win and mac.
	#ifdef WIN_ENV
				typedef ai::int32 Coordinates_t;
	#endif
	#ifdef MAC_ENV
				typedef short Coordinates_t;
	#endif
		};
		template<>
		struct PointStruct_Traits <AIRealPoint>
		{
			typedef AIReal Coordinates_t;
		};
	}
}
/*
* Wrapper Class
*/
//Class used to working with point
template <typename S>
class IAIPointImpl : public S
{
private:
	typedef typename ai::PointTraits::PointStruct_Traits<S>::Coordinates_t CoordinateType;
public: 
	IAIPointImpl()
	{
		this->h = 0;
		this->v = 0;
	}
	IAIPointImpl(const S& p)
	{	
		this->h = p.h;
		this->v = p.v;
	}
	IAIPointImpl(CoordinateType h, CoordinateType v)
	{
		this->h = h;
		this->v = v;
	}
	IAIPointImpl &operator = (const S& p)
		{this->h = p.h; this->v =p.v; return *this;}
	IAIPointImpl &operator ++()
		{ this->operator += (1); return *this;}
	IAIPointImpl &operator --()
		{ this->operator += (-1); return *this;}

	S operator + (const S& a) const
		{ return IAIPointImpl(this->h+a.h,this->v+a.v);}
	S operator - (const S& a) const
		{ return IAIPointImpl(this->h-a.h,this->v-a.v);}
	S operator + (const CoordinateType& a) const
	{ return IAIPointImpl(this->h+a,this->v+a);}
	S operator - (const CoordinateType& a) const
	{ return IAIPointImpl(this->h-a,this->v-a);}

	AIBoolean operator == (const S& a) const
		{ return (a.h == this->h && a.v == this->v);}
	AIBoolean operator != (const S& a) const
		{ return !(*this == a);}
	S operator * (CoordinateType s) const
		{ return IAIPointImpl(this->h * s, this->v * s);}	
	S operator / (CoordinateType s) const
		{ return IAIPointImpl(this->h / s, this->v / s);}
	void operator -()
		{ this->h = -this->h; this->v = -this->v; return;}

	IAIPointImpl &operator += (const S& p)
		{	this->h+=p.h; this->v+=p.v; return *this;}
	IAIPointImpl &operator -= (const S& p)
		{	this->h -= p.h; this->v -= p.v; return *this;}

	IAIPointImpl &operator *= (CoordinateType s)
		{	this->h*=s; this->v*=s; return *this;}
	IAIPointImpl &operator /= (CoordinateType s)
	{	
		if(s){this->h/=s; this->v/=s;}
		else {this->h = 0; this->v = 0;}
		return *this;
	}
};

typedef IAIPointImpl<AIRealPoint> IAIRealPoint;
typedef IAIPointImpl<AIPoint> IAIPoint;

#endif //__IAIPoint__