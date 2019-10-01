/* -------------------------------------------------------------------------------

    Copyright 2000-2006 Adobe Systems Incorporated. All Rights Reserved.

    NOTICE:  Adobe permits you to use, modify, and distribute this file 
    in accordance with the terms of the Adobe license agreement accompanying 
    it. If you have received this file from a source other than Adobe, then 
    your use, modification, or distribution of it requires the prior written 
    permission of Adobe.

 ----------------------------------------------------------------------------------

	File:	IText.h
		
	Notes:	Machine Generated file from script version 1.45
	        Please don't modify manually!
	
 ---------------------------------------------------------------------------------- */
#pragma once

#include "ATESuites.h"
#include "ATEException.h"
#include "SloTextdomTypes.h"

namespace ATE
{
class IApplicationPaint;
class ICompFont;
class ICompFontClass;
class ICompFontClassSet;
class ICompFontComponent;
class ICompFontSet;
class IGlyphRun;
class IGlyphRunsIterator;
class IMojiKumi;
class IMojiKumiSet;
class ITextFrame;
class ITextFramesIterator;
class ITextLine;
class ITextLinesIterator;
class ITextResources;
class IApplicationTextResources;
class IDocumentTextResources;
class IVersionInfo;
class IArrayApplicationPaintRef;
class IArrayReal;
class IArrayBool;
class IArrayInteger;
class IArrayLineCapType;
class IArrayFigureStyle;
class IArrayLineJoinType;
class IArrayWariChuJustification;
class IArrayStyleRunAlignment;
class IArrayAutoKernType;
class IArrayBaselineDirection;
class IArrayLanguage;
class IArrayFontCapsOption;
class IArrayFontBaselineOption;
class IArrayFontOpenTypePositionOption;
class IArrayUnderlinePosition;
class IArrayStrikethroughPosition;
class IArrayParagraphJustification;
class IArrayArrayReal;
class IArrayBurasagariType;
class IArrayPreferredKinsokuOrder;
class IArrayKinsokuRef;
class IArrayMojiKumiRef;
class IArrayMojiKumiSetRef;
class IArrayTabStopsRef;
class IArrayLeadingType;
class IArrayFontRef;
class IArrayGlyphID;
class IArrayRealPoint;
class IArrayRealMatrix;
#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
class IArrayParagraphDirection;
class IArrayJustificationMethod;
class IArrayKashidaWidth;
class IArrayKashidas;
class IArrayDirOverride;
class IArrayDigitSet;
class IArrayDiacVPos;
#endif
class ICharFeatures;
class ICharInspector;
class ICharStyle;
class ICharStyles;
class ICharStylesIterator;
class IFind;
class IFont;
class IGlyph;
class IGlyphs;
class IGlyphsIterator;
class IKinsoku;
class IKinsokuSet;
class IParaFeatures;
class IParagraph;
class IParagraphsIterator;
class IParaInspector;
class IParaStyle;
class IParaStyles;
class IParaStylesIterator;
class ISpell;
class IStories;
class IStory;
class ITabStop;
class ITabStops;
class ITabStopsIterator;
class ITextRange;
class ITextRanges;
class ITextRangesIterator;
class ITextRunsIterator;
class IWordsIterator;
class IArrayLine;
class IArrayComposerEngine;
//////////////////////////////////////////////
//       --IApplicationPaint--
//////////////////////////////////////////////
/** Encapsulates Illustrator-specific painting of
	fill and stroke for text, as defined by
	the \c #AIATEPaintSuite.

	@see \c IArrayApplicationPaintRef */
class IApplicationPaint
{
private:
	ApplicationPaintRef	fApplicationPaint;
public:
	/** Constructor
			@return The new object. */
 	IApplicationPaint();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IApplicationPaint(const IApplicationPaint& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
 	IApplicationPaint& operator=(const IApplicationPaint& rhs);
 	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IApplicationPaint& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IApplicationPaint& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param applicationpaint The C object.
 			@return The new C++ object.
 			@return The new C++ object. */
	explicit IApplicationPaint(ApplicationPaintRef applicationpaint);
 	/** Destructor */
	virtual ~IApplicationPaint();
 	/** Retrieves a reference to this object.
 			@return The object reference. */
	ApplicationPaintRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. 	*/
	bool IsNull() const;


};

//////////////////////////////////////////////
//       --ICompFont--
//////////////////////////////////////////////
/** Encapsulates a composite font as a text resource. The methods allow you to
	add, access, and manipulate fonts for use with the
	Adobe Text Engine (ATE). This font contains \c ICompFontComponent
	objects.	*/
class ICompFont
{
private:
	CompFontRef	fCompFont;
public:
	/** Constructor
			@return The new object. */
	ICompFont();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICompFont(const ICompFont& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICompFont& operator=(const ICompFont& rhs);
 	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICompFont& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICompFont& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param compfont The C object.
 			@return The new C++ object. */
	explicit ICompFont(CompFontRef compfont);
	/** Destructor */
	virtual ~ICompFont();
 	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CompFontRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

 	/** Constructor: Creates a composite font from a text resources object.
 			@param pResources The text resources object.
 			@return The new object. */
	ICompFont( ITextResources pResources);

	// =======================================================================
	// PROPERTIES
	// =======================================================================

	/** Retrieves the platform-specific name of this font.
			@param name A buffer in which to return the name string.
			@param maxLength The number of characters in the passed buffer. The name is
				truncated to this length if necessary.
			@return Nothing.
		*/
	void GetNativeName( ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength) const;

	/** Sets the platform-specific name of this font. The PostScript name is
		automatically derived from this name.
			@param name The new name string.
			@return Nothing.
		*/
	void SetNativeName( const ATETextDOM::Unicode* name);

	/** Retrieves the PostScript name of this font as Unicode.
			@param name A Unicode character buffer in which to return the name string.
			@param maxLength The number of characters in the passed buffer. The name is
				truncated to this length if necessary.
			@return Nothing.
		*/
	void GetPostScriptName( ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength) const;

	/** Retrieves the PostScript name of this font as a C string.
			@param name A \c char buffer in which to return the name string.
			@param maxLength The number of characters in the passed buffer. The name is
				truncated to this length if necessary.
			@return Nothing.
		*/
	void GetPostScriptName( char* name, ATETextDOM::Int32 maxLength) const;

	/** Sets the font dictionary for this font.
			@param fontDictionary A pointer to the new dictionary.
			@return Nothing.
			@see \c #AIDictionarySuite
		*/
	void SetFontDictionary( void* fontDictionary);

	/** Retrieves the font dictionary for this font.
			@return  A pointer to the dictionary..
			@see \c #AIDictionarySuite
		*/
	void* GetFontDictionary( ) const;

	// =======================================================================
	// METHODS
	// =======================================================================
	/** Duplicates this font.
			@return The new font object.
		*/
	ICompFont Duplicate( ) const;

	/** Reports whether the resource been modified since it became editable.
			@return True if the resource has been modified.
		*/
	bool IsModified( ) const;

	/** Reports whether the resource is currently editable.
			@return True if the resource is editable.
		*/
	bool IsEditable( ) const;

	/** Reports whether changes to the resource have been committed.
			@return True if changes have been committed.
		*/
	bool IsCommitted( ) const;

	/** Reports whether the resource is in a valid state, either editable or committed.
			@return True if the resource is in a valid state.
		*/
	bool VerifyState( ) const;

	/** Reports whether the ATC file for the font is currently loaded.
			@return True if the font file is loaded.
		*/
	bool IsATCFileLoaded( ) const;

	/** Retrieves the number of components of this font. Use with
		\c #GetComponent() to iterate through components.
			@return The number of components.
		*/
	ATETextDOM::Int32 GetComponentCount( ) const;

	/** Retrieves a component from this font by index position. Use with
		\c #GetComponentCount() to iterate through components.
			@param index The 0-based position index.
			@return The component object.
		*/
	ICompFontComponent GetComponent( ATETextDOM::Int32 index) const;

	/** Retrieves a specific component from this font.
			@param component The component object.
			@return The index position of the component, or -1 if the component
				is not in this font.
		*/
	ATETextDOM::Int32 Find( ICompFontComponent component) const;

	/** Removes a component from this font.
			@param index The 0-based position index of the component to remove.
			@return True if a component was successfully removed.
		*/
	bool RemoveComponent( ATETextDOM::Int32 index);

	/** Appends a component to this font.
			@param component The component object.
			@return The 0-based position index of the successfully
				added component, or -1 if the component could not be appended.
		*/
	ATETextDOM::Int32 AddComponent( ICompFontComponent component);

	/** Replaces a component in this font.
			@param index The 0-based position index of the component to replace.
			@param component The replacement component object.
			@return True if a component was successfully replaced.
		*/
	bool ReplaceComponent( ATETextDOM::Int32 index, ICompFontComponent component);

};

//////////////////////////////////////////////
//       --ICompFontClass--
//////////////////////////////////////////////
/** Encapsulates a font character class as a text resource. The methods allow you to
	 add, access, and manipulate font classes for use with the
	 Adobe Text Engine (ATE). A font character class contains a collection of Unicode characters.
	*/
class ICompFontClass
{
private:
	CompFontClassRef	fCompFontClass;
public:
	/** Constructor
			@return The new object. */
	ICompFontClass();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICompFontClass(const ICompFontClass& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICompFontClass& operator=(const ICompFontClass& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICompFontClass& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICompFontClass& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param compfontclass The C object.
 			@return The new C++ object. */
	explicit ICompFontClass(CompFontClassRef compfontclass);
	/** Destructor */
	virtual ~ICompFontClass();
 	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CompFontClassRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================

	/** Retrieves the platform-specific name of this font class.
			@param name A buffer in which to return the name string.
			@param maxLength The number of characters in the passed buffer. The name is
				truncated to this length if necessary.
			@return Nothing.
		*/
	void GetNativeName( ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength) const;

	/** Sets the platform-specific name of this font.
			@param name The new name string.
			@return Nothing.
		*/
	void SetNativeName( const ATETextDOM::Unicode* name);

	/** Retrieves the Unicode character codes that belong to this class.
			@param codes A buffer in which to return the character codes.
			@param maxLength The number of characters in the passed buffer. The return
				string (including the terminating 0) is truncated to this length if necessary.
			@return The number of character codes written to the buffer, including the terminating 0.
		*/
	ATETextDOM::Int32 GetCodes( ATETextDOM::Unicode* codes, ATETextDOM::Int32 maxLength) const;

	/** Sets the Unicode character codes that belong to this class.
			@param codes A buffer containing the new Unicode character codes.
			@return The character code count, not include the terminating 0.
		*/
	ATETextDOM::Int32 SetCodes( const ATETextDOM::Unicode* codes);

	// =======================================================================
	// METHODS
	// =======================================================================

	/** Duplicates this font class.
			@return The new font class object.
		*/
	ICompFontClass Duplicate( ) const;

	/** Retrieves the number of characters in this font class.
			@return The number of characters.
		*/
	ATETextDOM::Int32 GetCharacterCount( ) const;

	/** Retrieves the type of this font class.
			@return The class type constant.
		*/
	CompositeFontClassType GetClassType( ) const;

	/** Reports whether a Unicode character is in this font class.
			@param code The character code.
			@return True if the code is part of this class.
		*/
	bool IsCodeInClass( ATETextDOM::Unicode code) const;

	/** Reports whether the resource is currently editable.
			@return True if the resource is editable.
			@note Predefined classes are never editable.
		*/
	bool IsEditable( ) const;

	/** Reports whether this is a custom override class or predefined class.
			@return True if this is a custom override class, false if it is a predefined class.
			@note Predefined classes are never editable.
		*/
	bool IsCustomOverride( ) const;

	/** Reports whether the resource been modified since it became editable.
			@return True if the resource has been modified.
		*/
	bool IsModified( ) const;

	/** Reports whether the resource is in a valid state, either editable or committed.
			@return True if the resource is in a valid state.
		*/
	bool VerifyState( ) const;

};

//////////////////////////////////////////////
//       --ICompFontClassSet--
//////////////////////////////////////////////
/** Encapsulates a font class set as a text resource. The methods allow you to
	 add, access, and manipulate font class sets for use with the
	 Adobe Text Engine (ATE). A font class set contains a collection of \c ICompFontClass objects.
	*/
class ICompFontClassSet
{
private:
	CompFontClassSetRef	fCompFontClassSet;
public:
	/** Constructor
			@return The new object. */
	ICompFontClassSet();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICompFontClassSet(const ICompFontClassSet& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICompFontClassSet& operator=(const ICompFontClassSet& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICompFontClassSet& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICompFontClassSet& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param compfontclassset The C object.
 			@return The new C++ object. */
	explicit ICompFontClassSet(CompFontClassSetRef compfontclassset);
	/** Destructor */
	virtual ~ICompFontClassSet();
 	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CompFontClassSetRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.
		*/
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object.
		*/
	ICompFontClass GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object.
		*/
	ICompFontClass GetLast( ) const;

	// =======================================================================
	// METHODS
	// =======================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param nIndex The 0-based position index.
			@return The member object.
		*/
	ICompFontClass Item( ATETextDOM::Int32 nIndex) const;

	/** Retrieves a specific font class from this set.
			@param compFontClass The font class object.
			@return The index position of the object in this set, or -1
				if the object is not in this set.
		*/
	ATETextDOM::Int32 Find( ICompFontClass compFontClass) const;

	/** Retrieves a specific predefined font class type from this set.
			@param predefinedType The font class type.
			@return The index position of the type in this set, or -1
				if the type is not in this set.
		*/
	ATETextDOM::Int32 FindPredefined( CompositeFontClassType predefinedType) const;

};

//////////////////////////////////////////////
//       --ICompFontComponent--
//////////////////////////////////////////////
/** Encapsulates a font component as a text resource. The methods allow you to
	 add, access, and manipulate font components for use with the
	 Adobe Text Engine (ATE). Font components belong to \c ICompFont objects.
	 See \c ICompFont::GetComponent() */
class ICompFontComponent
{
private:
	CompFontComponentRef	fCompFontComponent;
public:
	/** Constructor
			@return The new object. */
	ICompFontComponent();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICompFontComponent(const ICompFontComponent& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICompFontComponent& operator=(const ICompFontComponent& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICompFontComponent& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICompFontComponent& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param compfontcomponent The C object.
 			@return The new C++ object. */
	explicit ICompFontComponent(CompFontComponentRef compfontcomponent);
	/** Destructor */
	virtual ~ICompFontComponent();
 	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CompFontComponentRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

 	/** Constructor: Creates a font component from a text resources object.
 			@param pResources The text resources object.
 			@return The new object. */
	ICompFontComponent( ITextResources pResources);

	// =======================================================================
	// PROPERTIES
	// =======================================================================

	/** Retrieves the font class to which this component belongs.
			@return  The font class object.
		*/
	ICompFontClass GetClass( ) const;

	/** Sets the font character class to which this component belongs.
			@param charClass  The font character class object.
			@return Nothing.
		*/
	void SetClass( ICompFontClass charClass);

	/** Retrieves the font to which this component belongs.
			@return  The font object.
		*/
	IFont GetFont( ) const;

	/** Sets the font to which this component belongs.
			@param font  The font object.
			@return Nothing.
		*/
	void SetFont( IFont font);

	/** Retrieves the point size of this component.
			@return  The point size.
		*/
	ATETextDOM::Real GetSize( ) const;

	/** Sets the point size of this component.
			@param size  The new point size.
		*/
	void SetSize( ATETextDOM::Real size);

	/** Retrieves the baseline value of this component.
			@return  The baseline value.
		*/
	ATETextDOM::Real GetBaseline( ) const;

	/** Sets the baseline value of this component.
			@param baseline  The new baseline value.
		*/
	void SetBaseline( ATETextDOM::Real baseline);

	/** Retrieves the horizontal scaling factor of this component.
			@return  The horizontal scaling factor.
		*/
	ATETextDOM::Real GetHorizontalScale( ) const;

	/** Sets the horizontal scaling factor of this component.
			@param horizontalScale  The new horizontal scaling factor.
		*/
	void SetHorizontalScale( ATETextDOM::Real horizontalScale);

	/** Retrieves the vertical scaling factor of this component.
			@return  The vertical scaling factor.
		*/
	ATETextDOM::Real GetVerticalScale( ) const;

	/** Sets the vertical scaling factor of this component.
			@param verticalScale  The new vertical scaling factor.
		*/
	void SetVerticalScale( ATETextDOM::Real verticalScale);

	/** Reports the centering state of this component.
			@return True if centering is on.
		*/
	bool GetCenterGlyph( ) const;

	/** Sets the centering state of this component.
			@param centerglyph True to turn centering on, false to turn it off
			@return Nothing
		*/
	void SetCenterGlyph( bool centerglyph);

	// =======================================================================
	// METHODS
	// =======================================================================

	/** Reports whether the resource been modified since it became editable.
			@return True if the resource has been modified.
		*/
	bool IsModified( ) const;

};

//////////////////////////////////////////////
//       --ICompFontSet--
//////////////////////////////////////////////
/** Encapsulates a composite font set as a text resource. The methods allow you to
	 add, access, and manipulate font sets for use with the
	 Adobe Text Engine (ATE). A font set contains a collection of \c ICompFont objects.
	*/
class ICompFontSet
{
private:
	CompFontSetRef	fCompFontSet;
public:
	/** Constructor
			@return The new object. */
	ICompFontSet();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICompFontSet(const ICompFontSet& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICompFontSet& operator=(const ICompFontSet& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICompFontSet& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICompFontSet& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param compfontset The C object.
 			@return The new C++ object. */
	explicit ICompFontSet(CompFontSetRef compfontset);
	/** Destructor */
	virtual ~ICompFontSet();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CompFontSetRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.
		*/
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object.
		*/
	ICompFont GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object.
		*/
	ICompFont GetLast( ) const;
	// =======================================================================
	// METHODS
	// =======================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param nIndex The 0-based position index.
			@return The member object.
		*/
	ICompFont Item( ATETextDOM::Int32 nIndex) const;

	/** Retrieves a specific font from this set.
			@param font The font object.
			@return The index position of the object in this set, or -1
				if the object is not in this set.
		*/
	ATETextDOM::Int32 Find( ICompFont font) const;

	/** Removes a member font from this font set.
			@param nIndex The 0-based position index of the font to remove.
			@return True if a font was successfully removed.
		*/
	bool Remove( ATETextDOM::Int32 nIndex);

	/** Appends a font to this font set.
			@param font The font object.
			@return The 0-based position index of the successfully
				added font, or -1 if the font could not be appended.
		*/
	ATETextDOM::Int32 Add( ICompFont font);

	/** Replaces a font in this set.
			@param nIndex The 0-based position index of the font to replace.
			@param newFont The replacement font object.
			@return True if a font was successfully replaced.
		*/
	bool Replace( ATETextDOM::Int32 nIndex, ICompFont newFont);

	/** Updates this font set to reflect what is currently in the
		document font resource's font set. This can invalidate
		previously saved font indices.
			@return Nothing.
		*/
	void Update( ) const;

};

//////////////////////////////////////////////
//       --IGlyphRun--
//////////////////////////////////////////////
/** Encapsulates a glyph run as a text resource. The methods allow you to
	 add, access, and manipulate glyph runs for use with the
	 Adobe Text Engine (ATE). A glyph run belongs to a \c ITextLine object.
	 It contains a string of characters, along with drawing information
	 for them.
	*/
class IGlyphRun
{
private:
	GlyphRunRef	fGlyphRun;
public:
	/** Constructor
			@return The new object. */
	IGlyphRun();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IGlyphRun(const IGlyphRun& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IGlyphRun& operator=(const IGlyphRun& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IGlyphRun& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IGlyphRun& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param glyphrun The C object.
 			@return The new C++ object. */
	explicit IGlyphRun(GlyphRunRef glyphrun);
	/** Destructor */
	virtual ~IGlyphRun();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	GlyphRunRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// METHODS
	// =======================================================================

	/** Retrieves the text-line parent of this glyph run.
			@return The text-line object.
	 	*/
	ITextLine GetTextLine( ) const;

	/** Retrieves the number of glyphs in this run.
		The number of the glyphs can be different from number of characters returned
		by \c #GetCharacterCount(), because of factors such ligature and hyphenation.
			@return The number of glyphs.
		*/
	ATETextDOM::Int32 GetSize( ) const;

	/** Retrieves the number of characters in this run.	Use to determine
		the size of buffer to pass to \c #GetContents().
			@return The number of characters.
			@see \c #GetSize()
		*/
	ATETextDOM::Int32 GetCharacterCount( ) const;

	/** Retrieves the origin points of each glyph in this run.
			@return The array of origin points.
		*/
	IArrayRealPoint GetOrigins( ) const;

	/** Retrieves the unique identifiers of each glyph in this run.
			@return The array of identifiers.
		*/
	IArrayGlyphID GetGlyphIDs( ) const;

	/** Retrieves the transformation matrix of this run, which
		specifies the full transformation. To get the location of
		an individual glyph, you must transform the origin by the value
		in the \c #GetOrigins() array, then concatinate this matrix with
		the text frame matrix, returned by \c ITextFrame::GetMatrix().
			@return The transformation matrix.
	 	*/
	ATETextDOM::RealMatrix GetMatrix( ) const;

	/** Retrieves the character features of this run.
		Only the following members are defined:
		<br>\c Font
		<br>\c FontSize
		<br>\c HorizontalScale
		<br>\c VerticalScale
		<br>\c Tracking
		<br>\c BaselineShift
		<br>\c FillColor
		<br>\c StrokeColor
		<br>\c fBlend
		<br>\c Fill
		<br>\c Stroke
		<br>\c FillFirst
		<br>\c FillOverPrint
		<br>\c StrokeOverPrint
		<br>\c FillBackgroundColor
		<br>\c FillBackground
		<br>\c LineCap
		<br>\c LineJoin
		<br>\c LineWidth
		<br>\c MiterLimit
		<br>\c LineDashOffset
		<br>\c LineDashArray
			@return The character features object.
	*/
	ICharFeatures GetCharFeatures( ) const;

	/** Retrieves the glyph orientation of this run.
			@return	The orientation constant.
		*/
	GlyphOrientation GetGlyphOrientation( ) const;

	/** Retrieves the ascent of this run.
			@return	The ascent value, in document points.
		*/
	ATETextDOM::Real GetAscent( ) const;

	/** Retrieves the descent of this run.
			@return	The descent value, in document points.
		 */
	ATETextDOM::Real GetDescent( ) const;

	/** Retrieves the tracking (space between each character) of this run,
			@return	The tracking value, in document points.
		*/
	ATETextDOM::Real GetTracking( ) const;

	/** Retrieves the width of the space glyph in the font for this run.
			@return	The width value, in document points.
		*/
	ATETextDOM::Real GetSpaceGlyphWidth( ) const;

	/** Retrieves the distance to the baseline in the font for this run.
			@return	The distance value, in document points.
		*/
	ATETextDOM::Real GetDistanceToBaseline( ) const;

	/** Retrieves the underline position in the font for this run.
			@return	The position value, in document points.
		*/
	ATETextDOM::Real GetUnderlinePosition( ) const;

	/** Retrieves the underline thickness in the font for this run.
			@return	The thickness value, in document points.
		*/
	ATETextDOM::Real GetUnderlineThickness( ) const;

	/** Retrieves the maximum height for capital letters in the font for this run.
			@return	The height value, in document points.
		*/
	ATETextDOM::Real GetMaxCapHeight( ) const;

	/** Retrieves the minimum height for capital letters in the font for this run.
			@return	The height value, in document points.
		*/
	ATETextDOM::Real GetMinCapHeight( ) const;

	/** Retrieves the component font for this run if the character-feature font is
		a composite font, otherwise retrieves the character-feature font.
			@return	The font object.
		*/
	IFont GetFlattenedFont( ) const;

	/** Retrieves the contents of this run as a Unicode string.
			@param text [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
				Use \c #GetCharacterCount()	to determine what size is needed.
			@return The number of characters written to the text buffer.
		*/
	ATETextDOM::Int32 GetContents( ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength) const;

	/** Retrieves the contents of this run as a C string.
			@param text [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
				Use \c #GetCharacterCount()	to determine what size is needed.
			@return The number of characters written to the text buffer.
		*/
	ATETextDOM::Int32 GetContents( char* text, ATETextDOM::Int32 maxLength) const;

};

//////////////////////////////////////////////
//       --IGlyphRunsIterator--
//////////////////////////////////////////////
/** This object enables you to iterate through the set of
	glyph runs in the current document.
	@see \c IGlyphRun.
	*/
class IGlyphRunsIterator
{
private:
	GlyphRunsIteratorRef	fGlyphRunsIterator;
public:
	/** Constructor
			@return The new object. */
	IGlyphRunsIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IGlyphRunsIterator(const IGlyphRunsIterator& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IGlyphRunsIterator& operator=(const IGlyphRunsIterator& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IGlyphRunsIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IGlyphRunsIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param glyphrunsiterator The C object.
 			@return The new C++ object. */
	explicit IGlyphRunsIterator(GlyphRunsIteratorRef glyphrunsiterator);
	/** Destructor */
	virtual ~IGlyphRunsIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	GlyphRunsIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// METHODS
	// =====================================================================
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsDone( ) const;
	/** Increments the current position in the set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Retrieves the current glyph run.
			@return The glyph run object. */
	IGlyphRun Item( ) const;

};

//////////////////////////////////////////////
//       --IMojiKumi--
//////////////////////////////////////////////
/** Encapsulates the MojiKumi characteristics of a character as a text resource.
	The methods allow you to add, access, and manipulate MojiKumi for use with the
	 Adobe Text Engine (ATE). These objects are collected in an \c IMojiKumiSet.
	*/
class IMojiKumi
{
private:
	MojiKumiRef	fMojiKumi;
public:
	/** Constructor
			@return The new object. */
	IMojiKumi();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IMojiKumi(const IMojiKumi& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IMojiKumi& operator=(const IMojiKumi& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IMojiKumi& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IMojiKumi& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param mojikumi The C object.
 			@return The new C++ object. */
	explicit IMojiKumi(MojiKumiRef mojikumi);
	/** Destructor */
	virtual ~IMojiKumi();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	MojiKumiRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================

	/** Retrieves the name of this object.
			@param name [out] A Unicode string in which to return the name.
			@param maxLength The number of characters in the buffer.
				Use \c #GetNameSize() to determine the size needed.
			@return The number of characters written to the buffer.
		*/
	ATETextDOM::Int32 GetName( ATETextDOM::Unicode * name, ATETextDOM::Int32 maxLength) const;
	/**	Retrieves the number of characters in the name of this object. Use to
		determine the size of buffer to pass to \c #GetName().
			@return The number of characters in the name.
		*/
	ATETextDOM::Int32 GetNameSize( ) const;
	/** Sets the name of this object.
			@param name A Unicode string containing the new name.
			@return Nothing.
		*/
	void SetName( const ATETextDOM::Unicode * name);
	/**	Reports whether this object matches a predefined tag in the
		MojiKumi table.
			@param tag The tag object.
			@return True if this object matches the tag.
		*/
	bool MatchesPredefinedResourceTag( ATE::MojikumiTablePredefinedTag tag) const;
	/**	Retrieves a MojiKumi table entry from this object.
			@param index The 0-based position index for the entry.
			@param minExpansion	[out] A buffer in which to return the maximum expansion value.
			@param maxExpansion	[out] A buffer in which to return the minimum expansion value.
			@param desiredExpansion [out] A buffer in which to return the desired expansion value.
			@return Nothing.
		*/
	void GetEntry( ATETextDOM::Int32 index, ATETextDOM::Float * minExpansion, ATETextDOM::Float * maxExpansion, ATETextDOM::Float * desiredExpansion) const;
	/**	Sets a MojiKumi table entry from this object.
			@param index The 0-based position index for the entry.
			@param minExpansion	The new maximum expansion value.
			@param maxExpansion	The new minimum expansion value.
			@param desiredExpansion The new desired expansion value.
			@return Nothing.
		*/
	void SetEntry( ATETextDOM::Int32 index, ATETextDOM::Real minExpansion, ATETextDOM::Real maxExpansion, ATETextDOM::Real desiredExpansion);

	// =======================================================================
	// METHODS
	// =======================================================================

	/** Reports whether this object is equivalent to another MojiKumi object.
			@param rhsMojiKumi The other MojiKumi object.
			@return True if the objects are equivalent.
		*/
	bool IsEquivalent( IMojiKumi rhsMojiKumi) const;
	/** Reports whether the resource been modified since it became editable.
			@return True if the resource has been modified.
		*/
	bool IsModified( ) const;
	/** Reports whether this is a predefined MojiKumi.
			@return True if the MojiKumi is predefined, false if it is customized.
		*/
	bool IsPredefined( ) const;
	/**	Creates a new object by duplicating the information in this one.
			@return The new object
		*/
	IMojiKumi Duplicate( ) const;

};

//////////////////////////////////////////////
//       --IMojiKumiSet--
//////////////////////////////////////////////
/** Encapsulates a MojiKumi set as a text resource. The methods allow you to
	add, access, and manipulate MojiKumi sets for use with the
	Adobe Text Engine (ATE). The set contains \c IMojiKumi objects.
	*/
class IMojiKumiSet
{
private:
	MojiKumiSetRef	fMojiKumiSet;
public:
	/** Constructor
			@return The new object. */
	IMojiKumiSet();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IMojiKumiSet(const IMojiKumiSet& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IMojiKumiSet& operator=(const IMojiKumiSet& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IMojiKumiSet& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IMojiKumiSet& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param mojikumiset The C object.
 			@return The new C++ object. */
	explicit IMojiKumiSet(MojiKumiSetRef mojikumiset);
	/** Destructor */
	virtual ~IMojiKumiSet();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	MojiKumiSetRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( );
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	IMojiKumi GetFirst( );
	/** Retrieves the last member of this set.
			@return The member object.  */
	IMojiKumi GetLast( );

	// =======================================================================
	// METHODS
	// =======================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param nIndex The 0-based position index.
			@return The member object.
		*/
	IMojiKumi Item( ATETextDOM::Int32 nIndex) const;
	/** Retrieves a specific MojiKumi object from this set, matching name and data.
			@param mojiKumi The MojiKumi object.
			@return The index position of the object in this set, or -1
				if the object is not in this set.
		*/
	ATETextDOM::Int32 Find( const IMojiKumi mojiKumi);
	/** Retrieves a specific MojiKumi object from this set, matching only the name.
			@param name The object name.
			@return The index position of the object in this set, or -1
				if the object is not in this set.
		*/
	ATETextDOM::Int32 Find( const ATETextDOM::Unicode* name);
	/** Retrieves a specific MojiKumi object from this set, matching a tag.
			@param tag The tag. Use \c #kUserDefinedMojikumiTableTag to get the first
				customized (not predefined) MojiKumi.
			@return The index position of the object in this set, or -1
				if the object is not in this set.
		*/
	ATETextDOM::Int32 Find( MojikumiTablePredefinedTag tag);
	/** Removes a member MojiKumi from this set.
			@param nIndex The 0-based position index of the MojiKumi to remove.
			@return True if a MojiKumi was successfully removed.
		*/
	bool Remove( ATETextDOM::Int32 nIndex);
	/** Appends a MojiKumi to this set.
			@param mojiKumi The MojiKumi object.
			@return The 0-based position index of the successfully
				added object, or the current index of this object
				if it is already in the set, or -1 if the object
				was not in the set and could not be appended.
		*/
	ATETextDOM::Int32 Add( IMojiKumi mojiKumi);
	/** Replaces a MojiKumi in this set.
			@param nIndex The 0-based position index of the MojiKumi to replace.
			@param mojiKumi The replacement MojiKumi object.
			@return True if an object was successfully replaced.
		*/
	bool Replace( ATETextDOM::Int32  nIndex, IMojiKumi mojiKumi);
	/** Creates a new, empty MojiKumi object and appends it to this set.
			@param name The name of the new object.
			@param nIndex [out] A buffer in which to return the
				0-based position index of the successfully
				added object, or -1 if it could not be added.
			@return The new object, or a \c NULL object
				if the MojiKumi could not be created.
		*/
	IMojiKumi CreateNewMojiKumi( const ATETextDOM::Unicode* name, ATETextDOM::Int32* nIndex);

};

//////////////////////////////////////////////
//       --ITextFrame--
//////////////////////////////////////////////
/**	This class encapsulates a text frame, which manages the layout
	of a text range into rows and columns. The methods allow you to
	add, access, and manipulate text frames for use with the
	Adobe Text Engine (ATE). The frame is associated with an \c ITextRange,
	and contains \c ITextLine objects representing rows of text, which you can
	access through an \c ITextLinesIterator. A text frame can be part
	of an \c IStory. 	*/
class ITextFrame
{
private:
	TextFrameRef	fTextFrame;
public:
	/** Constructor
			@return The new object. */
	ITextFrame();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITextFrame(const ITextFrame& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITextFrame& operator=(const ITextFrame& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITextFrame& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITextFrame& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param textframe The C object.
 			@return The new C++ object. */
	explicit ITextFrame(TextFrameRef textframe);
	/** Destructor */
	virtual ~ITextFrame();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TextFrameRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// METHODS
	// =====================================================================
	/** Retrieves the parent story of this text frame.
			@return The story object.
	 	*/
	IStory GetStory( ) const;
	/** Retrieves the text range of this frame.
			@param bIncludeOverflow Optional. When true (the default), if
				the frame is the last one in its story, the range includes any
				overflow text. When false, overflow text is not included.
			@return The text range object.
		*/
	ITextRange GetTextRange( bool bIncludeOverflow = true) const;
	/** Retrieves a text-line iterator with which you can access
		the text lines of this text frame.
 			@return The text-line iterator object.
 	 	*/
	ITextLinesIterator GetTextLinesIterator( ) const;
	/** Retrieves the type of this text frame.
 			@return The type constant.
 	 	*/
	FrameType GetType( ) const;
	/** Retrieves the line orientation of this text frame.
 			@return The line orientation constant.
 	 	*/
	LineOrientation GetLineOrientation( ) const;
	/** Reports whether this frame is selected. Use the \c #AIArtSuite
		to set the selection.
			@return True if the text frame is selected.
		*/
	bool GetSelected( ) const;
	/** Retrieves the transformation matrix of this text frame.
 			@return The transformation matrix.
 	 	*/
	ATETextDOM::RealMatrix GetMatrix( ) const;
	/** Retrieves the number of rows for this text frame.
 			@return The number of rows.
 	 	*/
	ATETextDOM::Int32 GetRowCount( ) const;
	/** Retrieves the number of columns for this text frame.
 			@return The number of columns.
 	 	*/
	ATETextDOM::Int32 GetColumnCount( ) const;
	/** Reports whether the text range is arranged in row-major order.
 			@return True if the text frame is in row-major order.
 	 	*/
	bool GetRowMajorOrder( ) const;
	/** Retrieves the row gutter value for this text frame.
 			@return The row gutter value, in document points.
 	 	*/
	ATETextDOM::Real GetRowGutter( ) const;
	/** Retrieves the column gutter value for this text frame.
 			@return The column gutter value, in document points.
 	 	*/
	ATETextDOM::Real GetColumnGutter( ) const;
	/** Retrieves the line spacing value for this text frame.
 			@return The line spacing value, in document points.
 	 	*/
	ATETextDOM::Real GetSpacing( ) const;
	/** Reports whether optical alignment is on for this text frame
 			@return True if optical alignment is on.
 	 	*/
	bool GetOpticalAlignment( ) const;
#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	/**	Retrieves the paragraph direction for this text frame.
		@return The paragraph direction object.
		*/
	ParagraphDirection GetStoryDirection( ) const;
#endif
	/** Sets the number of rows for this text frame.
			@param rowCount The number of rows.
			@return Nothing.
		*/
	void SetRowCount( ATETextDOM::Int32 rowCount);
	/** Sets the number of columns for this text frame.
			@param columnCount The number of columns.
			@return Nothing.
		*/
	void SetColumnCount( ATETextDOM::Int32 columnCount);
	/** Turns row-major order on or off for this text frame.
			@param isRowMajor True to turn row-major order on,
				false to turn it off.
			@return Nothing.
		*/
	void SetRowMajorOrder( bool isRowMajor);
	/** Sets the row gutter value for this text frame.
			@param gutter The new row-gutter value in document points.
			@return Nothing.
		*/
	void SetRowGutter( ATETextDOM::Real gutter);
	/** Sets the column gutter value for this text frame.
			@param gutter The new column-gutter value in document points.
			@return Nothing.
		*/
	void SetColumnGutter( ATETextDOM::Real gutter);
	/** Sets the line spacing value for this text frame.
			@param spacing The new line spacing value in document points.
			@return Nothing.
		*/
	void SetSpacing( ATETextDOM::Real spacing);
	/** Turns optical alignment on or off for this text frame.
			@param isActive True to turn optical alignment on,
				false to turn it off.
			@return Nothing.
		*/
	void SetOpticalAlignment( bool isActive);
	/** Sets the line orientation value for this text frame.
			@param lineOrientation The new line orientation constant.
			@return Nothing.
		*/
	void SetLineOrientation( LineOrientation lineOrientation);

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	/**	Sets the paragragh direction for this text frame.
		@param direction The paragraph direction.
		@return Nothing.
		*/
	void SetStoryDirection( ParagraphDirection direction);
#endif
};

//////////////////////////////////////////////
//       --ITextFramesIterator--
//////////////////////////////////////////////
/** This object enables you to iterate through the set of
	text frames in the current document.
	@see \c ITextFrame.   	*/
class ITextFramesIterator
{
private:
	TextFramesIteratorRef	fTextFramesIterator;
public:
	/** Constructor
			@return The new object. */
	ITextFramesIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITextFramesIterator(const ITextFramesIterator& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITextFramesIterator& operator=(const ITextFramesIterator& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITextFramesIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITextFramesIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param textframesiterator The C object.
 			@return The new C++ object. */
	explicit ITextFramesIterator(TextFramesIteratorRef textframesiterator);
	/** Destructor */
	virtual ~ITextFramesIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TextFramesIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates an iterator for the text frames
		contained in a text range.
			@param range The text range object.
			@return The new iterator object.
		*/
	ITextFramesIterator( const ITextRange& range);

	// =======================================================================
	// METHODS
	// =====================================================================

	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Increments the current position in the set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Decrements the current position in the set.
			@return Nothing. */
	void Previous( );
	/** Retrieves the current text frame.
			@return The text frame object. */
	ITextFrame Item( ) const;

};

//////////////////////////////////////////////
//       --ITextLine--
//////////////////////////////////////////////

/**	This class encapsulates a line of text in a text frame.
	The line is part of an \c ITextFrame, contains \c IGlyphRun
	objects that you can access with an \c IGlyphRunIterator,
	and is associated with an \c ITextRange.
	@see \c ITextFrame::GetTextLinesIterator() */
class ITextLine
{
private:
	TextLineRef	fTextLine;
public:
	/** Constructor
			@return The new object. */
	ITextLine();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITextLine(const ITextLine& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITextLine& operator=(const ITextLine& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITextLine& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITextLine& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param textline The C object.
 			@return The new C++ object. */
	explicit ITextLine(TextLineRef textline);
	/** Destructor */
	virtual ~ITextLine();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TextLineRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// METHODS
	// =======================================================================

	/** Retrieves a glyph-run iterator with which you can access
		the glyph runs of this line.
 			@return The glyph-run iterator object.
			@see GetVisualGlyphRunsIterator()
 	 	*/
	IGlyphRunsIterator GetGlyphRunsIterator( ) const;
	/** Retrieves a glyph-run iterator with which you can access
         the glyph runs of this line, handling the special case of text that
         contains a mixture of left-to-right (LTR) and right-to-left (RTL)
         text. If this case is not expected, use \c #GetGlyphRunsIterator().
                @return The glyph-run iterator object.
				@see GetGlyphRunsIterator() */
	IGlyphRunsIterator GetVisualGlyphRunsIterator( ) const;
	/** Retrieves the parent text frame of this line.
			@return The text frame object.
	 	*/
	ITextFrame GetTextFrame( ) const;
	/** Retrieves the text range for this line.
			@return The text range object.
	 	*/
	ITextRange GetTextRange( ) const;
	/** Retrieves an array of baselines (IArrayLine) specified by a 
		start and end point in the coordinate space of the containing text frame.
		An array is required since each composed line can contain several segments 
		due to intrusions such as text wraps and Japanese features such as warichu.
			@return The array of baselines.
		*/
	IArrayLine GetBaselines() const;
};

//////////////////////////////////////////////
//       --ITextLinesIterator--
//////////////////////////////////////////////
/** This object enables you to iterate through the set of
	text lines in a text frame.
	@see \c ITextFrame::GetTextLinesIterator()	*/
class ITextLinesIterator
{
private:
	TextLinesIteratorRef	fTextLinesIterator;
public:
	/** Constructor
			@return The new object. */
	ITextLinesIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITextLinesIterator(const ITextLinesIterator& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITextLinesIterator& operator=(const ITextLinesIterator& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITextLinesIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITextLinesIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param textlinesiterator The C object.
 			@return The new C++ object. */
	explicit ITextLinesIterator(TextLinesIteratorRef textlinesiterator);
	/** Destructor */
	virtual ~ITextLinesIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TextLinesIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// METHODS
	// =======================================================================

	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Increments the current position in the set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Decrements the current position in the set.
			@return Nothing. */
	void Previous( );
	/** Retrieves the current text line.
			@return The text line object. */
	ITextLine Item( ) const;

};

//////////////////////////////////////////////
//       --ITextResources--
//////////////////////////////////////////////
/** Parent class for \c IApplicationTextResources
and \c IDocumentTextResources */
class ITextResources
{
private:
	TextResourcesRef	fTextResources;
public:
	ITextResources();
	ITextResources(const ITextResources& src);
	ITextResources& operator=(const ITextResources& rhs);
	bool operator==(const ITextResources& rhs) const;
	bool operator!=(const ITextResources& rhs) const;
	explicit ITextResources(TextResourcesRef textresources);
	virtual ~ITextResources();
	TextResourcesRef GetRef() const;
	bool IsNull() const;

	ITextResources GetTextResources( );

};

//////////////////////////////////////////////
//       --IApplicationTextResources--
//////////////////////////////////////////////
/** Parent class for \c IDocumentTextResources */
class IApplicationTextResources
{
private:
	ApplicationTextResourcesRef	fApplicationTextResources;
public:
	/** Constructor
			@return The new object. */
	IApplicationTextResources();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IApplicationTextResources(const IApplicationTextResources& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IApplicationTextResources& operator=(const IApplicationTextResources& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IApplicationTextResources& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IApplicationTextResources& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param applicationtextresources The C object.
 			@return The new C++ object. */
	explicit IApplicationTextResources(ApplicationTextResourcesRef applicationtextresources);
	/** Destructor */
	virtual ~IApplicationTextResources();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ApplicationTextResourcesRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// From parent class...
	ITextResources GetTextResources( );
	// =======================================================================
	// PROPERTIES
	// =======================================================================
	IKinsokuSet GetKinsokuSet( ) const;
	IMojiKumiSet GetMojiKumiSet( ) const;
	ICompFontClassSet GetCompFontClassSet( ) const;
	ICompFontSet GetCompFontSet( ) const;

};

//////////////////////////////////////////////
//       --IDocumentTextResources--
//////////////////////////////////////////////
/** This object encapsulates the text resources of a document.
	Text resources include fonts, character and paragraph styles,
	and various text preferences. */
class IDocumentTextResources
{
private:
	DocumentTextResourcesRef	fDocumentTextResources;
public:
	/** Constructor
			@return The new object. */
	IDocumentTextResources();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IDocumentTextResources(const IDocumentTextResources& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IDocumentTextResources& operator=(const IDocumentTextResources& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IDocumentTextResources& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IDocumentTextResources& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param documenttextresources The C object.
 			@return The new C++ object. */
	explicit IDocumentTextResources(DocumentTextResourcesRef documenttextresources);
	/** Destructor */
	virtual ~IDocumentTextResources();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	DocumentTextResourcesRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// From parent class...
 	/** Retrieves the Kinsoku set for the document.
			@return The Kinsoku set object.
		*/
	IKinsokuSet GetKinsokuSet( ) const;
 	/** Retrieves the MojiKumi set for the document.
			@return The MojiKumi set object.
		*/
	IMojiKumiSet GetMojiKumiSet( ) const;
 	/** Retrieves the composite font class set for the document.
			@return The composite font class set object.
		*/
	ICompFontClassSet GetCompFontClassSet( ) const;
 	/** Retrieves the composite font set for the document.
			@return The composite font set object.
		*/
	ICompFontSet GetCompFontSet( ) const;
 	/** Retrieves the text resources for the document.
			@return The text resources object.
		*/
	ITextResources GetTextResources( );

 	/** Retrieves the search object for the document.
			@return The search object.
		*/
	IFind GetFind( );
 	/** Retrieves the spell-check object for the document.
			@return The spell-check object.
		*/
	ISpell GetSpell( );

 	/** Retrieves the glyph for the document.
			@return The glyph object.
		*/
	IGlyph GetGlyphAndAlternates( ) const;
 	/** Retrieves the alternate glyph for the document.
			@return The glyph object.
		*/
	IGlyph GetAlternateGlyph( ) const;
	/**	Inserts a new alternate glyph.
			@param theCharacters The characters for which this glyph is an alternate.
			@param glyphID	The glyph identifier.
			@param otFeatureArray An array of features.
			@param otFeatureCount The size of the feature array.
			@param otFeatureIndexArray A mapping of the glyph-feature array to the character features.
			@param leaveSelected True to leave the character in the selected state.
			@return Nothing.
		*/
	void InsertAlternateGlyph( const ATETextDOM::Unicode* theCharacters, const ATEGlyphID glyphID, const char* otFeatureArray, ATETextDOM::Int32 otFeatureCount, const ATETextDOM::Int32* otFeatureIndexArray, bool leaveSelected);

 	/** Retrieves the alternate glyphs for the document that are available
 		for selection.
			@return The array of alternate glyphs.	*/
	IArrayInteger GetAlternatesAvailableThroughoutSelection( ) const;

 	/** Retrieves the Japanese alternate-feature value for the document selection.
			@param isFeature [out] A buffer in which to return true if the alternate is found.
			@return The feature constant.
		*/
	JapaneseAlternateFeature GetJapaneseAlternateFeatureInSelection( bool* isFeature) const;
 	/** Sets the Japanese alternate-feature value for the document selection.
			@param feature The feature constant.
			@return Nothing.
		*/
	void SetJapaneseAlternateFeatureInSelection( JapaneseAlternateFeature feature);

 	/** Retrieves the character style set for the document.
			@return The character style set object.
		*/
	ICharStyles GetCharStylesInDocument( ) const;
 	/** Retrieves the paragraph style set for the document.
			@return The paragraph style set object.
		*/
	IParaStyles GetParaStylesInDocument( ) const;
 	/** Retrieves a specific character style from the style set for the document.
			@param pName The style name.
			@return The character style object.
		*/
	ICharStyle GetCharStyle( const ATETextDOM::Unicode* pName) const;
 	/** Retrieves a specific paragraph style from the style set for the document.
			@param pName The style name.
			@return The paragraph style object.
		*/
	IParaStyle GetParaStyle( const ATETextDOM::Unicode* pName) const;
 	/** Retrieves the normal character style for the document.
			@return The character style object.
		*/
	ICharStyle GetNormalCharStyle( ) const;
 	/** Retrieves the normal paragraph style for the document.
			@return The paragraph style object.
		*/
	IParaStyle GetNormalParaStyle( ) const;
 	/** Sets the normal character style for the document to the
 		application default.
			@return Nothing.
		*/
	void ResetNormalCharStyle( );
 	/** Sets the normal paragraph style for the document to the
 		application default.
			@return Nothing.
		*/
	void ResetNormalParaStyle( );

 	/** Creates a new, empty character style and adds it to the style set for the document.
			@param pName The style name.
			@return The character style object, or a null object if a style with
				this name already exists, or if the name is an empty string. If
				no style is created, the document style set remains unchanged.
		*/
	ICharStyle CreateCharStyle( const ATETextDOM::Unicode* pName);
 	/** Creates a new, empty paragraph style and adds it to the style set for the document.
			@param pName The style name.
			@return The paragraph style object, or a null object if a style with
				this name already exists, or if the name is an empty string. If
				no style is created, the document style set remains unchanged.
		*/
	IParaStyle CreateParaStyle( const ATETextDOM::Unicode* pName);
 	/** Creates a new character style with specified features
 		and adds it to the style set for the document.
			@param pName The style name.
			@param pFeatures The feature set for the new style.
			@return The character style object, or a null object if a style with
				this name already exists, or if the name is an empty string. If
				no style is created, the document style set remains unchanged.
		*/
	ICharStyle CreateCharStyleWithFeatures( const ATETextDOM::Unicode* pName, ICharFeatures pFeatures);
 	/** Creates a new paragraph style with specified features
 		and adds it to the style set for the document.
			@param pName The style name.
			@param pFeatures The feature set for the new style.
			@return The paragraph style object, or a null object if a style with
				this name already exists, or if the name is an empty string. If
				no style is created, the document style set remains unchanged.
		*/
	IParaStyle CreateParaStyleWithFeatures( const ATETextDOM::Unicode* pName, IParaFeatures pFeatures);

	/** Removes a character style from the style set for the document.
			@param pName The style name.
			@return True if a style with this name is removed, false if no style
				with this name is in the document, or if the name is an empty string.
		*/
	bool RemoveCharStyle( const ATETextDOM::Unicode* pName);
	/** Removes a paragraph style from the style set for the document.
			@param pName The style name.
			@return True if a style with this name is removed, false if no style
				with this name is in the document, or if the name is an empty string.
		*/
	bool RemoveParaStyle( const ATETextDOM::Unicode* pName);

	/** Imports a set of character styles into this document
		from another resource set.
			@param pSrcResources The source text-resources object.
			@return Nothing.
		*/
	void ImportCharStyles( ITextResources pSrcResources);
	/** Imports a set of paragraph styles into this document
		from another resource set.
			@param pSrcResources The source text-resources object.
			@return Nothing.
		*/
	void ImportParaStyles( ITextResources pSrcResources);

	/**	Turns smart-quotes on or off for this document.
			@param smartQuotesAreOn True to turn smart-quotes on, false to turn them off.
			@return Nothing
		*/
	void SetUseSmartQuotes( bool smartQuotesAreOn);
	/**	Sets the smart-quotes double-quote character codes for a specific language.
			@param openQuote The code to use for opening double-quote.
			@param closeQuote The code to use for opening double-quote.
			@param language The language in which to use these codes.
			@return Nothing
		*/
	void SetSmartDoubleQuoteCharacters( ATETextDOM::Unicode openQuote, ATETextDOM::Unicode closeQuote, Language language);
	/**	Sets the smart-quotes single-quote character codes for a specific language.
			@param openQuote The code to use for opening single-quote.
			@param closeQuote The code to use for opening single-quote.
			@param language The language in which to use these codes.
			@return Nothing
		*/
	void SetSmartSingleQuoteCharacters( ATETextDOM::Unicode openQuote, ATETextDOM::Unicode closeQuote, Language language);
	/** Reports whether smart-quotes are on for this document.
 			@return True if smart-quotes are on.
 	 	*/
 	bool UseSmartQuotes( );
	/**	Retrieves the smart-quotes double-quote character codes for a specific language.
			@param openQuote [out] A buffer in which to return the code used for opening double-quote.
			@param closeQuote [out] A buffer in which to return the code used for opening double-quote.
			@param language The language for which to get codes.
			@return Nothing
		*/
	void GetSmartDoubleQuoteCharacters( ATETextDOM::Unicode* openQuote, ATETextDOM::Unicode* closeQuote, Language language);
	/**	Retrieves the smart-quotes single-quote character codes for a specific language.
			@param openQuote [out] A buffer in which to return the code used for opening single-quote.
			@param closeQuote [out] A buffer in which to return the code used for opening single-quote.
			@param language The language for which to get codes.
			@return Nothing
		*/
	void GetSmartSingleQuoteCharacters( ATETextDOM::Unicode* openQuote, ATETextDOM::Unicode* closeQuote, Language language);

	/** Retrieves the local overrides (character features) from the insertion
		attributes, saved from the most recent text selection or attribute change to text.
			@return The character features object.
		*/
	ICharFeatures GetInsertionCharFeatures( ) const;
	/** Retrieves the character style from the insertion
		attributes, saved from the most recent text selection or attribute change to text.
			@return The character style object.
		*/
	ICharStyle GetInsertionCharStyle( ) const;
	/** Sets the character features and style for the current insertion attributes.
			@param pFeatures The new character features object.
			@param pStyleName The new style name.
			@return Nothing
		*/
	void SetInsertionFeaturesAndStyle( const ICharFeatures& pFeatures, const ATETextDOM::Unicode* pStyleName);

	/** Retrieves the superscript size.
			@return The size in document points.
		*/
	ATETextDOM::Real GetSuperscriptSize( ) const;
	/** Sets the superscript size.
			@param value The new size in document points.
			@return Nothing
		*/
	void SetSuperscriptSize( ATETextDOM::Real value);
	/** Retrieves the superscript position.
			@return The position in document points and page coordinates.
		*/
	ATETextDOM::Real GetSuperscriptPosition( ) const;
	/** Sets the superscript position.
			@param value The new position in document points and page coordinates.
			@return Nothing
		*/
	void SetSuperscriptPosition( ATETextDOM::Real value);
	/** Retrieves the subscript size.
			@return The size in document points.
		*/
	ATETextDOM::Real GetSubscriptSize( ) const;
	/** Sets the supbscript size.
			@param value The new size in document points.
			@return Nothing
		*/
	void SetSubscriptSize( ATETextDOM::Real value);
	/** Retrieves the subscript position.
			@return The position in document points and page coordinates.
		*/
	ATETextDOM::Real GetSubscriptPosition( ) const;
	/** Sets the subscript position.
			@param value The new position in document points and page coordinates.Text that does not fit is truncated
			@return Nothing
		*/
	void SetSubscriptPosition( ATETextDOM::Real value);

	/** Retrieves the small-cap size.
			@return The size in document points.
		*/
	ATETextDOM::Real GetSmallCapSize( ) const;
	/** Sets the small-cap size.
			@param value The new size in document points.
			@return Nothing
		*/
	void SetSmallCapSize( ATETextDOM::Real value);

	/** Reports whether hidden characters are shown.
			@return True if hidden characters are shown.
		*/
	bool GetShowHiddenCharacters( ) const;
	/** Turns show hidden characters on or off.
			@param value True to show hidden characters, false to hide them.
		*/
	void SetShowHiddenCharacters( bool value);

	/** Retrieves the greeking threshhold.
			@return The greeking threshhold in document points.
		*/
	ATETextDOM::Int32 GetGreekingSize( ) const;
	/** Sets the greeking threshhold.
			@param value The new threshhold in document points.
			@return Nothing
		*/
	void SetGreekingSize( ATETextDOM::Int32 value);

	/** Reports whether substitute fonts are highlighted.
			@return True if substitute fonts are highlighted.
		*/
	bool GetHighlightSubstituteFonts( ) const;
	/** Turns highlighting of substitute fonts on or off.
			@param value True to highlight substitute fonts, false to turn highlighting off.
		*/
	void SetHighlightSubstituteFonts( bool value);
	/** Reports whether alternate glyphs are highlighted.
			@return True if alternate glyphs are highlighted.
		*/
	bool GetHighlightAlternateGlyphs( ) const;
	/** Turns highlighting of alternate glyphs on or off.
			@param value True to highligh alternate glyphs, false to turn highlighting off.
		*/
	void SetHighlightAlternateGlyphs( bool value);

};

//////////////////////////////////////////////
//       --IVersionInfo--
//////////////////////////////////////////////
/** This object encapsulates version information for
	the Adobe Text Engine (ATE).
*/
class IVersionInfo
{
private:
	VersionInfoRef	fVersionInfo;
public:
	/** Constructor
			@return The new object. */
	IVersionInfo();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IVersionInfo(const IVersionInfo& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IVersionInfo& operator=(const IVersionInfo& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IVersionInfo& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IVersionInfo& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param versioninfo The C object.
 			@return The new C++ object. */
	explicit IVersionInfo(VersionInfoRef versioninfo);
	/** Destructor */
	virtual ~IVersionInfo();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	VersionInfoRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Retrieves the major version portion of the version number.
			@return The major version value. */
	int GetMajorVersion( );
	/** Retrieves the minor version portion of the version number.
			@return The minor version value. */
	int GetMinorVersion( );
	/** Retrieves the sub-minor version (patch) portion of the version number.
			@return The sub-minor version value. */
	int GetSubMinorVersion( );

	/** Retrieves the version number as a string of UTF-16 characters.
		For example:
		@code
 ASUTF16 versionString[256];
 GetVersionAsUTF16(versionString , 256);
		@endcode
		@param versionString [out] A buffer in which to return the string.
		@param maxLength The number of characters in the buffer.
	*/
	int GetVersionAsUTF16( ASUTF16* versionString, int maxLength);

};

//////////////////////////////////////////////
//       --IArrayApplicationPaintRef--
//////////////////////////////////////////////
/** Provides access to an ordered collection of application paint
	objects, which encapsulate Illustrator-specific painting
	of fill and stroke for text, as defined by the \c #AIATEPaintSuite.
	@see \c IApplicationPaint
	*/

class IArrayApplicationPaintRef
{
private:
	ArrayApplicationPaintRefRef	fArrayApplicationPaintRef;
public:
	/** Constructor
			@return The new object. */
	IArrayApplicationPaintRef();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayApplicationPaintRef(const IArrayApplicationPaintRef& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayApplicationPaintRef& operator=(const IArrayApplicationPaintRef& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayApplicationPaintRef& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayApplicationPaintRef& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayapplicationpaintref The C object.
 			@return The new C++ object. */
	explicit IArrayApplicationPaintRef(ArrayApplicationPaintRefRef arrayapplicationpaintref);
	/** Destructor */
	virtual ~IArrayApplicationPaintRef();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayApplicationPaintRefRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	IApplicationPaint GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	IApplicationPaint GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member object.
		*/
	IApplicationPaint Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayReal--
//////////////////////////////////////////////
/** Provides access to an ordered collection of real-number values. */
class IArrayReal
{
private:
	ArrayRealRef	fArrayReal;
public:
	/** Constructor
			@return The new object. */
	IArrayReal();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayReal(const IArrayReal& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayReal& operator=(const IArrayReal& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayReal& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayReal& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayreal The C object.
 			@return The new C++ object. */
	explicit IArrayReal(ArrayRealRef arrayreal);
	/** Destructor */
	virtual ~IArrayReal();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayRealRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	ATETextDOM::Real GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	ATETextDOM::Real GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	ATETextDOM::Real Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayBool--
//////////////////////////////////////////////
/** Provides access to an ordered collection of boolean values. */
class IArrayBool
{
private:
	ArrayBoolRef	fArrayBool;
public:
	/** Constructor
			@return The new object. */
	IArrayBool();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayBool(const IArrayBool& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayBool& operator=(const IArrayBool& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayBool& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayBool& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraybool The C object.
 			@return The new C++ object. */
	explicit IArrayBool(ArrayBoolRef arraybool);
	/** Destructor */
	virtual ~IArrayBool();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayBoolRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	bool GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	bool GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	bool Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayInteger--
//////////////////////////////////////////////
/** Provides access to an ordered collection of integer values. */
class IArrayInteger
{
private:
	ArrayIntegerRef	fArrayInteger;
public:
	/** Constructor
			@return The new object. */
	IArrayInteger();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayInteger(const IArrayInteger& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayInteger& operator=(const IArrayInteger& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayInteger& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayInteger& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayinteger The C object.
 			@return The new C++ object. */
	explicit IArrayInteger(ArrayIntegerRef arrayinteger);
	/** Destructor */
	virtual ~IArrayInteger();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayIntegerRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	ATETextDOM::Int32 GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	ATETextDOM::Int32 GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	ATETextDOM::Int32 Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLineCapType--
//////////////////////////////////////////////
/** Provides access to an ordered collection of line-cap type values.
	See \c #LineCapType. */
class IArrayLineCapType
{
private:
	ArrayLineCapTypeRef	fArrayLineCapType;
public:
	/** Constructor
			@return The new object. */
	IArrayLineCapType();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayLineCapType(const IArrayLineCapType& src);
 	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayLineCapType& operator=(const IArrayLineCapType& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayLineCapType& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayLineCapType& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraylinecaptype The C object.
 			@return The new C++ object. */
	explicit IArrayLineCapType(ArrayLineCapTypeRef arraylinecaptype);
	/** Destructor */
	virtual ~IArrayLineCapType();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayLineCapTypeRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	LineCapType GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	LineCapType GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	LineCapType Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFigureStyle--
//////////////////////////////////////////////
/** Provides access to an ordered collection of figure style values.
	See \c #FigureStyle. */
class IArrayFigureStyle
{
private:
	ArrayFigureStyleRef	fArrayFigureStyle;
public:
	/** Constructor
			@return The new object. */
	IArrayFigureStyle();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayFigureStyle(const IArrayFigureStyle& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayFigureStyle& operator=(const IArrayFigureStyle& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayFigureStyle& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayFigureStyle& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayfigurestyle The C object.
 			@return The new C++ object. */
	explicit IArrayFigureStyle(ArrayFigureStyleRef arrayfigurestyle);
	/** Destructor */
	virtual ~IArrayFigureStyle();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayFigureStyleRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	FigureStyle GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	FigureStyle GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	FigureStyle Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLineJoinType--
//////////////////////////////////////////////
/** Provides access to an ordered collection of line-join type values.
	See \c #LineJoinType. */
class IArrayLineJoinType
{
private:
	ArrayLineJoinTypeRef	fArrayLineJoinType;
public:
	/** Constructor
			@return The new object. */
	IArrayLineJoinType();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayLineJoinType(const IArrayLineJoinType& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayLineJoinType& operator=(const IArrayLineJoinType& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayLineJoinType& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayLineJoinType& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraylinejointype The C object.
 			@return The new C++ object. */
	explicit IArrayLineJoinType(ArrayLineJoinTypeRef arraylinejointype);
	/** Destructor */
	virtual ~IArrayLineJoinType();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayLineJoinTypeRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	LineJoinType GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	LineJoinType GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	LineJoinType Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayWariChuJustification--
//////////////////////////////////////////////
/** Provides access to an ordered collection of WariChu justification values.
	See \c #WariChuJustification. */
class IArrayWariChuJustification
{
private:
	ArrayWariChuJustificationRef	fArrayWariChuJustification;
public:
	/** Constructor
			@return The new object. */
	IArrayWariChuJustification();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayWariChuJustification(const IArrayWariChuJustification& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayWariChuJustification& operator=(const IArrayWariChuJustification& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayWariChuJustification& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayWariChuJustification& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraywarichujustification The C object.
 			@return The new C++ object. */
	explicit IArrayWariChuJustification(ArrayWariChuJustificationRef arraywarichujustification);
	/** Destructor */
	virtual ~IArrayWariChuJustification();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayWariChuJustificationRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	WariChuJustification GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	WariChuJustification GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	WariChuJustification Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayStyleRunAlignment--
//////////////////////////////////////////////
/** Provides access to an ordered collection of style-run alignment values.
	See \c #StyleRunAlignment. */
class IArrayStyleRunAlignment
{
private:
	ArrayStyleRunAlignmentRef	fArrayStyleRunAlignment;
public:
	/** Constructor
			@return The new object. */
	IArrayStyleRunAlignment();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayStyleRunAlignment(const IArrayStyleRunAlignment& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayStyleRunAlignment& operator=(const IArrayStyleRunAlignment& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayStyleRunAlignment& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayStyleRunAlignment& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraystylerunalignment The C object.
 			@return The new C++ object. */
	explicit IArrayStyleRunAlignment(ArrayStyleRunAlignmentRef arraystylerunalignment);
	/** Destructor */
	virtual ~IArrayStyleRunAlignment();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayStyleRunAlignmentRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	StyleRunAlignment GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	StyleRunAlignment GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	StyleRunAlignment Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayAutoKernType--
//////////////////////////////////////////////
/** Provides access to an ordered collection of automatic kern type values.
	See \c #AutoKernType. */
class IArrayAutoKernType
{
private:
	ArrayAutoKernTypeRef	fArrayAutoKernType;
public:
	/** Constructor
			@return The new object. */
	IArrayAutoKernType();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayAutoKernType(const IArrayAutoKernType& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayAutoKernType& operator=(const IArrayAutoKernType& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayAutoKernType& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayAutoKernType& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayautokerntype The C object.
 			@return The new C++ object. */
	explicit IArrayAutoKernType(ArrayAutoKernTypeRef arrayautokerntype);
	/** Destructor */
	virtual ~IArrayAutoKernType();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayAutoKernTypeRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	AutoKernType GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	AutoKernType GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	AutoKernType Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayBaselineDirection--
//////////////////////////////////////////////
/** Provides access to an ordered collection of baseline direction values.
	See \c #BaselineDirection. */
class IArrayBaselineDirection
{
private:
	ArrayBaselineDirectionRef	fArrayBaselineDirection;
public:
	/** Constructor
			@return The new object. */
	IArrayBaselineDirection();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayBaselineDirection(const IArrayBaselineDirection& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayBaselineDirection& operator=(const IArrayBaselineDirection& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayBaselineDirection& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayBaselineDirection& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraybaselinedirection The C object.
 			@return The new C++ object. */
	explicit IArrayBaselineDirection(ArrayBaselineDirectionRef arraybaselinedirection);
	/** Destructor */
	virtual ~IArrayBaselineDirection();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayBaselineDirectionRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	BaselineDirection GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	BaselineDirection GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	BaselineDirection Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLanguage--
//////////////////////////////////////////////
/** Provides access to an ordered collection of language values.
	See \c #Language. */
class IArrayLanguage
{
private:
	ArrayLanguageRef	fArrayLanguage;
public:
	/** Constructor
			@return The new object. */
	IArrayLanguage();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayLanguage(const IArrayLanguage& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayLanguage& operator=(const IArrayLanguage& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayLanguage& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayLanguage& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraylanguage The C object.
 			@return The new C++ object. */
	explicit IArrayLanguage(ArrayLanguageRef arraylanguage);
	/** Destructor */
	virtual ~IArrayLanguage();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayLanguageRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	Language GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	Language GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	Language Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFontCapsOption--
//////////////////////////////////////////////
/** Provides access to an ordered collection of font caps option values.
	See \c #FontCapsOption. */
class IArrayFontCapsOption
{
private:
	ArrayFontCapsOptionRef	fArrayFontCapsOption;
public:
	/** Constructor
			@return The new object. */
	IArrayFontCapsOption();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayFontCapsOption(const IArrayFontCapsOption& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayFontCapsOption& operator=(const IArrayFontCapsOption& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayFontCapsOption& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayFontCapsOption& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayfontcapsoption The C object.
 			@return The new C++ object. */
	explicit IArrayFontCapsOption(ArrayFontCapsOptionRef arrayfontcapsoption);
	/** Destructor */
	virtual ~IArrayFontCapsOption();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayFontCapsOptionRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	FontCapsOption GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	FontCapsOption GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	FontCapsOption Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFontBaselineOption--
//////////////////////////////////////////////
/** Provides access to an ordered collection of font baseline option values.
	See \c #FontBaselineOption. */
class IArrayFontBaselineOption
{
private:
	ArrayFontBaselineOptionRef	fArrayFontBaselineOption;
public:
	/** Constructor
			@return The new object. */
	IArrayFontBaselineOption();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayFontBaselineOption(const IArrayFontBaselineOption& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayFontBaselineOption& operator=(const IArrayFontBaselineOption& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayFontBaselineOption& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayFontBaselineOption& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayfontbaselineoption The C object.
 			@return The new C++ object. */
	explicit IArrayFontBaselineOption(ArrayFontBaselineOptionRef arrayfontbaselineoption);
	/** Destructor */
	virtual ~IArrayFontBaselineOption();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayFontBaselineOptionRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	FontBaselineOption GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	FontBaselineOption GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	FontBaselineOption Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFontOpenTypePositionOption--
//////////////////////////////////////////////
/** Provides access to an ordered collection of font OpenType position option values.
	See \c #FontOpenTypePositionOption. */
class IArrayFontOpenTypePositionOption
{
private:
	ArrayFontOpenTypePositionOptionRef	fArrayFontOpenTypePositionOption;
public:
	/** Constructor
			@return The new object. */
	IArrayFontOpenTypePositionOption();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayFontOpenTypePositionOption(const IArrayFontOpenTypePositionOption& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayFontOpenTypePositionOption& operator=(const IArrayFontOpenTypePositionOption& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayFontOpenTypePositionOption& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayFontOpenTypePositionOption& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayfontopentypepositionoption The C object.
 			@return The new C++ object. */
	explicit IArrayFontOpenTypePositionOption(ArrayFontOpenTypePositionOptionRef arrayfontopentypepositionoption);
	/** Destructor */
	virtual ~IArrayFontOpenTypePositionOption();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayFontOpenTypePositionOptionRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	FontOpenTypePositionOption GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	FontOpenTypePositionOption GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	FontOpenTypePositionOption Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayUnderlinePosition--
//////////////////////////////////////////////
/** Provides access to an ordered collection of underline position values.
	See \c #UnderlinePosition. */
class IArrayUnderlinePosition
{
private:
	ArrayUnderlinePositionRef	fArrayUnderlinePosition;
public:
	/** Constructor
			@return The new object. */
	IArrayUnderlinePosition();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayUnderlinePosition(const IArrayUnderlinePosition& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayUnderlinePosition& operator=(const IArrayUnderlinePosition& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayUnderlinePosition& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayUnderlinePosition& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayunderlineposition The C object.
 			@return The new C++ object. */
	explicit IArrayUnderlinePosition(ArrayUnderlinePositionRef arrayunderlineposition);
	/** Destructor */
	virtual ~IArrayUnderlinePosition();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayUnderlinePositionRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	UnderlinePosition GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	UnderlinePosition GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	UnderlinePosition Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayStrikethroughPosition--
//////////////////////////////////////////////
/** Provides access to an ordered collection of strikethrough position values.
	See \c #StrikethroughPosition. */
class IArrayStrikethroughPosition
{
private:
	ArrayStrikethroughPositionRef	fArrayStrikethroughPosition;
public:
	/** Constructor
			@return The new object. */
	IArrayStrikethroughPosition();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayStrikethroughPosition(const IArrayStrikethroughPosition& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayStrikethroughPosition& operator=(const IArrayStrikethroughPosition& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayStrikethroughPosition& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayStrikethroughPosition& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraystrikethroughposition The C object.
 			@return The new C++ object. */
	explicit IArrayStrikethroughPosition(ArrayStrikethroughPositionRef arraystrikethroughposition);
	/** Destructor */
	virtual ~IArrayStrikethroughPosition();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayStrikethroughPositionRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	StrikethroughPosition GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	StrikethroughPosition GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	StrikethroughPosition Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayParagraphJustification--
//////////////////////////////////////////////
/** Provides access to an ordered collection of paragraph justification values.
	See \c #ParagraphJustification. */
class IArrayParagraphJustification
{
private:
	ArrayParagraphJustificationRef	fArrayParagraphJustification;
public:
	/** Constructor
			@return The new object. */
	IArrayParagraphJustification();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayParagraphJustification(const IArrayParagraphJustification& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayParagraphJustification& operator=(const IArrayParagraphJustification& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayParagraphJustification& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayParagraphJustification& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayparagraphjustification The C object.
 			@return The new C++ object. */
	explicit IArrayParagraphJustification(ArrayParagraphJustificationRef arrayparagraphjustification);
	/** Destructor */
	virtual ~IArrayParagraphJustification();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayParagraphJustificationRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	ParagraphJustification GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	ParagraphJustification GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	ParagraphJustification Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayArrayReal--
//////////////////////////////////////////////
/** Provides access to an ordered collection of arrays of real-number values. */
class IArrayArrayReal
{
private:
	ArrayArrayRealRef	fArrayArrayReal;
public:
	/** Constructor
			@return The new object. */
	IArrayArrayReal();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayArrayReal(const IArrayArrayReal& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayArrayReal& operator=(const IArrayArrayReal& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayArrayReal& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayArrayReal& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayarrayreal The C object.
 			@return The new C++ object. */
	explicit IArrayArrayReal(ArrayArrayRealRef arrayarrayreal);
	/** Destructor */
	virtual ~IArrayArrayReal();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayArrayRealRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of member arrays.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member array value. 	*/
	IArrayReal GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member array value. 	*/
	IArrayReal GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member array value.
		*/
	IArrayReal Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayBurasagariType--
//////////////////////////////////////////////
/** Provides access to an ordered collection of Burasagari type values.
	See \c #BurasagariType. */
class IArrayBurasagariType
{
private:
	ArrayBurasagariTypeRef	fArrayBurasagariType;
public:
	/** Constructor
			@return The new object. */
	IArrayBurasagariType();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayBurasagariType(const IArrayBurasagariType& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayBurasagariType& operator=(const IArrayBurasagariType& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayBurasagariType& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayBurasagariType& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayburasagaritype The C object.
 			@return The new C++ object. */
	explicit IArrayBurasagariType(ArrayBurasagariTypeRef arrayburasagaritype);
	/** Destructor */
	virtual ~IArrayBurasagariType();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayBurasagariTypeRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	BurasagariType GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	BurasagariType GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	BurasagariType Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayPreferredKinsokuOrder--
//////////////////////////////////////////////
/** Provides access to an ordered collection of preferred Kinsoku order values.
	See \c #PreferredKinsokuOrder. */
class IArrayPreferredKinsokuOrder
{
private:
	ArrayPreferredKinsokuOrderRef	fArrayPreferredKinsokuOrder;
public:
	/** Constructor
			@return The new object. */
	IArrayPreferredKinsokuOrder();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayPreferredKinsokuOrder(const IArrayPreferredKinsokuOrder& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayPreferredKinsokuOrder& operator=(const IArrayPreferredKinsokuOrder& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayPreferredKinsokuOrder& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayPreferredKinsokuOrder& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraypreferredkinsokuorder The C object.
 			@return The new C++ object. */
	explicit IArrayPreferredKinsokuOrder(ArrayPreferredKinsokuOrderRef arraypreferredkinsokuorder);
	/** Destructor */
	virtual ~IArrayPreferredKinsokuOrder();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayPreferredKinsokuOrderRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	PreferredKinsokuOrder GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	PreferredKinsokuOrder GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	PreferredKinsokuOrder Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayKinsokuRef--
//////////////////////////////////////////////
/** Provides access to an ordered collection of Kinsoku objects. */
class IArrayKinsokuRef
{
private:
	ArrayKinsokuRefRef	fArrayKinsokuRef;
public:
	/** Constructor
			@return The new object. */
	IArrayKinsokuRef();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayKinsokuRef(const IArrayKinsokuRef& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayKinsokuRef& operator=(const IArrayKinsokuRef& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayKinsokuRef& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayKinsokuRef& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraykinsokuref The C object.
 			@return The new C++ object. */
	explicit IArrayKinsokuRef(ArrayKinsokuRefRef arraykinsokuref);
	/** Destructor */
	virtual ~IArrayKinsokuRef();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayKinsokuRefRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	IKinsoku GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	IKinsoku GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member object.
		*/
	IKinsoku Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayMojiKumiRef--
//////////////////////////////////////////////
/** Provides access to an ordered collection of MojiKumi objects. */
class IArrayMojiKumiRef
{
private:
	ArrayMojiKumiRefRef	fArrayMojiKumiRef;
public:
	/** Constructor
			@return The new object. */
	IArrayMojiKumiRef();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayMojiKumiRef(const IArrayMojiKumiRef& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayMojiKumiRef& operator=(const IArrayMojiKumiRef& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayMojiKumiRef& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayMojiKumiRef& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraymojikumiref The C object.
 			@return The new C++ object. */
	explicit IArrayMojiKumiRef(ArrayMojiKumiRefRef arraymojikumiref);
	/** Destructor */
	virtual ~IArrayMojiKumiRef();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayMojiKumiRefRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	IMojiKumi GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	IMojiKumi GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member object.
		*/
	IMojiKumi Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayMojiKumiSetRef--
//////////////////////////////////////////////
/** Provides access to an ordered collection of MojiKumi set objects. */
class IArrayMojiKumiSetRef
{
private:
	ArrayMojiKumiSetRefRef	fArrayMojiKumiSetRef;
public:
	/** Constructor
			@return The new object. */
	IArrayMojiKumiSetRef();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayMojiKumiSetRef(const IArrayMojiKumiSetRef& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayMojiKumiSetRef& operator=(const IArrayMojiKumiSetRef& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayMojiKumiSetRef& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayMojiKumiSetRef& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraymojikumisetref The C object.
 			@return The new C++ object. */
	explicit IArrayMojiKumiSetRef(ArrayMojiKumiSetRefRef arraymojikumisetref);
	/** Destructor */
	virtual ~IArrayMojiKumiSetRef();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayMojiKumiSetRefRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	IMojiKumiSet GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	IMojiKumiSet GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member object.
		*/
	IMojiKumiSet Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayTabStopsRef--
//////////////////////////////////////////////
/** Provides access to an ordered collection of tab-stops objects. */
class IArrayTabStopsRef
{
private:
	ArrayTabStopsRefRef	fArrayTabStopsRef;
public:
	/** Constructor
			@return The new object. */
	IArrayTabStopsRef();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayTabStopsRef(const IArrayTabStopsRef& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayTabStopsRef& operator=(const IArrayTabStopsRef& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayTabStopsRef& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayTabStopsRef& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraytabstopsref The C object.
 			@return The new C++ object. */
	explicit IArrayTabStopsRef(ArrayTabStopsRefRef arraytabstopsref);
	/** Destructor */
	virtual ~IArrayTabStopsRef();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayTabStopsRefRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	ITabStops GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	ITabStops GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member object.
		*/
	ITabStops Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLeadingType--
//////////////////////////////////////////////
/** Provides access to an ordered collection of preferred leading type values.
	See \c #LeadingType. */
class IArrayLeadingType
{
private:
	ArrayLeadingTypeRef	fArrayLeadingType;
public:
	/** Constructor
			@return The new object. */
	IArrayLeadingType();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayLeadingType(const IArrayLeadingType& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayLeadingType& operator=(const IArrayLeadingType& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayLeadingType& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayLeadingType& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayleadingtype The C object.
 			@return The new C++ object. */
	explicit IArrayLeadingType(ArrayLeadingTypeRef arrayleadingtype);
	/** Destructor */
	virtual ~IArrayLeadingType();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayLeadingTypeRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	LeadingType GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	LeadingType GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	LeadingType Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayFontRef--
//////////////////////////////////////////////
/** Provides access to an ordered collection of font objects. */
class IArrayFontRef
{
private:
	ArrayFontRefRef	fArrayFontRef;
public:
	/** Constructor
			@return The new object. */
	IArrayFontRef();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayFontRef(const IArrayFontRef& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayFontRef& operator=(const IArrayFontRef& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayFontRef& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayFontRef& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayfontref The C object.
 			@return The new C++ object. */
	explicit IArrayFontRef(ArrayFontRefRef arrayfontref);
	/** Destructor */
	virtual ~IArrayFontRef();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayFontRefRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	IFont GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	IFont GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member object.
		*/
	IFont Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayGlyphID--
//////////////////////////////////////////////
/** Provides access to an ordered collection of glyph identifier objects. */
class IArrayGlyphID
{
private:
	ArrayGlyphIDRef	fArrayGlyphID;
public:
	/** Constructor
			@return The new object. */
	IArrayGlyphID();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayGlyphID(const IArrayGlyphID& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayGlyphID& operator=(const IArrayGlyphID& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayGlyphID& rhs) const;
	 /** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same.   */
	bool operator!=(const IArrayGlyphID& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayglyphid The C object.
 			@return The new C++ object. */
	explicit IArrayGlyphID(ArrayGlyphIDRef arrayglyphid);
	/** Destructor */
	virtual ~IArrayGlyphID();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayGlyphIDRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	ATEGlyphID GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	ATEGlyphID GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member object.
		*/
	ATEGlyphID Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayRealPoint--
//////////////////////////////////////////////
/** Provides access to an ordered collection of point position values
	with real-number coordinates.  */
class IArrayRealPoint
{
private:
	ArrayRealPointRef	fArrayRealPoint;
public:
	/** Constructor
			@return The new object. */
	IArrayRealPoint();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayRealPoint(const IArrayRealPoint& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayRealPoint& operator=(const IArrayRealPoint& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayRealPoint& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayRealPoint& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayrealpoint The C object.
 			@return The new C++ object. */
	explicit IArrayRealPoint(ArrayRealPointRef arrayrealpoint);
	/** Destructor */
	virtual ~IArrayRealPoint();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayRealPointRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	ATETextDOM::RealPoint GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	ATETextDOM::RealPoint GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	ATETextDOM::RealPoint Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayRealMatrix--
//////////////////////////////////////////////
/** Provides access to an ordered collection of transformation matrix values. */
class IArrayRealMatrix
{
private:
	ArrayRealMatrixRef	fArrayRealMatrix;
public:
	/** Constructor
			@return The new object. */
	IArrayRealMatrix();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayRealMatrix(const IArrayRealMatrix& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayRealMatrix& operator=(const IArrayRealMatrix& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayRealMatrix& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayRealMatrix& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayrealmatrix The C object.
 			@return The new C++ object. */
	explicit IArrayRealMatrix(ArrayRealMatrixRef arrayrealmatrix);
	/** Destructor */
	virtual ~IArrayRealMatrix();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayRealMatrixRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	ATETextDOM::RealMatrix GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	ATETextDOM::RealMatrix GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	ATETextDOM::RealMatrix Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayLine--
//////////////////////////////////////////////
/** Provides access to an ordered collection of line objects 
	where each entry is the start and end point of a 2D line.
*/
class IArrayLine 
{
private:
	ArrayLineRef	fArrayLine;
public:
	/** Constructor.
			@return The new object. */
	IArrayLine();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayLine(const IArrayLine& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayLine& operator=(const IArrayLine& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayLine& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayLine& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param ArrayLineRef The C object.
 			@return The new C++ object. */
	explicit IArrayLine(ArrayLineRef ArrayLineRef);
	/** Destructor */
	virtual ~IArrayLine();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayLineRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	
	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves the line start and end points of a 2Dline in this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@param lineStart [out] the ATETextDOM::RealPoint object defining the start of the line.
			@param lineEnd [out] the ATETextDOM::RealPoint object defining the end of the line.
			@return Nothing.
		*/
	void Item( ATETextDOM::Int32 index, ATETextDOM::FloatPoint* lineStart, ATETextDOM::FloatPoint* lineEnd) const;
};

//////////////////////////////////////////////
//       --IArrayComposerEngine--
//////////////////////////////////////////////
/** Provides access to an ordered collection of composer engine objects.
*/
class IArrayComposerEngine
{
private:
	ArrayComposerEngineRef	fArrayComposerEngine;
public:
	/** Constructor.
			@return The new object. */
	IArrayComposerEngine();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayComposerEngine(const IArrayComposerEngine& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayComposerEngine& operator=(const IArrayComposerEngine& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayComposerEngine& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayComposerEngine& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraycomposerengine The C object.
 			@return The new C++ object. */
	explicit IArrayComposerEngine(ArrayComposerEngineRef arraycomposerengine);
	/** Destructor */
	virtual ~IArrayComposerEngine();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayComposerEngineRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	ComposerEngine GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	ComposerEngine GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	ComposerEngine Item( ATETextDOM::Int32 index) const;

};
#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
//////////////////////////////////////////////
//       --IArrayParagraphDirection--
//////////////////////////////////////////////
/** Provides access to an ordered collection of paragraph direction objects.
*/
class IArrayParagraphDirection
{
private:
	ArrayParagraphDirectionRef	fArrayParagraphDirection;
public:
	/** Constructor
			@return The new object. */
	IArrayParagraphDirection();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayParagraphDirection(const IArrayParagraphDirection& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayParagraphDirection& operator=(const IArrayParagraphDirection& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayParagraphDirection& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayParagraphDirection& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayparagraphdirection The C object.
 			@return The new C++ object. */
	explicit IArrayParagraphDirection(ArrayParagraphDirectionRef arrayparagraphdirection);
	/** Destructor */
	virtual ~IArrayParagraphDirection();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayParagraphDirectionRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	ParagraphDirection GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	ParagraphDirection GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	ParagraphDirection Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayJustificationMethod--
//////////////////////////////////////////////
/** Provides access to an ordered collection of justification method objects.
*/
class IArrayJustificationMethod
{
private:
	ArrayJustificationMethodRef	fArrayJustificationMethod;
public:
	/** Constructor
			@return The new object. */
	IArrayJustificationMethod();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayJustificationMethod(const IArrayJustificationMethod& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayJustificationMethod& operator=(const IArrayJustificationMethod& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayJustificationMethod& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayJustificationMethod& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arrayjustificationmethod The C object.
 			@return The new C++ object. */
	explicit IArrayJustificationMethod(ArrayJustificationMethodRef arrayjustificationmethod);
	/** Destructor */
	virtual ~IArrayJustificationMethod();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayJustificationMethodRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	JustificationMethod GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	JustificationMethod GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	JustificationMethod Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayKashidaWidth--
//////////////////////////////////////////////
/** Provides access to an ordered collection of justification method objects.
*/
class IArrayKashidaWidth
{
private:
	ArrayKashidaWidthRef	fArrayKashidaWidth;
public:
	/** Constructor
			@return The new object. */
	IArrayKashidaWidth();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayKashidaWidth(const IArrayKashidaWidth& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayKashidaWidth& operator=(const IArrayKashidaWidth& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayKashidaWidth& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayKashidaWidth& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraykashidawidth The C object.
 			@return The new C++ object. */
	explicit IArrayKashidaWidth(ArrayKashidaWidthRef arraykashidawidth);
	/** Destructor */
	virtual ~IArrayKashidaWidth();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayKashidaWidthRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	KashidaWidth GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	KashidaWidth GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	KashidaWidth Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayKashidas--
//////////////////////////////////////////////
/** Provides access to an ordered collection of kashidas objects.
*/
class IArrayKashidas
{
private:
	ArrayKashidasRef	fArrayKashidas;
public:
	/** Constructor
			@return The new object. */
	IArrayKashidas();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayKashidas(const IArrayKashidas& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayKashidas& operator=(const IArrayKashidas& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayKashidas& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayKashidas& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraykashidas The C object.
 			@return The new C++ object. */
	explicit IArrayKashidas(ArrayKashidasRef arraykashidas);
	/** Destructor */
	virtual ~IArrayKashidas();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayKashidasRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	Kashidas GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	Kashidas GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	Kashidas Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayDirOverride--
//////////////////////////////////////////////
/** Provides access to an ordered collection of writing direction override objects.
*/
class IArrayDirOverride
{
private:
	ArrayDirOverrideRef	fArrayDirOverride;
public:
	/** Constructor
			@return The new object. */
	IArrayDirOverride();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayDirOverride(const IArrayDirOverride& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayDirOverride& operator=(const IArrayDirOverride& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayDirOverride& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayDirOverride& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraydiroverride The C object.
 			@return The new C++ object. */
	explicit IArrayDirOverride(ArrayDirOverrideRef arraydiroverride);
	/** Destructor */
	virtual ~IArrayDirOverride();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayDirOverrideRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	DirOverride GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	DirOverride GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	DirOverride Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayDigitSet--
//////////////////////////////////////////////
/** Provides access to an ordered collection of digit set objects.
*/
class IArrayDigitSet
{
private:
	ArrayDigitSetRef	fArrayDigitSet;
public:
	/** Constructor
			@return The new object. */
	IArrayDigitSet();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayDigitSet(const IArrayDigitSet& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayDigitSet& operator=(const IArrayDigitSet& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayDigitSet& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayDigitSet& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraydigitset The C object.
 			@return The new C++ object. */
	explicit IArrayDigitSet(ArrayDigitSetRef arraydigitset);
	/** Destructor */
	virtual ~IArrayDigitSet();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayDigitSetRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	DigitSet GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	DigitSet GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	DigitSet Item( ATETextDOM::Int32 index) const;

};

//////////////////////////////////////////////
//       --IArrayDiacVPos--
//////////////////////////////////////////////
/** Provides access to an ordered collection of diacritics positioning objects.
*/
class IArrayDiacVPos
{
private:
	ArrayDiacVPosRef	fArrayDiacVPos;
public:
	/** Constructor
			@return The new object. */
	IArrayDiacVPos();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IArrayDiacVPos(const IArrayDiacVPos& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IArrayDiacVPos& operator=(const IArrayDiacVPos& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IArrayDiacVPos& rhs) const;
	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IArrayDiacVPos& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param arraydiacvpos The C object.
 			@return The new C++ object. */
	explicit IArrayDiacVPos(ArrayDiacVPosRef arraydiacvpos);
	/** Destructor */
	virtual ~IArrayDiacVPos();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ArrayDiacVPosRef GetRef() const;
	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	DiacVPos GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	DiacVPos GetLast( ) const;

	// ========================================================================
	// METHODS
	// ========================================================================

	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param index The 0-based position index.
			@return The member value.
		*/
	DiacVPos Item( ATETextDOM::Int32 index) const;

};
#endif


//////////////////////////////////////////////
//       --ICharFeatures--
//////////////////////////////////////////////

/** This class encapsulates the complete set of	character attributes that
	can be applied to text. An object of this type is contained in an
	\c ICharStyle object, and is returned from various methods that
	query character features of text runs and text ranges. A paragraph
	style can also have a default set of character features; see
	\c IParaFeatures::GetDefaultCharFeatures().

	Attribute values are inherited from the Normal style, and can be overridden
	in a named style associated with the character, or at the local character level.

	A style or character can partially define attributes. Only those values
	that are assigned override the inherited values. The constructor creates
	an empty object, in which all attribute values are unassigned.
	Setting a value causes it to be assigned, and clearing it causes
	it to be unassigned. When you retrieve an attribute value, a boolean
	return value, \c isAssigned, reports whether that attribute has a local
	value in the queried object.

	@see \c ICharInspector

	*/
class ICharFeatures
{
private:
	CharFeaturesRef	fCharFeatures;
public:
	/** Constructor. The object is empty; that is, all
		attribute values are unassigned.
			@return The new object. */
	ICharFeatures();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICharFeatures(const ICharFeatures& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICharFeatures& operator=(const ICharFeatures& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICharFeatures& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICharFeatures& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param charfeatures The C object.
 			@return The new C++ object. */
	explicit ICharFeatures(CharFeaturesRef charfeatures);
	/** Destructor */
	virtual ~ICharFeatures();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CharFeaturesRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Creates a duplicate of this object.
			@return The new object. */
	ICharFeatures Clone( ) const;

	///////////////////////////////////////////////////////////////////////
	// GET PROPERTIES
	///////////////////////////////////////////////////////////////////////

	/** Retrieves the font attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The font object. */
	IFont GetFont( bool* isAssigned) const;
	/** Retrieves the font size attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The font size in dcoument points. */
	ATETextDOM::Real GetFontSize( bool* isAssigned) const;
	/** Retrieves the horizontal scale attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The scale value, where 1 is 100% */
	ATETextDOM::Real GetHorizontalScale( bool* isAssigned) const;
	/** Retrieves the vertical scale attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The scale value, where 1 is 100%. */
	ATETextDOM::Real GetVerticalScale( bool* isAssigned) const;
	/** Retrieves the automatic leading attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if automatic leading is on, false if it is off. */
	bool GetAutoLeading( bool* isAssigned) const;
	/** Retrieves the leading attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The leading value in document points. */
	ATETextDOM::Real GetLeading( bool* isAssigned) const;
	/** Retrieves the tracking attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The tracking value in document points. */
	ATETextDOM::Int32 GetTracking( bool* isAssigned) const;
	/** Retrieves the baseline shift attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The baseline shift value in document points. */
	ATETextDOM::Real GetBaselineShift( bool* isAssigned) const;
	/** Retrieves the character rotation attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The character rotation value in degrees. */
	ATETextDOM::Real GetCharacterRotation( bool* isAssigned) const;
	/** Retrieves the automatic kerning type attribute of this character.
		(The actual kerning value applies to character pairs rather than
		individual characters, so is available through the \c ICharStyle.)
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The automatic kerning type constant.
			@note Use \c IStory::GetKern( ) to get the kerning
				value for a text range.	*/
	AutoKernType GetAutoKernType( bool* isAssigned) const;

	/** Retrieves the font caps option attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The font caps option constant. */
	FontCapsOption GetFontCapsOption( bool* isAssigned) const;
	/** Retrieves the font baseline option attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The font baseline option constant. */
	FontBaselineOption GetFontBaselineOption( bool* isAssigned) const;
	/** Retrieves the font OpenType position option attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The font OpenType position option constant. */
	FontOpenTypePositionOption GetFontOpenTypePositionOption( bool* isAssigned) const;
	/** Retrieves the strikethrough position attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The strikethrough position constant. */
	StrikethroughPosition GetStrikethroughPosition( bool* isAssigned) const;
	/** Retrieves the underline position attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The underline position constant. */
	UnderlinePosition GetUnderlinePosition( bool* isAssigned) const;
	/** Retrieves the underline offset attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The underline offset value, in document points. */
	ATETextDOM::Real GetUnderlineOffset( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// OpenType settings
	// ------------------------------------------------------------------
	/** Retrieves the OpenType ligature attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if ligature is on, false if it is off. */
	bool GetLigature( bool* isAssigned) const;
	/** Retrieves the OpenType discretionary ligatures attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if discretionary ligatures are on, false if they are off. */
	bool GetDiscretionaryLigatures( bool* isAssigned) const;
	/** Retrieves the OpenType context ligatures attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if context ligatures are on, false if they are off. */
	bool GetContextualLigatures( bool* isAssigned) const;
	/** Retrieves the OpenType alternate ligatures attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if alternate ligatures are on, false if they are off. */
	bool GetAlternateLigatures( bool* isAssigned) const;
	/** Retrieves the OpenType old-style attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if the character is old-style, false if it is not. */
	bool GetOldStyle( bool* isAssigned) const;
	/** Retrieves the OpenType fractions attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if fractions are on, false if they are off. */
	bool GetFractions( bool* isAssigned) const;
	/** Retrieves the OpenType ordinals attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if ordinals are on, false if they are off. */
	bool GetOrdinals( bool* isAssigned) const;
	/** Retrieves the OpenType swash attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if swash is on, false if it is off. */
	bool GetSwash( bool* isAssigned) const;
	/** Retrieves the OpenType titling attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if titling is on, false if it is off. */
	bool GetTitling( bool* isAssigned) const;
	/** Retrieves the OpenType connection forms attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if connection forms are on, false if they are off. */
	bool GetConnectionForms( bool* isAssigned) const;
	/** Retrieves the OpenType stylistic alternates attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if stylistic alternates are on, false if they are off. */
	bool GetStylisticAlternates( bool* isAssigned) const;
	/** Retrieves the OpenType stylistic sets attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value. */
	ATETextDOM::Int32 GetStylisticSets(bool* isAssigned) const;
	/** Retrieves the OpenType ornaments attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if ornaments are on, false if they are off. */
	bool GetOrnaments( bool* isAssigned) const;
	/** Retrieves the OpenType figure style attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The figure style constant. */
	FigureStyle GetFigureStyle( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Japanese OpenType settings
	// ------------------------------------------------------------------
	/** Retrieves the Japanese OpenType proportional metrics attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if proportional metrics are on, false if they are off. */
	bool GetProportionalMetrics( bool* isAssigned) const;
	/** Retrieves the Japanese OpenType Kana attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if Kana is on, false if it is off. */
	bool GetKana( bool* isAssigned) const;
	/** Retrieves the Japanese OpenType Ruby attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if Ruby is on, false if it is off. */
	bool GetRuby( bool* isAssigned) const;
	/** Retrieves the Japanese OpenType italics attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if italics is on, false if it is off. */
	bool GetItalics( bool* isAssigned) const;
	/** Retrieves the Japanese OpenType baseline direction attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The baseline direction constant. */
	BaselineDirection GetBaselineDirection( bool* isAssigned) const;
	/** Retrieves the Japanese OpenType language attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The language constant. */
	Language GetLanguage( bool* isAssigned) const;
	/** Retrieves the Japanese OpenType alternate feature attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The Japanese alternate feature constant. */
	JapaneseAlternateFeature GetJapaneseAlternateFeature( bool* isAssigned) const;
	/** Retrieves the Japanese OpenType Tsume attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The Tsume value, in document points. */
	ATETextDOM::Real GetTsume( bool* isAssigned) const;
	/** Retrieves the Japanese OpenType style run alignment attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The style run alignment constant. */
	StyleRunAlignment GetStyleRunAlignment( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// WariChu settings
	// ------------------------------------------------------------------
	/** Retrieves the WariChu-enabled attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if WariChu is on, false if it is off. */
	bool GetWariChuEnabled( bool* isAssigned) const;
	/** Retrieves the WariChu line count attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The WariChu line count value. */
	ATETextDOM::Int32 GetWariChuLineCount( bool* isAssigned) const;
	/** Retrieves the WariChu line gap attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The WariChu line gap value. */
	ATETextDOM::Int32 GetWariChuLineGap( bool* isAssigned) const;
	/** Retrieves the WariChu scale attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The WariChu scale factor, where 1 is 100% */
	ATETextDOM::Real GetWariChuScale( bool* isAssigned) const;
	/** Retrieves the WariChu size attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The WariChu size in document points. */
	ATETextDOM::Real GetWariChuSize( bool* isAssigned) const;
	/** Retrieves the WariChu widow amount attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The WariChu widow amount value. */
	ATETextDOM::Int32 GetWariChuWidowAmount( bool* isAssigned) const;
	/** Retrieves the WariChu orphan amount attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The WariChu orphan amount value. */
	ATETextDOM::Int32 GetWariChuOrphanAmount( bool* isAssigned) const;
	/** Retrieves the WariChu justification attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The WariChu justification constant. */
	WariChuJustification GetWariChuJustification( bool* isAssigned) const;
	/** Retrieves the Tate Chu Yoko up-down adjustment attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The up-down adjustment value. */
	ATETextDOM::Int32 GetTCYUpDownAdjustment( bool* isAssigned) const;
	/** Retrieves the Tate Chu Yoko right-left adjustment attribute of this character style.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The right-left adjustment value. */
	ATETextDOM::Int32 GetTCYLeftRightAdjustment( bool* isAssigned) const;
	/** Retrieves the left Aki attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The left Aki value. */
	ATETextDOM::Real GetLeftAki( bool* isAssigned) const;
	/** Retrieves the right Aki attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The right Aki value. */
	ATETextDOM::Real GetRightAki( bool* isAssigned) const;
	//---------------------------------------------------------------
	// General settings
	//---------------------------------------------------------------
	/** Retrieves the no-break attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if no-break is on, false if it is off. */
	bool GetNoBreak( bool* isAssigned) const;
	/** Retrieves the fill color attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The paint object containing the fill color. */
	IApplicationPaint GetFillColor( bool* isAssigned) const;
	/** Retrieves the stroke color attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The paint object containing the stroke color. */
	IApplicationPaint GetStrokeColor( bool* isAssigned) const;
	/** Retrieves the fill attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if fill is on, false if it is off. */
	bool GetFill( bool* isAssigned) const;
	/** Retrieves the fill visibilty attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if fill is visible, false if it is not. */
	bool GetFillVisible( bool* isAssigned) const;
	/** Retrieves the stroke attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if stroke is on, false if it is off. */
	bool GetStroke( bool* isAssigned) const;
	/** Retrieves the stroke visibility attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if stroke is visible, false if it is not. */
	bool GetStrokeVisible( bool* isAssigned) const;	
	/** Retrieves the fill-first attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if fill-first is on, false if it is off. */
	bool GetFillFirst( bool* isAssigned) const;
	/** Retrieves the fill overprint attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if fill overprint is on, false if it is off. */
	bool GetFillOverPrint( bool* isAssigned) const;
	/** Retrieves the stroke overprint attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if stroke overprint is on, false if it is off. */
	bool GetStrokeOverPrint( bool* isAssigned) const;
	/** Retrieves the fill background color attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The paint object containing the fill color. */
	IApplicationPaint GetFillBackgroundColor( bool* isAssigned) const;
	/** Retrieves the fill background attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if fill is on, false if it is off. */
	bool GetFillBackground( bool* isAssigned) const;
	/** Retrieves the line cap attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The line cap type constant. */
	LineCapType GetLineCap( bool* isAssigned) const;
	/** Retrieves the line join attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The line join type constant. */
	LineJoinType GetLineJoin( bool* isAssigned) const;
	/** Retrieves the line width attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The line width value in document points. */
	ATETextDOM::Real GetLineWidth( bool* isAssigned) const;
	/** Retrieves the miter limit attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The miter limit value in document points. */
	ATETextDOM::Real GetMiterLimit( bool* isAssigned) const;
	/** Retrieves the line dash offset attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The line dash offset value in document points. */
	ATETextDOM::Real GetLineDashOffset( bool* isAssigned) const;
	/** Retrieves the line dash array attribute of this character.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The line dash array object. */
	IArrayReal GetLineDashArray( bool* isAssigned) const;

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	// ------------------------------------------------------------------
	// Complex Script Settings
	// ------------------------------------------------------------------

	/**	Retrieves the kashidas attribute of this character.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return The kashidas object.
	*/
	Kashidas GetKashidas( bool* isAssigned) const;
	/**	Retrieves the direction override attribute of this character.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return The direction override object.
	*/
	DirOverride GetDirOverride( bool* isAssigned) const;
	/**	Retrieves the digit set attribute of this character.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return The digit set object.
	*/
	DigitSet GetDigitSet( bool* isAssigned) const;
	/**	Retrieves the diacritics positioning attribute of this 
			character.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return The diacritics positioning object.
	*/
	DiacVPos GetDiacVPos( bool* isAssigned) const;
	/**	Retrieves the diacritics x offset attribute of this 
			character as a real number.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return diacritics x offset as a real number.
	*/
	ATETextDOM::Real GetDiacXOffset( bool* isAssigned) const;
	/**	Retrieves the diacritics y offset attribute of this 
			character as a real number.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return diacritics y offset as a real number.
	*/
	ATETextDOM::Real GetDiacYOffset( bool* isAssigned) const;
	/**	Retrieves the automatic diacritics y distance from baseline attribute of this character.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return True if automatic diacritics y distance from baseline is on, false if it is off.
	*/
	bool GetAutoMydfb( bool* isAssigned) const;
	/**	Retrieves the diacritics y distance from baseline attribute 
			 of this character as a real number.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return diacritics y distance from baseline as a real number.
	*/
	ATETextDOM::Real GetMarkYDistFromBaseline( bool* isAssigned) const;
	/**	Retrieves the OpenType overlap swash attribute of
			this character.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return True if overlap swash is on, false if it is off.
	*/
	bool GetOverlapSwash( bool* isAssigned) const;
	/**	Retrieves the justification alternates attribute of
			this character.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return True if justification alternates is on, false if it is off.
	*/
	bool GetJustificationAlternates( bool* isAssigned) const;
	/**	Retrieves the stretched alternates attribute of this character.
		@param isAssigned [out] a buffer in which to return 
			true if this attribute has a local value.
		@return True if stretched alternates is on, false if it is off.
	*/
	bool GetStretchedAlternates( bool* isAssigned) const;
#endif

	///////////////////////////////////////////////////////////////////
	// SET PROPERTIES
	////////////////////////////////////////////////////////////////

	/** Sets the local font attribute for this character.
			@param newVal The new font object.
			@return Nothing.
		*/
	void SetFont( IFont newVal);
	/** Sets the local font size attribute for this character.
			@param newVal The new value, in the range [0.1..1296].
			@return Nothing.
		*/
	void SetFontSize( ATETextDOM::Real newVal);
	/** Sets the local horizontal scale attribute for this character.
			@param newVal The new scaling factor, in the range [0.1..100], where 1 is 100%.
			@return Nothing.
		*/
	void SetHorizontalScale( ATETextDOM::Real newVal);
	/** Sets the local vertical scale attribute for this character.
			@param newVal The new scaling factor, in the range [0.1..100], where 1 is 100%.
			@return Nothing.
		*/
	void SetVerticalScale( ATETextDOM::Real newVal);
	/** Sets the local automatic leading attribute for this character.
			@param newVal True to turn automatic leading on, false to turn it off.
			@return Nothing.
		*/
	void SetAutoLeading( bool newVal);
	/** Sets the local leading attribute for this character.
			@param newVal The new leading value in document points.
			@return Nothing.
		*/
	void SetLeading( ATETextDOM::Real newVal);
	/** Sets the local tracking attribute for this character.
			@param newVal The new tracking value in document points.
			@return Nothing.
		*/
	void SetTracking( ATETextDOM::Int32 newVal);
	/** Sets the local baseline shift attribute for this character.
			@param newVal The new baseline shift value in document points.
			@return Nothing.
		*/
	void SetBaselineShift( ATETextDOM::Real newVal);
	/** Sets the local character rotation attribute for this character.
			@param newVal The new rotation value in degrees.
			@return Nothing.
		*/
	void SetCharacterRotation( ATETextDOM::Real newVal);
	/** Sets the local automatic kerning type attribute for this character style.
		This is not available for individual characters.
			@param newVal The new automatic kerning type constant.
			@return Nothing.
		*/
	void SetAutoKernType( AutoKernType newVal);
	/** Sets the local font caps option attribute for this character style.
			@param newVal The new font caps option constant.
			@return Nothing.
		*/
	void SetFontCapsOption( FontCapsOption newVal);
	/** Sets the local font baseline option attribute for this character style.
			@param newVal The new font baseline option constant.
			@return Nothing.
		*/
	void SetFontBaselineOption( FontBaselineOption newVal);
	/** Sets the local font OpenType position option attribute for this character style.
			@param newVal The new font OpenType position option constant.
			@return Nothing.
		*/
	void SetFontOpenTypePositionOption( FontOpenTypePositionOption newVal);
	/** Sets the local strikethrough position  attribute for this character style.
			@param newVal The new strikethrough position constant.
			@return Nothing.
		*/
	void SetStrikethroughPosition( StrikethroughPosition newVal);
	/** Sets the local underline position  attribute for this character style.
			@param newVal The new underline position constant.
			@return Nothing.
		*/
	void SetUnderlinePosition( UnderlinePosition newVal);
	/** Sets the local underline offset  attribute for this character style.
			@param newVal The new underline offset value, in document points.
			@return Nothing.
		*/
	void SetUnderlineOffset( ATETextDOM::Real newVal);
	// ------------------------------------------------------------------
	// OpenType settings
	// ------------------------------------------------------------------
	/** Sets the local OpenType ligature attribute for this character style.
			@param newVal The new underline offset value, in document points.
			@return Nothing.
		*/
	void SetLigature( bool newVal);
	/** Sets the local OpenType discretionary ligatures attribute for this character style.
			@param newVal True to turn discretionary ligatures on, false to turn it off.
			@return Nothing.
		*/
	void SetDiscretionaryLigatures( bool newVal);
	/** Sets the local OpenType contextual ligatures attribute for this character style.
			@param newVal True to turn contextual ligatures on, false to turn it off.
			@return Nothing.
		*/
	void SetContextualLigatures( bool newVal);
	/** Sets the local OpenType alternate ligatures attribute for this character style.
			@param newVal True to turn alternate ligatures on, false to turn it off.
			@return Nothing.
		*/
	void SetAlternateLigatures( bool newVal);
	/** Sets the local OpenType old-style attribute for this character style.
			@param newVal True to turn old-style on, false to turn it off.
			@return Nothing.
		*/
	void SetOldStyle( bool newVal);
	/** Sets the local OpenType fractions attribute for this character style.
			@param newVal True to turn fractions on, false to turn it off.
			@return Nothing.
		*/
	void SetFractions( bool newVal);
	/** Sets the local OpenType ordinals attribute for this character style.
			@param newVal True to turn ordinals on, false to turn it off.
			@return Nothing.
		*/
	void SetOrdinals( bool newVal);
	/** Sets the local OpenType swash attribute for this character style.
			@param newVal True to turn swash on, false to turn it off.
			@return Nothing.
		*/
	void SetSwash( bool newVal);
	/** Sets the local OpenType titling attribute for this character style.
			@param newVal True to turn titling on, false to turn it off.
			@return Nothing.
		*/
	void SetTitling( bool newVal);
	/** Sets the local OpenType connection forms attribute for this character style.
			@param newVal True to turn connection forms on, false to turn it off.
			@return Nothing.
		*/
	void SetConnectionForms( bool newVal);
	/** Sets the local OpenType stylistic alternates attribute for this character style.
			@param newVal True to turn stylistic alternates on, false to turn it off.
			@return Nothing.
		*/
	void SetStylisticAlternates( bool newVal);

	/** Sets the local OpenType stylistic sets attributes for this character style.	
	*/
	void SetStylisticSets(ATETextDOM::Int32 newVal);
	/** Sets the local OpenType ornaments attribute for this character style.
			@param newVal True to turn ornaments on, false to turn it off.
			@return Nothing.
		*/
	void SetOrnaments( bool newVal);
	/** Sets the local OpenType figure style attribute for this character style.
			@param newVal The new figure style constant.
			@return Nothing.
		*/
	void SetFigureStyle( FigureStyle newVal);
	// ------------------------------------------------------------------
	// Japanese OpenType settings
	// ------------------------------------------------------------------
	/** Sets the local Japanese OpenType proportional metrics attribute of this character.
			@param newVal True to turn proportional metrics on, false to turn it off.
			@return Nothing. */
	void SetProportionalMetrics( bool newVal);
	/** Sets the local Japanese OpenType Kana attribute of this character.
			@param newVal True to turn Kana on, false to turn it off.
			@return Nothing. */
	void SetKana( bool newVal);
	/** Sets the local Japanese OpenType italics attribute of this character.
			@param newVal True to turn italics on, false to turn it off.
			@return Nothing. */
	void SetItalics( bool newVal);
	/** Sets the local Japanese OpenType Ruby attribute of this character.
			@param newVal True to turn Ruby on, false to turn it off.
			@return Nothing. */
	void SetRuby( bool newVal);
	/** Sets the local Japanese OpenType baseline direction attribute of this character.
			@param newVal The new baseline direction constant.
			@return Nothing. */
	void SetBaselineDirection( BaselineDirection newVal);
	/** Sets the local Japanese OpenType language attribute of this character.
			@param newVal The new language constant.
			@return Nothing. */
	void SetLanguage( Language newVal);
	/** Sets the local Japanese OpenType Japanese alternate feature attribute of this character.
			@param newVal The new Japanese alternate feature constant.
			@return Nothing. */
	void SetJapaneseAlternateFeature( JapaneseAlternateFeature newVal);
	/** Sets the local Japanese OpenType Tsume attribute of this character.
			@param newVal The new Tsume value in document points.
			@return Nothing. */
	void SetTsume( ATETextDOM::Real newVal);
	/** Sets the local Japanese OpenType style run alignment attribute of this character.
			@param newVal The new style run alignment constant.
			@return Nothing. */
	void SetStyleRunAlignment( StyleRunAlignment newVal);
	// ------------------------------------------------------------------
	// WariChu settings
	// ------------------------------------------------------------------
	/** Sets the local WariChu enabled attribute of this character.
			@param newVal True to turn enabling on, false to turn it off.
			@return Nothing. */
	void SetWariChuEnabled( bool newVal);
	/** Sets the local WariChu line count attribute of this character.
			@param newVal The new line count value.
			@return Nothing. */
	void SetWariChuLineCount( ATETextDOM::Int32 newVal);
	/** Sets the local WariChu line gap attribute of this character.
			@param newVal The new line gap value.
			@return Nothing. */
	void SetWariChuLineGap( ATETextDOM::Int32 newVal);
	/** Sets the local WariChu scale attribute of this character.
			@param newVal The new scaling factor, where 1 is 100%.
			@return Nothing. */
	void SetWariChuScale( ATETextDOM::Real newVal);
	/** Sets the local WariChu size attribute of this character.
			@param newVal The new size value in document points.
			@return Nothing. */
	void SetWariChuSize( ATETextDOM::Real newVal);
	/** Sets the local WariChu widow amount attribute of this character.
			@param newVal The new widow amount value.
			@return Nothing. */
	void SetWariChuWidowAmount( ATETextDOM::Int32 newVal);
	/** Sets the local WariChu orphan amount attribute of this character.
			@param newVal The new orphan amount value.
			@return Nothing. */
	void SetWariChuOrphanAmount( ATETextDOM::Int32 newVal);
	/** Sets the local WariChu justification attribute of this character.
			@param newVal The new justification constant.
			@return Nothing. */
	void SetWariChuJustification( WariChuJustification newVal);
	/** Sets the local Tate Chu Yoko up-down adjustment attribute of this character.
			@param newVal The new adjustment value.
			@return Nothing. */
	void SetTCYUpDownAdjustment( ATETextDOM::Int32 newVal);
	/** Sets the local Tate Chu Yoko right-left adjustment attribute of this character.
			@param newVal The new adjustment value.
			@return Nothing. */
	void SetTCYLeftRightAdjustment( ATETextDOM::Int32 newVal);
	/** Sets the local left Aki attribute of this character.
			@param newVal The new left Aki value.
			@return Nothing. */
	void SetLeftAki( ATETextDOM::Real newVal);
	/** Sets the local right Aki attribute of this character.
			@param newVal The new right Aki value.
			@return Nothing. */
	void SetRightAki( ATETextDOM::Real newVal);
	//------------------------------------------------
	// General settings
	//------------------------------------------------
	/** Sets the local no-break attribute of this character.
			@param newVal True to turn no-break on, false to turn it off.
			@return Nothing. */
	void SetNoBreak( bool newVal);
	/** Sets the local fill color attribute of this character.
			@param newVal The paint object containing the new fill color value.
			@return Nothing. */
	void SetFillColor( IApplicationPaint newVal);
	/** Sets the local stroke color attribute of this character.
			@param newVal The paint object containing the new stroke color value.
			@return Nothing. */
	void SetStrokeColor( IApplicationPaint newVal);
	/** Sets the local fill attribute of this character.
			@param newVal True to turn fill on, false to turn it off.
			@return Nothing. */
	void SetFill( bool newVal);
	/** Sets the local fill visibilty attribute of this character.
			@param newVal True to turn fill visibility on, false to turn it off.
			@return Nothing. */
	void SetFillVisible( bool newVal);	
	/** Sets the local stroke attribute of this character.
			@param newVal True to turn stroke on, false to turn it off.
			@return Nothing. */
	void SetStroke( bool newVal);
	/** Sets the local stroke visibility attribute of this character.
			@param newVal True to turn stroke visibility on, false to turn it off.
			@return Nothing. */
	void SetStrokeVisible( bool newVal);
	/** Sets the local fill-first attribute of this character.
			@param newVal True to turn fill-first on, false to turn it off.
			@return Nothing. */
	void SetFillFirst( bool newVal);
	/** Sets the local fill overprint attribute of this character.
			@param newVal True to turn fill overprint on, false to turn it off.
			@return Nothing. */
	void SetFillOverPrint( bool newVal);
	/** Sets the local stroke overprint attribute of this character.
			@param newVal True to turn stroke overprint on, false to turn it off.
			@return Nothing. */
	void SetStrokeOverPrint( bool newVal);
	/** Sets the local fill background color attribute of this character.
			@param newVal The paint object containing the new fill color value.
			@return Nothing. */
	void SetFillBackgroundColor( IApplicationPaint newVal);
	/** Sets the local fill background attribute of this character.
			@param newVal True to turn fill on, false to turn it off.
			@return Nothing. */
	void SetFillBackground( bool newVal);
	/** Sets the local line cap attribute of this character.
			@param newVal The new line cap type constant.
			@return Nothing. */
	void SetLineCap( LineCapType newVal);
	/** Sets the local line join attribute of this character.
			@param newVal The new line join type constant.
			@return Nothing. */
	void SetLineJoin( LineJoinType newVal);
	/** Sets the local line width attribute of this character.
			@param newVal The new line width value in document points.
			@return Nothing. */
	void SetLineWidth( ATETextDOM::Real newVal);
	/** Sets the local miter limit attribute of this character.
			@param newVal The new miter limit value in document points.
			@return Nothing. */
	void SetMiterLimit( ATETextDOM::Real newVal);
	/** Sets the local line dash offset attribute of this character.
			@param newVal The new line dash offset value in document points.
			@return Nothing. */
	void SetLineDashOffset( ATETextDOM::Real newVal);
	/** Sets the local line dash array attribute of this character.
			@param newVal The new line dash array object.
			@return Nothing. */
	void SetLineDashArray( IArrayReal newVal);

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	// ------------------------------------------------------------------
	// Complex Script Settings
	// ------------------------------------------------------------------

	/**	Sets the kashidas attribute of this character.
		@param newVal The new kashidas object.
		@return Nothing.
	*/
	void SetKashidas( Kashidas newVal);
	/**	Sets the direction override attribute of this character.
		@param newVal The new direction override object.
		@return Nothing.
	*/
	void SetDirOverride( DirOverride newVal);
	/**	Sets the digit set attribute of this character.
		@param newVal The new digit set object.
		@return Nothing.
	*/
	void SetDigitSet( DigitSet newVal);
	/**	Sets the diacritics positioning attribute of this character.
		@param newVal The diacritics positioning object.
		@return Nothing.
	*/
	void SetDiacVPos( DiacVPos newVal);
	/**	Sets the diacritics x offset attribute of this character.
		@param newVal The new diacritics x offset in document points.
		@return Nothing.
	*/
	void SetDiacXOffset( ATETextDOM::Real newVal);
	/**	Sets the diacritics y offset attribute of this character.
		@param newVal The new diacritics y offset in document points.
		@return Nothing.
	*/
	void SetDiacYOffset( ATETextDOM::Real newVal);
	/**	Sets the automatic diacritics y distance from baseline attribute of this character.
		@param newVal True to turn automatic diacritics y distance from baseline on, false to turn it off.
		@return Nothing.
	*/
	void SetAutoMydfb( bool newVal);
	/**	Sets the diacritics y distance from baseline attribute of this character.
		@param newVal The new diacritics y distance from baseline in document points.
		@return Nothing.
	*/
	void SetMarkYDistFromBaseline( ATETextDOM::Real newVal);
	/**	Sets the overlap swash attribute of this character.
		@param newVal True to turn overlap swash on, false to turn it off.
		@return Nothing.
	*/
	void SetOverlapSwash( bool newVal);
	/**	Sets the justification alternates attribute of this character.
		@param newVal True to turn justification alternates on, false to turn it off.
		@return Nothing.
	*/
	void SetJustificationAlternates( bool newVal);
	/**	Sets the stretched alternates attribute of this character.
		@param newVal Trues to turn stretched alternates on, false to turn it off.
		@return Nothing.
	*/
	void SetStretchedAlternates( bool newVal);
#endif

	// ======================================================================
	// CLEAR PROPERTIES
	// ======================================================================

	/** Removes the local font attribute value of this character.
			@return Nothing. */
	void ClearFont( );
	/** Removes the local font size attribute value of this character.
			@return Nothing. */
	void ClearFontSize( );
	/** Removes the local horizontal scale attribute value of this character.
			@return Nothing. */
	void ClearHorizontalScale( );
	/** Removes the local vertical scale attribute value of this character.
			@return Nothing. */
	void ClearVerticalScale( );
	/** Removes the local automatic leading attribute value of this character.
			@return Nothing. */
	void ClearAutoLeading( );
	/** Removes the local leading attribute value of this character.
			@return Nothing. */
	void ClearLeading( );
	/** Removes the local tracking attribute value of this character.
			@return Nothing. */
	void ClearTracking( );
	/** Removes the local baseline shift attribute value of this character.
			@return Nothing. */
	void ClearBaselineShift( );
	/** Removes the local character rotation attribute value of this character.
			@return Nothing. */
	void ClearCharacterRotation( );
	/** Removes the local automatic kerning attribute value of this character style.
		This is not available for individual characters.
			@return Nothing. */
	void ClearAutoKernType( );
	/** Removes the local font caps option attribute value of this character.
			@return Nothing. */
	void ClearFontCapsOption( );
	/** Removes the local font baseline option attribute value of this character.
			@return Nothing. */
	void ClearFontBaselineOption( );
	/** Removes the local font OpenType position option attribute value of this character.
			@return Nothing. */
	void ClearFontOpenTypePositionOption( );
	/** Removes the local strikethrough position attribute value of this character.
			@return Nothing. */
	void ClearStrikethroughPosition( );
	/** Removes the local underline position attribute value of this character.
			@return Nothing. */
	void ClearUnderlinePosition( );
	/** Removes the local underline offset attribute value of this character.
			@return Nothing. */
	void ClearUnderlineOffset( );
	// ------------------------------------------------------------------
	// OpenType settings
	// ------------------------------------------------------------------
	/** Removes the local OpenType ligature attribute value of this character.
			@return Nothing. */
	void ClearLigature( );
	/** Removes the local OpenType discretionary ligature attribute value of this character.
			@return Nothing. */
	void ClearDiscretionaryLigatures( );
	/** Removes the local OpenType contextual ligature attribute value of this character.
			@return Nothing. */
	void ClearContextualLigatures( );
	/** Removes the local OpenType alternate ligature attribute value of this character.
			@return Nothing. */
	void ClearAlternateLigatures( );
	/** Removes the local OpenType old-style attribute value of this character.
			@return Nothing. */
	void ClearOldStyle( );
	/** Removes the local OpenType fractions attribute value of this character.
			@return Nothing. */
	void ClearFractions( );
	/** Removes the local OpenType ordinals attribute value of this character.
			@return Nothing. */
	void ClearOrdinals( );
	/** Removes the local OpenType swash attribute value of this character.
			@return Nothing. */
	void ClearSwash( );
	/** Removes the local OpenType titling attribute value of this character.
			@return Nothing. */
	void ClearTitling( );
	/** Removes the local OpenType connection forms attribute value of this character.
			@return Nothing. */
	void ClearConnectionForms( );
	/** Removes the local OpenType stylistic alternates attribute value of this character.
			@return Nothing. */
	void ClearStylisticAlternates( );
	/** Removes the local OpenType stylistic sets attribute value of this character.
	@return Nothing. */
	void ClearStylisticSets();
	/** Removes the local OpenType ornaments attribute value of this character.
			@return Nothing. */
	void ClearOrnaments( );
	/** Removes the local OpenType figure style attribute value of this character.
			@return Nothing. */
	void ClearFigureStyle( );
	// ------------------------------------------------------------------
	// Japanese OpenType settings
	// ------------------------------------------------------------------
	/** Removes the local Japanese OpenType proportional metrics attribute value of this character.
			@return Nothing. */
	void ClearProportionalMetrics( );
	/** Removes the local Japanese OpenType Kana attribute value of this character.
			@return Nothing. */
	void ClearKana( );
	/** Removes the local Japanese OpenType italics attribute value of this character.
			@return Nothing. */
	void ClearItalics( );
	/** Removes the local Japanese OpenType Ruby attribute value of this character.
			@return Nothing. */
	void ClearRuby( );
	/** Removes the local Japanese OpenType baseline direction attribute value of this character.
			@return Nothing. */
	void ClearBaselineDirection( );
	/** Removes the local Japanese OpenType language attribute value of this character.
			@return Nothing. */
	void ClearLanguage( );
	/** Removes the local Japanese OpenType Japanese alternate feature attribute value of this character.
			@return Nothing. */
	void ClearJapaneseAlternateFeature( );
	/** Removes the local Japanese OpenType Tsume attribute value of this character.
			@return Nothing. */
	void ClearTsume( );
	/** Removes the local Japanese OpenType style-run alignment attribute value of this character.
			@return Nothing. */
	void ClearStyleRunAlignment( );
	// ------------------------------------------------------------------
	// WariChu settings
	// ------------------------------------------------------------------
	/** Removes the local WariChu enabled attribute value of this character.
			@return Nothing. */
	void ClearWariChuEnabled( );
	/** Removes the local WariChu line count attribute value of this character.
			@return Nothing. */
	void ClearWariChuLineCount( );
	/** Removes the local WariChu line gap attribute value of this character.
			@return Nothing. */
	void ClearWariChuLineGap( );
	/** Removes the local WariChu sub-line amount attribute value of this character.
			@return Nothing. */
	void ClearWariChuSubLineAmount( );
	/** Removes the local WariChu widow amount attribute value of this character.
			@return Nothing. */
	void ClearWariChuWidowAmount( );
	/** Removes the local WariChu orphan amount attribute value of this character.
			@return Nothing. */
	void ClearWariChuOrphanAmount( );
	/** Removes the local WariChu justification attribute value of this character.
			@return Nothing. */
	void ClearWariChuJustification( );
	/** Removes the local Tate Chu Yoko up-down adjustment attribute value of this character.
			@return Nothing. */
	void ClearTCYUpDownAdjustment( );
	/** Removes the local Tate Chu Yoko right-left adjustment attribute value of this character.
			@return Nothing. */
	void ClearTCYLeftRightAdjustment( );
	/** Removes the local left Aki attribute value of this character.
			@return Nothing. */
	void ClearLeftAki( );
	/** Removes the local right Aki attribute value of this character.
			@return Nothing. */
	void ClearRightAki( );
	// ------------------------------------------------------------------
	// General settings
	// ------------------------------------------------------------------
	/** Removes the local no-break attribute value of this character.
			@return Nothing. */
	void ClearNoBreak( );
	/** Removes the local fill color attribute value of this character.
			@return Nothing. */
	void ClearFillColor( );
	/** Removes the local stroke color attribute value of this character.
			@return Nothing. */
	void ClearStrokeColor( );
	/** Removes the local fill attribute value of this character.
			@return Nothing. */
	void ClearFill( );
	/** Removes the local fill visibility attribute value of this character.
			@return Nothing. */
	void ClearFillVisible( );
	/** Removes the local stroke attribute value of this character.
			@return Nothing. */
	void ClearStroke( );
	/** Removes the local stroke visibility attribute value of this character.
			@return Nothing. */
	void ClearStrokeVisible( );
	/** Removes the local fill-first attribute value of this character.
			@return Nothing. */
	void ClearFillFirst( );
	/** Removes the local fill overprint attribute value of this character.
			@return Nothing. */
	void ClearFillOverPrint( );
	/** Removes the local stroke overprint attribute value of this character.
			@return Nothing. */
	void ClearStrokeOverPrint( );
	/** Removes the local fill background color attribute value of this character.
			@return Nothing. */
	void ClearFillBackgroundColor( );
	/** Removes the local fill background attribute value of this character.
			@return Nothing. */
	void ClearFillBackground( );
	/** Removes the local line cap attribute value of this character.
			@return Nothing. */
	void ClearLineCap( );
	/** Removes the local line join attribute value of this character.
			@return Nothing. */
	void ClearLineJoin( );
	/** Removes the local line width attribute value of this character.
			@return Nothing. */
	void ClearLineWidth( );
	/** Removes the local miter limit attribute value of this character.
			@return Nothing. */
	void ClearMiterLimit( );
	/** Removes the local line dash offset attribute value of this character.
			@return Nothing. */
	void ClearLineDashOffset( );
	/** Removes the local line dash array attribute value of this character.
			@return Nothing. */
	void ClearLineDashArray( );

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	// ------------------------------------------------------------------
	// Complex Script Settings
	// ------------------------------------------------------------------

	/**	Removes the kashidas attribute value of this character.
		@return Nothing.
	*/
	void ClearKashidas( );
	/**	Removes the direction override attribute value of this character.
		@return Nothing.
	*/
	void ClearDirOverride( );
	/**	Removes the digit set attribute value of this character.
		@return Nothing.
	*/
	void ClearDigitSet( );
	/**	Removes the diacritics positioning attribute value of this character.
		@return Nothing.
	*/
	void ClearDiacVPos( );
	/**	Removes the diacritics x offset attribute value of this character.
		@return Nothing.
	*/
	void ClearDiacXOffset( );
	/**	Removes the diacritics y offset attribute value of this character.
		@return Nothing.
	*/
	void ClearDiacYOffset( );
	/**	Removes the automatic diacritics y distance from baseline attribute value of this character.
		@return Nothing.
	*/
	void ClearAutoMydfb( );
	/**	Removes the diacritics y distance from baseline attribute value of this character.
		@return Nothing.
	*/
	void ClearMarkYDistFromBaseline( );
	/**	Removes the overlap swash attribute value of this character.
		@return Nothing.
	*/
	void ClearOverlapSwash( );
	/**	Removes the justification alternates attribute value of this character.
		@return Nothing.
	*/
	void ClearJustificationAlternates( );
	/**	Removes the stretched alternates attribute value of this character.
		@return Nothing.
	*/
	void ClearStretchedAlternates( );
#endif

	////////////////////////////////////////////////////////////////////////////
	// ALGEBRA METHODS
	////////////////////////////////////////////////////////////////////////////

	/**	Clears any attributes in this object whose values are
		not the same as or are unassigned in the comparison object.
		The only values that remain are those that match
		the corresponding value in the comparison object.
			@param rhs Right-hand side of comparison.
			@return True if changes were made. */
	bool IntersectFeatures( ICharFeatures rhs);
	/**	Sets any attributes in this object whose values are
		assigned in the comparison object to those values.
			@param rhs Right-hand side of comparison.
			@return True if changes were made. */
	bool ReplaceOrAddFeatures( ICharFeatures rhs);
	/**	Clears any attributes in this object whose values are the
		same as in the comparison object.
			@param rhs Right-hand side of comparison.
			@return True if changes were made. */
	bool UnassignEachIfEqual( ICharFeatures rhs);

	/**	Reports whether all attributes of this object are unassigned.
			@return True if no attributes have local values. */
	bool IsEachNotAssigned( ) const;
	/**	Reports whether all attributes of this object are assigned.
			@return True if all attributes have local values. */
	bool IsEachAssigned( ) const;

};

//////////////////////////////////////////////
//       --ICharInspector--
//////////////////////////////////////////////

/** This class allows you to retrieve the
	character features that apply to the characters in a text range,
	after considering all inherited style values and local overrides.

	Obtain an \c ICharInspector object from a text range or set of text
	ranges. See \c ITextRange::GetCharInspector().

	The methods collect the values of a particular attribute into
	an array whose order is the same as the order of characters in the text.
	*/
class ICharInspector
{
private:
	CharInspectorRef	fCharInspector;
public:
	/** Constructor. The object is empty; that is, all
		attribute values are unassigned.
			@return The new object. */
	ICharInspector();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICharInspector(const ICharInspector& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICharInspector& operator=(const ICharInspector& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICharInspector& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICharInspector& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param charinspector The C object.
 			@return The new C++ object. */
	explicit ICharInspector(CharInspectorRef charinspector);
	/** Destructor */
	virtual ~ICharInspector();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CharInspectorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	//------------------------------------------------------------
	// Properties
	//------------------------------------------------------------

	/** Retrieves the font values from the character set.
			@return The array object containing the values. */
	IArrayFontRef GetFont( ) const;
	/** Retrieves the font size values from the character set.
			@return The array object containing the values. */
	IArrayReal GetFontSize( ) const;
	/** Retrieves the horizontal scale values from the character set.
			@return The array object containing the values. */
	IArrayReal GetHorizontalScale( ) const;
	/** Retrieves the vertical scale values from the character set.
			@return The array object. */
	IArrayReal GetVerticalScale( ) const;
	/** Retrieves the synthetic bold values from the character set.
			@return The array object containing the values. */
	IArrayBool GetSyntheticBold( ) const;
	/** Retrieves the synthetic italic values from the character set.
			@return The array object containing the values. */
	IArrayBool GetSyntheticItalic( ) const;
	/** Retrieves the automatic leading values from the character set.
			@return The array object containing the values. */
	IArrayBool GetAutoLeading( ) const;
	/** Retrieves the leading values from the character set.
			@return The array object containing the values. */
	IArrayReal GetLeading( ) const;
	/** Retrieves the tracking values from the character set.
			@return The array object containing the values. */
	IArrayInteger GetTracking( ) const;
	/** Retrieves the baseline shift values from the character set.
			@return The array object containing the values. */
	IArrayReal GetBaselineShift( ) const;
	/** Retrieves the character rotation values from the character set.
			@return The array object containing the values. */
	IArrayReal GetCharacterRotation( ) const;
	/** Retrieves the font caps option values from the character set.
			@return The array object containing the values. */
	IArrayFontCapsOption GetFontCapsOption( ) const;
	/** Retrieves the font baseline option values from the character set.
			@return The array object containing the values. */
	IArrayFontBaselineOption GetFontBaselineOption( ) const;
	/** Retrieves the font OpenType position option values from the character set.
			@return The array object containing the values. */
	IArrayFontOpenTypePositionOption GetFontOpenTypePositionOption( ) const;
	/** Retrieves the strikethrough position values from the character set.
			@return The array object containing the values. */
	IArrayStrikethroughPosition GetStrikethroughPosition( ) const;
	/** Retrieves the underline position values from the character set.
			@return The array object containing the values. */
	IArrayUnderlinePosition GetUnderlinePosition( ) const;
	/** Retrieves the underline offset values from the character set.
			@return The array object containing the values. */
	IArrayReal GetUnderlineOffset( ) const;

	// ------------------------------------------------------------------
	// OpenType settings
	// ------------------------------------------------------------------
	/** Retrieves the OpenType ligature values from the character set.
			@return The array object containing the values. */
	IArrayBool GetLigature( ) const;
	/** Retrieves the OpenType discretionary ligature values from the character set.
			@return The array object containing the values. */
	IArrayBool GetDiscretionaryLigatures( ) const;
	/** Retrieves the OpenType contextual ligature values from the character set.
			@return The array object containing the values. */
	IArrayBool GetContextualLigatures( ) const;
	/** Retrieves the OpenType alternate ligature values from the character set.
			@return The array object containing the values. */
	IArrayBool GetAlternateLigatures( ) const;
	/** Retrieves the OpenType old-style values from the character set.
			@return The array object containing the values. */
	IArrayBool GetOldStyle( ) const;
	/** Retrieves the OpenType fractions values from the character set.
			@return The array object containing the values. */
	IArrayBool GetFractions( ) const;
	/** Retrieves the OpenType ordinals values from the character set.
			@return The array object containing the values. */
	IArrayBool GetOrdinals( ) const;
	/** Retrieves the OpenType swash values from the character set.
			@return The array object containing the values. */
	IArrayBool GetSwash( ) const;
	/** Retrieves the OpenType titling values from the character set.
			@return The array object containing the values. */
	IArrayBool GetTitling( ) const;
	/** Retrieves the OpenType connection forms values from the character set.
			@return The array object containing the values. */
	IArrayBool GetConnectionForms( ) const;
	/** Retrieves the OpenType stylistic alternates values from the character set.
			@return The array object containing the values. */
	IArrayBool GetStylisticAlternates( ) const;
	/** Retrieves the OpenType stylistic set values from the character set.
			@return The array object containing the values. */
	IArrayInteger GetStylisticSets( ) const;
	/** Retrieves the OpenType ornaments values from the character set.
			@return The array object containing the values. */
	IArrayBool GetOrnaments( ) const;
	/** Retrieves the OpenType figure style values from the character set.
			@return The array object containing the values. */
	IArrayFigureStyle GetFigureStyle( ) const;
	// ------------------------------------------------------------------
	// Japanese OpenType settings
	// ------------------------------------------------------------------
	/** Retrieves the Japanese OpenType proportional metrics values from the character set.
			@return The array object containing the values. */
	IArrayBool GetProportionalMetrics( ) const;
	/** Retrieves the Japanese OpenType Kana values from the character set.
			@return The array object containing the values. */
	IArrayBool GetKana( ) const;
	/** Retrieves the Japanese OpenType italics values from the character set.
			@return The array object containing the values. */
	IArrayBool GetItalics( ) const;
	/** Retrieves the Japanese OpenType Ruby values from the character set.
			@return The array object containing the values. */
	IArrayBool GetRuby( ) const;
	/** Retrieves the Japanese OpenType baseline direction values from the character set.
			@return The array object containing the values. */
	IArrayBaselineDirection GetBaselineDirection( ) const;
	/** Retrieves the Japanese OpenType language values from the character set.
			@return The array object containing the values. */
	IArrayLanguage GetLanguage( ) const;
	/** Retrieves the Japanese OpenType Tsume values from the character set.
			@return The array object containing the values. */
	IArrayReal GetTsume( ) const;
	/** Retrieves the Japanese OpenType style-run alignment values from the character set.
			@return The array object containing the values. */
	IArrayStyleRunAlignment GetStyleRunAlignment( ) const;
	// ------------------------------------------------------------------
	// WariChu settings
	// ------------------------------------------------------------------
	/** Retrieves the WariChu line count values from the character set.
			@return The array object containing the values. */
	IArrayInteger GetWariChuLineCount( ) const;
	/** Retrieves the WariChu line gap values from the character set.
			@return The array object containing the values. */
	IArrayInteger GetWariChuLineGap( ) const;
	/** Retrieves the WariChu scale values from the character set.
			@return The array object containing the values. */
	IArrayReal GetWariChuScale( ) const;
	/** Retrieves the WariChu size values from the character set.
			@return The array object containing the values. */
	IArrayReal GetWariChuSize( ) const;
	/** Retrieves the WariChu widow amount values from the character set.
			@return The array object containing the values. */
	IArrayInteger GetWariChuWidowAmount( ) const;
	/** Retrieves the WariChu orphan amount values from the character set.
			@return The array object containing the values. */
	IArrayInteger GetWariChuOrphanAmount( ) const;
	/** Retrieves the WariChu justification values from the character set.
			@return The array object containing the values. */
	IArrayWariChuJustification GetWariChuJustification( ) const;
	/** Retrieves the WariChu enabled values from the character set.
			@return The array object containing the values. */
	IArrayBool GetWariChuEnabled( ) const;
	/** Retrieves the Tate Chu Yoko up-down adjustment values from the character set.
			@return The array object containing the values. */
	IArrayInteger GetTCYUpDownAdjustment( ) const;
	/** Retrieves the Tate Chu Yoko right-left adjustment values from the character set.
			@return The array object containing the values. */
	IArrayInteger GetTCYLeftRightAdjustment( ) const;
	/** Retrieves the left Aki values from the character set.
			@return The array object containing the values. */
	IArrayReal GetLeftAki( ) const;
	/** Retrieves the right Aki values from the character set.
			@return The array object containing the values. */
	IArrayReal GetRightAki( ) const;

	// ------------------------------------------------------------------
	// General settings
	// ------------------------------------------------------------------

	/** Retrieves the no-break values from the character set.
			@return The array object containing the values. */
	IArrayBool GetNoBreak( ) const;
	/** Retrieves the fill color values from the character set.
			@return The array object containing the values. */
	IArrayApplicationPaintRef GetFillColor( ) const;
	/** Retrieves the stroke color values from the character set.
			@return The array object containing the values. */
	IArrayApplicationPaintRef GetStrokeColor( ) const;
	/** Retrieves the fill values from the character set.
			@return The array object containing the values. */
	IArrayBool GetFill( ) const;
	/** Retrieves the fill visibility values from the character set.
			@return The array object containing the values. */
	IArrayBool GetFillVisible( ) const;
	/** Retrieves the stroke values from the character set.
			@return The array object containing the values. */
	IArrayBool GetStroke( ) const;
	/** Retrieves the stroke visibility values from the character set.
			@return The array object containing the values. */
	IArrayBool GetStrokeVisible( ) const;
	/** Retrieves the fill-first values from the character set.
			@return The array object containing the values. */
	IArrayBool GetFillFirst( ) const;
	/** Retrieves the fill overprint values from the character set.
			@return The array object containing the values. */
	IArrayBool GetFillOverPrint( ) const;
	/** Retrieves the stroke overprint values from the character set.
			@return The array object containing the values. */
	IArrayBool GetStrokeOverPrint( ) const;
	/** Retrieves the fill background color values from the character set.
			@return The array object containing the values. */
	IArrayApplicationPaintRef GetFillBackgroundColor( ) const;
	/** Retrieves the fill background values from the character set.
			@return The array object containing the values. */
	IArrayBool GetFillBackground( ) const;
	/** Retrieves the line cap values from the character set.
			@return The array object containing the values. */
	IArrayLineCapType GetLineCap( ) const;
	/** Retrieves the line join values from the character set.
			@return The array object containing the values. */
	IArrayLineJoinType GetLineJoin( ) const;
	/** Retrieves the line width values from the character set.
			@return The array object containing the values. */
	IArrayReal GetLineWidth( ) const;
	/** Retrieves the miter limit values from the character set.
			@return The array object containing the values. */
	IArrayReal GetMiterLimit( ) const;
	/** Retrieves the line dash offset values from the character set.
			@return The array object containing the values. */
	IArrayReal GetLineDashOffset( ) const;
	/** Retrieves the line dash array values from the character set.
			@return The array object containing the values. */
	IArrayArrayReal GetLineDashArray( ) const;

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	// ------------------------------------------------------------------
	// Complex Script Settings
	// ------------------------------------------------------------------

	/**	Retrieves the kashidas values from the character set.
		@return The array object containing the values.
	*/
	IArrayKashidas GetKashidas( ) const;
	/**	Retrieves the direction override values from the character set.
		@return The array object containing the values.
	*/
	IArrayDirOverride GetDirOverride( ) const;
	/**	Retrieves the digit set values from the character set.
		@return The array object containing the values.
	*/
	IArrayDigitSet GetDigitSet( ) const;
	/**	Retrieves the diacritics positioning values from the character set.
		@return The array object containing the values.
	*/
	IArrayDiacVPos GetDiacVPos( ) const;
	/**	Retrieves the diacritics x offset values from the character set.
		@return The array object containing the values.
	*/
	IArrayReal GetDiacXOffset( ) const;
	/**	Retrieves the diacritics y offset values from the character set.
		@return The array object containing the values.
	*/
	IArrayReal GetDiacYOffset( ) const;
	/**	Retrieves the automatic diacritics y offset from baseline values from the character set.
		@return The array object containing the values.
	*/
	IArrayBool GetAutoMydfb( ) const;
	/**	Retrieves the diacritics y offset from baseline values from the character set.
		@return The array object containing the values.
	*/
	IArrayReal GetMarkYDistFromBaseline( ) const;
	/**	Retrieves the overlap swash values from the character set.
		@return The array object containing the values.
	*/
	IArrayBool GetOverlapSwash( ) const;
	/**	Retrieves the justification alternate values from the character set.
		@return The array object containing the values.
	*/
	IArrayBool GetJustificationAlternates( ) const;
	/**	Retrieves the stretched alternates values from the character set.
		@return The array object containing the values.
	*/
	IArrayBool GetStretchedAlternates( ) const;
#endif

};

//////////////////////////////////////////////
//       --ICharStyle--
//////////////////////////////////////////////
/** This class encapsulates a named character style, which can be
	applied to  a set of characters. It contains an \c ICharFeatures
	object, which defines the character attributes for this style.

	Attribute values are inherited from the Normal style, and can be overridden
	in a named style associated with a text run or text range, or at the
	local character level.

	A style or character can partially define attributes. Only those values
	that are assigned override the inherited values. The constructor creates
	an empty object, in which all attribute values are unassigned.
	Setting a value causes it to be assigned, and clearing it causes
	it to be unassigned. When you retrieve an attribute value, a boolean
	return value, \c isAssigned, reports whether that attribute has a local
	value in the queried object.
	*/
class ICharStyle
{
private:
	CharStyleRef	fCharStyle;
public:
	/** Constructor. The object is empty; that is, all
		attribute values are unassigned.
			@return The new object. */
	ICharStyle();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICharStyle(const ICharStyle& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICharStyle& operator=(const ICharStyle& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICharStyle& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICharStyle& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param charstyle The C object.
 			@return The new C++ object. */
	explicit ICharStyle(CharStyleRef charstyle);
	/** Destructor */
	virtual ~ICharStyle();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CharStyleRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	//-------------------------------------------------
	// Properties
	//-------------------------------------------------

	/** Retrieves the name of this style.
			@param pName [out] A buffer in which to return the name string.
			@param maxLength [in, out] The number of characters in the buffer.
			@return The length of the returned string, or 0 if an error occurred.
		*/
	ATETextDOM::Int32 GetName( ATETextDOM::Unicode* pName, ATETextDOM::Int32 maxLength) const;
	/** Sets the name of this style.
			@param pName The new, \c NULL terminated name string.
			@return True if the name was set successfully, false if a style
				already has the specified name or if the name string is empty.
		*/
	bool SetName( const ATETextDOM::Unicode* pName);
	/** Retrieves the parent style of this style.
			@return The style object, or a \c NULL object for the Normal (root) style.
		*/
	ICharStyle GetParent( ) const;
	/** Sets the parent style of this style.
			@param pStyle The new parent style object,
			@return True if the parent was set successfully, false if
				this is the  Normal (root) style.
		*/
	bool SetParent( const ICharStyle pStyle);
	/** Reports whether this style has a parent.
			@return True if this style has a parent, false if this is the Normal (root) style.
		*/
	bool HasParent( ) const;
	/** Retrieves the features defined for this style.
			@return The character features object.
		*/
	ICharFeatures GetFeatures( ) const;
	/** Sets the features defined for this style. For the Normal (root) style,
		this is the same as \c #ReplaceOrAddFeatures().	For all other
		styles, the new feature set completely replaces the old feature set.
			@param pFeatures The new character features object.
			@return Nothing.
		*/
	void SetFeatures( ICharFeatures pFeatures);
	/** Sets attribute values of this style's feature set to those values that
		are specifically assigned in the replacement feature set. Those values
		that are unassigned in the replacement set remain unchanged in this
		style.
			@param pFeatures The replacement character features object.
			@return Nothing.
		*/
	void ReplaceOrAddFeatures( ICharFeatures pFeatures);

};

//////////////////////////////////////////////
//       --ICharStyles--
//////////////////////////////////////////////
/** Encapsulates a set of character styles as a text resource.
	A style set contains a collection of \c ICharStyle objects.
	Use an \c ICharStylesIterator object to iterate through the set.
	*/
class ICharStyles
{
private:
	CharStylesRef	fCharStyles;
public:
	/** Constructor.
			@return The new object. */
	ICharStyles();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICharStyles(const ICharStyles& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICharStyles& operator=(const ICharStyles& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICharStyles& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICharStyles& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param charstyles The C object.
 			@return The new C++ object. */
	explicit ICharStyles(CharStylesRef charstyles);
	/** Destructor */
	virtual ~ICharStyles();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CharStylesRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	//-----------------------------------------------------------
	// METHODS
	//-----------------------------------------------------------

 	/** Reports whether this is set is empty.
			@return True if this set contains no style objects. */
	bool IsEmpty( ) const;

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;

	/** Shows all styles.
			@return Nothing.
			@see \c #ShowOnlyUnreferencedStyles(), \c #ShowOnlyStylesReferencedIn()
		*/
	void ShowAllStyles( ) const;
	/** Shows only styles to which there are not references in text.
			@return Nothing.
			@see \c #ShowAllStyles(), \c #ShowOnlyStylesReferencedIn()
		*/
	void ShowOnlyUnreferencedStyles( ) const;
	/** Shows only styles that are used in a text range.
			@param pRange The text range object.
			@return Nothing.
			@see \c #ShowAllStyles(), \c #ShowOnlyUnreferencedStyles()
		*/
	void ShowOnlyStylesReferencedIn( ITextRange pRange) const;
	/** Reorders styles in this set by moving a style to a given position.
			@param pStyle The style object.
			@param position The new 0-based position index.
			@return Nothing.
		*/
	void MoveStyleTo( ICharStyle pStyle, ATETextDOM::Int32 position);

};

//////////////////////////////////////////////
//       --ICharStylesIterator--
//////////////////////////////////////////////
/** This class enables you to iterate through a set of
	character styles.
	@see \c ICharStyles	*/
class ICharStylesIterator
{
private:
	CharStylesIteratorRef	fCharStylesIterator;
public:
	/** Constructor.
			@return The new object. */
	ICharStylesIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ICharStylesIterator(const ICharStylesIterator& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ICharStylesIterator& operator=(const ICharStylesIterator& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ICharStylesIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ICharStylesIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param charstylesiterator The C object.
 			@return The new C++ object. */
	explicit ICharStylesIterator(CharStylesIteratorRef charstylesiterator);
	/** Destructor */
	virtual ~ICharStylesIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	CharStylesIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates an iterator for a specific style set
		that is ordered first-to-last or last-to-first.
			@param pStyles The style set object.
			@param direction Optional. The order of iteration. Default is first to last.
			@return The new iterator object.
		*/
	ICharStylesIterator( ICharStyles pStyles, Direction direction = kForward);

	//------------------------------------------------------
	// Methods
	//------------------------------------------------------
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Sets the current position to the first member in the set.
			@return Nothing. */
	void MoveToFirst( );
	/** Sets the current position to the last member in the set.
			@return Nothing. */
	void MoveToLast( );
	/** Increments the current position in the set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Decrements the current position in the set.
			@return Nothing. */
	void Previous( );
	/** Retrieves the current character style.
			@return The character style object. */
	ICharStyle Item( ) const;

};

//////////////////////////////////////////////
//       --IFind--
//////////////////////////////////////////////
/** This class encapsulates a search through text. The
	methods allow you to find and replace text in a document
	using various kinds of character matching.

	To find or replace all matches in the search scope, do the following:
		\li Save the text object you are currently working with.
		\li Retrieve the current search position markers with \c #GetPreReplaceAllSettings()
			and save them.
		\li Implement a loop through all text objects, using
			\c #FindMatch(), \c #FindNextMatch(), and \c #ReplaceMatch()
			to find or replace all occurances of your match string.
			<br>Keep track of how many matches or replacements were found,
			to report back to the user.
		\li Restore the previous search position markers with \c #RestorePreReplaceAllSettings()
		\li Restore the working text object with \c #SetSearchRange().

	*/
class IFind
{
private:
	FindRef	fFind;
public:
	/** Constructor.
			@return The new object. */
	IFind();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IFind(const IFind& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IFind& operator=(const IFind& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IFind& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IFind& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param find The C object.
 			@return The new C++ object. */
	explicit IFind(FindRef find);
	/** Destructor */
	virtual ~IFind();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	FindRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	//------------------------------------------------------
	// Options
	//------------------------------------------------------
	/** Retrieves the direction of search, front-to-back or
		back-to-front.
			@return The direction constant.
		*/
	Direction GetSearchDirection( ) const;
	/** Reports whether searching is case-sensitive.
			@return True if the search is set to ignore case, false if
				it is case-sensitive.
		*/
	bool GetIgnoreCase( ) const;
	/** Reports whether searching matches whole words.
			@return True if the search is set to match whole words.
		*/
	bool GetWholeWord( ) const;
	/** Reports whether searching wraps.
			@return True if the search is set to wrap.
		*/
	bool GetWrap( ) const;
	/** Reports whether searching should continue beyond selected text.
			@return True if the search is set to go out-of-bounds.
		*/
	bool GetFindWordsOutOfBounds( ) const;

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	/**	Reports whether accents are to be ignored during the find.
		@return True if accents are to be ignored, false if they are not.
	*/
	bool GetIgnoreAccents( ) const;
	/**	Reports whether kashidas are to be ignored during the find.
		@return True if kashidas are to be ignored, false if they are not.
	*/
	bool GetIgnoreKashidas( ) const;
#endif	

	/** Sets the direction of search, front-to-back or back-to-front.
			@param newValue The direction constant.
			@return Nothing.
		*/
	void SetSearchDirection( Direction newValue);
	/** Sets whether searching is case-sensitive.
			@param newValue True to set the search to ignore case,
				false to make it case-sensitive.
			@return Nothing.
		*/
	void SetIgnoreCase( bool newValue);
	/** Sets whether searching matches whole words.
			@param newValue True to turn whole-word matching on,
				false to turn it off.
			@return Nothing.
		*/
	void SetWholeWord( bool newValue);
	/** Sets whether searching wraps, ignoring line breaks.
			@param newValue True to turn wrapping on,
				false to turn it off.
			@return Nothing.
		*/
	void SetWrap( bool newValue);
	/** Sets whether searching matches words that are out-of-bounds.
			@param newValue True to turn out-of-bounds matching on,
				false to turn it off.
			@return Nothing.
		*/
	void SetFindWordsOutOfBounds( bool newValue);

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	/**	Sets whether accents should be ignored during the find.
		@param newValue True to ignore accents.
		@return Nothing.
	*/
	void SetIgnoreAccents( bool newValue);
	/**	Sets whether kashidas are to be ignored during the find.
		@param newValue True to ignore kashidas.
		@return Nothing.
	*/
	void SetIgnoreKashidas( bool newValue);
#endif

	/** Retrieves the scope of the search, the entire document or the current \c IStory.
		The default scope is the entire document.
			@return The search-scope constant.
		*/
	SearchScope GetSearchScope( ) const;
	/** Sets the scope of the search to be the entire document or the current \c IStory.
		The default scope is the entire document.
			@param searchScope The search-scope constant.
			@return Nothing.
		*/
	void SetSearchScope( SearchScope searchScope);
	/** Sets the range of this search to a specific text range. Use to restore
		the range after a global search or replace operation.
			@param pRange The text range object.
			@return Nothing.
			@see Class description of \c IFind.
		*/
	void SetSearchRange( ITextRange pRange);
	/**	Sets the character string that this search tries to match
		within the range and scope.
			@param pSearchChars The search string.
			@return Nothing.
		*/
	void SetSearchChars( ATETextDOM::Unicode* pSearchChars);
	/**	Retrieves the character string that this search tries to match.
			@param pSearchChars [out] A buffer in which to return the search string.
			@param length The number of characters in the buffer. Only this much of
				the search string is returned.
			@return Nothing.
		*/
	void GetSearchChars( ATETextDOM::Unicode* pSearchChars, ATETextDOM::Int32 length) const;
	/**	Sets the character string that this search uses to replace
		matches found within the range and scope.
			@param pSearchChars The replacement string.
			@return Nothing.
		*/
	void SetReplaceChars( ATETextDOM::Unicode* pSearchChars);
	/**	Retrieves the character string that this search uses to replace
		matches found within the range and scope.
			@param pSearchChars [out] A buffer in which to return the replacement string.
			@param length The number of characters in the buffer. Only this much of
				the replacement string is returned.
			@return Nothing.
		*/
	void GetReplaceChars( ATETextDOM::Unicode* pSearchChars, ATETextDOM::Int32 length) const;
	// Temporary way to reset the engine for modeless operation
	void Reset( );
	//------------------------------------------------------
	// Methods
	//------------------------------------------------------
	// Searches current user selection.
	/** Searches for the match string in the specified text range.
			@param pTextRange The text range within which to search.
			@return True if a match is found, false otherwise.
			@see SetSearchChars()
		*/
	bool FindMatch( ITextRange pTextRange);
	// Skips the current user selection.
	/** Searches for the match string starting at the end of the current selection in the
		specified text range.
			@param pTextRange The text range object.
			@return True if a match is found, false otherwise.
			@see \c #SetSearchChars()
		*/
	bool FindNextMatch( ITextRange pTextRange);

	/** Searches for the match string in specified text range and replaces it, if found,
		with the replacement string.
			@param pTextRange The text range object.
			@param findNext When true, searches in the current selection. When
				false, begins searching at the end of the current selection.
			@return If findNext parameter is true this function will return true if there is 
				another occurance found after the one just replaced, 
				and will return false if there is no other occurance found.
				If findNext is false this function will always return false.
			@see \c #SetSearchChars(), \c #SetReplaceChars()
		*/
	bool ReplaceMatch( ITextRange pTextRange, bool findNext);

	/** @deprecated  Do not use. See class description of \c IFind.	*/
	bool FindAndReplaceAllMatches( ATETextDOM::Int32* pReplaceCount);

	/** Retrieves the current position markers in this object, so that they
		can be saved before a global search or replacement operation.
			@param pCurrentPoint A buffer in which to return the
				0-based index to the current position.
			@param pStartPoint A buffer in which to return the
				0-based index to the starting position.
			@return Nothing.
			@see Class description of \c IFind.

		*/
	void GetPreReplaceAllSettings( ATETextDOM::Int32* pCurrentPoint, ATETextDOM::Int32* pStartPoint) const;

	/** Restores the current position markers in this object after a global
		search or replacement operation.
			@param currentPoint The saved 0-based index to the current position.
			@param startPoint The saved 0-based index to the starting position.
			@return Nothing.
			@see Class description of \c IFind.
		*/
	void RestorePreReplaceAllSettings( const ATETextDOM::Int32 currentPoint, const ATETextDOM::Int32 startPoint);

};

//////////////////////////////////////////////
//       --IFont--
//////////////////////////////////////////////
/** Encapsulates a font as a text resource. The methods allow you to
	add, access, and manipulate fonts for use with the
	Adobe Text Engine (ATE). 	*/

class IFont
{
private:
	FontRef	fFont;
public:
	/** Constructor.
			@return The new object. */
	IFont();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IFont(const IFont& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IFont& operator=(const IFont& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IFont& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IFont& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param font The C object.
 			@return The new C++ object. */
	explicit IFont(FontRef font);
	/** Destructor */
	virtual ~IFont();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	FontRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	//-----------------------------------------------
	// METHODS
	//-----------------------------------------------
	/** Reports whether this is a CoolType font.
			@return True if this is a CoolType font.
		*/
	bool IsCoolTypeTechnology( ) const;

	/** Reports whether Roman glyphs in this font are sideways by default for a specified character alignment.
			@param withItalics True to report the default for italics.
			@param characterAlignment The style-run alignment constant for which to get the default.
			@return True if the default for Roman glyphs is sideways.
		*/
	bool IsVerticalRomanGlyphsOnSideByDefault( bool withItalics, StyleRunAlignment characterAlignment) const;

	/** Retrieves a pointer to the CT font dictionary for this font.
			@return A pointer to the dictionary. */
	void* GetCTFontDict( );

};

//////////////////////////////////////////////
//       --IGlyph--
//////////////////////////////////////////////
/** Encapsulates a glyph as a text resource. The methods allow you to
	add, access, and manipulate glyphs for use with the
	Adobe Text Engine (ATE). 	*/
class IGlyph
{
private:
	GlyphRef	fGlyph;
public:
	/** Constructor.
			@return The new object. */
	IGlyph();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IGlyph(const IGlyph& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IGlyph& operator=(const IGlyph& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IGlyph& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IGlyph& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param glyph The C object.
 			@return The new C++ object. */
	explicit IGlyph(GlyphRef glyph);
	/** Destructor */
	virtual ~IGlyph();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	GlyphRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the unique identifier for this glyph.
			@return The identifier. */
	ATEGlyphID GetGlyphID( ) const;
	/** Retrieves the set of alternates for this glyph.
			@return The alternate glyph set. */
	IGlyphs GetAlternateGlyphs( ) const;
	/** Retrieves the OpenType feature of this glyph.
			@param otFeatures [out] A buffer in which to return the features string.
			@param otFeatureCount [out] A buffer in which to return the number of features.
			@param otFeatureIndex [out] A buffer in which to return the index into the feature string.
			@return Nothing. */
	void GetOTFeatures( char** otFeatures, ATETextDOM::Int32* otFeatureCount, ATETextDOM::Int32** otFeatureIndex);
	// RealMatrix   GetTransformation();

};

//////////////////////////////////////////////
//       --IGlyphs--
//////////////////////////////////////////////
/** Encapsulates a set of glyphs as a text resource.
	A glyph set contains a collection of \c IGlyph objects.
	Use an \c IGlyphsIterator object to iterate through the set.
	*/
class IGlyphs
{
private:
	GlyphsRef	fGlyphs;
public:
	/** Constructor.
			@return The new object. */
	IGlyphs();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IGlyphs(const IGlyphs& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IGlyphs& operator=(const IGlyphs& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IGlyphs& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IGlyphs& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param glyphs The C object.
 			@return The new C++ object. */
	explicit IGlyphs(GlyphsRef glyphs);
	/** Destructor */
	virtual ~IGlyphs();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	GlyphsRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;
	// ========================================================================
	// PROPERTIES
	// ========================================================================
	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( );
	/** Retrieves the first member of this set.
			@return The member value. 	*/
	IGlyph GetFirst( );
	/** Retrieves the last member of this set.
			@return The member value. 	*/
	IGlyph GetLast( );
	// navigation objects.
	/** Retrieves the set of text ranges that use this glyph set.
			@return The text ranges set objet. */
	ITextRanges GetTextRanges( ) const;
	/** Retrieves the set of selected text ranges that use this glyph set.
			@return The text ranges set objet. */
	ITextRanges GetTextSelection( ) const;
	/** Creates an iterator object for all paragraphs in the current document
		that use this glyph set.
			@return The iterator object. */
	IParagraphsIterator GetParagraphsIterator( ) const;
	/** Creates an iterator object for all text runs in the current document
		that use this glyph set.
			@return The iterator object. */
	ITextRunsIterator GetTextRunsIterator( ) const;
	/** Creates an iterator object for all words in the current document
		that use this glyph set.
			@return The iterator object. */
	IWordsIterator GetWordsIterator( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	/** Appends a glyph to this set.
			@param glyph The glyph object.
			@return The 0-based position index of the successfully
				added object, or the current index of this object
				if it is already in the set, or -1 if the object
				was not in the set and could not be appended.
		*/
	void Add( const IGlyph& glyph);
	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param nIndex The 0-based position index.
			@return The member object.
		*/
	IGlyph Item( ATETextDOM::Int32 nIndex) const;
	/** Removes all members from the set.
			@return Nothing. */
	void RemoveAll( );
	/** Removes a member from the set.
			@param nIndex The 0-based position index of the member to remove.
			@return Nothing. */
	void Remove( ATETextDOM::Int32 nIndex);

};

//////////////////////////////////////////////
//       --IGlyphsIterator--
//////////////////////////////////////////////
/** This class enables you to iterate through a set of.glyphs
	@see \c IGlyphs	*/
class IGlyphsIterator
{
private:
	GlyphsIteratorRef	fGlyphsIterator;
public:
	/** Constructor.
			@return The new object. */
	IGlyphsIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IGlyphsIterator(const IGlyphsIterator& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IGlyphsIterator& operator=(const IGlyphsIterator& rhs);
	 /** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IGlyphsIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IGlyphsIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param glyphsiterator The C object.
 			@return The new C++ object. */
	explicit IGlyphsIterator(GlyphsIteratorRef glyphsiterator);
	/** Destructor */
	virtual ~IGlyphsIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	GlyphsIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates an iterator for a specific glyph set
		that is ordered first-to-last or last-to-first.
			@param glyphs The glyph set object.
			@param direction Optional. The order of iteration. Default is first-to-last.
			@return The new iterator object.
		*/
	IGlyphsIterator( IGlyphs glyphs, Direction direction = kForward);

	//------------------------------------------------------
	// Methods
	//------------------------------------------------------
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Retrieves the first member in this set.
			@return The glyph object. */
	IGlyph GetFirst( );
	/** Retrieves the last member in this set.
			@return The glyph object. */
	IGlyph GetLast( );
	/** Retrieves the next member in this set in the iterator's current direction.
			@return The glyph object. */
	IGlyph GetNext( );
	/** Retrieves the current glyph.
			@return The glyph object. */
	IGlyph Item( ) const;
	/** Increments the current position in this set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Decrements the current position in this set.
			@return Nothing. */
	void Previous( );

};

//////////////////////////////////////////////
//       --IKinsoku--
//////////////////////////////////////////////
/** Encapsulates a Kinsoku  as a text resource. The methods allow you to
	add, access, and manipulate Kinsoku for use with the
	Adobe Text Engine (ATE). The \c IKinsokuSet collects \c IKinsoku objects.
	*/
class IKinsoku
{
private:
	KinsokuRef	fKinsoku;
public:
	/** Constructor. Constructs an empty Kinsoku.
			@return The new object. */
	IKinsoku();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IKinsoku(const IKinsoku& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IKinsoku& operator=(const IKinsoku& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IKinsoku& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IKinsoku& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param kinsoku The C object.
 			@return The new C++ object. */
	explicit IKinsoku(KinsokuRef kinsoku);
	/** Destructor */
	virtual ~IKinsoku();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	KinsokuRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	//========================================================================
	// PROPERTIES
	// =======================================================================
	/** Retrieves the name of this Kinsoku.
			@param name [out] A buffer in which to return the name string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetName( ATETextDOM::Unicode* name, ATETextDOM::Int32 maxLength) const;
	/** Retrieves the number of characters in the name of this Kinsoku.
			@return The number of characters needed in the buffer to get the name. */
	ATETextDOM::Int32 GetNameSize( ) const;
	/** Sets the name of this Kinsoku.
  			@param name The name string.
   			@return Nothing. */
	void SetName( const ATETextDOM::Unicode* name);
	/** Reports whether this object matches a predefined tag.
			@param tag The tag object.
			@return True if this object matches the tag.
		*/
	bool MatchesPredefinedResourceTag( ATE::KinsokuPredefinedTag tag) const;
	/** Retrieves the characters that cannot be used to start this Kinsoku.
			@param noStartCharSet [out] A buffer in which to return the no-start character string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetNoStartCharSet( ATETextDOM::Unicode* noStartCharSet, ATETextDOM::Int32 maxLength) const;
	/** Retrieves the number of characters in the no-start character set of this Kinsoku.
			@return The number of characters needed in the buffer to get the no-start set. */
	ATETextDOM::Int32 GetNoStartCharSetSize( ) const;
	/** Sets the characters that cannot be used to start this Kinsoku.
  			@param noStartCharSet The string containing the characters.
   			@return Nothing. */
	void SetNoStartCharSet( const ATETextDOM::Unicode* noStartCharSet);
	/** Retrieves the characters that cannot be used to end this Kinsoku.
			@param noEndCharSet [out] A buffer in which to return the no-end character string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetNoEndCharSet( ATETextDOM::Unicode* noEndCharSet, ATETextDOM::Int32 maxLength) const;
	/** Retrieves the number of characters in the no-end character set of this Kinsoku.
			@return The number of characters needed in the buffer to get the no-end set. */
	ATETextDOM::Int32 GetNoEndCharSetSize( ) const;
	/** Sets the characters that cannot be used to end this Kinsoku.
  			@param noEndCharSet The string containing the characters.
   			@return Nothing. */
	void SetNoEndCharSet( const ATETextDOM::Unicode* noEndCharSet);
	/** Retrieves the characters that cannot be used at a break in this Kinsoku.
			@param noBreakCharSet [out] A buffer in which to return the no-break character string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetNoBreakCharSet( ATETextDOM::Unicode* noBreakCharSet, ATETextDOM::Int32 maxLength) const;
	/** Retrieves the number of characters in the no-break character set of this Kinsoku.
			@return The number of characters needed in the buffer to get the no-break set. */
	ATETextDOM::Int32 GetNoBreakCharSetSize( ) const;
	/** Sets the characters that cannot be used at a break in this Kinsoku.
  			@param noBreakCharSet The string containing the characters.
   			@return Nothing. */
	void SetNoBreakCharSet( const ATETextDOM::Unicode* noBreakCharSet);
	/** Retrieves the characters that can be left hanging in this Kinsoku.
			@param hangingCharSet [out] A buffer in which to return the hanging character string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetHangingCharSet( ATETextDOM::Unicode* hangingCharSet, ATETextDOM::Int32 maxLength) const;
	/** Retrieves the number of characters in the hanging character set of this Kinsoku.
			@return The number of characters needed in the buffer to get the hanging set. */
	ATETextDOM::Int32 GetHangingCharSetSize( ) const;
	/** Sets the characters that can be left hanging in this Kinsoku.
  			@param hangingCharSet The string containing the characters.
   			@return Nothing. */
	void SetHangingCharSet( const ATETextDOM::Unicode* hangingCharSet);
	// =======================================================================
	// METHODS
	// =======================================================================

	/** Reports whether a character is in the no-start set of this Kinsoku.
			@param character The character.
			@return True if this character is in the set. 	*/
	bool IsNoStartChar( ATETextDOM::Unicode character) const;
	/** Reports whether a character is in the no-end set of this Kinsoku.
			@param character The character.
			@return True if this character is in the set. 	*/
	bool IsNoEndChar( ATETextDOM::Unicode character) const;
	/** Reports whether a character is in the no-break set of this Kinsoku.
			@param character The character.
			@return True if this character is in the set. 	*/
	bool IsNoBreakChar( ATETextDOM::Unicode character) const;
	/** Reports whether a character is in the hanging set of this Kinsoku.
			@param character The character.
			@return True if this character is in the set. 	*/
	bool IsHangingChar( ATETextDOM::Unicode character) const;

	/// Does a shallow equivalency test
	/// Does a deep equivalency test
	/** Reports whether this object represents the same Kinsoku as another Kinsoku object.
			@param rhsKinsoku The comparison object.
			@return True if the two objects are the same. */
	bool IsEquivalent( IKinsoku rhsKinsoku) const;
	/** Reports whether the resource been modified since it became editable.
			@return True if the resource has been modified. */
	bool IsModified( ) const;
	/** Reports whether this is a predefined Kinsoku.
			@return True if the Kinsoku is predefined, false if it is customized. */
	bool IsPredefined( ) const;
	/**	Creates a new object by duplicating the information in this one.
			@return The new object	*/
	IKinsoku Duplicate( ) const;

};

//////////////////////////////////////////////
//       --IKinsokuSet--
//////////////////////////////////////////////
/** Encapsulates a set of Kinsoku as a text resource.
	A Kinsoku set contains a collection of \c IKinsoku objects.	*/
class IKinsokuSet
{
private:
	KinsokuSetRef	fKinsokuSet;
public:
	/** Constructor.
			@return The new object. */
	IKinsokuSet();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IKinsokuSet(const IKinsokuSet& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IKinsokuSet& operator=(const IKinsokuSet& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IKinsokuSet& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IKinsokuSet& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param kinsokuset The C object.
 			@return The new C++ object. */
	explicit IKinsokuSet(KinsokuSetRef kinsokuset);
	/** Destructor */
	virtual ~IKinsokuSet();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	KinsokuSetRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================
	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( );
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	IKinsoku GetFirst( );
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	IKinsoku GetLast( );

	// =======================================================================
	// METHODS
	// =======================================================================
	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param nIndex The 0-based position index.
			@return The member object.
		*/
	IKinsoku Item( ATETextDOM::Int32 nIndex) const;
	/** Retrieves a specific Kinsoku object from this set, matching name and data.
			@param kinsoku The Kinsoku object.
			@return The index position of the object in this set, or -1
				if the object is not in this set.
		*/
	ATETextDOM::Int32 Find( IKinsoku kinsoku);
	/** Retrieves a specific Kinsoku object from this set, matching only the name.
			@param name The name string.
			@return The index position of the object in this set, or -1
				if the object is not in this set.
		*/
	ATETextDOM::Int32 Find( const ATETextDOM::Unicode* name);
	/** Retrieves a specific Kinsoku object from this set, matching a tag.
			@param tag The tag. Use \c #kUserDefinedKinsokuTag to get the first
				customized (not predefined) Kinsoku.
			@return The index position of the object in this set, or -1
				if the object is not in this set.
		*/
	ATETextDOM::Int32 Find( KinsokuPredefinedTag tag);
	/** Removes a member from the set.
			@param nIndex The 0-based position index of the member to remove.
			@return True if a member was successfully removed. */
	bool Remove( ATETextDOM::Int32 nIndex);
	/** Appends a Kinsoku to this set.
			@param kinsoku The Kinsoku object.
			@return The 0-based position index of the successfully
				added object, or the current index of this object
				if it is already in the set, or -1 if the object
				was not in the set and could not be appended.
		*/
	ATETextDOM::Int32 Add( IKinsoku kinsoku);
	/** Replaces a Kinsoku in this set.
			@param nIndex The 0-based position index of the MojiKumi to replace.
			@param kinsoku The replacement Kinsoku object.
			@return True if an object was successfully replaced.
		*/
	bool Replace( ATETextDOM::Int32 nIndex, IKinsoku kinsoku);

};

//////////////////////////////////////////////
//       --IParaFeatures--
//////////////////////////////////////////////
/** This class encapsulates the complete set of	paragraph attributes that
	can be applied to text. An object of this type is contained in an
	\c IParaStyle object, and can be associated with a \c ITextRange.

	Attribute values are inherited from the Normal style, and can be overridden
	in a named style associated with the text, or at the local text level.

	A style or text range can partially define attributes. Only those values
	that are assigned override the inherited values. The constructor creates
	an empty object, in which all attribute values are unassigned.
	Setting a value causes it to be assigned, and clearing it causes
	it to be unassigned. When you retrieve an attribute value, a boolean
	return value, \c isAssigned, reports whether that attribute has a local
	value in the queried object.
	*/
class IParaFeatures
{
private:
	ParaFeaturesRef	fParaFeatures;
public:
	/** Constructor. Creates an empty object, in which all attributes
		are undefined.
			@return The new object. */
	IParaFeatures();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IParaFeatures(const IParaFeatures& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IParaFeatures& operator=(const IParaFeatures& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IParaFeatures& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IParaFeatures& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param parafeatures The C object.
 			@return The new C++ object. */
	explicit IParaFeatures(ParaFeaturesRef parafeatures);
	/** Destructor */
	virtual ~IParaFeatures();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ParaFeaturesRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;
	/** Creates a duplicate of this object.
			@return The new object. */
	IParaFeatures Clone( ) const;

	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	/** Retrieves the justification attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The justification constant. */
	ParagraphJustification GetJustification( bool* isAssigned) const;
	/** Retrieves the first-line indent attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The first-line indent value in document points. */
	ATETextDOM::Real GetFirstLineIndent( bool* isAssigned) const;
	/** Retrieves the paragraph start indent attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The start indent value in document points. */
	ATETextDOM::Real GetStartIndent( bool* isAssigned) const;
	/** Retrieves the paragraph end indent attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The end indent value in document points. */
	ATETextDOM::Real GetEndIndent( bool* isAssigned) const;
	/** Retrieves the line space before attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The line space before value in document points. */
	ATETextDOM::Real GetSpaceBefore( bool* isAssigned) const;
	/** Retrieves the line space after attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The line space after value in document points. */
	ATETextDOM::Real GetSpaceAfter( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	/** Retrieves the automatic hyphenation attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if automatic hyphenation is on, false if it is off. */
	bool GetAutoHyphenate( bool* isAssigned) const;
	/** Retrieves the hyphenation word size attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The hyphenation word size value (number of characters). */
	ATETextDOM::Int32 GetHyphenatedWordSize( bool* isAssigned) const;
	/** Retrieves the pre-hyphen size attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The pre-hyphen size value (number of characters). */
	ATETextDOM::Int32 GetPreHyphenSize( bool* isAssigned) const;
	/** Retrieves the post-hyphen size attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The post-hyphen size value (number of characters). */
	ATETextDOM::Int32 GetPostHyphenSize( bool* isAssigned) const;
	/** Retrieves the consecutive hyphen limit attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The consecutive hyphen limit value (number of hyphens). */
	ATETextDOM::Int32 GetConsecutiveHyphenLimit( bool* isAssigned) const;
	/** Retrieves the hyphenation zone attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The hyphenation zone value in document points. */
	ATETextDOM::Real GetHyphenationZone( bool* isAssigned) const;
	/** Retrieves the hyphenation capitalization attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if hyphenation capitalization is on, false if it is off. */
	bool GetHyphenateCapitalized( bool* isAssigned) const;
	/** Retrieves the hyphenation preference attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The hyphenation preference value. */
	ATETextDOM::Real GetHyphenationPreference( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	/** Retrieves the desired word spacing attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The desired word spacing value, in document points. */
	ATETextDOM::Real GetDesiredWordSpacing( bool* isAssigned) const;
	/** Retrieves the maximum word spacing attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The maximum word spacing value, in document points. */
	ATETextDOM::Real GetMaxWordSpacing( bool* isAssigned) const;
	/** Retrieves the minimum word spacing attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The minimum word spacing value, in document points. */
	ATETextDOM::Real GetMinWordSpacing( bool* isAssigned) const;
	/** Retrieves the desired letter spacing attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The desired letter spacing value, in document points. */
	ATETextDOM::Real GetDesiredLetterSpacing( bool* isAssigned) const;
	/** Retrieves the maximum letter spacing attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The maximum letter spacing value, in document points. */
	ATETextDOM::Real GetMaxLetterSpacing( bool* isAssigned) const;
	/** Retrieves the minimum letter spacing attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The minimum letter spacing value, in document points. */
	ATETextDOM::Real GetMinLetterSpacing( bool* isAssigned) const;
	/** Retrieves the desired glyph scaling attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The desired glyph scaling value, where 1 is 100%. */
	ATETextDOM::Real GetDesiredGlyphScaling( bool* isAssigned) const;
	/** Retrieves the maximum glyph scaling attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The maximum glyph scaling value, where 1 is 100%. */
	ATETextDOM::Real GetMaxGlyphScaling( bool* isAssigned) const;
	/** Retrieves the minimum glyph scaling attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The minimum glyph scaling value, where 1 is 100%. */
	ATETextDOM::Real GetMinGlyphScaling( bool* isAssigned) const;
	/** Retrieves the single-word justification attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The single-word justification type constant. */
	ParagraphJustification GetSingleWordJustification( bool* isAssigned) const;
	/** Retrieves the automatic leading percentage attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return Theautomatic leading percentage value, where 1 is 100%. */
	ATETextDOM::Real GetAutoLeadingPercentage( bool* isAssigned) const;
	/** Retrieves the leading type attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The leading type constant. */
	LeadingType GetLeadingType( bool* isAssigned) const;
	/** Retrieves the tab stops attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The tab stops object. */
	ITabStops GetTabStops( bool* isAssigned) const;
	/** Retrieves the default tab width attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The default tab width value, in document points. */
	ATETextDOM::Real GetDefaultTabWidth( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	/** Retrieves the Japanese hanging Roman attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if hanging Roman is on, false if it is off. */
	bool GetHangingRoman( bool* isAssigned) const;
	/** Retrieves the Japanese automatic Tate Chu Yoko attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The automatic Tate Chu Yoko value. */
	ATETextDOM::Int32 GetAutoTCY( bool* isAssigned) const;
	/** Retrieves the Japanese Bunri Kinshi attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if Bunri Kinshi is on, false if it is off. */
	bool GetBunriKinshi( bool* isAssigned) const;
	/** Retrieves the Japanese Burasagari type attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The Burasagari type constant. */
	BurasagariType GetBurasagariType( bool* isAssigned) const;
	/** Retrieves the Japanese preferred Kinsoku order attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The preferred Kinsoku order constant. */
	PreferredKinsokuOrder GetPreferredKinsokuOrder( bool* isAssigned) const;
	/** Retrieves the Japanese Kurikaeshi Moji Shori attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if Kurikaeshi Moji Shori is on, false if it is off. */
	bool GetKurikaeshiMojiShori( bool* isAssigned) const;
	/** Retrieves the Kinsoku attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The Kinsoku object, or a \c NULL object if Kinsoku is not used. */
	IKinsoku GetKinsoku( bool* isAssigned) const;
	/** Retrieves the MojiKumi attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The MojiKumi object, or a \c NULL object if MojiKumi is not used. */
	IMojiKumi GetMojiKumi( bool* isAssigned) const;
	// ------------------------------------------------------------------
	// Other Features
	// ------------------------------------------------------------------
	/** Retrieves the every-line composer attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return True if every-line composer is on, false if it is off. */
	bool GetEveryLineComposer( bool* isAssigned) const;
	/** Retrieves the default character features attribute of this paragraph.
			@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
			@return The character features object. */
	ICharFeatures GetDefaultCharFeatures( bool* isAssigned) const;

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	// ------------------------------------------------------------------
	// Complex Script Features
	// ------------------------------------------------------------------
	/**	Retrieves the main writing direction attribute of this paragraph.
		@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
		@return The paragragh direction object.
	*/
	ATE::ParagraphDirection GetParagraphDirection( bool* isAssigned) const;
	/**	Retrieves the justification method attribute of this paragraph.
		@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
		@return The justification method object.
	*/
	ATE::JustificationMethod GetJustificationMethod( bool* isAssigned) const;
	/**	Retrieves the Kashida Width attribute of this paragraph.
		@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
		@return The Kashida Width object.
	*/
	ATE::KashidaWidth GetKashidaWidth( bool* isAssigned) const;
#endif
	/**	Retrieves the composer engine attribute of this paragraph.
		@param isAssigned [out] A buffer in which to return
				true if this attribute has a local value.
		@return The composer engine object.
	*/
	ATE::ComposerEngine GetComposerEngine( bool* isAssigned ) const;

	// ======================================================================
	// SET PROPERTIES
	// ======================================================================
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	/** Sets the local justification attribute of this paragraph.
			@param newVal The new justification constant.
			@return Nothing. */
	void SetJustification( ParagraphJustification newVal);
	/** Sets the local first-line indent attribute of this paragraph.
			@param newVal The new first-line indent value, in document points.
			@return Nothing. */
	void SetFirstLineIndent( ATETextDOM::Real newVal);
	/** Sets the local start indent attribute of this paragraph.
			@param newVal The new start indent value, in document points.
			@return Nothing. */
	void SetStartIndent( ATETextDOM::Real newVal);
	/** Sets the local end indent attribute of this paragraph.
			@param newVal The new end indent value, in document points.
			@return Nothing. */
	void SetEndIndent( ATETextDOM::Real newVal);
	/** Sets the local line space before attribute of this paragraph.
			@param newVal The new line space before value, in document points.
			@return Nothing. */
	void SetSpaceBefore( ATETextDOM::Real newVal);
	/** Sets the local line space after attribute of this paragraph.
			@param newVal The new line space after value, in document points.
			@return Nothing. */
	void SetSpaceAfter( ATETextDOM::Real newVal);
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	/** Sets the local automatic hyphenation attribute of this paragraph.
			@param newVal True to turn automatic hyphenation on, false to turn it off.
			@return Nothing. */
	void SetAutoHyphenate( bool newVal);
	/** Sets the local hyphenated word size attribute of this paragraph.
			@param newVal The new hyphenated word size value, in characters.
			@return Nothing. */
	void SetHyphenatedWordSize( ATETextDOM::Int32 newVal);
	/** Sets the local pre-hyphen size attribute of this paragraph.
			@param newVal The new pre-hyphen size value, in characters.
			@return Nothing. */
	void SetPreHyphenSize( ATETextDOM::Int32 newVal);
	/** Sets the local post-hyphen size attribute of this paragraph.
			@param newVal The new post-hyphen size value, in characters.
			@return Nothing. */
	void SetPostHyphenSize( ATETextDOM::Int32 newVal);
	/** Sets the local consecutive hyphen limit attribute of this paragraph.
			@param newVal The new consecutive hyphen limit value, a number of hyphens.
			@return Nothing. */
	void SetConsecutiveHyphenLimit( ATETextDOM::Int32 newVal);
	/** Sets the local hyphenation zone attribute of this paragraph.
			@param newVal The new hyphenation zone value, in document points.
			@return Nothing. */
	void SetHyphenationZone( ATETextDOM::Real newVal);
	/** Sets the local hyphenation capitalized attribute of this paragraph.
			@param newVal True to turn hyphenation capitalized on, false to turn it off.
			@return Nothing. */
	void SetHyphenateCapitalized( bool newVal);
	/** Sets the local hyphenation preference attribute of this paragraph.
			@param newVal The new hyphenation preference value.
			@return Nothing. */
	void SetHyphenationPreference( ATETextDOM::Real newVal);
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	/** Sets the local desired word spacing attribute of this paragraph.
			@param newVal The new desired word spacing value, in document points.
			@return Nothing. */
	void SetDesiredWordSpacing( ATETextDOM::Real newVal);
	/** Sets the local maximum word spacing attribute of this paragraph.
			@param newVal The new maximum word spacing value, in document points.
			@return Nothing. */
	void SetMaxWordSpacing( ATETextDOM::Real newVal);
	/** Sets the local minimum word spacing attribute of this paragraph.
			@param newVal The new minimum word spacing value, in document points.
			@return Nothing. */
	void SetMinWordSpacing( ATETextDOM::Real newVal);
	/** Sets the local desired letter spacing attribute of this paragraph.
			@param newVal The new desired letter spacing value, in document points.
			@return Nothing. */
	void SetDesiredLetterSpacing( ATETextDOM::Real newVal);
	/** Sets the local maximum letter spacing attribute of this paragraph.
			@param newVal The new maximum letter spacing value, in document points.
			@return Nothing. */
	void SetMaxLetterSpacing( ATETextDOM::Real newVal);
	/** Sets the local minimum letter spacing attribute of this paragraph.
			@param newVal The new minimum letter spacing value, in document points.
			@return Nothing. */
	void SetMinLetterSpacing( ATETextDOM::Real newVal);
	/** Sets the local desired glyph scaling attribute of this paragraph.
			@param newVal The new desired glyph scaling value, where 1 is 100%.
			@return Nothing. */
	void SetDesiredGlyphScaling( ATETextDOM::Real newVal);
	/** Sets the local maximum glyph scaling attribute of this paragraph.
			@param newVal The new maximum glyph scaling value, where 1 is 100%.
			@return Nothing. */
	void SetMaxGlyphScaling( ATETextDOM::Real newVal);
	/** Sets the local minimum glyph scaling attribute of this paragraph.
			@param newVal The new minimum glyph scaling value, where 1 is 100%.
			@return Nothing. */
	void SetMinGlyphScaling( ATETextDOM::Real newVal);
	/** Sets the local single-word justification attribute of this paragraph.
			@param newVal The new single-word justification type constant.
			@return Nothing. */
	void SetSingleWordJustification( ParagraphJustification newVal);
	/** Sets the local automatic leading percentage attribute of this paragraph.
			@param newVal The new automatic leading percentage value, where 1 is 100%.
			@return Nothing. */
	void SetAutoLeadingPercentage( ATETextDOM::Real newVal);
	/** Sets the local leading type attribute of this paragraph.
			@param newVal The new leading type constant.
			@return Nothing. */
	void SetLeadingType( LeadingType newVal);
	/** Sets the local tab stops attribute of this paragraph.
			@param newVal The new tab stops object.
			@return Nothing. */
	void SetTabStops( ITabStops newVal);
	/** Sets the local default tab width attribute of this paragraph.
			@param newVal The new default tab width value, in document points.
			@return Nothing. */
	void SetDefaultTabWidth( ATETextDOM::Real newVal);
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	/** Sets the local Japanese hanging Roman attribute of this paragraph.
			@param newVal True to turn hanging Roman on, false to turn it off.
			@return Nothing. */
	void SetHangingRoman( bool newVal);
	/** Sets the local automatic Tate Chu Yoko attribute of this paragraph.
			@param newVal The new automatic Tate Chu Yoko value.
			@return Nothing. */
	void SetAutoTCY( ATETextDOM::Int32 newVal);
	/** Sets the local Bunri Kinshi attribute of this paragraph.
			@param newVal True to turn Bunri Kinshi on, false to turn it off.
			@return Nothing. */
	void SetBunriKinshi( bool newVal);
	/** Sets the local Burasagari type attribute of this paragraph.
			@param newVal The new Burasagari type constant.
			@return Nothing. */
	void SetBurasagariType( BurasagariType newVal);
	/** Sets the local preferred Kinsoku order attribute of this paragraph.
			@param newVal The new preferred Kinsoku order constant.
			@return Nothing. */
	void SetPreferredKinsokuOrder( PreferredKinsokuOrder newVal);
	/** Sets the local Kurikaeshi Moji Shori attribute of this paragraph.
			@param newVal True to turn Kurikaeshi Moji Shori on, false to turn it off.
			@return Nothing. */
	void SetKurikaeshiMojiShori( bool newVal);
	/** Sets the local Kinsoku attribute of this paragraph.
			@param newVal The new Kinsoku object.
			@return Nothing. */
	void SetKinsoku( IKinsoku newVal);
	/** Sets the local Moji Kumi attribute of this paragraph.
			@param newVal The new Moji Kumi object.
			@return Nothing. */
	void SetMojiKumi( IMojiKumi newVal);
	// ------------------------------------------------------------------
	// Other Features
	// ------------------------------------------------------------------
	/** Sets the local every-line composer attribute of this paragraph.
			@param newVal True to turn every-line composer on, false to turn it off.
			@return Nothing. */
	void SetEveryLineComposer( bool newVal);
	/** Sets the local default character features attribute of this paragraph.
			@param newVal The new default character features object.
			@return Nothing. */
	void SetDefaultCharFeatures( ICharFeatures newVal);

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	// ------------------------------------------------------------------
	// Complex Script Features
	// ------------------------------------------------------------------
	/**	Sets the main writing direction attribute of this paragraph.
		@param newVal The new paragraph direction object.
		@return Nothing.
	*/
	void SetParagraphDirection( ATE::ParagraphDirection newVal);
	/**	Sets the justification method attribute of this paragraph.
		@param newVal The new justification method object.
		@return Nothing.
	*/
	void SetJustificationMethod( ATE::JustificationMethod newVal);
	/**	Sets the Kashida Width attribute of this paragraph.
		@param newVal The new kashida width object.
		@return Nothing.
	*/
	void SetKashidaWidth( ATE::KashidaWidth newVal);
#endif
	/**	Sets the composer engine attribute of this paragraph.
		@param newVal The new composer engine object.
		@return Nothing.
	*/
	void SetComposerEngine( ATE::ComposerEngine newVal);

	// ======================================================================
	// CLEAR PROPERTIES
	// ======================================================================
	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	/** Removes the local justification attribute value of this paragraph.
			@return Nothing. */
	void ClearJustification( );
	/** Removes the local first-line indent attribute value of this paragraph.
			@return Nothing. */
	void ClearFirstLineIndent( );
	/** Removes the local start indent attribute value of this paragraph.
			@return Nothing. */
	void ClearStartIndent( );
	/** Removes the local end indent attribute value of this paragraph.
			@return Nothing. */
	void ClearEndIndent( );
	/** Removes the local line space before attribute value of this paragraph.
			@return Nothing. */
	void ClearSpaceBefore( );
	/** Removes the local line space after attribute value of this paragraph.
			@return Nothing. */
	void ClearSpaceAfter( );
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	/** Removes the local automatic hyphenation attribute value of this paragraph.
			@return Nothing. */
	void ClearAutoHyphenate( );
	/** Removes the local hyphenation word size attribute value of this paragraph.
			@return Nothing. */
	void ClearHyphenatedWordSize( );
	/** Removes the local pre-hyphen size attribute value of this paragraph.
			@return Nothing. */
	void ClearPreHyphenSize( );
	/** Removes the local post-hyphen size attribute value of this paragraph.
			@return Nothing. */
	void ClearPostHyphenSize( );
	/** Removes the local consecutive hyphen limit attribute value of this paragraph.
			@return Nothing. */
	void ClearConsecutiveHyphenLimit( );
	/** Removes the local hyphenation zone attribute value of this paragraph.
			@return Nothing. */
	void ClearHyphenationZone( );
	/** Removes the local hyphenate capitalized attribute value of this paragraph.
			@return Nothing. */
	void ClearHyphenateCapitalized( );
	/** Removes the local hyphenation preference attribute value of this paragraph.
			@return Nothing. */
	void ClearHyphenationPreference( );
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	/** Removes all of the local word spacing attribute values of this paragraph.
			@return Nothing. */
	void ClearWordSpacing( );
	/** Removes all of the local letter spacing attribute values of this paragraph.
			@return Nothing. */
	void ClearLetterSpacing( );
	/** Removes all of the local glyph scaling attribute values of this paragraph.
			@return Nothing. */
	void ClearGlyphScaling( );
	/** Removes the local single-word justification attribute value of this paragraph.
			@return Nothing. */
	void ClearSingleWordJustification( );
	/** Removes the local automatic leading percentage attribute value of this paragraph.
			@return Nothing. */
	void ClearAutoLeadingPercentage( );
	/** Removes the local leading type attribute value of this paragraph.
			@return Nothing. */
	void ClearLeadingType( );
	/** Removes the local tab stops attribute value of this paragraph.
			@return Nothing. */
	void ClearTabStops( );
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	/** Removes the local Japanese hanging Roman attribute value of this paragraph.
			@return Nothing. */
	void ClearHangingRoman( );
	/** Removes the local automatic Tate Chu Yoko attribute value of this paragraph.
			@return Nothing. */
	void ClearAutoTCY( );
	/** Removes the local Bunri Kinshi attribute value of this paragraph.
			@return Nothing. */
	void ClearBunriKinshi( );
	/** Removes the local Burasagari type attribute value of this paragraph.
			@return Nothing. */
	void ClearBurasagariType( );
	/** Removes the local preferred Kinsoku order attribute value of this paragraph.
			@return Nothing. */
	void ClearPreferredKinsokuOrder( );
	/** Removes the local Kurikaeshi Moji Shori attribute value of this paragraph.
			@return Nothing. */
	void ClearKurikaeshiMojiShori( );
	/** Removes the local Kinsoku attribute value of this paragraph.
			@return Nothing. */
	void ClearKinsoku( );
	/** Removes the local Moji Kumi attribute value of this paragraph.
			@return Nothing. */
	void ClearMojiKumi( );
	// ------------------------------------------------------------------
	// Other Features
	// ------------------------------------------------------------------
	/** Removes the local every-line composer attribute value of this paragraph.
			@return Nothing. */
	void ClearEveryLineComposer( );
	/** Removes the local default character features attribute value of this paragraph.
			@return Nothing. */
	void ClearDefaultCharFeatures( );

#if SLO_COMPLEXSCRIPT // Available for use in Middle Eastern versions of the product only.
	// ------------------------------------------------------------------
	// Complex Script Features
	// ------------------------------------------------------------------
	/**	Removes the main writing direction attribute value of this paragraph.
		@return Nothing.
	*/
	void ClearParagraphDirection( );
	/**	Removes the justification method attribute value of this paragraph.
		@return Nothing.
	*/
	void ClearJustificationMethod( );
	/**	Removes the kashida width attribute value of this paragraph.
		@return Nothing.
	*/
	void ClearKashidaWidth( );
#endif
	/**	Removes the composer engine attribute value of this paragraph.
		@return Nothing.
	*/
	void ClearComposerEngine( );

	////////////////////////////////////////////////////////////////////////////
	// ALGEBRA METHODS
	////////////////////////////////////////////////////////////////////////////

	/**	Clears any attributes in this object whose values are
		not the same as or are unassigned in the comparison object.
		The only values that remain are those that match
		the corresponding value in the comparison object.
			@param rhs Right-hand side of comparison.
			@return True if changes were made. */
	bool IntersectFeatures( IParaFeatures rhs);
	/**	Sets any attributes in this object whose values are
		assigned in the comparison object to those values.
			@param rhs Right-hand side of comparison.
			@return True if changes were made. */
	bool ReplaceOrAddFeatures( IParaFeatures rhs);
	/**	Clears any attributes in this object whose values are the
		same as in the comparison object.
			@param rhs Right-hand side of comparison.
			@return True if changes were made. */
	bool UnassignEachIfEqual( const IParaFeatures rhs);

	/**	Reports whether all attributes of this object are unassigned.
			@return True if no attributes have local values. */
	bool IsEachNotAssigned( ) const;
	/**	Reports whether all attributes of this object are assigned.
			@return True if all attributes have local values. */
	bool IsEachAssigned( ) const;

};

//////////////////////////////////////////////
//       --IParagraph--
//////////////////////////////////////////////
/** This class encapsulates a paragraph of text, to which a
	paragraph style (\c IParaStyle) can be applied.
	Paragraphs are contained in stories.
	Use an \c IParagraphsIterator object to iterate through
	paragraphs in a set of stories.

	Use an \c IParaInspector object to retrieve the
	paragraph features that apply to a specific paragraph,
	after considering all inherited style values and local overrides.
	*/
class IParagraph
{
private:
	ParagraphRef	fParagraph;
public:
	/** Constructor.
			@return The new object. */
	IParagraph();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IParagraph(const IParagraph& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IParagraph& operator=(const IParagraph& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IParagraph& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IParagraph& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param paragraph The C object.
 			@return The new C++ object. */
	explicit IParagraph(ParagraphRef paragraph);
	/** Destructor */
	virtual ~IParagraph();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ParagraphRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================
	/** Retrieves the length of this paragraph.
			@return The number of characters in this paragraph. */
	ATETextDOM::Int32 GetLength( );
	// navigation objects.
	/** Retrieves the story that contains this paragraph
			@return The story object. */
	IStory GetStory( );
	/** Retrieves the text range corresponding to this paragraph
			@return The text range object. */
	ITextRange GetTextRange( );
	/** Retrieves the set of text ranges corresponding to this paragraph
			@return The text ranges object. */
	ITextRanges GetTextRanges( );
	/** Retrieves the text selection in this paragraph.
			@return The text range set object. */
	ITextRanges GetTextSelection( );
	/** Creates an iteration object with which to access the words in this paragraph.
			@return The word iterator object. */
	IWordsIterator GetWordsIterator( );
	// ========================================================================
	// METHODS
	// ========================================================================
	/** Retrieves the paragraph after this one in the containing story.
			@return The paragraph object. */
	IParagraph GetNext( );
	/** Retrieves the paragraph before this one in the containing story.
			@return The paragraph object. */
	IParagraph GetPrev( );
	/** Retrieves the text contents of this paragraph as a Unicode string.
			@param text [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
		*/
	ATETextDOM::ATETextDomErr GetContents( ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength);
	/** Retrieves the text contents of this paragraph as a C string.
			@param text [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
		*/
	ATETextDOM::ATETextDomErr GetContents( char* text, ATETextDOM::Int32 maxLength);

};

//////////////////////////////////////////////
//       --IParagraphsIterator--
//////////////////////////////////////////////
/**	This class allows you to iterate through a set of paragraphs contained in
	a set of story objects or text ranges. Retrieve the iteration object
	with \c IStories::GetParagraphsIterator(), or create one
	from a set of text ranges (\c ITextRanges). Use it to access
	the \c IParagraph objects in the document's text.
*/
class IParagraphsIterator
{
private:
	ParagraphsIteratorRef	fParagraphsIterator;
public:
	/** Constructor.
			@return The new object. */
	IParagraphsIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IParagraphsIterator(const IParagraphsIterator& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IParagraphsIterator& operator=(const IParagraphsIterator& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IParagraphsIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IParagraphsIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param paragraphsiterator The C object.
 			@return The new C++ object. */
	explicit IParagraphsIterator(ParagraphsIteratorRef paragraphsiterator);
	/** Destructor */
	virtual ~IParagraphsIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ParagraphsIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates a paragraph iterator for a specific text-range set
		that is ordered first-to-last or last-to-first.
			@param ranges The text-range set object.
			@param direction Optional. The order of iteration. Default is first-to-last.
			@return The new iterator object.
		*/
	IParagraphsIterator( ITextRanges ranges, Direction direction = kForward);
	//------------------------------------------------------
	// Methods
	//------------------------------------------------------
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Sets the current position to the first member of this set.
			@return Nothing. */
	void MoveToFirst( );
	/** Sets the current position to the last member of this set.
			@return Nothing. */
	void MoveToLast( );
	/** Increments the current position in this set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Retrieves the current paragraph.
			@return The paragraph object. */
	IParagraph Item( );

};

//////////////////////////////////////////////
//       --IParaInspector--
//////////////////////////////////////////////
/**	This class allows you to retrieve the
	paragraph features that apply to a specific paragraph,
	after considering all inherited style values and local overrides.

	Obtain an \c IParaInspector object from a text range or set of text
	ranges. See \c ITextRange::GetParaInspector().

	The methods collect the values of a particular attribute into
	an array whose order is the same as the order of paragraphs in the text.
*/
class IParaInspector
{
private:
	ParaInspectorRef	fParaInspector;
public:
	/** Constructor.
			@return The new object. */
	IParaInspector();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IParaInspector(const IParaInspector& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IParaInspector& operator=(const IParaInspector& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IParaInspector& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IParaInspector& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param parainspector The C object.
 			@return The new C++ object. */
	explicit IParaInspector(ParaInspectorRef parainspector);
	/** Destructor */
	virtual ~IParaInspector();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ParaInspectorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ------------------------------------------------------------------
	// Justification
	// ------------------------------------------------------------------
	/** Retrieves the justification values from the paragraph set.
			@return The array object containing the values. */
	IArrayParagraphJustification GetJustification( ) const;
	/** Retrieves the first-line indent values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetFirstLineIndent( ) const;
	/** Retrieves the start indent values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetStartIndent( ) const;
	/** Retrieves the end indent values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetEndIndent( ) const;
	/** Retrieves the line space before values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetSpaceBefore( ) const;
	/** Retrieves the line space after values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetSpaceAfter( ) const;
	// ------------------------------------------------------------------
	// Hyphenation
	// ------------------------------------------------------------------
	/** Retrieves the automatic hyphenation values from the paragraph set.
			@return The array object containing the values. */
	IArrayBool GetAutoHyphenate( ) const;
	/** Retrieves the hyphenated word size values from the paragraph set.
			@return The array object containing the values. */
	IArrayInteger GetHyphenatedWordSize( ) const;
	/** Retrieves the pre-hyphen size values from the paragraph set.
			@return The array object containing the values. */
	IArrayInteger GetPreHyphenSize( ) const;
	/** Retrieves the post-hyphen size values from the paragraph set.
			@return The array object containing the values. */
	IArrayInteger GetPostHyphenSize( ) const;
	/** Retrieves the consecutive hyphen limit values from the paragraph set.
			@return The array object containing the values. */
	IArrayInteger GetConsecutiveHyphenLimit( ) const;
	/** Retrieves the hyphenation zone values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetHyphenationZone( ) const;
	/** Retrieves the hyphenate capitalized values from the paragraph set.
			@return The array object containing the values. */
	IArrayBool GetHyphenateCapitalized( ) const;
	/** Retrieves the hyphenation preference values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetHyphenationPreference( ) const;
	// ------------------------------------------------------------------
	// Justification Features
	// ------------------------------------------------------------------
	/** Retrieves the desired word spacing values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetDesiredWordSpacing( ) const;
	/** Retrieves the maximum word spacing values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetMaxWordSpacing( ) const;
	/** Retrieves the minimum word spacing values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetMinWordSpacing( ) const;
	/** Retrieves the desired letter spacing values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetDesiredLetterSpacing( ) const;
	/** Retrieves the maximum letter spacing values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetMaxLetterSpacing( ) const;
	/** Retrieves the minimum letter spacing values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetMinLetterSpacing( ) const;
	/** Retrieves the desired glyph scaling values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetDesiredGlyphScaling( ) const;
	/** Retrieves the maximum glyph scaling values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetMaxGlyphScaling( ) const;
	/** Retrieves the minimum glyph scaling values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetMinGlyphScaling( ) const;
	/** Retrieves the single-word justification values from the paragraph set.
			@return The array object containing the values. */
	IArrayParagraphJustification GetSingleWordJustification( ) const;
	/** Retrieves the automatic leading percentage values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetAutoLeadingPercentage( ) const;
	/** Retrieves the leading type values from the paragraph set.
			@return The array object containing the values. */
	IArrayLeadingType GetLeadingType( ) const;
	/** Retrieves the tab stops values from the paragraph set.
			@return The array object containing the values. */
	IArrayTabStopsRef GetTabStops( ) const;
	/** Retrieves the tab width values from the paragraph set.
			@return The array object containing the values. */
	IArrayReal GetDefaultTabWidth( ) const;
	// ------------------------------------------------------------------
	// Japanese Features
	// ------------------------------------------------------------------
	/** Retrieves the Japanese hanging Roman values from the paragraph set.
			@return The array object containing the values. */
	IArrayBool GetHangingRoman( ) const;
	/** Retrieves the automatic Tate Chu Yoko values from the paragraph set.
			@return The array object containing the values. */
	IArrayInteger GetAutoTCY( ) const;
	/** Retrieves the Bunri Kinshi values from the paragraph set.
			@return The array object containing the values. */
	IArrayBool GetBunriKinshi( ) const;
	/** Retrieves the Burasagari type values from the paragraph set.
			@return The array object containing the values. */
	IArrayBurasagariType GetBurasagariType( ) const;
	/** Retrieves the preferred Kinsoku order values from the paragraph set.
			@return The array object containing the values. */
	IArrayPreferredKinsokuOrder GetPreferredKinsokuOrder( ) const;
	/** Retrieves the Kurikaeshi Moji Shori values from the paragraph set.
			@return The array object containing the values. */
	IArrayBool GetKurikaeshiMojiShori( ) const;
	/** Retrieves the Kinsoku values from the paragraph set.
			@return The array object containing the values. */
	IArrayKinsokuRef GetKinsoku( ) const;
	/** Retrieves the Moji Kumi values from the paragraph set.
			@return The array object containing the values. */
	IArrayMojiKumiRef GetMojiKumi( ) const;
	// ------------------------------------------------------------------
	// Other Features
	// ------------------------------------------------------------------
	/** Retrieves the every-line composer values from the paragraph set.
			@return The array object containing the values. */
	IArrayBool GetEveryLineComposer( ) const;

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	// ------------------------------------------------------------------
	// Complex Script Features
	// ------------------------------------------------------------------
	/**	Retrieves the main writing direction values from the paragraph set.
		@return The array object containing the values.
	*/
	IArrayParagraphDirection GetParagraphDirection( ) const;
	/**	Retrieves the justification method values from the paragraph set.
		@return The array object containing the values.
	*/
	IArrayJustificationMethod GetJustificationMethod( ) const;
	/**	Retrieves the Kashida Width values from the paragraph set.
		@return The array object containing the values.
	*/
	IArrayKashidaWidth GetKashidaWidth( ) const;
#endif
	/**	Retrieves the composer engine values from the paragraph set.
		@return The array object containing the values.
	*/
	IArrayComposerEngine GetComposerEngine( ) const;

};

//////////////////////////////////////////////
//       --IParaStyle--
//////////////////////////////////////////////
/** This class encapsulates a named paragraph style, which can be
	applied to a paragraph or set of paragraphs. It contains an \c IParaFeatures
	object, which defines the paragraph attributes for this style.

	Attribute values are inherited from the Normal style, and can be overridden
	in a named style associated with a story or text range, or at the
	local paragraph level.

	A style or paragraph can partially define attributes. Only those values
	that are assigned override the inherited values. The constructor creates
	an empty object, in which all attribute values are unassigned.
	Setting a value causes it to be assigned, and clearing it causes
	it to be unassigned. When you retrieve an attribute value, a boolean
	return value, \c isAssigned, reports whether that attribute has a local
	value in the queried object.
	*/
class IParaStyle
{
private:
	ParaStyleRef	fParaStyle;
public:
	/** Constructor.
			@return The new object. */
	IParaStyle();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IParaStyle(const IParaStyle& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IParaStyle& operator=(const IParaStyle& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IParaStyle& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IParaStyle& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param parastyle The C object.
 			@return The new C++ object. */
	explicit IParaStyle(ParaStyleRef parastyle);
	/** Destructor */
	virtual ~IParaStyle();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ParaStyleRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Retrieves the name of this style.
			@param pName [out] A buffer in which to return the name string.
			@param maxLength [in, out] The number of characters in the buffer.
			@return The length of the returned string, or 0 if an error occurred.
		*/
	ATETextDOM::Int32 GetName( ATETextDOM::Unicode* pName, ATETextDOM::Int32 maxLength) const;
	/** Sets the name of this style.
			@param pName The new, \c NULL terminated name string.
			@return True if the name was set successfully, false if a style
				already has the specified name or if the name string is empty.
		*/
	bool SetName( const ATETextDOM::Unicode* pName);
	/** Retrieves the parent style of this style.
			@return The style object, or a \c NULL object for the Normal (root) style.
		*/
	IParaStyle GetParent( ) const;
	/** Sets the parent style of this style.
			@param pStyle The new parent style object,
			@return True if the parent was set successfully, false if
				this is the  Normal (root) style.
		*/
	bool SetParent( const IParaStyle pStyle);
	/** Reports whether this style has a parent.
			@return True if this style has a parent, false if this is the Normal (root) style.
		*/
	bool HasParent( ) const;
	/** Retrieves the features defined for this style.
			@return The paragraph features object.
		*/
	IParaFeatures GetFeatures( ) const;
	/** Sets the features defined for this style. For the Normal (root) style,
		this is the same as \c #ReplaceOrAddFeatures().	For all other
		styles, the new feature set completely replaces the old feature set.
			@param pFeatures The new paragraph features object.
			@return Nothing.
		*/
	void SetFeatures( IParaFeatures pFeatures);
	/** Sets attribute values of this style's feature set to those values that
		are specifically assigned in the replacement feature set. Those values
		that are unassigned in the replacement set remain unchanged in this
		style.
			@param pFeatures The replacement paragraph features object.
			@return Nothing.
		*/
	void ReplaceOrAddFeatures( IParaFeatures pFeatures);

};

//////////////////////////////////////////////
//       --IParaStyles--
//////////////////////////////////////////////
/** Encapsulates a set of paragraph styles as a text resource.
	A style set contains a collection of \c IParaStyle objects.
	Use an \c IParaStylesIterator object to iterate through the set.
	*/
class IParaStyles
{
private:
	ParaStylesRef	fParaStyles;
public:
	/** Constructor.
			@return The new object. */
	IParaStyles();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IParaStyles(const IParaStyles& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IParaStyles& operator=(const IParaStyles& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IParaStyles& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IParaStyles& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param parastyles The C object.
 			@return The new C++ object. */
	explicit IParaStyles(ParaStylesRef parastyles);
	/** Destructor */
	virtual ~IParaStyles();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ParaStylesRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	//------------------------------------------------------
	// Methods
	//------------------------------------------------------
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Shows all styles.
			@return Nothing.
			@see \c #ShowOnlyUnreferencedStyles(), \c #ShowOnlyStylesReferencedIn()
		*/
	void ShowAllStyles( ) const;
	/** Shows only styles to which there are not references in text.
			@return Nothing.
			@see \c #ShowAllStyles(), \c #ShowOnlyStylesReferencedIn()
		*/
	void ShowOnlyUnreferencedStyles( ) const;
	/** Shows only styles that are used in a text range.
			@param pRange The text range object.
			@return Nothing.
			@see \c #ShowAllStyles(), \c #ShowOnlyUnreferencedStyles()
		*/
	void ShowOnlyStylesReferencedIn( ITextRange pRange) const;
	/** Reorders styles in this set by moving a style to a given position.
			@param pStyle The style object.
			@param position The new 0-based position index.
			@return Nothing.
		*/
	void MoveStyleTo( IParaStyle pStyle, ATETextDOM::Int32 position);

};

//////////////////////////////////////////////
//       --IParaStylesIterator--
//////////////////////////////////////////////
/**	This class allows you to iterate through a set of paragraph styles.
	Create the iterator object from a \c IParaStyles object.
	Use it to access the \c IParaStyle objects in the collection.
*/
class IParaStylesIterator
{
private:
	ParaStylesIteratorRef	fParaStylesIterator;
public:
	/** Constructor.
			@return The new object. */
 	IParaStylesIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IParaStylesIterator(const IParaStylesIterator& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IParaStylesIterator& operator=(const IParaStylesIterator& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IParaStylesIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IParaStylesIterator& rhs) const;
	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param parastylesiterator The C object.
 			@return The new C++ object. */
	explicit IParaStylesIterator(ParaStylesIteratorRef parastylesiterator);
	/** Destructor */
	virtual ~IParaStylesIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	ParaStylesIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates an iterator object for a specific paragraph style set
		that is ordered first-to-last or last-to-first.
			@param paraStyles The paragraph style set object.
			@param direction Optional. The order of iteration. Default is first-to-last.
			@return The new iterator object.
		*/
	IParaStylesIterator( IParaStyles paraStyles, Direction direction = kForward);
	//------------------------------------------------------
	// Methods
	//------------------------------------------------------
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Sets the current position to the first member of this set.
			@return Nothing. */
	void MoveToFirst( );
	/** Sets the current position to the last member of this set.
			@return Nothing. */
	void MoveToLast( );
	/** Increments the current position in this set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Decrements the current position in this set.
			@return Nothing. */
	void Previous( );
	/** Retrieves the current paragraph style.
			@return The paragraph style object. */
	IParaStyle Item( ) const;

};

//////////////////////////////////////////////
//       --ISpell--
//////////////////////////////////////////////
/** This class allows you to configure and execute spell-checks
	within a document, story, or text range. Use the object to
	perform searches for unknown words, replace them with corrected words,
	and maintain associated dictionaries and word lists.

	To implement a replace-all operation,
	\li Save the current text object and search state, using
		\c #GetSearchRange() and \c #GetPreReplaceAllSettings().
	\li Loop through the text objects, and use \c #FindReplaceAllWord() to find all instances
		of the target word in the current text object. Keep calling until the method
		returns false, making sure to set the \c firstTimeInThisObject flag as needed.
		When the method returns a text range, select it and call \c #ReplaceSelected().

	\li When the operation is complete, restore the text object using \c #SetSearchRange(),
		then restore the position and sentence-end flag using \c #RestorePreReplaceAllSettings().
		You must do it in this order, because \c #SetSearchRange() resets the flag.
	*/
class ISpell
{
private:
	SpellRef	fSpell;
public:
	/** Constructor.
			@return The new object. */
	ISpell();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ISpell(const ISpell& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ISpell& operator=(const ISpell& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ISpell& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ISpell& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param spell The C object.
 			@return The new C++ object. */
	explicit ISpell(SpellRef spell);
	/** Destructor */
	virtual ~ISpell();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	SpellRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// Options
	// ========================================================================
	/** Initializes this spell-check object with a directory.
			@return Nothing*/
	void Initialize( );
	/** Reports whether this spell-check object has been initialized.
			@return True if this object has been initialized. */
	bool IsInitialized( );
	/** Reports whether this spell-check ignores words that are all uppercase.
			@return True if this spell-check ignores words that are all uppercase. */
	bool GetIgnoreWordsInAllUppercase( ) const;
	/** Reports whether this spell-check ignores words that contain numbers.
			@return True if this spell-check ignores words that contain numbers. */
	bool GetIgnoreWordsWithNumbers( ) const;
	/** Reports whether this spell-check ignores roman numerals.
			@return True if this spell-check ignores roman numerals. */
	bool GetIgnoreRomanNumerals( ) const;
	/** Reports whether this spell-check ignores repeated words.
			@return True if this spell-check ignores repeated words. */
	bool GetIgnoreRepeatedWords( ) const;
	/** Reports whether this spell-check ignores the uncapitalized first word of a sentence.
			@return True if this spell-check ignores the uncapitalized first word of a sentence. */
	bool GetIgnoreUncapitalizedStartOfSentence( ) const;

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	/**	Reports whether strict Yeh characters are considered during the spell check.
		@return True if strict Yeh characters are considered, false if they are not.
	*/
	bool GetStrictYeh( ) const;
	/**	Reports whether strict Alef characters are considered during the spell check.
		@return True if strict Alef characters are considered, false if they are not.
	*/
	bool GetStrictAlef( ) const;
#endif

	/** Sets whether this spell-check ignores words that are all uppercase.
			@param newValue True to ignore words that are all uppercase,
				false to report as a spelling error. */
	void SetIgnoreWordsInAllUppercase( bool newValue);
	/** Sets whether this spell-check ignores words that contain numbers.
			@param newValue True to ignore words that contain numbers,
				false to report as a spelling error. */
	void SetIgnoreWordsWithNumbers( bool newValue);
	/** Sets whether this spell-check ignores roman numerals.
			@param newValue True to ignore roman numerals,
				false to report as a spelling error. */
	void SetIgnoreRomanNumerals( bool newValue);
	/** Sets whether this spell-check ignores repeated word.
			@param newValue True to ignore repeated words,
				false to report as a spelling error. */
	void SetIgnoreRepeatedWords( bool newValue);
	/** Sets whether this spell-check ignores uncapitalized first words of sentences.
			@param newValue True to ignore uncapitalized first words of sentences,
				false to report as a spelling error. */
	void SetIgnoreUncapitalizedStartOfSentence( bool newValue);

#if SLO_COMPLEXSCRIPT // Middle Eastern specific features only
	/**	Sets whether to consider strict Yeh characters during the spell check.
		@param newValue True to consider strict Yeh characters, false to not.
		@return Nothing.
	*/
	void SetStrictYeh( bool newValue);
	/**	Sets whether to consider strict Alef characters during the spell check.
		@param newValue True to consider strict Alef characters, false to not.
		@return Nothing.
	*/
	void SetStrictAlef( bool newValue);
#endif

	/** Reports the scope of search for this spell-check, the entire document or
		a story. The default scope is the entire document.
			@return The search-scope constant. */
	SearchScope GetSearchScope( ) const;
	/** Sets the scope of search for this spell-check, the entire document or
		a story. The default scope is the entire document.
			@param searchScope The search-scope constant. */
	void SetSearchScope( SearchScope searchScope);

	/** Sets the range of search for this spell-check, limiting the search
		to a specific text range within the scope.
			@param pRange The text range object.
			@param resetEndOfSentence Optional, whether to reset the end-of-sentence marker.
				Default is true.
			@param resetCurPos Optional, whether to reset the cursor position after the search.
				Default is true.
			*/
	void SetSearchRange( const ITextRange& pRange, const bool resetEndOfSentence = true, const bool resetCurPos = true);

	/** Resets the search temporarily, for a modeless search.
			@return Nothing. */
	void Reset( );
	/** Resumes this search from a given point.
		Use this if the user has changed
		the text significantly enough that you need to reset, but you are fairly
		certain that the text has not been changed before the given point.
			@param resumePoint A number of characters, the 0-based  offset
				into the text at which to resume.
			@return Nothing. */
	void ResumeFrom( const ATETextDOM::Int32 resumePoint);
	// Use this to resume from the current insertion point.
	/** Resumes this search from the current insertion point.
			@return Nothing. */
	void ResumeFromInsertionPoint( );

	// ========================================================================
	// Methods
	// ========================================================================

	/** Searches from the start of the range for the first occurrance of an unknown word.
		If a word is found, fills a word list with suggested corrections. To retrieve this
		list, use \c #GetWordListSize() and GetWordListContents().
			@param pResult [out] A buffer in which to return the first unknown word found.
			@param pRange [out] A buffer in which to return the text range that contains the returned word.
			@param pLanguage [out] Optional. A buffer in which to return the language.
			@return True if an unknown word was found and returned, false if the search reached
				the end of the range without finding an unknown word. */
	bool FindOneMisspelledWord( SpellCheckingResult* pResult, ITextRange pRange, Language* pLanguage = NULL);
	/** Retrieves the number of characters in the list of suggested corrections
		for an unknown word found by \c #FindOneMisspelledWord().
		Use to create a string buffer for \c #GetWordListContents().
			@return The number of characters in the list.*/
	ATETextDOM::Int32 GetWordListSize( );
	/** Retrieves the list of suggested corrections for an unknown word
		found by \c #FindOneMisspelledWord().
			@param pWordListBuffer [out] A buffer in which to return the word list. Use \c #GetWordListSize()
				to allocate sufficient space for the string.
			@param sizeOfBuffer The number of characters in the passed buffer.
			@param pNumberOfWords [out] A buffer in which to return the number of
				NULL-terminated words in the returned word list.
			@return Nothing. */
	void GetWordListContents( ATETextDOM::Unicode*   pWordListBuffer, ATETextDOM::Int32    sizeOfBuffer, ATETextDOM::Int32*   pNumberOfWords);
	/** Replaces a text range with new text.
			@param pRange The destination text range object.
			@param pCorrection A string containing the replacement text.
			@return Nothing.	*/
	void Replace( ITextRange pRange, const ATETextDOM::Unicode* pCorrection);

	// Use this to add an entry to a pair dictionary, binding the selected word to rCorrection.
	/** Adds the selected text to the replace-all dictionary
		associating it with a given correction string.
			@param pCorrection The correction string.
			@return Nothing. */
	void AddSelectedToReplaceAllDict( const ATETextDOM::Unicode* pCorrection);

	/** @deprecated Obsolete, do not use. See \c ISpell class description
		for information on implementing a replace-all operation. */
	bool DoReplaceAll( );

	/** Stores search positions before a replace-all operation that you implement
		using \c #FindReplaceAllWord(). Use \c #RestorePreReplaceAllSettings() to
		restore the positions after the operation.
		You must also save the text object you are currently working with,
		and use \c #SetSearchRange() to restore it.
		See \c ISpell class description for information on implementing a replace-all operation.
			@param pCurrentPoint [out] A buffer in which to save the current search offset.
			@param pFoundSentenceEnd [out] A buffer in which to save the current sentence-end flag.
			@return Nothing.
		*/
	void GetPreReplaceAllSettings( ATETextDOM::Int32* pCurrentPoint, bool* pFoundSentenceEnd) const;
	// Implement a loop to go through all the text objects you want to replace all with.
	// Use this to find all instances of the target word in the current text object.
	// Keep calling it until it returns false, making sure to set firstTimeInThisObject as needed.
	// It will return the text range to select and call ReplaceSelected( ) with.
	/** Searches for the current target word in a text range object. Use to implement
		a replace-all operation, by finding all instances of the target word in all text objects
		in the range. See \c ISpell class description.
			@param pRange The text range object.
			@param firstTimeInThisObject True to indicate that that search is
				being done in a new text object in your loop.
			@return True if the target word is found in the text range.
		*/
	bool FindReplaceAllWord( ITextRange pRange, const bool firstTimeInThisObject);
	/** Restores search positions after a replace-all operation that you implement using \c #FindReplaceAllWord().
		Use \c #GetPreReplaceAllSettings() to store the positions before the operation.
		You must also save the text object you are currently working with, and use \c #SetSearchRange()
		to restore it.  See \c ISpell class description for information on implementing a replace-all operation.
			@param currentPoint The buffer containing the saved search offset.
			@param foundSentenceEnd The buffer containing the saved sentence-end flag.
			@return Nothing.
		*/
	void RestorePreReplaceAllSettings( const ATETextDOM::Int32 currentPoint, const bool foundSentenceEnd);

	/// Manage spell-check dictionaries

	/** Removes all pairs from the pair dictionary associated with this spell-checker.
		The dictionary is never cleared automatically.
			@return Nothing. */
	void ClearPairDictionary( );

	/** Adds the currently selected word to the dictionary associated with this spell-checker.
			@return Nothing. */
	void AddSelectedToUserDict( );

	/** Copies the known-word dictionary for this spell-checker
		to the internal word list. Use \c #GetWordListSize() and
		\c #GetWordListContents() to examine the result.
			@return Nothing. */
	void GetUserDictionaryContents( );
	/**	Adds a word to the known-word dictionary for this spell-checker.
			@param pWord A string containing the word.
			@return True if the addition was successful, false if the string contains
				spaces (multiple words) and no word was added. */
	bool AddToUserDictionary( const ATETextDOM::Unicode* pWord);
	/**	Removes a word from the known-word dictionary for this spell-checker.
			@param pWord A string containing the word.
			@return Nothing. */
	void DeleteFromUserDictionary( const ATETextDOM::Unicode* pWord);
	/**	 Reports whether a word is contained in the known-word dictionary for this spell-checker.
			@param pWord A string containing the word.
			@return True if the word is in the dictionary. */
	bool WordExistsInUserDictionary( const ATETextDOM::Unicode* pWord);
	/** Adds the currently selected word to the list of words to be
		ignored by this spell-checker.
			@return Nothing. */
	void AddSelectedToIgnoreList( );
	/** Removes all words from the list of words to be ignored by this spell-checker.
		The list is never cleared automatically.
			@return Nothing. */
	void ClearIgnoreList( );
	/**	Retrieves the language of the most recent missing dictionary.
			@return The language constant. */
	Language GetLanguageOfLastMissingDictionary( );
	//param @out : the size of the length of the path
	//      @in  : the memory where the path is to be stored
	ATETextDOM::Int32 GetSpellingDictionaryPath(ATETextDOM::Unicode* path);
};

//////////////////////////////////////////////
//       --IStories--
//////////////////////////////////////////////
/** Encapsulates a set of stories. Contains a collection of \c IStory objects.
	Use to access the text and input focus of the member stories, and to
	temporarily suspend reflow calculations for efficiency when altering the text. */
class IStories
{
private:
	StoriesRef	fStories;
public:
	/** Constructor.
			@return The new object. */
	IStories();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IStories(const IStories& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IStories& operator=(const IStories& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IStories& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IStories& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param stories The C object.
 			@return The new C++ object. */
	explicit IStories(StoriesRef stories);
	/** Destructor */
	virtual ~IStories();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	StoriesRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	IStory GetFirst( );
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	IStory GetLast( );
	// Focus methods
	/** Reports whether a member story has the input focus.
			@return True if a story in this collection is currently being edited.
			@note Only one story can have the focus. It can lose focus if
				the user selects text outside it, or clicks outside the
				text of the story. */
	bool HasFocus( ) const;
	/** Retrieves the member story that has input focus.
			@return The story currently being edited, or a \c NULL oject if no text is being edited. */
	IStory GetFocus( ) const;
	/** Sets the input focus to a member story, deselecting everything in the document.
			@param story The story object.
			@return Nothing. */
	void SetFocus( const IStory& story);
	/** Removes input focus from the story currently being edited,
		deselecting everything in the document.
			@return Nothing. */
	void LoseFocus( );
	// Navigation objects.
	/** Retrieves the set of text ranges in these stories.
			@return The text range set object. */
	ITextRanges GetTextRanges( ) const;
	/** Retrieves the set of text ranges for selected text in these stories.
			@return The text range set object. */
	ITextRanges GetTextSelection( ) const;
	/** Creates an iterator object for the set of paragraphs in these stories.
			@return The paragraph iterator object. */
	IParagraphsIterator GetParagraphsIterator( ) const;
	/** Creates an iterator object for the set of words in these stories.
			@return The word iterator object. */
	IWordsIterator GetWordsIterator( ) const;
	/** Creates an iterator object for the set of text runs in these stories.
			@return The text run iterator object. */
	ITextRunsIterator GetTextRunsIterator( ) const;
	/** Retrieves the document text resources for these stories.
			@return The document text resources object. */
	IDocumentTextResources GetDocumentTextResources( ) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param nIndex The 0-based position index.
			@return The member object.
		*/
	IStory Item( ATETextDOM::Int32 nIndex) const;
	/** Suspends reflow calculation for these stories. Speeds up calls that cause reflow,
		such as \c ITextRange insertion methods. Use \c #ResumeReflow()
		to restore normal reflow calculation.
			@return Nothing. */
	void SuspendReflow( );
	/** Resumes normal reflow calculation after a call to \c #SuspendReflow().
			@return Nothing. */
	void ResumeReflow( );

};

//////////////////////////////////////////////
//       --IStory--
//////////////////////////////////////////////
/** This class represents a text flow. A story contains
	paragraphs, words, text runs, and text frames. You can
	get a text range for any arbitrary subset of the text,
	or for the selected text.

	<<need some discussion of how this is organized, why you
	access text at different levels>>

	Kerning is managed at the story level.

	A set of stories is collected in an \c IStories object.
	*/
class IStory
{
private:
	StoryRef	fStory;
public:
	/** Constructor.
			@return The new object. */
	IStory();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IStory(const IStory& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IStory& operator=(const IStory& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IStory& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IStory& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param story The C object.
 			@return The new C++ object. */
	explicit IStory(StoryRef story);
	/** Destructor */
	virtual ~IStory();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	StoryRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// ========================================================================
	// PROPERTIES
	// ========================================================================

	/** Retrieves the index position of this story in its \c IStories collection.
			@return The 0-based index. */
	ATETextDOM::Int32 GetIndex( ) const;
	/** Retrieves the number of characters in this story.
			@return The number of characters. */
	ATETextDOM::Int32 GetSize( ) const;
	/// navigation objects.
	/** Retrieves the story collection that contains this story.
			@return The story collection object. */
	IStories GetStories( ) const;
	/** Retrieves the text range that contains the entire text of this story.
			@return The text range object. */
	ITextRange GetTextRange( ) const;
	/** Retrieves the set of text ranges that contains the selected text of this story.
			@return The text range set object. */
	ITextRanges GetTextSelection( ) const;
	/** Creates an iterator object for the set of paragraphs in this story.
			@return The paragraph iterator object. */
	IParagraphsIterator GetParagraphsIterator( ) const;
	/** Creates an iterator object for the set of words in this story.
			@return The word iterator object. */
	IWordsIterator GetWordsIterator( ) const;
	/** Creates an iterator object for the set of text runs in this story.
			@return The text run iterator object. */
	ITextRunsIterator GetTextRunsIterator( ) const;
	/** Creates an iterator object for the set of text frames in this story.
			@return The text frame iterator object. */
	ITextFramesIterator GetTextFramesIterator( ) const;
	/** Retrieves a text frame from this story.
			@param frameIndex The 0-based position index.
			@return The text frame object. */
	ITextFrame GetFrame( ATETextDOM::Int32 frameIndex) const;

	/// Kerning management
	/// for auto or optical kerns
	/** Sets automatic or optical kerning for a text range in this story.
			@param textRange The text range.
			@param autoKernType The kerning type constant.
			@return Nothing. */
	void SetKernForSelection( const ITextRange& textRange, AutoKernType autoKernType);
	/// for manual kerns
	/** Sets a specific kern value in this story.
			@param charIndex The 0-based position index of the character to kern.
			@param value The kerning value.
			@return Nothing. */
	void SetKernAtChar( ATETextDOM::Int32 charIndex, ATETextDOM::Int32 value);
	/** Retrieves the kerning type and value for a text range in this story.
			@param textRange The text range object.
			@param pAutoKernType [out] A buffer in which to return the kerning type constant.
			@param value [out] A buffer in which to return the kerning value.
			@return Nothing. */
	void GetKern( const ITextRange& textRange, AutoKernType* pAutoKernType, ATETextDOM::Int32* value) const;
	/** Retrieves the kerning type and value for a character in this story.
			@param charIndex The 0-based position index of the character.
			@param pManualKernValue [out] A buffer in which to return the kerning value.
			@return The kerning type constant that applies to this character. */
	AutoKernType GetModelKernAtChar( ATETextDOM::Int32 charIndex, ATETextDOM::Int32* pManualKernValue) const;
	// ========================================================================
	// METHODS
	// ========================================================================
	/** Retrieves an arbitrary text range from this story.
			@param start The 0-based position index of the first character in the range.
				If negative, 0 is used.
			@param end The 0-based position index of the last character in the range.
				If greater than the size of the story, the last character of the story is used.
			@return The text range object. */
	ITextRange GetTextRange( ATETextDOM::Int32 start, ATETextDOM::Int32 end) const;
	/** Creates a new story that is a copy of this one.
			@return The story object. */
	IStory Duplicate( );
 	/** Suspends reflow calculation for this story. Speeds up calls that cause reflow,
		such as \c ITextRange insertion methods. Use \c #ResumeReflow()
		to restore normal reflow calculation.
			@return Nothing. */
	void SuspendReflow( );
	/** Resumes normal reflow calculation after a call to \c #SuspendReflow().
			@return Nothing. */
	void ResumeReflow( );

};

//////////////////////////////////////////////
//       --ITabStop--
//////////////////////////////////////////////
/** Encapsulates a tab stop in a paragraph. Tab stops are collected
	in an \c ITabStops object, which you can retrieve from
	a paragraph using \c IParaFeatures::GetTabStops.
	Use an \c ITabStopsIterator object to iterate through the collection. */
class ITabStop
{
private:
	TabStopRef	fTabStop;
public:
	/** Constructor.
			@return The new object. */
	ITabStop();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITabStop(const ITabStop& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITabStop& operator=(const ITabStop& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITabStop& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITabStop& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param tabstop The C object.
 			@return The new C++ object. */
	explicit ITabStop(TabStopRef tabstop);
	/** Destructor */
	virtual ~ITabStop();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TabStopRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================
	/** Retrieves the type of this tab stop (right or left).
			@return The tab type constant. */
	TabType GetTabType( ) const;
	/** Sets the type of this tab stop (right or left).
			@param tabType The tab type constant.
			@return Nothing. */
	void SetTabType( TabType tabType);
	/** Retrieves the position of this tab stop.
			@return The tab position in document points. */
	ATETextDOM::Real GetPosition( ) const;
	/** Sets the position of this tab stop.
			@param position The tab position in document points.
			@return Nothing. */
	void SetPosition( ATETextDOM::Real position);
	/** Reports whether this tab stop uses a leader.
			@return True if the tab uses a leader. */
	bool HasLeader( ) const;
	/** Retrieves the leader string for this tab stop.
			@param leader [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
			@return Nothing. */
	void GetLeader( ATETextDOM::Unicode* leader, ATETextDOM::Int32 maxLength) const;
	/** Sets the leader string for this tab stop.
			@param leader The string.
			@return Nothing. */
	void SetLeader( ATETextDOM::Unicode* leader);
	/** Retrieves the decimal character for this tab stop.
			@return A string containing the character. */
	ATETextDOM::Unicode GetDecimalCharacter( ) const;
	/** Sets the decimal character for this tab stop.
			@param decimalChar A string containing the character. */
	void SetDecimalCharacter( ATETextDOM::Unicode decimalChar);

};

//////////////////////////////////////////////
//       --ITabStops--
//////////////////////////////////////////////
/** Encapsulates a set if tab stops in a paragraph.
	You can create a new set of tab stops to apply to a paragraph,
	with \c IParaFeatures::SetTabStops(), or retrieve the existing
	tab stops with \c IParaFeatures::GetTabStops().
	Tab stop sets are collected in an \c IArrayTabStops object,
	which you can retrieve from a set of paragraphs using
	\c IParaInspector::GetTabStops. Use an \c ITabStopsIterator
	object to iterate through each set in the array.
	 */
class ITabStops
{
private:
	TabStopsRef	fTabStops;
public:
	/** Constructor. Creates an empty container.
			@return The new object. */
	ITabStops();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITabStops(const ITabStops& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITabStops& operator=(const ITabStops& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITabStops& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITabStops& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param tabstops The C object.
 			@return The new C++ object. */
	explicit ITabStops(TabStopsRef tabstops);
	/** Destructor */
	virtual ~ITabStops();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TabStopsRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// =======================================================================
	/** Retrieves the number of members of this set.
			@return The number of members.  */
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	ITabStop GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	ITabStop GetLast( ) const;
	// =======================================================================
	// METHODS
	// =======================================================================
	/** Replaces or adds a tab stop to this set.
			@param pTabStop The replacement or new tab stop object.
			@return Nothing.
		*/
	void ReplaceOrAdd( const ITabStop& pTabStop);
	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param nIndex The 0-based position index.
			@return The member object.
		*/
	ITabStop Item( ATETextDOM::Int32 nIndex) const;
	/** Removes a member from the set.
			@param nIndex The 0-based position index of the member to remove.
			@return Nothing. */
	void Remove( ATETextDOM::Int32 nIndex);
	/** Removes all members from the set.
			@return Nothing. */
	void RemoveAll( );
};

//////////////////////////////////////////////
//       --ITabStopsIterator--
//////////////////////////////////////////////
/**	This class allows you to iterate through a set of tab stops.
	Create the iterator object from a \c ITabStops object.
	Use it to access the \c ITabStop objects in the collection.
*/
class ITabStopsIterator
{
private:
	TabStopsIteratorRef	fTabStopsIterator;
public:
	/** Constructor.
			@return The new object. */
	ITabStopsIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITabStopsIterator(const ITabStopsIterator& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITabStopsIterator& operator=(const ITabStopsIterator& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITabStopsIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITabStopsIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param tabstopsiterator The C object.
 			@return The new C++ object. */
	explicit ITabStopsIterator(TabStopsIteratorRef tabstopsiterator);
	/** Destructor */
	virtual ~ITabStopsIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TabStopsIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates an iterator object for a specific tab stop set
		that is ordered first-to-last or last-to-first.
			@param tabStops The tab stops set object.
			@param direction Optional. The order of iteration. Default is first-to-last.
			@return The new iterator object.
		*/
	ITabStopsIterator( ITabStops tabStops, Direction direction = kForward);


	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( );
	/** Sets the current position to the first member of this set.
			@return Nothing. */
	void MoveToFirst( );
	/** Sets the current position to the last member of this set.
			@return Nothing. */
	void MoveToLast( );
	/** Increments the current position in the set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Retrieves the current tab stop.
			@return The tab stop object. */
	ITabStop Item( ) const;

};

/**	A text range, the basic text unit of the Adobe Text Engine, is a set
	of characters that ranges from a start offset to an end offset within a story.
	Use a text range object:
		\li To access selected text, paragraphs, words, text frames,
			and text runs (character sequences that share attributes)
			within the contained text.
		\li To access and modify paragraph and character styles and features in the contained text.
		\li To convert text to a Unicode or C string.
		\li	To select or deselect text programmatically.
		\li To convert case in text.
		\li To find a single glyph that represents a multiple characters.

	Each time you manipulate the contents of a text range, a reflow operation occurs.
	Reflow can change the length and endpoints of any text range in the containing story,
	and can cause previously obtained text runs to become invalid; see \c ITextRunIterator.
	For efficiency, you can temporarily	disable reflowing, then renable it after
	making your changes. Use \c IStory::SuspendReflow() and \c IStory::ResumeReflow(),
	or the \c IInhibitReflow class.  Functions that can cause reflow are:
	<br><br>\c InsertAfter()
	<br>\c InsertBefore()
	<br>\c #Remove()
	<br>\c #SetLocalCharFeatures()
	<br>\c #ReplaceOrAddLocalCharFeatures()
	<br>\c #SetLocalParaFeatures()
	<br>\c #ReplaceOrAddLocalParaFeatures()

	For example, suppose you have the initial text "0123456789", and have created two
    ranges, Range1 from 0 to 5 whose content is "01234", and Range2 from 3 to 9
    whose content is "345678". If you call <code>Range1.insertAfter("abc")</code>
    the text becomes "01234abc56789", Range1 becomes "01234abc", and
	Range2 becomes "34abc5678". The offsets change automatically so that the
	contained text in the ranges reflects the insertion.
*/
//////////////////////////////////////////////
//       --ITextRange--
//////////////////////////////////////////////
class ITextRange
{
private:
	TextRangeRef	fTextRange;
public:
	/** Constructor.
			@return The new object. */
	ITextRange();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITextRange(const ITextRange& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITextRange& operator=(const ITextRange& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITextRange& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITextRange& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param textrange The C object.
 			@return The new C++ object. */
	explicit ITextRange(TextRangeRef textrange);
	/** Destructor */
	virtual ~ITextRange();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TextRangeRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// ========================================================================
	/** Retrieves the start offset of this text range.
			@return The 0-based index of the start offset from the
				beginning of the containing story. */
	ATETextDOM::Int32 GetStart( ) const;
	/** Sets the start offset of this text range.
			@param start The 0-based index of the start offset from the
				beginning of the containing story.
			@return Nothing. */
	void SetStart( ATETextDOM::Int32 start);
	/** Retrieves the end offset of this text range.
			@return The 0-based index of the end offset from the
				beginning of the containing story. */
	ATETextDOM::Int32 GetEnd( ) const;
	/** Sets the end offset of this text range.
			@param end The 0-based index of the end offset from the
				beginning of the containing story.
			@return Nothing. */
	void SetEnd( ATETextDOM::Int32 end);
	/** Retrieves the size of this text range.
			@return The number of characters. */
	ATETextDOM::Int32 GetSize( ) const;
	// =======================================================================
	// NAVIGATION OBJECTS
	// ========================================================================
	/** Retrieves the story that contains this text range.
			@return The story object. */
	IStory GetStory( ) const;
	/** Retrieves the selected text within this text range.
			@return The text ranges object containing the selected text. */
	ITextRanges GetTextSelection( ) const;
	/** Creates an iterator for the text frames contained in this text range.
			@return The iterator object. */
	ITextFramesIterator GetTextFramesIterator( ) const;
	/** Creates an iterator for the paragraphs contained in this text range.
			@return The iterator object. */
	IParagraphsIterator GetParagraphsIterator( ) const;
	/** Creates an iterator for the words contained in this text range.
			@return The iterator object. */
	IWordsIterator GetWordsIterator( ) const;
	/** Creates an iterator for the text runs contained in this text range.
		Text runs are character sequences that share attributes.
			@return The iterator object. */
	ITextRunsIterator GetTextRunsIterator( ) const;
	// =======================================================================
	// ATTRIBUTE INSPECTION AND MODIFICATION
	// ========================================================================
	/** Creates an inspector with which to access the character features of
		all characters in this text range.
			@return The inspector object. */
	ICharInspector GetCharInspector( ) const;
	/** Creates an inspector with which to access the paragraph features of
		all paragraphs in this text range.
			@return The inspector object. */
	IParaInspector GetParaInspector( ) const;
	/** Retrieves a set of all named character styles used in this text range.
			@return The character style set object. */
	ICharStyles GetNamedCharStyles( ) const;
	/** Retrieves a set of all named paragraph styles used in this text range.
			@return The paragraph style set object. */
	IParaStyles GetNamedParaStyles( ) const;
	/** Associates a named character style to this text range. The inherited values can
		be overridden by styles or features specified locally in contained
		text ranges or individual characters.
			@param pName The style name.
			@return True if the style is successfully applied, false if there
				is no style with the specified name. */
	bool SetNamedCharStyle( const ATETextDOM::Unicode* pName);
	/** Associates a named paragraph style to this text range. The inherited values can
		be overridden by styles or features specified locally in contained
		text ranges or individual paragraphs.
			@param pName The style name.
			@return True if the style is successfully applied, false if there
				is no style with the specified name. */
	bool SetNamedParaStyle( const ATETextDOM::Unicode* pName);
	/** Removes the association of this text range and its character style.
		Copies the feature values of the character style into local override
		values in the contained characters. See \c ICharFeatures.
			@return Nothing. */
	void ClearNamedCharStyle( );
	/** Removes the association of this text range and its paragraph style.
		Copies the feature values of the paragraph style into local override
		values in the contained paragraphs. See \c IParaFeatures.
			@return Nothing. */
	void ClearNamedParaStyle( );
	/** Retrieves the unique character features used in this text range.
		Unique features are those which have the same value in all text
		runs in the range.
			@return The character features object containing the unique
				feature values. Other features are unassigned.*/
	ICharFeatures GetUniqueCharFeatures( ) const;
	/** Retrieves the unique paragraph features used in this text range.
		Unique features are those which have the same value in all text
		runs in the range.
			@return The paragraph features object containing the unique
				feature values. Other features are unassigned.*/
	IParaFeatures GetUniqueParaFeatures( ) const;
	/** Reports whether there any local character feature overrides for
		characters contained in this text range.
			@return True if there are local overrides. */
	bool HasLocalCharFeatures( );
	/** Reports whether there any local paragraph feature overrides for
		paragraphs contained in this text range.
			@return True if there are local overrides. */
	bool HasLocalParaFeatures( );
	/** Retrieves the character features that have local overrides in this text range,
		and whose local values are the same in all text runs in the range.
			@return The character features object containing the unique
				local feature values. Other features are unassigned. If all
				features are unassigned, either there are no local overrides,
				or the local overrides have no common values. */
	ICharFeatures GetUniqueLocalCharFeatures( );
	/** Retrieves the paragraph features that have local overrides in this text range,
		and whose local values are the same in all text runs in the range.
			@return The paragraph features object containing the unique
				local feature values. Other features are unassigned. If all
				features are unassigned, either there are no local overrides,
				or the local overrides have no common values. */
	IParaFeatures GetUniqueLocalParaFeatures( );

	/** Replaces all of the local overrides for all characters in this text range
		with a new set of feature values. All values that are assigned
		become local values, replacing any previous local value. These local
		values override any specified in a style associated with the
		character or the text range. All values that are unassigned remove
		any previous local values, so that those values are inherited.

		Triggers a reflow operation that can cause previously obtained
		text runs to become invalid; see \c ITextRunIterator.
			@param pFeatures The new feature set object.
			@return Nothing.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow()  */
	void SetLocalCharFeatures( const ICharFeatures& pFeatures);
	/** Modifies the local overrides for all characters	in this text range.
		All values that are assigned become local values, replacing any
		previous local value. Values that are unassigned leave any previous
		local values unchanged.

		Triggers a reflow operation that can cause previously obtained
		text runs to become invalid; see \c ITextRunIterator.

			@param pFeatures The new feature set object.
			@return Nothing.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow()  */
	void ReplaceOrAddLocalCharFeatures( const ICharFeatures& pFeatures);
	/** Removes all local overrides for all characters	in this text range.
		All character features are then inherited from styles associated
		with the character or text range, or from the Normal style.
			@return Nothing. */
	void ClearLocalCharFeatures( );

	/** Replaces all of the local overrides for all paragraphs in this text range
		with a new set of feature values. All values that are assigned
		become local values, replacing any previous local value. These local
		values override any specified in a style associated with the
		paragraph or the text range. All values that are unassigned remove
		any previous local values, so that those values are inherited.

		Triggers a reflow operation that can cause previously obtained
		text runs to become invalid; see \c ITextRunIterator.
			@param pFeatures The new feature set object.
			@return Nothing.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow()  */
	void SetLocalParaFeatures( const IParaFeatures& pFeatures);
	/** Modifies the local overrides for all paragraphs	in this text range.
		All values that are assigned become local values, replacing any
		previous local value. Values that are unassigned leave any previous
		local values unchanged.

		Triggers a reflow operation that can cause previously obtained
		text runs to become invalid; see \c ITextRunIterator.
			@param pFeatures The new feature set object.
			@return Nothing.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow() */
	void ReplaceOrAddLocalParaFeatures( const IParaFeatures& pFeatures);
	/** Removes all local overrides for all paragraphs in this text range.
		All paragraph features are then inherited from styles associated
		with the paragraph or text range, or from the Normal style.
			@return Nothing. */
	void ClearLocalParaFeatures( );
	// =======================================================================
	// METHODS
	// ========================================================================
	/** Associates this text range with a new story.
			@param story The story object.
			@return Nothing. */
	void SetStory( const IStory& story);
	/** Sets the start and end points of this text range.
			@param start The 0-based index of the start offset from the
				beginning of the containing story.
			@param end The 0-based index of the end offset from the
				beginning of the containing story.
			@return Nothing. */
	void SetRange( ATETextDOM::Int32 start, ATETextDOM::Int32 end);
	/** Resets start or end point of this range so that it contains only
		one character, either the first or the last.
			@param direction Optional. The direction constant. Default is
				\c CollapseEnd, which sets the start offset to the end offset.
				Use \c CollapseStart to set the end offset to the start offset. */
	void Collapse( CollapseDirection direction = CollapseEnd);
	/** Moves this text range by adding or subtracting a number of characters
		to or from the start and end offsets. Does not move the range if the
		result would be out of the story bounds.
			@param unit The number of characters, positive to move the range
				toward the end, negative to move it toward the beginning of
				the story.
			@return The number of characters by which the range was translated,
				or 0 if the translation could not be made within the story bounds.	*/
	ATETextDOM::Int32 Move( ATETextDOM::Int32 unit);
	/** Creates a duplicate of this object.
			@return The new object. */
	ITextRange Clone( ) const;
	/** Inserts text into this text range before the current start point. Triggers a
		reflow operation that resets the start and end points of this and any other
		affected ranges to include both the old and new text.
			@param text A Unicode string containing the text.
			@param length (Optional) The number of characters, or -1 (the default) if
				the string is NULL-terminated.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow() */
	void InsertBefore( const ATETextDOM::Unicode* text, ATETextDOM::Int32 length = -1);
	/** Inserts text into this text range after the current end point. Triggers a
		reflow operation that resets the start and end points of this and any other
		affected ranges to include both the old and new text.
			@param text A Unicode string containing the text.
			@param length (Optional) The number of characters, or -1 (the default) if
				the string is NULL-terminated.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow() */
	void InsertAfter( const ATETextDOM::Unicode* text, ATETextDOM::Int32 length = -1);
	/** Inserts text into this text range before the current start point. Triggers a
		reflow operation that resets the start and end points of this and any other
		affected ranges to include both the old and new text.
			@param anotherRange A text range object containing the text.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow() */
	void InsertBefore( const ITextRange& anotherRange);
	/** Inserts text into this text range after the current end point. Triggers a
		reflow operation that resets the start and end points of this and any other
		affected ranges to include both the old and new text.
			@param anotherRange A text range object containing the text.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow() */
	void InsertAfter( const ITextRange& anotherRange);

	/** Retrieves the contents of this text range as a Unicode string.
			@param text [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetContents( ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength) const;
	/** Retrieves the contents of this text range as a C string.
			@param text [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetContents( char* text, ATETextDOM::Int32 maxLength) const;

	/** Reports whether the characters in this text range map to a single glyph,
		and if so, retrieves that glyph.
			@param pSingleGlyph [out] A buffer in which to return the glyph identifier,
				if there is one. Otherwise, the buffer is not changed.
			@return True if the characters in this range map to a single glyph. */
	bool GetSingleGlyphInRange( ATEGlyphID* pSingleGlyph) const;

	/** Selects the text in this text range.
			@param addToSelection (Optional) True to add this text to the current
				selection, false (the default) to clear the current selection before
				selecting this text.
			@return Nothing. */
	void Select( bool addToSelection = false);
	/** Deselects the text in this text range. This can result in a discontiguous selection,
		if this text range is a subset of the selected text.
			@return Nothing. */
	void DeSelect( );
	/** Changes the case of the text in this text range.
			@param caseChangeType The case type constant.
			@return Nothing. */
	void ChangeCase( CaseChangeType caseChangeType);
	/** Adjusts the tracking of the text in this range to
		fit on one line spanning the width of the area text object.
		This is the equivalent of choosing Type > Fit Headline with
		the text range selected.
			@return Nothing. */
	void FitHeadlines( );
	/** Deletes all of the characters in this text range. Triggers a
		reflow operation that resets the start and end points of any other
		affected ranges.
			@return Nothing.
			@see \c IStory::SuspendReflow(), \c IStory::ResumeReflow()  */
	void Remove( );
	/** Retrieves the character type of the single character in this
		text range. Throws \c #kBadParameterErr if this text range
		does not contain exactly one character.
			@return The character type constant,  */
	ASCharType GetCharacterType( ) const;

};

//////////////////////////////////////////////
//       --ITextRanges--
//////////////////////////////////////////////
/** Encapsulates a set of text ranges. Contains a collection of \c ITextRange objects.
	Allows you to perform many of the text operations on all of the member ranges
	at once. Use an \c ITextRangesIterator object to iterate through the member ranges. */
class ITextRanges
{
private:
	TextRangesRef	fTextRanges;
public:
	/** Constructor.
			@return The new object. */
	ITextRanges();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITextRanges(const ITextRanges& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITextRanges& operator=(const ITextRanges& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITextRanges& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITextRanges& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param textranges The C object.
 			@return The new C++ object. */
	explicit ITextRanges(TextRangesRef textranges);
	/** Destructor */
	virtual ~ITextRanges();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TextRangesRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	// =======================================================================
	// PROPERTIES
	// ======================================================================
	/** Retrieves the number of members of this set.
			@return The number of members.
		*/
	ATETextDOM::Int32 GetSize( ) const;
	/** Retrieves the first member of this set.
			@return The member object. 	*/
	ITextRange GetFirst( ) const;
	/** Retrieves the last member of this set.
			@return The member object. 	*/
	ITextRange GetLast( ) const;
	// navigation objects.
	/** Retrieves the selected text within this text range set.
			@return The text ranges object containing the selected text. 	*/
	ITextRanges GetTextSelection( ) const;
	/** Creates an iterator for the paragraphs contained in this text range set.
			@return The iterator object. */
	IParagraphsIterator GetParagraphsIterator( ) const;
	/** Creates an iterator for the words contained in this text range set.
			@return The iterator object. */
	IWordsIterator GetWordsIterator( ) const;
	/** Creates an iterator for the text runs contained in this text range set.
			@return The iterator object. */
	ITextRunsIterator GetTextRunsIterator( ) const;
	// =======================================================================
	// ATTRIBUTE INSPECTION AND MODIFICATION
	// ========================================================================
	/** Creates an inspector with which to access the character features of
		all characters in this text range set.
			@return The inspector object. */
	ICharInspector GetCharInspector( ) const;
	/** Creates an inspector with which to access the paragraph features of
		all paragraphs in this text range set.
			@return The inspector object. */
	IParaInspector GetParaInspector( ) const;
	/** Removes the association of this text range set and its character style.
		Copies the feature values of the character style into local override
		values in the contained characters. See \c ICharFeatures.
			@return Nothing. */
	void ClearNamedCharStyle( );
	/** Removes the association of this text range set and its paragraph style.
		Copies the feature values of the paragraph style into local override
		values in the contained paragraphs. See \c IParaFeatures.
			@return Nothing. */
	void ClearNamedParaStyle( );
	/** Retrieves the unique character features used in this text range set.
		Unique features are those which have the same value in all text
		runs in the ranges.
			@return The character features object containing the unique
				feature values. Other features are unassigned.*/
	ICharFeatures GetUniqueCharFeatures( ) const;
	/** Retrieves the unique paragraph features used in this text range set.
		Unique features are those which have the same value in all text
		runs in the ranges.
			@return The paragraph features object containing the unique
				feature values. Other features are unassigned.*/
	IParaFeatures GetUniqueParaFeatures( ) const;
	/** Reports whether there any local character feature overrides for
		characters contained in this text range set.
			@return True if there are local overrides. */
	bool HasLocalCharFeatures( );
	/** Reports whether there any local paragraph feature overrides for
		paragraphs contained in this text range set.
			@return True if there are local overrides. */
	bool HasLocalParaFeatures( );
	/** Retrieves the character features that have local overrides in this text range set,
		and whose local values are the same in all text runs in the ranges.
			@return The character features object containing the unique
				local feature values. Other features are unassigned. If all
				features are unassigned, either there are no local overrides,
				or the local overrides have no common values. */
	ICharFeatures GetUniqueLocalCharFeatures( );
	/** Retrieves the paragraph features that have local overrides in this text range set,
		and whose local values are the same in all text runs in the ranges.
			@return The paragraph features object containing the unique
				local feature values. Other features are unassigned. If all
				features are unassigned, either there are no local overrides,
				or the local overrides have no common values. */
	IParaFeatures GetUniqueLocalParaFeatures( );

	/** Replaces all of the local overrides for all characters in this text range set
		with a new set of feature values. All values that are assigned
		become local values, replacing any previous local value. These local
		values override any specified in a style associated with a
		character or a text range. All values that are unassigned remove
		any previous local values, so that those values are inherited.
			@param pFeatures The new feature set object.
			@return Nothing. */
	void SetLocalCharFeatures( const ICharFeatures& pFeatures);
	/** Modifies the local overrides for all characters	in this text range set.
		All values that are assigned become local values, replacing any
		previous local value. Values that are unassigned leave any previous
		local values unchanged.
			@param pFeatures The new feature set object.
			@return Nothing. */
	void ReplaceOrAddLocalCharFeatures( const ICharFeatures& pFeatures);
	/** Removes all local overrides for all characters	in this text range set.
		All character features are then inherited from styles associated
		with the character or text range, or from the Normal style.
			@return Nothing. */
	void ClearLocalCharFeatures( );
	/** Replaces all of the local overrides for all paragraphs in this text range set
		with a new set of feature values. All values that are assigned
		become local values, replacing any previous local value. These local
		values override any specified in a style associated with a
		paragraph or a text range. All values that are unassigned remove
		any previous local values, so that those values are inherited.
			@param pFeatures The new feature set object.
			@return Nothing. */
	void SetLocalParaFeatures( const IParaFeatures& pFeatures);
	/** Modifies the local overrides for all paragraphs	in this text range set.
		All values that are assigned become local values, replacing any
		previous local value. Values that are unassigned leave any previous
		local values unchanged.
			@param pFeatures The new feature set object.
			@return Nothing. */
	void ReplaceOrAddLocalParaFeatures( const IParaFeatures& pFeatures);
	/** Removes all local overrides for all paragraphs in this text range set.
		All paragraph features are then inherited from styles associated
		with the paragraph or text range, or from the Normal style.
			@return Nothing. */
	void ClearLocalParaFeatures( );
	// =======================================================================
	// METHODS
	// ======================================================================
	/** Selects the text in this text range set.
			@param addToSelection (Optional) True to add this text to the current
				selection, false (the default) to clear the current selection before
				selecting this text.
			@return Nothing. */
	void Select( bool addToSelection = false);
	/** Deselects the text in this text range set.
		This can result in a discontiguous selection,
		if this text is a subset of the selected text.
			@return Nothing. */
	void DeSelect( );
	/** Retrieves the contents of this text range set as a Unicode string.
			@param text [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetContents( ATETextDOM::Unicode* text, ATETextDOM::Int32 maxLength) const;
	/** Retrieves the contents of this text range set as a C string.
			@param text [out] A buffer in which to return the string.
			@param maxLength The number of characters in the buffer.
			@return The number of characters in the returned string. */
	ATETextDOM::Int32 GetContents( char* text, ATETextDOM::Int32 maxLength) const;
	/** Changes the case of the text in this text range set.
			@param caseChangeType The case type constant.
			@return Nothing. */
	void ChangeCase( CaseChangeType caseChangeType);
	/** Adds a text range as a member of this set.
			@param textRange The text range object.
			@return Nothing. */
	void Add( const ITextRange& textRange);
	/** Retrieves a member of this set by position index. Use with \c GetSize()
		to iterate through members.
			@param nIndex The 0-based position index.
			@return The member object.
		*/
	ITextRange Item( ATETextDOM::Int32 nIndex) const;
	/** Removes all members from the set.
			@return Nothing. */
	void RemoveAll( );
	/** Removes a member from the set.
			@param nIndex The 0-based position index of the member to remove.
			@return Nothing. */
	void Remove( ATETextDOM::Int32 nIndex);

};

//////////////////////////////////////////////
//       --ITextRangesIterator--
//////////////////////////////////////////////
/** This object allows you to iterate through a set of text ranges.
	Create the iterator from a set of text ranges (\c ITextRanges). */
class ITextRangesIterator
{
private:
	TextRangesIteratorRef	fTextRangesIterator;
public:
	/** Constructor.
			@return The new object. */
	ITextRangesIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITextRangesIterator(const ITextRangesIterator& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITextRangesIterator& operator=(const ITextRangesIterator& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITextRangesIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITextRangesIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param textrangesiterator The C object.
 			@return The new C++ object. */
	explicit ITextRangesIterator(TextRangesIteratorRef textrangesiterator);
	/** Destructor */
	virtual ~ITextRangesIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TextRangesIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates an iterator object for a specific text range set
		that is ordered first-to-last or last-to-first.
			@param textRanges The text range set object.
			@param direction Optional. The order of iteration. Default is first-to-last.
			@return The new iterator object.
		*/
	ITextRangesIterator( ITextRanges textRanges, Direction direction = kForward);

	/** Creates a duplicate of this object.
			@return The new object. */
	ITextRangesIterator Clone( ) const;

	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Sets the current position to the first member of this set.
			@return Nothing. */
	void MoveToFirst( );
	/** Sets the current position to the last member of this set.
			@return Nothing. */
	void MoveToLast( );
	/** Increments the current position in the set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Retrieves the current text range.
			@return The text range object. */
	ITextRange Item( ) const;

};

//////////////////////////////////////////////
//       --ITextRunsIterator--
//////////////////////////////////////////////
/** This object allows you to iterate through a set of text runs in a story.
	A text run is a range of text whose characters all share the
	same set of attributes. If the text of the story changes through insertions
	or deletions, an existing text run iterator is rendered invalid.

	Create a text run iterator object using  \c ITextRange::GetTextRunsIterator(),
	or the corresponding method in \c ITextRanges, \c IStory, \c IStories, or \c IGlyphs.
	*/
class ITextRunsIterator
{
private:
	TextRunsIteratorRef	fTextRunsIterator;
public:
	/** Constructor.
			@return The new object. */
	ITextRunsIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	ITextRunsIterator(const ITextRunsIterator& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	ITextRunsIterator& operator=(const ITextRunsIterator& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const ITextRunsIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const ITextRunsIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param textrunsiterator The C object.
 			@return The new C++ object. */
	explicit ITextRunsIterator(TextRunsIteratorRef textrunsiterator);
	/** Destructor */
	virtual ~ITextRunsIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	TextRunsIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates an iterator object for a the text runs in a specific text range set
		that is ordered first-to-last or last-to-first.
			@param ranges The text range set object.
			@param direction Optional. The order of iteration. Default is first-to-last.
			@return The new iterator object.
		*/
	ITextRunsIterator( const ITextRanges& ranges, Direction direction = kForward);
	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Sets the current position to the first member of this set.
			@return Nothing. */
	void MoveToFirst( );
	/** Sets the current position to the last member of this set.
			@return Nothing. */
	void MoveToLast( );
	/** Increments the current position in the set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Retrieves the text range containing the current text run.
			@return The text range object.
			@note This can change from one call to the next if the story text changes.
				For foward iteration, the new text run begins at or before the old one.
				For backward iteration, the new text run begins at or after the old one.  */
	ITextRange Item( ) const;

};

//////////////////////////////////////////////
//       --IWordsIterator--
//////////////////////////////////////////////
/** This object allows you to iterate through a set of words in a text range.
	Create an iterator object using  \c ITextRange::GetWordsIterator(),
	or the corresponding method in \c ITextRanges, \c IStory, \c IStories,
	\c IParagraph, or \c IGlyphs.
	*/
class IWordsIterator
{
private:
	WordsIteratorRef	fWordsIterator;
public:
	/** Constructor.
			@return The new object. */
	IWordsIterator();
	/** Copy constructor
			@param src The object to copy.
			@return The new object. */
	IWordsIterator(const IWordsIterator& src);
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
	IWordsIterator& operator=(const IWordsIterator& rhs);
	/** Comparison operator tests for equality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are the same.   */
	bool operator==(const IWordsIterator& rhs) const;
 	/** Comparison operator tests for inequality.
 			@param rhs The object to compare to this one.
			@return True if the two objects are not the same. 	*/
	bool operator!=(const IWordsIterator& rhs) const;
 	/** Constructs this C++ object from the corresponding C object
 		returned by an ATE suite function.
		The C++ object manages reference counting.
 			@param wordsiterator The C object.
 			@return The new C++ object. */
	explicit IWordsIterator(WordsIteratorRef wordsiterator);
	/** Destructor */
	virtual ~IWordsIterator();
	/** Retrieves a reference to this object.
 			@return The object reference.  	*/
	WordsIteratorRef GetRef() const;
 	/** Reports whether this is a null object.
			@return True if this is a null object. */
	bool IsNull() const;

	/** Constructor. Creates an iterator object for the words in a specific text range set.
		that is ordered first-to-last or last-to-first.
			@param ranges The text range set object.
			@param direction Optional. The order of iteration. Default is first-to-last.
			@return The new iterator object.
		*/
	IWordsIterator( const ITextRanges& ranges, Direction direction = kForward);

	/** Reports whether the end of the set has been reached.
			@return True if more members remain in the set. */
	bool IsNotDone( ) const;
	/** Reports whether the end of the set has been reached.
			@return True if no more members remain in the set. */
	bool IsDone( ) const;
	/** Reports whether the set is empty.
			@return True if the set is empty. */
	bool IsEmpty( ) const;
	/** Sets the current position to the first member of this set.
			@return Nothing. */
	void MoveToFirst( );
	/** Sets the current position to the last member of this set.
			@return Nothing. */
	void MoveToLast( );
	/** Increments the current position in the set in the iterator's current direction.
			@return Nothing. */
	void Next( );
	/** Retrieves the text range for the current word, including trailing characters.
		This is equivalent to Ctrl/Cmd + arrow. For example, "..." is considered a word.
			@return The text range object. */
	ITextRange Item( ) const;

	/// Trailing characters

	/** Retrieves the number of trailing spaces for the current word.
		Trailing spaces are those after the word, regardless of the direction of
		iteration.
			@return The number of trailing spaces. */
	ATETextDOM::Int32 GetTrailingSpaceCount( ) const;
	/** Retrieves the total number of trailing characters for the current word, including
		spaces, other white-space characters, and punctuation characters.
		Trailing characters are those after the word, regardless of the direction of
		iteration.
			@return The number of trailing characters. */
	ATETextDOM::Int32 GetTrailingCount( ) const;
	/** Retrieves the number of trailing punctuation characters for the current word.
		Trailing characters are those after the word, regardless of the direction of
		iteration.
			@return The number of trailing punctuation characters. */
	ATETextDOM::Int32 GetTrailingTerminatingPunctuationCount( ) const;

};

/** A convenience class for temporarily inhibiting reflow in a text story.
	By default, as edits are made to the contents of a text story and its attributes,
	the story contents are reflowed through the story containers. This operation
	can be expensive. Use this class to inhibit reflow when batching together
	a series of edits to one or more text objects. Destroy the object when
	all the edits are complete, so that reflow is automatically resumed.
	*/
class IInhibitReflow
{
public:
	/** Constructor.
			@return The new object. */
   IInhibitReflow()
   {
   }
	/** Constructor. Creates a reflow inhibitor object for a story.
			@param story The story object.
			@return The new reflow inhibitor object.
		*/
   IInhibitReflow(const IStory& story)
   :fStory(story)
   {
       fStory.SuspendReflow();
   }
	/** Copy constructor
			@param reflow The object to copy.
			@return The new object. */
   IInhibitReflow(const IInhibitReflow& reflow)
   :fStory(reflow.fStory)
   {
       fStory.SuspendReflow();
   }
	/** Destructor. */
   virtual ~IInhibitReflow()
   {
	   try
	   {
		   if (!fStory.IsNull())
			   fStory.ResumeReflow();
	   }
	   catch (...) {}
   }
	/** Assignment operator.
			@param rhs The object to assign to this one.
			@return A reference to this object. */
   IInhibitReflow& operator=(const IInhibitReflow& rhs)
   {
       this->~IInhibitReflow( );
       fStory = rhs.fStory;
       if(!fStory.IsNull())
          fStory.SuspendReflow();
       return *this;
   }
protected:
   IStory    fStory;
};
}// namespace ATE

