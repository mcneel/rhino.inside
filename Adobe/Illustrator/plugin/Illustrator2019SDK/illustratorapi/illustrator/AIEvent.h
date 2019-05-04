#ifndef __AIEvent__
#define __AIEvent__

/*
 *        Name:	AIEvent.h
 *   $Revision: 5 $
 *      Author:
 *        Date:
 *     Purpose:	Adobe Illustrator Event Suite.
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


/*******************************************************************************
 **
 **	Imports
 **
 **/

#ifndef __AITypes__
#include "AITypes.h"
#endif

#include "AIHeaderBegin.h"

/** @file AIEvent.h */

/*******************************************************************************
 **
 **	Constants
 **
 **/

/** Modifier keys for an event. See \c #AIEventModifersValue.
	Used in the \c #AIToolSuite and \c #AICursorSnapSuite. */
typedef ASUInt16 AIEventModifiers;

// Originally based on Mac OS EventRecord
/** Event modifier key masks and bit flags, used in deprecated ADM functions.
	Use masks to check values, bit flags to bit-shift values to a position.*/
enum AIEventModifersValue {
	/** Not used. */
	aiEventModifiers_activeFlag			= 0x0001,
	/** Mask. Main mouse button down. */
	aiEventModifiers_btnState			= 0x0080,
	/** Mask. Either Cmd key is pressed in Mac OS, or the Ctrl key in Windows.   */
	aiEventModifiers_cmdKey				= 0x0100,
	/** Mask. Either Shift key is pressed.  */
	aiEventModifiers_shiftKey			= 0x0200,
	/** Not used. */
	aiEventModifiers_alphaLock			= 0x0400,
	/** Mask. The Alt or Option key is pressed.  */
	aiEventModifiers_optionKey			= 0x0800,	/* Alt key on MSWIndows	*/
	/** Mask. The Ctrl key is pressed in Mac OS. Not used in Windows. */
	aiEventModifiers_controlKey			= 0x1000,
	/** Mask. The right Shift key is pressed.  */
	aiEventModifiers_rightShiftKey		= 0x2000,
	/** Mask. The right Alt or Option key is pressed.  */
	aiEventModifiers_rightOptionKey		= 0x4000,
	/** Mask. The right Ctrl key is pressed in Mac OS. Not used in Windows.  */
	aiEventModifiers_rightControlKey	= 0x8000,
	/** Not used. */
	aiEventModifiers_activeFlagBit		= 0,
	/** Bit flag. When set, the main mouse button is down.  */
	aiEventModifiers_btnStateBit		= 7,
	/** Bit flag. When set, either the Cmd key is pressed in Mac OS, or the Ctrl key in Windows. */
	aiEventModifiers_cmdKeyBit			= 8,
	/** Bit flag. When set, either Shift key is pressed. */
	aiEventModifiers_shiftKeyBit		= 9,
	/** Not used. */
	aiEventModifiers_alphaLockBit		= 10,
	/** Bit flag. When set, the Alt or Option key is pressed. */
	aiEventModifiers_optionKeyBit		= 11,
	/** Bit flag. The Ctrl key is pressed in Mac OS. Not used in Windows. */
	aiEventModifiers_controlKeyBit		= 12,
	/** Bit flag. When set, the right Shift key is pressed. */
	aiEventModifiers_rightShiftKeyBit	= 13,
	/** Bit flag. When set, the right Alt or Option key is pressed. */
	aiEventModifiers_rightOptionKeyBit	= 14,
	/** Bit flag. When set, the right Ctrl key is pressed in Mac OS. Not used in Windows. */
	aiEventModifiers_rightControlKeyBit	= 15,

// additional information used by ADM tracker modifiers
	/** Mask. Space bar is pressed.  */
	aiEventModifiers_spaceKey			= 0x0002,
	/** Mask. Tab key is pressed. */
	aiEventModifiers_tabKey				= 0x0004,
	/** Mask. Caps Lock is on.  */
	aiEventModifiers_capsLockOn			= 0x0008,
	/** Mask. Double click.  */
	aiEventModifiers_doubleClick		= 0x0010,
	/** Mask. Triple click.   */
	aiEventModifiers_tripleClick		= 0x0020,
	/** Bit flag. When set, the space bar is pressed. */
	aiEventModifiers_spaceKeyBit		= 1,
	/** Bit flag. When set, the tab key is pressed. */
	aiEventModifiers_tabKeyBit			= 2,
	/** Bit flag. When set, Caps Lock is on. */
	aiEventModifiers_capsLcokBit		= 3,
	/** Bit flag. When set, there was a double click. */
	aiEventModifiers_doubleClickBit		= 4,
	/** Bit flag. When set, there was a triple click. */
	aiEventModifiers_tripleClickBit		= 5
};









#include "AIHeaderEnd.h"

#endif
