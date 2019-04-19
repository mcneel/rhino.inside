/*************************************************************************
*
* ADOBE CONFIDENTIAL
* 
* Copyright 2017 Adobe
* 
* All Rights Reserved.
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying
* it. If you have received this file from a source other than Adobe,
* then your use, modification, or distribution of it requires the prior
* written permission of Adobe.
*
**************************************************************************/

#pragma once

#include "AIEntry.h"
#include "AIArray.h"
#include "AIDictionary.h"
#include "IAILiteralString.h"
#include "IAIRef.h"

#include <memory>
#include <vector>
#include <utility>


/** @file IAIDictionary.hpp */

namespace ai
{
	/**
	A C++ based wrapper over AIDictionary, AIArray, and AIEntry Suite. 
	Forget about missing AddRef/Release.

	ai::Dictionary, ai::Array and ai::Entry classes provide C++ syntactic sugar over these APIs
	with iterators to support range loops and move semantics 

	Just add following line in your .mp and start using it.
	MP.call_once(include_ai_dictionary_wrapper)


Usage Examples
ai::Entry
	Construction
		
		ai::int32 intVal(10);
		ai::Entry e(intVal);

		//inline construction
		ai::Array arr;
		arr.push_back(ai::Entry(ai::UnicodeString::FromRoman("Test unicode string"));
		arr.push_back(std::string("Test std string"));

	Query
		//Get the type of entry
		auto entryType = e.GetType();

		//Get values by automatic types
		ai::int32 intval = e;
		AIReal realval = e;
		ai::UnicodeString strval = e;

		//Get values of specific type
		auto i = e.IntegerVal();
		auto s = e.StringVal();
		auto us = e.UnicodeStringVal();

	Compare
		if(e == e1)
		{
			
		}

ai::Array

	Construction:
		1. Default empty array
			ai::Array arr;

		2. Create with existing AIArrayRef. It increments the refcount in c'tor and decrements in d'tor.
			//Don't work with this c'tor if you're uncomfortable with the ref count logic
			ai::Array arr(arrayRef);

	Query
		//Get the size of array
		auto arraySize = arr.size();

		//Convenient [] operator
		arr[0] = ai::Entry(20.456);
		AIReal realVal = ai::Entry(arr[0]);

		//Get entry at index, via entry and value methods
		auto entry = arr.at(0);
		auto intVal = entry.IntegerVal();
 
        //Range loop access
        for(auto entry : arr)
        {
            ai::int32 intVal = entry;
            auto floatval = entry.RealVal();
        }

	Clone/Copy
		//Create a deep copy of self
			Array duplicateArr = arr.clone();
		
		//Deep copy into self from other Array
			arr.copy(otherArray);

	Edit
		//Insert an entry at location, automatic entry creation
		arr.insert(0, std::string("test"));

		//Insert an entry at a location with explicit entry creation
		arr.insert(1, ai::Entry(true));

		//Insert at end of an array
		arr.push_back(ai::Entry(10.34));

		//Reserve space upfront. This doesn't create default entries or increases the size()
		arr.reserve(10);
		
ai::Dictionary

	Construction:
		1. Work with ArtHandle's dictionary
			ai::Dictionary dict(art);

		2. Document's dictionary
			ai::Dictionary dict(ai::Dictionary::Type::kCurrentDocument);

		3. Document's non-recorded dictionary
			ai::Dictionary dict(ai::Dictionary::Type::kCurrentDocumentNonRecorded);

		4. Create a new dictionary, which can be used temporarily, or set a dict entry in another 
		   dictionary

		   ai::Dictionary dict;

	Creating AIDictKey
		//Create dictionary keys via AIDictionaryKeyHelper.hpp, which caches the AIDictKey for reuse
		//Creating AIDictKey on every call is costly
		#include "AIDictionaryKeyHelper.hpp"

		DictionaryKeyDeclareAndDefine(kMyKey, "My Dict Key");
		DictionaryKeyDeclareAndDefine(kMyChildDictKey, "My child dict key");
		DictionaryKeyDeclareAndDefine(kMyRealValkey2, "My real val key2");
		DictionaryKeyDeclareAndDefine(kIntKey, "My Int Key");

	Accessors

		//Get values with automatic type detection. Throws exception if there's a type mismatch.
		ai::int32 intVal = dict.Get(kMyKey);
		ai::UnicodeString strVal = dict.Get(kMyKey);

		//Exception based getter methods. Throws exception if a key is not found or there's a type mismatch.
		1. auto value = dict.GetString(kMyKey);
		2. auto value = dict.GetUnicodeString(kMyKey);

		//No exception getters, check error yourself
		ai::UnicodeString value;
		if(dict.GetUnicodeString(kMykey, value) == kNoErr)
		{
			//value is valid
		}

		//Setters
		dict.Set(kMyKey, floatVal); //automatic entry of AIReal type creation
		dict.Set(kMyKey, ai::UnicodeString("Automatic type detection"));

		//Set with specific type methods
		dict.SetUnicodeString(kMKey, value);
		dict.SetReal(kMyKey, floatVal);

		//Convenient [] operator
		dict[kMyRealValkey2] = ai::Entry(20.456);
		AIReal realVal = ai::Entry(dict[kMyRealValkey2]);

		//Touch art
		dict.TouchArt();

	//Nested Dictionary
		
		//Set
		ai::Dictionary child_dict;
		child_dict.SetReal(kMyKey, realval);

		dict.SetDictionary(kMyChildDictKey, child_dict);

		//Get value from child dict
		auto child_dict = dict.GetDictionary(kMyChildDictKey);
		auto value = child_dict.GetReal(kMykey);

	Query
		//find, it is more efficient than first calling IsKnown() and then Get()
		auto found = dict.find(kMyRealValkey2);
		if(found != dict.end())
		{
			//entry exists, work with it
			auto key = found.first;
			AIReal realVal = found.second;
		}

		//Check if a key exists
		auto exist = dict.IsKnown(kMyKey);

		//Get the entry type
		auto entryType = dict.GetEntryType(kMyKey);

		//Get IntegerValue
		auto intVal = dict.GetInteger(kIntKey);

		//Get value via entry
		auto intVal2 = dict.Get(kIntKey).IntegerVal();

		//Iterate through range loop
		for (auto entry : dict)
		{
			auto dictKeyString = dict.GetKeyString(entry.first);
			auto entryType = entry.second.GetType();
			auto intVal = entry.second.IntegerVal();
			ai::int32 val = entry.second;
		}

	Clone/Copy
		Create a deep copy of self
			auto duplicateDict = dict.clone();

		Deep copy entries from other dict, erasing your own entries
			dict.copy(otherDict);
		
	Delete/erase an Entry
		dict.erase(kMyKey);

	Unit Test
		ai::Dictionary::Test(); //will test Dictionary functionality

*/
	class Dictionary;
	class Array;

	class Entry
	{
	public:
		using BinaryType = std::vector<char>;

		explicit Entry(AIEntryRef entryRef);
		Entry(bool boolVal);
		Entry(ai::int32 intVal);
		Entry(AIReal realVal);
		Entry(const AIRealPoint& point);
		Entry(const AIRealMatrix& matrix);
		Entry(const std::string& strVal);
		Entry(const ai::UnicodeString& value);
		Entry(const BinaryType& value);
		Entry(const Array& value);
		Entry(const Dictionary& value);
		Entry(const AIFillStyle& value);
		Entry(const AIStrokeStyle& value);

		//Static Entry Creators as the types are not overloadable in c'tor
		static Entry FromPattern(AIPatternHandle pattern);
		static Entry FromBrushPattern(AIPatternHandle pattern);
		static Entry FromGradient(AIGradientHandle gradient);
		static Entry FromCustomColor(AICustomColorHandle customColor);
		static Entry FromPluginObject(AIObjectHandle obj);
		static Entry FromSymbolPattern(AIPatternHandle symbolPattern);
		static Entry FromArtStyle(AIArtStyleHandle artStyle);
		static Entry FromBinary(void* data, size_t size);

		Entry(const Entry& other);
		~Entry();

		bool BoolVal() const;
		operator bool() const
		{
			return BoolVal();
		}

		ai::int32 IntVal() const;
	    operator ai::int32() const
		{
			return IntVal();
		}

		AIReal RealVal() const;
		operator AIReal() const
		{
			return RealVal();
		}

		AIRealMatrix MatrixVal() const;
		operator AIRealMatrix() const 
		{
			return MatrixVal();
		}

		AIRealPoint PointVal() const;
		operator AIRealPoint () const
		{
			return PointVal();
		}

		BinaryType BinaryVal() const;
		operator BinaryType() const
		{
			return BinaryVal();
		}

		std::string StringVal() const;
		operator std::string() const
		{
			return StringVal();
		}

		ai::UnicodeString UnicodeStringVal() const;
		operator ai::UnicodeString() const
		{
			return UnicodeStringVal();
		}

		AIArtHandle ArtHandleVal() const;
		AIPatternHandle PatternVal() const;
		AIPatternHandle BrushPatternVal() const;
		AIGradientHandle GradientVal() const;
		AICustomColorHandle CustomColorVal() const;
		AIObjectHandle PluginObjectVal() const;
		AIPatternHandle SymbolPatternVal() const;
		std::unique_ptr<AIFillStyle> FillStyleVal() const;
		std::unique_ptr<AIStrokeStyle> StrokeStyleVal() const;
		AIArtStyleHandle ArtStyleVal() const;
		void BinaryVal(void *value, size_t &size) const;

		Array ArrayVal() const;
		operator Array() const;

		Dictionary DictionaryVal() const;
		operator Dictionary () const;

		AIEntryType GetType() const;
		AIEntryRef get() const;

		//Compare
		bool operator == (const Entry& other) const;

		/** 
			Try to get the entry value as a string if possible, throw if it can't
		*/
		ai::UnicodeString GetAsUnicodeString() const;

		//swap
		void swap(Entry& other) AINOEXCEPT;

		//Move constructor and assignment
		Entry(Entry&& other) AINOEXCEPT;
		Entry& operator = (Entry other) AINOEXCEPT;

	private:
		class Impl;
		std::unique_ptr<Impl> pImpl;
		Entry(std::unique_ptr<Impl>&& impl);
	};


	class Array
	{
	public:
		//iterator
		class iterator 
		{
		public:
			using value_type = Entry;
			explicit iterator(ai::int32 index, const Array& arr) :
				mIndex(index),
				mArray(arr)
			{
			}

			iterator& operator++()
			{
				if (mIndex < mArray.size())
				{
					++mIndex;
				}
				return *this;
			}

			iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }
			bool operator==(iterator other) const { return mIndex == other.mIndex; }
			bool operator!=(iterator other) const { return !(*this == other); }
			value_type operator*() const
			{
				return mArray.at(mIndex);
			}

		private:
			ai::int32 mIndex = -1;
			const Array& mArray;
		};

		Array();
		explicit Array(AIArrayRef arrayRef);

		~Array(); //required for unique_ptr

		//Copy and assignment
		Array(const Array& other);
		Array& operator = (Array other) AINOEXCEPT;//defines both move and non-move version

		//Clone self
		Array clone() const;

		//Copy into self from other
		void copy(const Array& other);

		//query
		ai::int32 size() const AINOEXCEPT;
		Entry at(ai::int32 index) const;

		//Helper class for operator[]
		class ArrayEntryGetSet
		{
		public:
			ArrayEntryGetSet(ai::int32 index, Array& arr) :mIndex(index), mArray(arr) {}

			void operator = (Entry entry)
			{
				//replace or insert 
				if (mArray.size() > mIndex)
					mArray.set(mIndex, entry);
				else
				{
					//Index out of range
					throw ai::Error(kBadParameterErr);
				}
			}

			operator Entry() const
			{
				return mArray.at(mIndex);
			}

		private:
			ai::int32 mIndex;
			Array& mArray;
		};

		ArrayEntryGetSet operator[](ai::int32 index)
		{
			return ArrayEntryGetSet(index, *this);
		}

		//edit
		void insert(ai::int32 index, const Entry& entry);
		
		//replace the entry at location
		void set(ai::int32 index, const Entry& entry);
		
		//remove entry at location
		void erase(ai::int32 index);

		//add an entry at the end
		void push_back(const Entry& entry);

		//Reserves space upfront,
		void reserve(ai::int32 size);

		//get ArrayRef, not recommended to use it directly
		AIArrayRef get() const;

		//iterators
		iterator begin() const;
		iterator end() const;

		//swap
		void swap(Array& other) AINOEXCEPT;

		//Move constructor and assignment
		Array(Array&& other) AINOEXCEPT;

		//Unit Test
		static void Test();
	private:
		class Impl;
		std::unique_ptr<Impl> pImpl;
	};


	class Dictionary
	{
	public:
		//iterator
		class iterator 
		{
		public:
			using value_type = std::pair<AIDictKey, Entry>;

			explicit iterator(ai::Ref<AIDictionaryIterator> dict_iter) 
				: mDictIterator(std::move(dict_iter))
			{
			}

			iterator& operator++();
			iterator operator++(int) { iterator retval = *this; ++(*this); return retval; }

			bool operator==(iterator other) const;
			bool operator!=(iterator other) const { return !(*this == other); }

			value_type operator*() const;

			void swap(iterator& other) AINOEXCEPT
			{
				mDictIterator.swap(other.mDictIterator);
			}

			iterator(const iterator&) = default;
			iterator(iterator&&) = default;
			iterator& operator = (iterator other)
			{
				swap(other);
				return *this;
			}

		private:
			ai::Ref<AIDictionaryIterator> mDictIterator;
		};

		using KeyType = AIDictKey;

		enum Type
		{
			kCreateEmpty,
			kCurrentDocument,
			kCurrentDocumentNonRecorded,
		};

		explicit Dictionary(Type type = Type::kCreateEmpty); //construct an Dictionary of specific type

		//Get ArtObject's dictionary
		explicit Dictionary(AIArtHandle art); 

		//Create a dictionary from AIDictionaryRef, 
		//increments ref count in c'tor, and decrements in d'tor
		explicit Dictionary(AIDictionaryRef dictRef);

		//required for unique_ptr
		~Dictionary(); 

		//Ref counted Copy and assignment
		Dictionary(const Dictionary& other);
		Dictionary& operator = (Dictionary other) AINOEXCEPT;

		//Deep Copy/Clone 
		Dictionary clone() const;
		void copy(const Dictionary& other);

		//get/set Unicode
		ai::UnicodeString GetUnicodeString(KeyType key) const; //throws error if not found
		AIErr GetUnicodeString(KeyType key, ai::UnicodeString& value) const AINOEXCEPT;
		void SetUnicodeString(KeyType key, const ai::UnicodeString& value);

		//get/set c string
		std::string GetString(KeyType key) const; //throws error if not found
		AIErr GetString(KeyType key, std::string& value) const AINOEXCEPT;
		void SetString(KeyType key, const std::string& value);

		//get/set real
		AIReal GetReal(KeyType key) const;
		AIErr GetReal(KeyType key, AIReal& value) const AINOEXCEPT;
		void SetReal(KeyType key, AIReal value);

		//get/set bool
		AIBoolean GetBoolean(KeyType key) const;
		AIErr GetBoolean(KeyType key, AIBoolean& value) const AINOEXCEPT;
		void SetBoolean(KeyType key, AIBoolean value);

		//get set integer
		ai::int32 GetInteger(KeyType key) const;
		AIErr GetInteger(KeyType key, ai::int32& value) const AINOEXCEPT;
		void SetInteger(KeyType key, ai::int32 value);

		//get/set pointer
		ai::intptr GetPointer(KeyType key) const;
		AIErr GetPointer(KeyType key, ai::intptr& value) const AINOEXCEPT;
		void SetPointer(KeyType key, ai::intptr value);

		//get/set binary
		using BinaryType = Entry::BinaryType;
		BinaryType GetBinary(KeyType key) const;
		AIErr GetBinary(KeyType key, BinaryType& value) const AINOEXCEPT;
		void SetBinary(KeyType key, const BinaryType& value);

		//get/set Dictionary
		Dictionary GetDictionary(KeyType key) const;
		AIErr GetDictionary(KeyType key, Dictionary& value) const AINOEXCEPT;
		void SetDictionary(KeyType key, const Dictionary& value);

		//get/set array
		Array GetArray(KeyType key) const;
		AIErr GetArray(KeyType key, Array& value) const AINOEXCEPT;
		void SetArray(KeyType key, const Array& value);

		//get/set entry
		Entry Get(KeyType key) const;
		void Set(KeyType key, const Entry& entry);

		//Helper class for operator[]
		class DictEntryGetSet
		{
		public: 
			DictEntryGetSet(KeyType key, Dictionary& dict):mKey(key), mDict(dict){}
			void operator = (Entry entry)
			{
				mDict.Set(mKey, entry);
			}

			operator Entry() const
			{
				return mDict.Get(mKey);
			}

		private:
			KeyType mKey;
			Dictionary& mDict;
		};

		DictEntryGetSet operator[](KeyType key)
		{
			return DictEntryGetSet(key, *this);
		}

		const char* GetKeyString(KeyType key) const;

		//Query
		bool IsKnown(KeyType key) const;
		AIEntryType GetEntryType(KeyType key) const;
		
		iterator find(KeyType key);

		//Deletes/erases an entry
		void erase(KeyType key);
		
		//Mark art as changed
		void TouchArt();

		//get DictionaryRef, recommended not to use it
		AIDictionaryRef get() const AINOEXCEPT;
		
		iterator begin() const;
		iterator end() const;

		//swap
		void swap(Dictionary& other) AINOEXCEPT;

		//Move constructor and assignment
		Dictionary(Dictionary&& other) AINOEXCEPT;

		//Unit Test
		static void Test();
	private:
		class Impl;
		std::unique_ptr<Impl> pImpl;
	};

	// Utility functions

	// True if a dictionary is associated with the art object, false otherwise.
	bool HasDictionary(AIArtHandle art) AINOEXCEPT;

	// True if a dictionary exists and is empty or if no dictionary exists.
	// False if a dictionary associated with the art object contains any entries.
	bool IsDictionaryEmpty(AIArtHandle art) AINOEXCEPT;
}
