/*
*        Name:	IAIRect.h
*   $Revision:	 1 $
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

#ifndef __IAIRect__
#define __IAIRect__

/*
* Includes
*/

#include "AITypes.h"
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include "AIBasicUtilities.h"

namespace ai
{
	template<typename T>
	struct Absolute
	{
		static T Absolute_Val(T a){
			return ::abs(a);
		}
	};

	template<>
	struct Absolute<AIReal>
	{
		static AIReal Absolute_Val(AIReal a){
			return ::fabs(a);
		}
	};

	namespace RectTraits
	{
		template<typename T>
		struct RectStruct_Traits
		{
			
		};
		template<>
		struct RectStruct_Traits <AIRect>
		{
			typedef AIPoint Point_t;	
			//current implementation is compatible with ADMRect, 
			//but we plan to make is same for win and mac.
	#ifdef WIN_ENV
			typedef ai::int32 Coordinates_t;
	#endif
	#ifdef MAC_ENV
			typedef short Coordinates_t;
	#endif
			typedef Absolute<Coordinates_t> ABS_t;
		};
		template<>
		struct RectStruct_Traits <AIRealRect>
		{
			typedef AIRealPoint Point_t;		
			typedef AIReal Coordinates_t;
			typedef Absolute<Coordinates_t> ABS_t;
		};
	}
}
/*
* Wrapper Class
*/
//Class used to working with Rectangles
template <typename T>
class IAIRectImpl : public T
{
private:
	typedef typename ai::RectTraits::RectStruct_Traits<T>::ABS_t AbsoluteFunction;
	typedef typename ai::RectTraits::RectStruct_Traits<T>::Point_t PointType;
	typedef typename ai::RectTraits::RectStruct_Traits<T>::Coordinates_t CoordinateType;	
public:	
	IAIRectImpl(){}
	IAIRectImpl(const T& rect)
	{
		this->left = rect.left;
		this->top = rect.top;
		this->right = rect.right;
		this->bottom = rect.bottom;
	}

	IAIRectImpl(const PointType& a)
	{
		this->left = a.h;
		this->right = a.h; 
		this->top = a.v;
		this->bottom = a.v;
	}

	IAIRectImpl(const PointType& a, const PointType& b)	
	{
		this->left = ai::Min(a.h, b.h);
		this->right = ai::Max(a.h, b.h);
		this->top = ai::Min(a.v, b.v);
		this->bottom = ai::Max(a.v, b.v);	
	}

	IAIRectImpl(CoordinateType l, CoordinateType t, CoordinateType r, CoordinateType b)
	{ 
		this->left = l;
		this->top = t;
		this->right = r;
		this->bottom = b;
	}
	
	CoordinateType Width() const
		{ return AbsoluteFunction::Absolute_Val(this->right - this->left);}
	CoordinateType Height() const
		{ return AbsoluteFunction::Absolute_Val(this->top - this->bottom);}
	
	AIBoolean IsEmpty() const
		{ return (this->top == this->bottom && this->right == this->left); }
	void SetEmpty()
		{this->left = this->top = this->right = this->bottom = 0; }

	AIBoolean IsNormalized() const
		{return this->left <= this->right && this->top <= this->bottom;	}
	void Normalize()	{
			if (this->left > this->right) 
			{
				CoordinateType saveLeft = this->left; this->left = this->right; this->right = saveLeft;
			}
			if (this->top > this->bottom)
			{
				CoordinateType saveTop = this->top; this->top = this->bottom; this->bottom = saveTop;
			}
		}

	AIBoolean Contains(const PointType& p) const{
			return this->left <= p.h && this->right >= p.h && this->top <= p.v && this->bottom >= p.v;	}
	AIBoolean Contains(const T& r) const{
		return this->left <= r.left && this->right >= r.left && this->top <= r.top && this->bottom >= r.top &&
			this->left <= r.right && this->right >= r.right && this->top <= r.bottom && this->bottom >= r.bottom;	}

	CoordinateType Area() const
		{return Width() * Height(); }
	PointType Center() const{
			PointType center;
			center.h = (this->left + this->right) / 2;
			center.v = (this->top + this->bottom) / 2;
			return center;
			}
	AIBoolean Overlaps(const T& r) const{
			return  this->right  >= r.left && this->left <= r.right  && 
				this->bottom >= r.top  && this->top  <= r.bottom;}

	IAIRectImpl& operator ++ ()	{ 
			this->operator += (1); return *this; 	}
	IAIRectImpl& operator -- ()	{ 	
			this->operator -= (1); 	return *this; 	}
	IAIRectImpl& operator += (CoordinateType n)	{ 
			this->left -= n; 	this->top -= n; 	this->right += n; 	this->bottom += n; 	return *this; }
	IAIRectImpl& operator -= (CoordinateType n)	{ 
			this->operator += (-n); return *this; 	}
	IAIRectImpl& operator += (const PointType& p)	{ 
			this->left += p.h; 	this->top += p.v; 	this->right += p.h; 	this->bottom += p.v; 	return *this; 	}
	IAIRectImpl& operator -= (PointType& p)	{ 
			this->left -= p.h; 	this->top -= p.v; 	this->right -= p.h; 	this->bottom -= p.v;  return *this; 	}	

	IAIRectImpl& operator = (const PointType& p)	{
			this->left = this->right = p.h;	this->top = this->bottom = p.v;
			return *this;	}	
	void Inset(CoordinateType h, CoordinateType v){ 
			this->left += h; 	this->top += v; 
			this->right -= h; this->bottom -= v; }
	void Inflate(CoordinateType h, CoordinateType v)	{ 
			this->left -= h; 	this->top -= v; 
			this->right += h; this->bottom += v; }
	void Offset(CoordinateType h, CoordinateType v){ 
			this->left += h; 	this->top += v; 
			this->right += h; this->bottom += v; }
	void Union(const PointType& a)	{
		this->left = ai::Min(this->left, a.h);
		this->top = ai::Min(this->top, a.v);
		this->right = ai::Max(this->right, a.h);
		this->bottom = ai::Max(this->bottom, a.v);	
		}
	void Union(const T& a){
		this->left = ai::Min(a.left, this->left);
		this->top = ai::Min(a.top, this->top);
		this->right = ai:: Max(a.right, this->right);
		this->bottom = ai::Max( a.bottom, this->bottom);}
	void Union(const T& a, const T& b)	{
		this->left = ai::Min(a.left, b.left);
		this->top = ai::Min(a.top, b.top);
		this->right = ai::Max(a.right, b.right);
		this->bottom = ai::Max(a.bottom, b.bottom);	}
	void Intersect(const T& a)	{
		this->left = ai::Max(this->left, a.left);
		this->top = ai::Max(this->top, a.top);
		this->right = ai::Min(this->right, a.right);
		this->bottom = ai::Min(this->bottom, a.bottom);	

		if (!Overlaps(a))
			SetEmpty();	
		}
	void Intersect(const T& a, const T& b)	{
		this->left = ai::Max(a.left, b.left);
		this->top = ai::Max(a.top, b.top);
		this->right = ai::Min(a.right, b.right);
		this->bottom = ai::Min(a.bottom, b.bottom);

		if (!Overlaps(a))
			SetEmpty();	
		} 

	void Center(const T& centerRect)	{
		Offset(centerRect.left + ((centerRect.right - centerRect.left) - Width()) / 2,
			centerRect.top + ((centerRect.bottom - centerRect.top) - Height()) / 2);
		}

	AIBoolean operator == (const T& a) const
		{
			return a.left == this->left &&
				a.top == this->top &&
				a.right == this->right &&
				a.bottom == this->bottom;
		}
	AIBoolean operator != (const T& a) const
		{return !(*this == a);}
};

typedef IAIRectImpl<AIRealRect> IAIRealRect;
typedef IAIRectImpl<AIRect> IAIRect;

#endif //	__IAIRect__
