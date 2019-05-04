/*
 *        Name:	IAILocale.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Interface to the wrapper class for AIStringFormatUtilsSuite & the
 *				primary interface for the AI core to the ai::Locale object.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 2004-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */


#ifndef _IAILOCALE_H_
#define _IAILOCALE_H_


namespace ai {

/**This class represents a predefined set of locales
	used in Illustrator, with a unique identifying code
	and associated descriptive string for the language and region.
	The methods allow you to access the current locale setting
	of the operating system or of the application.*/

class Locale {
public:

	/** Locale type constants, mapped to a descriptive string
		that contains the language name and region code. */
	enum ID
	{
		/** Invalid locale */
		kUndefined = -1,
		/** Implies the default language behavior for a particular context.
			For example, in the \c ai::NumberFormat class, implies the system
			setting for number formats */
		kDefault = 0,
		/** The operating-system locale */
		kSystem,
		/** The application locale */
		kApplication,
		/** US English (en_US) */
		kUS,
		/** English (en_GB) */
		kBritain,
		/** German (de_DE) */
		kGermany,
		/** French (fr_FR) */
		kFrance,
		/** Italian (it_IT) */
		kItaly,
		/** Japanese (ja_JP) */
		kJapan,
		/**  Chinese (Simplified - zh_CN) */
		kChina,
		/** Chinese (Traditional - zh_TW) */
		kTaiwan,
		/** Korean (Korea - ko_KR) */
		kKorea,
		/** Arabic (ar_AE) */
		kArabia,
		/** English (en_CA) */
		kCanadaComma,
		/** French (fr_CA) */
		kFrCanada,
		/** Spanish (es_ES) */
		kSpain,
		/** Swedish (sv_SE) */
		kSweden,
		/** Portuguese (pt_PT) */
		kPortugal,
		/** Portuguese (pt_BR) */
		kBrazil,
		/** Polish (pl_PL) */
		kPoland,
		/** Dutch (nl_NL) */
		kNetherlands,
		/** Danish (da_DK) */
		kDenmark,
		/** German (de_CH) */
		kGrSwiss,
		/** Norwegian (nb_NO) */
		kNorway,
		/** Nynorsk (nn_NO) */
		kNynorskNorway,
		/** Finnish (fi_FI) */
		kFinland,
		/** Czech (cs_CZ) */
		kCzech,
		/** Hungarian (hu_HU) */
		kHungary,
		/** Greek (el_GR) */
		kGreece,
		/** Russian (ru_RU) */
		kRussia,
		/** Romanian (ro_RO) */
		kRomania,
		/** Turkish (tr_TR) */
		kTurkey,
		/** Thai (th_TH) */
		kThailand,
		/** Vietnamese (vi_VN) */
		kVietnam,
		/** Bulgarian (bg_BG) */
		kBulgaria,
		/** Hebrew (he_IL) */
		kIsrael,
		/** Ukrainian (uk_UA) */
		kUkraine,
		/** Mexican Spanish (es_MX) */
		kSpMexican,
		/** Iranian Farsi (fa_IR) */
		kFarsi,
		/** Arabic with English UI (en_AE) */
		kEnArabia,	
		/** Hebrew with English UI  (en_IL)*/
		kEnHebrew,
		/** North African French  (fr_MA) */
		kFrNorthAfrica,
		/** */
		kAIDummyLocale = 0xFFFFFFFF
	};

	/** Retrieves the language and region code string for a locale.
			@param	id The locale identifier constant.
			@return	The language and region code string .
	  */
	static std::string getLocale(const Locale::ID id);

	/** Retrieves the current system locale as a locale identifier.
	  		 @return	The locale ID constant.
	  */
	static Locale::ID getSystemLocaleID();

	/** Retrieves the current application locale as a locale identifier.
	  		 @return	The locale ID constant.
	  */
	static Locale::ID getApplicationLocaleID();

	/**	Retrieves the locale identifier for a language and region code string.
			@param locale	language and region code string
	 		@return	The locale ID constant or \c ai::Locale::kUndefined if the string
				does not map to a valid type.
	  	*/
	static Locale::ID getID(const std::string& locale);

};

/** Locale unique identifying code. */
typedef Locale::ID LocaleID;

} // end of namespace ai

#endif //_IAILOCALE_H_
