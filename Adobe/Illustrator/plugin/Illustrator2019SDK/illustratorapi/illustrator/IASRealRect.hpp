#ifndef __IASRealRect_hpp__
#define __IASRealRect_hpp__

/*
 *        Name:	IASRealRect.hpp
 *   $Revision: $
 *      Author:	Darin Tomack 
 *        Date:	2/2/2001
 *     Purpose:	IASRealRect Wrapper Class.
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

#ifndef __AITypes__
#include "AITypes.h"
#endif
/*
 * Wrapper Class
 */

/*
	This file contains 2 wrapper classes for the C struct AIRealRect:
	
				IASRealRect and IASRealRectCartesian
	
	The 2 wrappers are nearly identical in terms of their interface and
	functionality, EXCEPT they assume different coordinate systems:
	
	 
		IASRealRect					IASRealRectCartesian
		
		0---------- +x				+y
		|							|
		|							|
		|							|
		|							|
		+y							0---------- +x
		
*/

struct IASRealRect : public AIRealRect
{
public:	
	IASRealRect();
	IASRealRect(const AIRealRect &rect);
	IASRealRect(const AIRect &rect);
	IASRealRect(const AIRealPoint &a);
	IASRealRect(const AIRealPoint &a, const AIRealPoint &b);
	IASRealRect(ai::int32 left, ai::int32 top, ai::int32 right, ai::int32 bottom);
	IASRealRect(AIReal left, AIReal top, AIReal right, AIReal bottom);
	
	AIReal Width() const;
	AIReal Height() const;
	
	ASBoolean IsEmpty() const;
	void SetEmpty();
	
	ASBoolean IsNormalized() const;	
	void Normalize();

	AIReal Area() const;
	
	AIRealPoint Center() const;
	
	ASBoolean Contains(const AIRealPoint &p) const;
	ASBoolean Contains(const AIRealRect &r) const;
	
	ASBoolean Overlaps(const AIRealRect &r) const;
	
	IASRealRect &operator ++ ();
	IASRealRect &operator -- ();
	IASRealRect operator ++ (int);
	IASRealRect operator -- (int);
	IASRealRect &operator += (AIReal n);
	IASRealRect &operator -= (AIReal n);
	
	IASRealRect &operator += (AIRealPoint &p);
	IASRealRect &operator -= (AIRealPoint &p);
	
	IASRealRect &operator = (AIRealPoint &p);
	
	void Inset(AIReal h, AIReal v);
	void Inflate(AIReal h, AIReal v);
	void Offset(AIReal h, AIReal v);
	
	void Union(const AIRealPoint &a);
	void Union(const AIRealRect &a);
	void Union(const AIRealRect &a, const AIRealRect &b);
	
	void Intersect(const AIRealRect &a);
	void Intersect(const AIRealRect &a, const AIRealRect &b);
	
	void Center(const AIRealRect &centerRect);
	
	friend inline ASBoolean operator == (const AIRealRect &a, const AIRealRect &b);
	friend inline ASBoolean operator != (const AIRealRect &a, const AIRealRect &b);

// Doesn't work in CodeWarrior 1.4.  Anyone know why?  DRL 4/22/96	
//	friend inline AIRealRect operator + (const IASRealRect &a, const IASRealPoint &b);
//	friend inline AIRealRect operator + (const IASRealPoint &a, const IASRealRect &b);
//	friend inline AIRealRect operator - (const IASRealRect &a, const IASRealPoint &b);
//	friend inline AIRealRect operator - (const IASRealPoint &a, const IASRealRect &b);
};


inline IASRealRect::IASRealRect() 					
{
}


inline IASRealRect::IASRealRect(const AIRealRect &rect) 
{ 
	left = rect.left;
	top = rect.top;
	right = rect.right;
	bottom = rect.bottom; 
}


inline IASRealRect::IASRealRect(const AIRect &rect)
{
	left = static_cast<AIReal>(rect.left);
	top = static_cast<AIReal>(rect.top);
	right = static_cast<AIReal>(rect.right);
	bottom = static_cast<AIReal>(rect.bottom);
}


inline IASRealRect::IASRealRect(const AIRealPoint &a)	
{ 
	left = right = a.h; 
	top = bottom = a.v; 
}


inline IASRealRect::IASRealRect(const AIRealPoint &a, const AIRealPoint &b)
{
	if (a.h < b.h)
	{
		left = a.h;
		right = b.h;
	}
	else
	{
		left = b.h;
		right = a.h;
	}
	
	if (a.v < b.v)
	{
		top = a.v;
		bottom = b.v;
	}
	else
	{
		top = b.v;
		bottom = a.v;
	}
}


inline IASRealRect::IASRealRect(ai::int32 left, ai::int32 top, ai::int32 right, ai::int32 bottom)
{
	this->left = static_cast<AIReal>(left);
	this->top = static_cast<AIReal>(top);
	this->right = static_cast<AIReal>(right);
	this->bottom = static_cast<AIReal>(bottom);
}

inline IASRealRect::IASRealRect(AIReal left, AIReal top, AIReal right, AIReal bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}


inline AIReal IASRealRect::Width()	const				
{ 
	return right - left; 
}


inline AIReal IASRealRect::Height() const			
{ 
	return bottom - top; 
}


inline ASBoolean IASRealRect::IsEmpty()	const		
{ 
	return top == bottom && right == left; 
}


inline void IASRealRect::SetEmpty()				
{ 
	left = top = right = bottom = 0; 
}


inline ASBoolean IASRealRect::IsNormalized() const
{
	return left <= right && top <= bottom;
}


inline void IASRealRect::Normalize()
{
	if (left > right) 
	{
		AIReal saveLeft = left; left = right; right = saveLeft;
	}
	if (top > bottom)
	{
		AIReal saveTop = top; top = bottom; bottom = saveTop;
	}
}


inline AIReal IASRealRect::Area() const					
{ 
	return Width() * Height(); 
}

inline AIRealPoint IASRealRect::Center() const
{
	AIRealPoint center;
	
	center.h = left + Width() / 2;
	center.v = top + Height() / 2;
	
	return center;
}

inline ASBoolean IASRealRect::Contains(const AIRealPoint &p) const
{
	return left <= p.h && right >= p.h && top <= p.v && bottom >= p.v;
}


inline ASBoolean IASRealRect::Contains(const AIRealRect &r) const
{
	return left <= r.left && right >= r.left && top <= r.top && bottom >= r.top &&
		   left <= r.right && right >= r.right && top <= r.bottom && bottom >= r.bottom;
}


inline ASBoolean IASRealRect::Overlaps(const AIRealRect &r) const
{
	return  right  >= r.left && left <= r.right  && 
		    bottom >= r.top  && top  <= r.bottom;
}


inline IASRealRect &IASRealRect::operator ++ ()
{ 
	left--; 
	top--; 
	right++; 
	bottom++; 
	
	return *this; 
}

inline IASRealRect &IASRealRect::operator -- ()		
{ 	
	left++; 
	top++; 
	right--; 
	bottom--; 
	
	return *this; 
}


inline IASRealRect IASRealRect::operator ++ (int)
{ 
	left--; 
	top--; 
	right++; 
	bottom++; 
	
	return *this; 
}

inline IASRealRect IASRealRect::operator -- (int)		
{ 
	left++; 
	top++; 
	right--; 
	bottom--; 
	
	return *this; 
}


inline IASRealRect &IASRealRect::operator += (AIReal n)	
{ 
	left -= n; 
	top -= n; 
	right += n; 
	bottom += n; 
	
	return *this; 
}


inline IASRealRect &IASRealRect::operator -= (AIReal n)
{ 
	left += n; 
	top += n; 
	right -= n; 
	bottom -= n; 
	
	return *this; 
}

inline IASRealRect &IASRealRect::operator += (AIRealPoint &p)	
{ 
	left += p.h; 
	top += p.v; 
	right += p.h; 
	bottom += p.v; 
	
	return *this; 
}


inline IASRealRect &IASRealRect::operator -= (AIRealPoint &p)
{ 
	left -= p.h; 
	top -= p.v; 
	right -= p.h; 
	bottom -= p.v; 
	
	return *this; 
}

	
inline IASRealRect &IASRealRect::operator = (AIRealPoint &p)
{
	left = right = p.h;
	top = bottom = p.v;
	
	return *this;
}


inline ASBoolean operator == (const AIRealRect &a, const AIRealRect &b)
{
	return a.left == b.left &&
		   a.top == b.top &&
		   a.right == b.right &&
		   a.bottom == b.bottom;
}


inline ASBoolean operator != (const AIRealRect &a, const AIRealRect &b)
{
	return a.left != b.left ||
		   a.top != b.top ||
		   a.right != b.right ||
		   a.bottom != b.bottom;
}


inline void IASRealRect::Inset(AIReal h, AIReal v)
{ 
	left += h; 
	top += v; 
	right -= h; 
	bottom -= v; 
}	


inline void IASRealRect::Inflate(AIReal h, AIReal v)
{ 
	left -= h; 
	top -= v; 
	right += h; 
	bottom += v; 
}	


inline void IASRealRect::Offset(AIReal h, AIReal v)
{ 
	left += h; 
	top += v; 
	right += h; 
	bottom += v; 
}	


inline void IASRealRect::Union(const AIRealPoint &a)
{
	if (left > a.h)
		left = a.h;
	if (top > a.v)
		top = a.v;
	if (right < a.h)
		right = a.h;
	if (bottom < a.v)
		bottom = a.v; 
}


inline void IASRealRect::Union(const AIRealRect &a)
{
	if (left > a.left)
		left = a.left;
	if (top > a.top)
		top = a.top;
	if (right < a.right)
		right = a.right;
	if (bottom < a.bottom)
		bottom = a.bottom; 
}


inline void IASRealRect::Union(const AIRealRect &a, const AIRealRect &b)
{
	if (b.left > a.left)
		left = a.left;
	else
		left = b.left;
	if (b.top > a.top)
		top = a.top;
	else
		top = b.top;
	if (b.right < a.right)
		right = a.right;
	else
		right = b.right;
	if (b.bottom < a.bottom)
		bottom = a.bottom;
	else
		bottom = b.bottom; 
}


inline void IASRealRect::Intersect(const AIRealRect &a)
{
	if (left < a.left)
		left = a.left;
	if (top < a.top)
		top = a.top;
	if (right > a.right)
		right = a.right;
	if (bottom > a.bottom)
		bottom = a.bottom;
		
	if (!Overlaps(a))
		SetEmpty();	
}


inline void IASRealRect::Intersect(const AIRealRect &a, const AIRealRect &b)
{
	if (b.left < a.left)
		left = a.left;
	else
		left = b.left;
	if (b.top < a.top)
		top = a.top;
	else
		top = b.top;
	if (b.right > a.right)
		top = a.right;
	else
		top = b.right;
	if (b.bottom > a.bottom)
		bottom = a.bottom;
	else
		bottom = b.bottom;			
	if (!Overlaps(a))
		SetEmpty();	
} 


inline void IASRealRect::Center(const AIRealRect &centerRect)
{
	Offset(centerRect.left + ((centerRect.right - centerRect.left) - Width()) / 2,
		   centerRect.top + ((centerRect.bottom - centerRect.top) - Height()) / 2);
}


/*
 * Doesn't work in CodeWarrior 1.4.  Anyone know why?  DRL 4/22/96.
inline AIRealRect operator + (const IASRealRect &a, const IASRealPoint &b)
{
	return IASRealRect(a.left + b.h, a.top + b.v, a.right + b.h, a.bottom + b.v);
}

inline AIRealRect operator + (const IASRealPoint &a, const IASRealRect &b)
{
	IASRealRect r;
	
	r.left = b.left + a.h;
	r.top = b.top + a.v;
	r.right = b.right + a.h;
	r.bottom = b.bottom + a.v;
	
	return r;
}

inline AIRealRect operator - (const IASRealRect &a, const IASRealPoint &b)
{
	IASRealRect r;
	
	r.left = a.left - b.h;
	r.top = a.top - b.v;
	r.right = a.right - b.h;
	r.bottom = a.bottom - b.v;
	
	return r;
}

inline AIRealRect operator - (const IASRealPoint &a, const IASRealRect &b)
{
	IASRealRect r;
	
	r.left = b.left - a.h;
	r.top = b.top - a.v;
	r.right = b.right - a.h;
	r.bottom = b.bottom - a.v;
	
	return r;
}
*/


struct IASRealRectCartesian : public AIRealRect
{
public:	
	IASRealRectCartesian();
	IASRealRectCartesian(const AIRealRect &rect);
	IASRealRectCartesian(const AIRect &rect);
	IASRealRectCartesian(const AIRealPoint &a);
	IASRealRectCartesian(const AIRealPoint &a, const AIRealPoint &b);
	IASRealRectCartesian(ai::int32 left, ai::int32 top, ai::int32 right, ai::int32 bottom);
	IASRealRectCartesian(AIReal left, AIReal top, AIReal right, AIReal bottom);
	
	AIReal Width() const;
	AIReal Height() const;
	
	ASBoolean IsEmpty() const;
	void SetEmpty();
	
	ASBoolean IsNormalized() const;	
	void Normalize();

	AIReal Area() const;
	
	AIRealPoint Center() const;
	
	ASBoolean Contains(const AIRealPoint &p) const;
	ASBoolean Contains(const AIRealRect &r) const;
	
	ASBoolean Overlaps(const AIRealRect &r) const;
	
	IASRealRectCartesian &operator ++ ();
	IASRealRectCartesian &operator -- ();
	IASRealRectCartesian operator ++ (int);
	IASRealRectCartesian operator -- (int);
	IASRealRectCartesian &operator += (AIReal n);
	IASRealRectCartesian &operator -= (AIReal n);
	
	IASRealRectCartesian &operator += (AIRealPoint &p);
	IASRealRectCartesian &operator -= (AIRealPoint &p);
	
	IASRealRectCartesian &operator = (AIRealPoint &p);
	
	void Inset(AIReal h, AIReal v);
	void Inflate(AIReal h, AIReal v);
	void Offset(AIReal h, AIReal v);
	
	void Union(const AIRealPoint &a);
	void Union(const AIRealRect &a);
	void Union(const AIRealRect &a, const AIRealRect &b);
	
	void Intersect(const AIRealRect &a);
	void Intersect(const AIRealRect &a, const AIRealRect &b);
	
	void Center(const AIRealRect &centerRect);
		
	AIRealPoint LeftBottom() const;
	AIRealPoint LeftTop() const;
	AIRealPoint RightTop() const;
	AIRealPoint RightBottom() const;
};


inline IASRealRectCartesian::IASRealRectCartesian() 					
{
}


inline IASRealRectCartesian::IASRealRectCartesian(const AIRealRect &rect) 
{ 
	left = rect.left;
	top = rect.top;
	right = rect.right;
	bottom = rect.bottom; 
}


inline IASRealRectCartesian::IASRealRectCartesian(const AIRect &rect)
{
	left = static_cast<AIReal>(rect.left);
	top = static_cast<AIReal>(rect.top);
	right = static_cast<AIReal>(rect.right);
	bottom = static_cast<AIReal>(rect.bottom);
}


inline IASRealRectCartesian::IASRealRectCartesian(const AIRealPoint &a)	
{ 
	left = right = a.h; 
	top = bottom = a.v; 
}


inline IASRealRectCartesian::IASRealRectCartesian(const AIRealPoint &a, const AIRealPoint &b)
{
	if (a.h < b.h)
	{
		left = a.h;
		right = b.h;
	}
	else
	{
		left = b.h;
		right = a.h;
	}
	
	if (a.v < b.v)
	{
		top = b.v;
		bottom = a.v;
	}
	else
	{
		top = a.v;
		bottom = b.v;
	}
}


inline IASRealRectCartesian::IASRealRectCartesian(ai::int32 left, ai::int32 top, ai::int32 right, ai::int32 bottom)
{
	this->left = static_cast<AIReal>(left);
	this->top = static_cast<AIReal>(top);
	this->right = static_cast<AIReal>(right);
	this->bottom = static_cast<AIReal>(bottom);
}

inline IASRealRectCartesian::IASRealRectCartesian(AIReal left, AIReal top, AIReal right, AIReal bottom)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
}


inline AIReal IASRealRectCartesian::Width()	const				
{ 
	return right - left; 
}


inline AIReal IASRealRectCartesian::Height() const			
{ 
	return top - bottom; 
}


inline ASBoolean IASRealRectCartesian::IsEmpty()	const		
{ 
	return top == bottom && right == left; 
}


inline void IASRealRectCartesian::SetEmpty()				
{ 
	left = top = right = bottom = 0; 
}


inline ASBoolean IASRealRectCartesian::IsNormalized() const
{
	return left <= right && top >= bottom;
}


inline void IASRealRectCartesian::Normalize()
{
	if (left > right) 
	{
		AIReal saveLeft = left; left = right; right = saveLeft;
	}
	if (top < bottom)
	{
		AIReal saveTop = top; top = bottom; bottom = saveTop;
	}
}


inline AIReal IASRealRectCartesian::Area() const					
{ 
	return Width() * Height(); 
}

inline AIRealPoint IASRealRectCartesian::Center() const
{
	AIRealPoint center;
	
	center.h = left + Width() / 2.0f;
	center.v = bottom + Height() / 2.0f;
	
	return center;
}

inline ASBoolean IASRealRectCartesian::Contains(const AIRealPoint &p) const
{
	return left <= p.h && right >= p.h && top >= p.v && bottom <= p.v;
}


inline ASBoolean IASRealRectCartesian::Contains(const AIRealRect &r) const
{
	return left <= r.left && right >= r.left && top >= r.top && bottom <= r.top &&
		   left <= r.right && right >= r.right && top >= r.bottom && bottom <= r.bottom;
}


inline ASBoolean IASRealRectCartesian::Overlaps(const AIRealRect &r) const
{
	return  right  >= r.left && left <= r.right  && 
		    bottom <= r.top  && top  >= r.bottom;
}


inline IASRealRectCartesian &IASRealRectCartesian::operator ++ ()
{ 
	left--; 
	top++; 
	right++; 
	bottom--; 
	
	return *this; 
}

inline IASRealRectCartesian &IASRealRectCartesian::operator -- ()		
{ 	
	left++; 
	top--; 
	right--; 
	bottom++; 
	
	return *this; 
}


inline IASRealRectCartesian IASRealRectCartesian::operator ++ (int)
{ 
	left--; 
	top++; 
	right++; 
	bottom--; 
	
	return *this; 
}

inline IASRealRectCartesian IASRealRectCartesian::operator -- (int)		
{ 
	left++; 
	top--; 
	right--; 
	bottom++; 
	
	return *this; 
}


inline IASRealRectCartesian &IASRealRectCartesian::operator += (AIReal n)	
{ 
	left -= n; 
	top += n; 
	right += n; 
	bottom -= n; 
	
	return *this; 
}


inline IASRealRectCartesian &IASRealRectCartesian::operator -= (AIReal n)
{ 
	left += n; 
	top -= n; 
	right -= n; 
	bottom += n; 
	
	return *this; 
}

inline IASRealRectCartesian &IASRealRectCartesian::operator += (AIRealPoint &p)	
{ 
	left += p.h; 
	top += p.v; 
	right += p.h; 
	bottom += p.v; 
	
	return *this; 
}


inline IASRealRectCartesian &IASRealRectCartesian::operator -= (AIRealPoint &p)
{ 
	left -= p.h; 
	top -= p.v; 
	right -= p.h; 
	bottom -= p.v; 
	
	return *this; 
}

	
inline IASRealRectCartesian &IASRealRectCartesian::operator = (AIRealPoint &p)
{
	left = right = p.h;
	top = bottom = p.v;
	
	return *this;
}

inline void IASRealRectCartesian::Inset(AIReal h, AIReal v)
{ 
	left += h; 
	top -= v; 
	right -= h; 
	bottom += v; 
}	


inline void IASRealRectCartesian::Inflate(AIReal h, AIReal v)
{ 
	left -= h; 
	top += v; 
	right += h; 
	bottom -= v; 
}	


inline void IASRealRectCartesian::Offset(AIReal h, AIReal v)
{ 
	left += h; 
	top += v; 
	right += h; 
	bottom += v; 
}	


inline void IASRealRectCartesian::Union(const AIRealPoint &a)
{
	if (left > a.h)
		left = a.h;
	if (top < a.v)
		top = a.v;
	if (right < a.h)
		right = a.h;
	if (bottom > a.v)
		bottom = a.v; 
}


inline void IASRealRectCartesian::Union(const AIRealRect &a)
{
	if (left > a.left)
		left = a.left;
	if (top < a.top)
		top = a.top;
	if (right < a.right)
		right = a.right;
	if (bottom > a.bottom)
		bottom = a.bottom; 
}


inline void IASRealRectCartesian::Union(const AIRealRect &a, const AIRealRect &b)
{
	if (b.left > a.left)
		left = a.left;
	else
		left = b.left;
	if (b.top < a.top)
		top = a.top;
	else
		top = b.top;
	if (b.right < a.right)
		right = a.right;
	else
		right = b.right;
	if (b.bottom > a.bottom)
		bottom = a.bottom;
	else
		bottom = b.bottom; 
}


inline void IASRealRectCartesian::Intersect(const AIRealRect &a)
{
	if (left < a.left)
		left = a.left;
	if (top > a.top)
		top = a.top;
	if (right > a.right)
		right = a.right;
	if (bottom < a.bottom)
		bottom = a.bottom;
		
	if (!Overlaps(a))
		SetEmpty();	
}


inline void IASRealRectCartesian::Intersect(const AIRealRect &a, const AIRealRect &b)
{
	if (b.left < a.left)
		left = a.left;
	else
		left = b.left;
	if (b.top > a.top)
		top = a.top;
	else
		top = b.top;
	if (b.right > a.right)
		top = a.right;
	else
		top = b.right;
	if (b.bottom < a.bottom)
		bottom = a.bottom;
	else
		bottom = b.bottom;			
	if (!Overlaps(a))
		SetEmpty();	
} 


inline void IASRealRectCartesian::Center(const AIRealRect &centerRect)
{
	Offset(centerRect.left + ((centerRect.right - centerRect.left) - Width()) / 2.0f,
		   centerRect.bottom + ((centerRect.top - centerRect.bottom) - Height()) / 2.0f);
}


inline AIRealPoint IASRealRectCartesian::LeftBottom() const
{
	AIRealPoint returnPt = {left, bottom};
	return returnPt;
}

inline AIRealPoint IASRealRectCartesian::LeftTop() const
{
	AIRealPoint returnPt = {left, top};
	return returnPt;
}

inline AIRealPoint IASRealRectCartesian::RightTop() const
{
	AIRealPoint returnPt = {right, top};
	return returnPt;
}

inline AIRealPoint IASRealRectCartesian::RightBottom() const
{
	AIRealPoint returnPt = {right, bottom};
	return returnPt;
}




#endif








