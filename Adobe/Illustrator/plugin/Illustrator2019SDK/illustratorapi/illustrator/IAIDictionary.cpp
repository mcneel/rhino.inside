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

#include "IAIDictionary.hpp"

#include "AIArt.h"
#include "AIDocument.h"
#include "AIErrorHandler.h"
#include "IAIRef.h"
#include "AIAssert.hpp"
#include "AIPathStyle.h"

#include <map>
#include <sstream>
#include <cmath>

#if AI_AUTO_SUITE_AVAILABLE
	#include "AutoSuite.h"
	use_suite(AIDictionary)
	use_suite(AIArt)
	use_suite(AIDocument)
	use_suite(AIArray)
	use_suite(AIEntry)
	use_suite(AIDictionaryIterator)
#elif defined (_IAIDICTIONARY_SUITE_INCLUDE_H)
	#include _IAIDICTIONARY_SUITE_INCLUDE_H
#else
	// these need to be declared by client
	extern "C" AIDictionarySuite* sAIDictionary;
	extern "C" AIArtSuite* sAIArt;
	extern "C" AIDocumentSuite* sAIDocument;
	extern "C" AIArraySuite*	sAIArray;
	extern "C" AIEntrySuite* sAIEntry;
	extern "C" AIDictionaryIteratorSuite* sAIDictionaryIterator;
#endif

#define TEST_AI_DICTIONARY 0

#if TEST_AI_DICTIONARY
#include "AIDictionaryKeyHelper.hpp"
#if AI_AUTO_SUITE_AVAILABLE
	use_suite(AIPathStyle)
#elif defined(_IAIDICTIONARY_SUITE_INCLUDE_H)
	//don't include it again
#else
	extern "C" AIPathStyleSuite* sAIPathStyle;
#endif

namespace
{
	DictionaryKeyDeclareAndDefine(kDictTypeEntry, "Dict type entry");
	DictionaryKeyDeclareAndDefine(kBoolkey, "Dict Test Int Bool");
	DictionaryKeyDeclareAndDefine(kIntKey, "Dict Test int Key" );
	DictionaryKeyDeclareAndDefine(kStringKey, "Dict test string key" );
	DictionaryKeyDeclareAndDefine(kUnicodeStringKey, "Dict test unicode string key");
	DictionaryKeyDeclareAndDefine(kRealKey, "Dict test real key" );
	DictionaryKeyDeclareAndDefine(kPointerKey, "-Dict test pointer key" );
	DictionaryKeyDeclareAndDefine(kBinaryKey, "Dict test binary key" );
	DictionaryKeyDeclareAndDefine(kMyRealValkey2, "My real val key2");
	DictionaryKeyDeclareAndDefine(kDictKey, "Dict test Dict key");
	DictionaryKeyDeclareAndDefine(kArrayKey, "Dict test array key" );
	DictionaryKeyDeclareAndDefine(kTestNotFoundKey, "Dict test not found key");

	DictionaryKeyDeclareAndDefine(kFillStyleKey, "Dict test fill style key");
	DictionaryKeyDeclareAndDefine(kStrokeStyleKey, "Dict test stroke style key");
}
#endif

namespace
{
	template <typename T>
	T AddRef(T ref)
	{
		ai::GetAICountedObjectSuitePtr()->AddRef(ref);
		return ref;
	}

	template <typename T>
	T Release(T ref)
	{
		ai::GetAICountedObjectSuitePtr()->Release(ref);
		return ref;
	}
}

namespace ai
{
	class Entry::Impl
	{
	public:
		explicit Impl(AIEntryRef entryRef):mEntry(entryRef)
		{
		}

		explicit Impl(const Impl& other):mEntry(other.mEntry)
		{
		}

		explicit Impl(bool boolVal)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromBoolean(boolVal);
		}
		explicit Impl(ai::int32 intVal)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromInteger(intVal);
		}
		explicit Impl(AIReal realVal)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromReal(realVal);
		}
		Impl(const AIRealPoint& point)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromRealPoint(&point);
		}
		Impl(const AIRealMatrix& matrix)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromRealMatrix(&matrix);
		}
		Impl(const std::string& strVal)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromString(strVal.c_str());
		}

		Impl(const ai::UnicodeString& value)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromUnicodeString(value);
		}
		Impl(const BinaryType& value)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromBinary((void*)value.data(), value.size());
		}

		Impl(const Array& value)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromArray(value.get());
		}

		Impl(const Dictionary& value)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromDict(value.get());
		}

		Impl(const AIFillStyle& value)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromFillStyle(&value);
		}

		Impl(const AIStrokeStyle& value)
		{
			*(mEntry << ai::Replace) = sAIEntry->FromStrokeStyle(&value);
		}

		bool BoolVal() const
		{
			AIBoolean boolval(false);
			mError = sAIEntry->ToBoolean(AddRef(mEntry), &boolval);
			return (boolval != false);
		}

		ai::int32 IntVal() const
		{
			ai::int32 value(0);
			mError = sAIEntry->ToInteger(AddRef(mEntry), &value);
			return value;
		}

		AIReal RealVal() const
		{
			AIReal value{};
			mError = sAIEntry->ToReal(AddRef(mEntry), &value);
			return value;
		}

		AIRealMatrix MatrixVal() const
		{
			AIRealMatrix value{};
			mError = sAIEntry->ToRealMatrix(AddRef(mEntry), &value);
			return value;
		}

		AIRealPoint PointVal() const
		{
			AIRealPoint value{};
			mError = sAIEntry->ToRealPoint(AddRef(mEntry), &value);
			return value;
		}

		BinaryType BinaryVal() const
		{
			size_t size(0);
			mError = sAIEntry->ToBinary(AddRef(mEntry), nullptr, &size);

			BinaryType value(size);
			mError = sAIEntry->ToBinary(AddRef(mEntry), reinterpret_cast<void*>(value.data()), &size);
			return value;
		}

		std::string StringVal() const
		{
			const char* valuePtr(nullptr);
			mError = sAIEntry->ToString(AddRef(mEntry), &valuePtr);
			return std::string(valuePtr);
		}

		ai::UnicodeString UnicodeStringVal() const
		{
			ai::UnicodeString value;
			mError = sAIEntry->ToUnicodeString(AddRef(mEntry), value);
			return value;
		}

		Array ArrayVal() const
		{
			ai::Ref<AIArrayRef> arrayRef;
			mError = sAIEntry->ToArray(AddRef(mEntry), arrayRef << ai::Replace);
			return Array(arrayRef);
		}

		Dictionary DictionaryVal() const
		{
			ai::Ref<AIDictionaryRef> dictRef;
			mError = sAIEntry->ToDict(AddRef(mEntry), dictRef << ai::Replace);

			return Dictionary(dictRef);
		}

		AIEntryType GetType() const
		{
			return sAIEntry->GetType(mEntry);
		}

		AIEntryRef get() const
		{
			return mEntry.operator AIEntryRef();
		}

		ai::UnicodeString GetAsUnicodeString() const
		{
			ai::UnicodeString value;
			mError = sAIEntry->AsUnicodeString(AddRef(mEntry), value);
			return value;
		}

		bool equal(const Impl& other) const
		{
			return (sAIEntry->Equiv(mEntry, other.mEntry) != false);
		}

		AIArtHandle ArtHandleVal() const
		{
			AIArtHandle artHandle(nullptr);
			mError = sAIEntry->ToArt(AddRef(mEntry), &artHandle);
			return artHandle;
		}

		AIPatternHandle PatternVal() const
		{
			AIPatternHandle pattern(nullptr);
			mError = sAIEntry->ToPattern(AddRef(mEntry), &pattern);
			return pattern;
		}

		AIPatternHandle BrushPatternVal() const
		{
			AIPatternHandle pattern(nullptr);
			mError = sAIEntry->ToBrushPattern(AddRef(mEntry), &pattern);
			return pattern;
		}

		AIGradientHandle GradientVal() const
		{
			AIGradientHandle gradient(nullptr);
			mError = sAIEntry->ToGradient(AddRef(mEntry), &gradient);
			return gradient;
		}

		AICustomColorHandle CustomColorVal() const
		{
			AICustomColorHandle customColor(nullptr);
			mError = sAIEntry->ToCustomColor(AddRef(mEntry), &customColor);
			return customColor;
		}
		static std::unique_ptr<Impl> CreateImplConsumeRef(AIEntryRef entry)
		{
			auto entryImpl = std::make_unique<Impl>(entry);
			Release(entry); //consume ref
			return entryImpl;
		}

		static std::unique_ptr<Impl> FromPattern(AIPatternHandle pattern)
		{
			return CreateImplConsumeRef(sAIEntry->FromPattern(pattern));
		}

		static std::unique_ptr<Impl> FromGradient(AIGradientHandle gradient)
		{
			return CreateImplConsumeRef(sAIEntry->FromGradient(gradient));
		}

		static std::unique_ptr<Impl> FromCustomColor(AICustomColorHandle customColor)
		{
			return CreateImplConsumeRef(sAIEntry->FromCustomColor(customColor));
		}

		static std::unique_ptr<Impl> FromPluginObject(AIObjectHandle obj)
		{
			return CreateImplConsumeRef(sAIEntry->FromPluginObject(obj));
		}

		AIObjectHandle PluginObjectVal() const
		{
			AIObjectHandle pluginObj(nullptr);
			mError = sAIEntry->ToPluginObject(AddRef(mEntry), &pluginObj);
			return pluginObj;
		}

		std::unique_ptr<AIFillStyle> AIFillStyleVal() const
		{
			auto fillStyle = std::make_unique<AIFillStyle>();
			mError = sAIEntry->ToFillStyle(AddRef(mEntry), fillStyle.get());
			return fillStyle;
		}

		std::unique_ptr<AIStrokeStyle> AIStrokeStyleVal() const
		{
			auto strokeStyle = std::make_unique<AIStrokeStyle>();
			mError = sAIEntry->ToStrokeStyle(AddRef(mEntry), strokeStyle.get());
			return strokeStyle;
		}

		static std::unique_ptr<Impl> FromSymbolPattern(AIPatternHandle obj)
		{
			return CreateImplConsumeRef(sAIEntry->FromSymbolPattern(obj));
		}

		static std::unique_ptr<Impl> FromBrushPattern(AIPatternHandle pattern)
		{
			return CreateImplConsumeRef(sAIEntry->FromBrushPattern(pattern));
		}

		AIPatternHandle SymbolPatternVal() const
		{
			AIPatternHandle symbolPattern(nullptr);
			mError = sAIEntry->ToSymbolPattern(AddRef(mEntry), &symbolPattern);
			return symbolPattern;
		}

		static std::unique_ptr<Impl> FromArtStyle(AIArtStyleHandle artStyle)
		{
			return CreateImplConsumeRef(sAIEntry->FromArtStyle(artStyle));
		}

		AIArtStyleHandle ArtStyleVal() const
		{
			AIArtStyleHandle artStyle(nullptr);
			mError = sAIEntry->ToArtStyle(AddRef(mEntry), &artStyle);
			return artStyle;
		}

		static std::unique_ptr<Impl> FromBinary(void* data, size_t size)
		{
			return CreateImplConsumeRef(sAIEntry->FromBinary(data, size));
		}

		void BinaryVal(void *value, size_t& size) const
		{
			mError = sAIEntry->ToBinary(AddRef(mEntry), value, &size);
		}


	private:
		ai::Ref<AIEntryRef> mEntry;
		mutable AIErrorThrower mError;
	};


	AIEntryRef Entry::get() const
	{
		return pImpl->get();
	}

	bool Entry::operator==(const Entry& other) const
	{
		return pImpl->equal(*other.pImpl);
	}

	ai::UnicodeString Entry::GetAsUnicodeString() const
	{
		return pImpl->GetAsUnicodeString();
	}

	void Entry::swap(Entry& other) AINOEXCEPT
	{
		std::swap(pImpl, other.pImpl);
	}

	Entry::Entry(AIEntryRef entryRef) :pImpl(std::make_unique<Impl>(entryRef))
	{

	}

	Entry::Entry(bool boolVal) : pImpl(std::make_unique<Impl>(boolVal))
	{

	}

	Entry::Entry(ai::int32 intVal) : pImpl(std::make_unique<Impl>(intVal))
	{

	}

	Entry::Entry(AIReal realVal) : pImpl(std::make_unique<Impl>(realVal))
	{

	}

	Entry::Entry(const AIRealPoint& point) : pImpl(std::make_unique<Impl>(point))
	{

	}

	Entry::Entry(const AIRealMatrix& matrix) : pImpl(std::make_unique<Impl>(matrix))
	{

	}

	Entry::Entry(const std::string& strVal) : pImpl(std::make_unique<Impl>(strVal))
	{

	}

	Entry::Entry(const ai::UnicodeString& value) : pImpl(std::make_unique<Impl>(value))
	{

	}

	Entry::Entry(const BinaryType& value) : pImpl(std::make_unique<Impl>(value))
	{

	}

	Entry::Entry(const Array& value) : pImpl(std::make_unique<Impl>(value))
	{

	}

	Entry::Entry(const Dictionary& value) : pImpl(std::make_unique<Impl>(value))
	{

	}

	Entry::Entry(Entry&& other) AINOEXCEPT
	{
		swap(other);
	}

	Entry::Entry(const Entry& other) :pImpl(std::make_unique<Impl>(*(other.pImpl)))
	{

	}


	Entry::Entry(std::unique_ptr<Impl>&& impl)
	{
		std::swap(pImpl, impl);
	}

	Entry::Entry(const AIFillStyle& value):pImpl(std::make_unique<Impl>(value))
	{

	}

	Entry::Entry(const AIStrokeStyle& value):pImpl(std::make_unique<Impl>(value))
	{

	}

	Entry Entry::FromPattern(AIPatternHandle pattern)
	{
		return Entry(Impl::FromPattern(pattern));
	}

	Entry Entry::FromBrushPattern(AIPatternHandle pattern)
	{
		return Entry(Impl::FromBrushPattern(pattern));
	}

	Entry Entry::FromGradient(AIGradientHandle gradient)
	{
		return Entry(Impl::FromGradient(gradient));
	}

	Entry Entry::FromCustomColor(AICustomColorHandle customColor)
	{
		return Entry(Impl::FromCustomColor(customColor));
	}

	Entry Entry::FromPluginObject(AIObjectHandle obj)
	{
		return Entry(Impl::FromPluginObject(obj));
	}

	Entry Entry::FromSymbolPattern(AIPatternHandle symbolPattern)
	{
		return Entry(Impl::FromSymbolPattern(symbolPattern));
	}

	Entry Entry::FromArtStyle(AIArtStyleHandle artStyle)
	{
		return Entry(Impl::FromArtStyle(artStyle));
	}

	Entry Entry::FromBinary(void* data, size_t size)
	{
		return Entry(Impl::FromBinary(data, size));
	}

	Entry& Entry::operator = (Entry other) AINOEXCEPT
	{
		swap(other);
		return *this;
	}

	bool Entry::BoolVal() const
	{
		return pImpl->BoolVal();
	}

	ai::int32 Entry::IntVal() const
	{
		return pImpl->IntVal();
	}

	AIReal Entry::RealVal() const
	{
		return pImpl->RealVal();
	}

	AIRealMatrix Entry::MatrixVal() const
	{
		return pImpl->MatrixVal();
	}

	AIRealPoint Entry::PointVal() const
	{
		return pImpl->PointVal();
	}

	Entry::BinaryType Entry::BinaryVal() const
	{
		return pImpl->BinaryVal();
	}

	std::string Entry::StringVal() const
	{
		return pImpl->StringVal();
	}

	ai::UnicodeString Entry::UnicodeStringVal() const
	{
		return pImpl->UnicodeStringVal();
	}

	AIArtHandle Entry::ArtHandleVal() const
	{
		return pImpl->ArtHandleVal();
	}

	AIPatternHandle Entry::PatternVal() const
	{
		return pImpl->PatternVal();
	}

	AIPatternHandle Entry::BrushPatternVal() const
	{
		return pImpl->BrushPatternVal();
	}

	AIGradientHandle Entry::GradientVal() const
	{
		return pImpl->GradientVal();
	}

	AICustomColorHandle Entry::CustomColorVal() const
	{
		return pImpl->CustomColorVal();
	}

	AIObjectHandle Entry::PluginObjectVal() const
	{
		return pImpl->PluginObjectVal();
	}

	AIPatternHandle Entry::SymbolPatternVal() const
	{
		return pImpl->SymbolPatternVal();
	}

	std::unique_ptr<AIFillStyle> Entry::FillStyleVal() const
	{
		return pImpl->AIFillStyleVal();
	}

	std::unique_ptr<AIStrokeStyle> Entry::StrokeStyleVal() const
	{
		return pImpl->AIStrokeStyleVal();
	}

	AIArtStyleHandle Entry::ArtStyleVal() const
	{
		return pImpl->ArtStyleVal();
	}

	Array Entry::ArrayVal() const
	{
		return pImpl->ArrayVal();
	}

	Entry::operator Array() const
	{
		return ArrayVal();
	}

	Dictionary Entry::DictionaryVal() const
	{
		return pImpl->DictionaryVal();
	}

	Entry::operator Dictionary() const
	{
		return DictionaryVal();
	}

	AIEntryType Entry::GetType() const
	{
		return pImpl->GetType();
	}

	void Entry::BinaryVal(void *value, size_t& size) const
	{
		return pImpl->BinaryVal(value, size);
	}

	Entry::~Entry()
	{

	}

	class Array::Impl
	{
	public:
		Impl()
		{
			mError = sAIArray->CreateArray(mArray << ai::Replace);
		}

		Impl(AIArrayRef arrayRef)
		{
			mArray = arrayRef;
		}

		Impl(const Impl& other)
		{
			mArray = other.mArray;
		}

		ai::int32 size() const
		{
			return sAIArray->Size(mArray);
		}

		AIArrayRef get() const
		{
			return mArray;
		}

		Entry at(ai::int32 index) const
		{
			Entry toReturn(sAIArray->Get(mArray, index));
			Release(toReturn.get());
			return toReturn;
		}

		//edit
		void set(ai::int32 index, const Entry& entry)
		{
			mError = sAIArray->Set(mArray, index, AddRef(entry.get()));
		}

		void erase(ai::int32 index)
		{
			mError = sAIArray->DeleteEntry(mArray, index);
		}

		void push_back(const Entry& entry)
		{
			mError = sAIArray->AppendEntry(mArray, AddRef(entry.get()));
		}

		void reserve(ai::int32 size)
		{
			mError = sAIArray->Reserve(mArray, size);
		}

		void insert(ai::int32 index, const Entry& entry)
		{
			mError = sAIArray->InsertEntry(mArray, index);
			set(index, entry);
		}

		void copy(const Impl& other)
		{
			mError = sAIArray->Copy(mArray, other.get());
		}

		Array clone() const
		{
			ai::Ref<AIArrayRef> clonedArray;
			mError = sAIArray->Clone(mArray, clonedArray << ai::Replace);
			return Array(clonedArray);
		}

	private:
		ai::Ref<AIArrayRef> mArray;
		mutable AIErrorThrower mError;
	};

	Array::Array() :pImpl(std::make_unique<Impl>())
	{

	}

	Array::Array(AIArrayRef arrrayRef) : pImpl(std::make_unique<Impl>(arrrayRef))
	{

	}

	Array::Array(const Array& other) : pImpl(std::make_unique<Impl>(*other.pImpl))
	{

	}

	Array Array::clone() const
	{
		return pImpl->clone();
	}

	void Array::copy(const Array& other)
	{
		pImpl->copy(*other.pImpl);
	}

	Array& Array::operator = (Array other) AINOEXCEPT
	{
		swap(other);
		return *this;
	}

	Array::Array(Array&& other) AINOEXCEPT
	{
		swap(other);
	}

	void Array::Test()
	{
#if TEST_AI_DICTIONARY
		//Test Array
		Array myArray;

		ai::int32 intVal(20);
		bool boolVal(true);
		std::string strVal("My Simple String");
		ASUnicode unicodePoints[] = { 2423,354,3434,343,344,0 };
		ai::UnicodeString ustrval(unicodePoints);

		myArray.reserve(4);

		myArray.insert(0, Entry(intVal));
		myArray.insert(1, Entry(boolVal));
		
		//replace Entry at index value
		boolVal = false;
		myArray[1] = Entry(boolVal);
		
		myArray.insert(2, Entry(strVal));
		myArray.insert(3, Entry(ustrval));
		myArray.insert(4, ai::UnicodeString("New Unicode String",kAIRomanCharacterEncoding));

		auto size = myArray.size();
		if (size != 5)
		{
			AIMsgAssert(false, "Size returned wrong value!");
		}

		//Get Unicode string at 3rd index
		ai::UnicodeString getUstrVal = ai::Entry(myArray[3]);
		if (ustrval != getUstrVal)
		{
			AIMsgAssert(false, "Wrong Unicode String Value!");
		}

		//Get string at 2nd index
		std::string getStrVal = ai::Entry(myArray[2]);

		if (strVal != getStrVal)
		{
			AIMsgAssert(false, "Wrong String value!");
		}

		if (boolVal != myArray.at(1).BoolVal())
		{
			AIMsgAssert(false, "Wrong Bool value!");
		}

		//Get value by explicit By Function Value calls
		auto getIntVal = ai::Entry(myArray[0]).IntVal();
		if (intVal != getIntVal)
		{
			AIMsgAssert(false, "Wrong Integer value!");
		}

		myArray.erase(0);
		if (myArray.size() != 4)
		{
			AIMsgAssert(false, "Didn't erase array properly!");
		}

		ai::int32 reserveSize(10);
		myArray.reserve(reserveSize);
		
		myArray.push_back(Entry(AIRealPoint{ 20., 30. }));

		Dictionary dict;
		dict.SetBoolean(kDictTypeEntry, true);
		myArray.push_back(Entry(dict));

		//test range loop
		std::ostringstream ostr;
		for (auto entry : myArray)
		{
			auto type = entry.GetType();
			ostr << entry.GetType() << "-";
			switch (type)
			{
			case IntegerType:
			case BooleanType:
			case RealType:
			case StringType:
			case UnicodeStringType:
				ostr << entry.GetAsUnicodeString().as_UTF8() ;
				break;
			default:
				ostr << " Missing";
			}
			ostr << ", ";
			
		}

		auto types = ostr.str();
		if (types.empty())
		{
			AIMsgAssert(false, "Can't get types from array entries!");
		}
#endif //TEST_AI_DICTIONARY
	}

	ai::int32 Array::size() const AINOEXCEPT
	{
		return pImpl->size();
	}

	Entry Array::at(ai::int32 index) const
	{
		return pImpl->at(index);
	}

	void Array::insert(ai::int32 index, const Entry& entry)
	{
		pImpl->insert(index, entry);
	}
	
	void Array::set(ai::int32 index, const Entry& entry)
	{
		pImpl->set(index, entry);
	}

	void Array::erase(ai::int32 index)
	{
		pImpl->erase(index);
	}

	void Array::push_back(const Entry& entry)
	{
		pImpl->push_back(entry);
	}

	void Array::reserve(ai::int32 size)
	{
		pImpl->reserve(size);
	}

	AIArrayRef Array::get() const
	{
		return pImpl->get();
	}

	Array::iterator Array::begin() const
	{
		auto arraySize = size();
		auto beginIndex = (arraySize > 0 ? 0 : arraySize);
		return iterator(beginIndex, *this);
	}

	Array::iterator Array::end() const
	{
		return iterator(size(), *this);
	}

	void Array::swap(Array& other) AINOEXCEPT
	{
		std::swap(pImpl, other.pImpl);
	}

	Array::~Array()
	{

	}

	class Dictionary::Impl
	{
	private:
		mutable AIErrorThrower mError;
		ai::Ref<AIDictionaryRef> mDict;

	public:
		Impl(Dictionary::Type type);
		explicit Impl(AIDictionaryRef dictRef);
		Impl(const Impl& other);

		explicit Impl(AIArtHandle art);

		ai::UnicodeString GetUnicodeString(Dictionary::KeyType key) const
		{
			ai::UnicodeString value;
			mError = GetUnicodeString(key, value);
			return value;
		}

		AIErr GetUnicodeString(Dictionary::KeyType key, ai::UnicodeString& value) const AINOEXCEPT
		{
			//don't throw, return error
			return sAIDictionary->GetUnicodeStringEntry(mDict, key, value);
		}

		void SetUnicodeString(Dictionary::KeyType key, const ai::UnicodeString& value) 
		{
			mError = sAIDictionary->SetUnicodeStringEntry(mDict, key, value);
		}

		std::string GetString(Dictionary::KeyType key) const
		{
			std::string value;
			mError = GetString(key, value);
			return value;
		}

		AIErr GetString(Dictionary::KeyType key, std::string& strValue) const AINOEXCEPT
		{
			const char* value{ nullptr };
			AIErr err = sAIDictionary->GetStringEntry(mDict, key, &value);
			if (!err)
			{
				strValue = std::string(value);
			}
			return err;
		}

		void SetString(Dictionary::KeyType key, const std::string& value)
		{
			mError = sAIDictionary->SetStringEntry(mDict, key, value.c_str());
		}

		AIReal GetReal(Dictionary::KeyType key) const
		{
			AIReal value(kAIRealZero);
			mError = GetReal(key, value);
			return value;
		}

		AIErr GetReal(Dictionary::KeyType key, AIReal& value) const AINOEXCEPT
		{
			return sAIDictionary->GetRealEntry(mDict, key, &value);
		}

		void SetReal(Dictionary::KeyType key, AIReal value)
		{
			mError = sAIDictionary->SetRealEntry(mDict, key, value);
		}

		AIBoolean GetBoolean(Dictionary::KeyType key) const
		{
			AIBoolean value(false);
			mError = GetBoolean(key, value);
			return value;
		}

		AIErr GetBoolean(Dictionary::KeyType key, AIBoolean& value) const AINOEXCEPT
		{
			return sAIDictionary->GetBooleanEntry(mDict, key, &value);
		}

		void SetBoolean(Dictionary::KeyType key, AIBoolean value) const
		{
			mError = sAIDictionary->SetBooleanEntry(mDict, key, value);
		}

		ai::int32 GetInteger(Dictionary::KeyType key) const
		{
			ai::int32 value(false);
			mError = GetInteger(key, value);
			return value;
		}

		AIErr GetInteger(Dictionary::KeyType key, ai::int32& value) const AINOEXCEPT
		{
			return sAIDictionary->GetIntegerEntry(mDict, key, &value);
		}

		void SetInteger(Dictionary::KeyType key, ai::int32 value) const
		{
			mError = sAIDictionary->SetIntegerEntry(mDict, key, value);
		}

		ai::intptr GetPointer(Dictionary::KeyType key) const
		{
			ai::intptr value(false);
			mError = GetPointer(key, value);
			return value;
		}

		AIErr GetPointer(Dictionary::KeyType key, ai::intptr& value) const AINOEXCEPT
		{
			return sAIDictionary->GetPointerEntry(mDict, key, &value);
		}

		void SetPointer(Dictionary::KeyType key, ai::intptr value) const
		{
			mError = sAIDictionary->SetPointerEntry(mDict, key, value);
		}

		Dictionary::BinaryType GetBinary(Dictionary::KeyType key) const
		{
			Dictionary::BinaryType value;
			mError = GetBinary(key, value);
			return value;
		}

		AIErr GetBinary(Dictionary::KeyType key, Dictionary::BinaryType& value) const AINOEXCEPT
		{
			//Get size first
			size_t size(0);
			AIErr err = sAIDictionary->GetBinaryEntry(mDict, key, nullptr, &size);
			if (err)
				return err;

			value.resize(size);
			err = sAIDictionary->GetBinaryEntry(mDict, key, value.data(), &size);
			return err;
		}

		void SetBinary(Dictionary::KeyType key, const Dictionary::BinaryType& value) const
		{
			mError = sAIDictionary->SetBinaryEntry(mDict, key, 
				(void*)(value.data()), value.size());
		}

		Dictionary GetDictionary(Dictionary::KeyType key) const
		{
			Dictionary dict(Dictionary::Type::kCreateEmpty);
			mError = GetDictionary(key, dict);
			return dict;
		}

		AIErr GetDictionary(Dictionary::KeyType key, Dictionary& value) const AINOEXCEPT
		{
			ai::Ref<AIDictionaryRef> dictRef;
			AIErr err = sAIDictionary->GetDictEntry(mDict, key, dictRef << ai::Replace);
			if (!err)
			{
				value = Dictionary(dictRef);
			}
			return err;
		}

		void SetDictionary(Dictionary::KeyType key, const Dictionary& value)
		{
			mError = sAIDictionary->SetDictEntry(mDict, key, value.get());
		}

		AIDictionaryRef get() const AINOEXCEPT
		{
			return mDict;
		}

		bool IsKnown(Dictionary::KeyType key) const
		{
			return (sAIDictionary->IsKnown(mDict, key) != false);
		}

		void DeleteEntry(Dictionary::KeyType key)
		{
			mError = sAIDictionary->DeleteEntry(mDict, key);
		}

		AIEntryType GetEntryType(Dictionary::KeyType key) const
		{
			AIEntryType entryType(UnknownType);
			mError = sAIDictionary->GetEntryType(mDict, key, &entryType);
			return entryType;
		}

		Array GetArray(KeyType key) const
		{
			Array arr;
			mError = GetArray(key, arr);
			return arr;
		}

		AIErr GetArray(KeyType key, Array& value) const AINOEXCEPT
		{
			ai::Ref<AIArrayRef> arrayRef;
			AIErr err = sAIDictionary->GetArrayEntry(mDict, key, arrayRef << ai::Replace);
			if (!err)
			{
				value = Array(arrayRef);
			}
			return err;
		}

		void SetArray(KeyType key, const Array& value) const
		{
			mError = sAIDictionary->SetArrayEntry(mDict, key, value.get());
		}

		Entry Get(KeyType dictKey) const
		{
			Entry entry(sAIDictionary->Get(mDict, dictKey));
			Release(entry.get());
			return entry;
		}

		void Set(KeyType dictKey, const Entry& entry)
		{
			mError = sAIDictionary->Set(mDict, dictKey, AddRef(entry.get()));
		}

		void copy(const Impl& other) const
		{
			//Copy into self
			mError = sAIDictionary->Copy(mDict, other.mDict);
		}

		Dictionary clone() const
		{
			ai::Ref<AIDictionaryRef> clonedRef;
			mError = sAIDictionary->Clone(mDict, clonedRef << ai::Replace);
			return Dictionary(clonedRef);
		}

		void TouchArt() 
		{
			mError = sAIDictionary->TouchArt(mDict);
		}

		const char* GetKeyString(AIDictKey dictKey) const
		{
			return sAIDictionary->GetKeyString(dictKey);
		}

	};

	Dictionary::Impl::Impl(Dictionary::Type type)
	{
		switch (type)
		{
		case Dictionary::Type::kCreateEmpty:
			mError = sAIDictionary->CreateDictionary(mDict << ai::Replace);
			break;
		case Dictionary::Type::kCurrentDocument:
			mError = sAIDocument->GetDictionary(mDict << ai::Replace);
			break;
		case Dictionary::Type::kCurrentDocumentNonRecorded:
			mError = sAIDocument->GetNonRecordedDictionary(mDict << ai::Replace);
			break;
		}
	}

	Dictionary::Impl::Impl(AIArtHandle art)
	{
		mError = sAIArt->GetDictionary(art, mDict << ai::Replace);
	}

	Dictionary::Impl::Impl(AIDictionaryRef dictRef)
	{
		mDict = dictRef;
	}

	Dictionary::Impl::Impl(const Impl& other)
	{
		mDict = other.mDict;
	}

	Dictionary::iterator& Dictionary::iterator::operator++()
	{
		if (mDictIterator)
		{
			sAIDictionaryIterator->Next(mDictIterator);
			if (sAIDictionaryIterator->AtEnd(mDictIterator))
			{
				mDictIterator = ai::Ref<AIDictionaryIterator>();
			}
		}
		return *this;
	}
	
	bool Dictionary::iterator::operator==(Dictionary::iterator other) const
	{
		if (mDictIterator && other.mDictIterator)
		{
			return (sAIDictionaryIterator->IsEqual(mDictIterator, other.mDictIterator)) != false;
		}
		
		if (!mDictIterator && !other.mDictIterator)
		{
			return true;
		}

		return false;
	}

	Dictionary::iterator::value_type Dictionary::iterator::operator*() const
	{
		auto key = sAIDictionaryIterator->GetKey(mDictIterator);
		Entry entry (sAIDictionaryIterator->GetEntry(mDictIterator));
		Release(entry.get());//consume the reference
		return std::make_pair(key, entry);
	}

	void Dictionary::swap(Dictionary& other) AINOEXCEPT
	{
		std::swap(pImpl, other.pImpl);
	}

	Dictionary::Dictionary(Type type) :pImpl(std::make_unique<Impl>(type))
	{

	}

	Dictionary::Dictionary(AIArtHandle art):pImpl(std::make_unique<Impl>(art))
	{

	}

	Dictionary::Dictionary(AIDictionaryRef dictRef):pImpl(std::make_unique<Impl>(dictRef))
	{

	}

	Dictionary::Dictionary(Dictionary&& other) AINOEXCEPT
	{
		swap(other);
	}

	Dictionary::Dictionary(const Dictionary& other):pImpl(std::make_unique<Impl>(*other.pImpl))
	{

	}

	Dictionary Dictionary::clone() const
	{
		return pImpl->clone();
	}

	void Dictionary::copy(const Dictionary& other)
	{
		pImpl->copy(*other.pImpl);
	}

	Dictionary& Dictionary::operator=(Dictionary other) AINOEXCEPT
	{
		swap(other);
		return *this;
	}

	Dictionary::~Dictionary()
	{

	}

	ai::UnicodeString Dictionary::GetUnicodeString(Dictionary::KeyType key) const
	{
		return pImpl->GetUnicodeString(key);
	}

	AIErr Dictionary::GetUnicodeString(Dictionary::KeyType key, ai::UnicodeString& value) const AINOEXCEPT
	{
		return pImpl->GetUnicodeString(key, value);
	}

	void Dictionary::SetUnicodeString(Dictionary::KeyType key, const ai::UnicodeString& value)
	{
		pImpl->SetUnicodeString(key, value);
	}

	std::string Dictionary::GetString(Dictionary::KeyType key) const
	{
		return pImpl->GetString(key);
	}

	AIErr Dictionary::GetString(Dictionary::KeyType key, std::string& value) const AINOEXCEPT
	{
		return pImpl->GetString(key, value);
	}

	void Dictionary::SetString(Dictionary::KeyType key, const std::string& value)
	{
		pImpl->SetString(key, value);
	}

	AIReal Dictionary::GetReal(Dictionary::KeyType key) const
	{
		return pImpl->GetReal(key);
	}

	AIErr Dictionary::GetReal(Dictionary::KeyType key, AIReal& value) const AINOEXCEPT
	{
		return pImpl->GetReal(key, value);
	}

	void Dictionary::SetReal(Dictionary::KeyType key, AIReal value)
	{
		pImpl->SetReal(key, value);
	}

	AIBoolean Dictionary::GetBoolean(Dictionary::KeyType key) const
	{
		return pImpl->GetBoolean(key);
	}

	AIErr Dictionary::GetBoolean(Dictionary::KeyType key, AIBoolean& value) const AINOEXCEPT
	{
		return pImpl->GetBoolean(key, value);
	}

	void Dictionary::SetBoolean(Dictionary::KeyType key, AIBoolean value)
	{
		pImpl->SetBoolean(key, value);
	}

	ai::int32 Dictionary::GetInteger(Dictionary::KeyType key) const
	{
		return pImpl->GetInteger(key);
	}

	AIErr Dictionary::GetInteger(Dictionary::KeyType key, ai::int32& value) const AINOEXCEPT
	{
		return pImpl->GetInteger(key, value);
	}

	void Dictionary::SetInteger(Dictionary::KeyType key, ai::int32 value)
	{
		pImpl->SetInteger(key, value);
	}

	ai::intptr Dictionary::GetPointer(Dictionary::KeyType key) const
	{
		return pImpl->GetPointer(key);
	}

	AIErr Dictionary::GetPointer(Dictionary::KeyType key, ai::intptr& value) const AINOEXCEPT
	{
		return pImpl->GetPointer(key, value);
	}

	void Dictionary::SetPointer(Dictionary::KeyType key, ai::intptr value)
	{
		pImpl->SetPointer(key, value);
	}

	Dictionary::BinaryType Dictionary::GetBinary(Dictionary::KeyType key) const
	{
		return pImpl->GetBinary(key);
	}

	AIErr Dictionary::GetBinary(Dictionary::KeyType key, BinaryType& value) const AINOEXCEPT
	{
		return pImpl->GetBinary(key, value);
	}

	void Dictionary::SetBinary(Dictionary::KeyType key, const BinaryType& value)
	{
		pImpl->SetBinary(key, value);
	}

	Dictionary Dictionary::GetDictionary(Dictionary::KeyType key) const
	{
		return pImpl->GetDictionary(key);
	}

	AIErr Dictionary::GetDictionary(Dictionary::KeyType key, Dictionary& value) const AINOEXCEPT
	{
		return pImpl->GetDictionary(key, value);
	}

	void Dictionary::SetDictionary(Dictionary::KeyType key, const Dictionary& value)
	{
		pImpl->SetDictionary(key, value);
	}

	Array Dictionary::GetArray(KeyType key) const
	{
		return pImpl->GetArray(key);
	}

	AIErr Dictionary::GetArray(KeyType key, Array& value) const AINOEXCEPT
	{
		return pImpl->GetArray(key, value);
	}

	void Dictionary::SetArray(KeyType key, const Array& value)
	{
		pImpl->SetArray(key, value);
	}

	Entry Dictionary::Get(KeyType key) const
	{
		return pImpl->Get(key);
	}

	void Dictionary::Set(KeyType key, const Entry& entry)
	{
		pImpl->Set(key, entry);
	}

	const char* Dictionary::GetKeyString(KeyType dictKey) const
	{
		return pImpl->GetKeyString(dictKey);
	}

	bool Dictionary::IsKnown(Dictionary::KeyType key) const
	{
		return pImpl->IsKnown(key);
	}

	AIEntryType Dictionary::GetEntryType(Dictionary::KeyType key) const
	{
		return pImpl->GetEntryType(key);
	}

	ai::Dictionary::iterator Dictionary::find(KeyType key)
	{
		ai::Ref<AIDictionaryIterator> iterRef;
		AIErr err = sAIDictionary->Find(get(), key, iterRef << ai::Replace);
		if (err || !iterRef)
		{
			//return end iterator
			return end();
		}
		return iterator(std::move(iterRef));
	}

	void Dictionary::erase(Dictionary::KeyType key)
	{
		pImpl->DeleteEntry(key);
	}

	void Dictionary::TouchArt()
	{
		pImpl->TouchArt();
	}

	AIDictionaryRef Dictionary::get() const AINOEXCEPT
	{
		return pImpl->get();
	}

	Dictionary::iterator Dictionary::begin() const
	{
		ai::Ref<AIDictionaryIterator> iterRef;
		AIErr err = sAIDictionary->Begin(get(), iterRef << ai::Replace);
		if (err || !iterRef || sAIDictionaryIterator->AtEnd(iterRef) )
		{
			return end();
		}
		return iterator(std::move(iterRef));
	}

	Dictionary::iterator Dictionary::end() const
	{
		ai::Ref<AIDictionaryIterator> iterRef;
		return iterator(std::move(iterRef));
	}

	void Dictionary::Test()
	{
#if TEST_AI_DICTIONARY
		try
		{
			//Test array first
			Array::Test();

			Dictionary dict(Dictionary::Type::kCurrentDocumentNonRecorded);

			//test bool
			AIBoolean boolVal(true);
			dict.SetBoolean(kBoolkey, boolVal);
			if (dict.GetBoolean(kBoolkey) != boolVal)
			{
				//Failure
				AIMsgAssert(false, "Dictionary Bool test failed");
			}

			//test int
			ai::int32 intval(2567);
			dict.SetInteger(kIntKey, intval);
			if (intval != dict.GetInteger(kIntKey))
			{
				//Failure
				AIMsgAssert(false, "Dictionary Int test failed");
			}

			//test string
			std::string strval("Automatic string type detected.");
			dict.Set(kStringKey, strval);
			if (strval.compare(dict.Get(kStringKey)) != 0)
			{
				//Failure
				AIMsgAssert(false, "Dictionary String test failed");
			}

			//test Unicode String
			ASUnicode unicodeArray[] = { 3453, 2353, 232, 114, 0 };
			ai::UnicodeString ustrval(unicodeArray);
			dict.SetUnicodeString(kUnicodeStringKey, ustrval);
			if (ustrval.compare(dict.GetUnicodeString(kUnicodeStringKey)) != 0)
			{
				//Failure
				AIMsgAssert(false, "Dictionary Unicode String test failed");
			}

			//test real
			AIReal realval = 4556.3434;
			constexpr AIReal kEpsilon = 1e-10;
			dict.SetReal(kRealKey, realval);
			if (std::fabs(realval - dict.GetReal(kRealKey)) > kEpsilon)
			{
				//Failure
				AIMsgAssert(false, "Dictionary Real test failed");
			}

			//test pointer
#ifdef AS_X86_64
			ai::intptr ptrval = 0x1234567812345678;
#else
			ai::intptr ptrval = 0x12345678;
#endif
			dict.SetPointer(kPointerKey, ptrval);
			if (ptrval != dict.GetPointer(kPointerKey))
			{
				//Failure
				AIMsgAssert(false, "Dictionary Pointer test failed");
			}

			//test binary
			Dictionary::BinaryType value{ 3,5,67,2,4,4,6,3 };
			dict.SetBinary(kBinaryKey, value);
			if (value != dict.GetBinary(kBinaryKey))
			{
				//Failure
				AIMsgAssert(false, "Dictionary Binary test failed");
			}

			//test [] operator 
			AIReal realval2 = 20.456;
			dict[kMyRealValkey2] = ai::Entry(realval2);
			AIReal realVal2received = ai::Entry(dict[kMyRealValkey2]);
			if (std::fabs(realval2 - realVal2received) > kEpsilon)
			{
				AIMsgAssert(false, "Operator [] didn't return correct value!");
			}

			//test dictionary
			Dictionary child_dict(Dictionary::Type::kEmpty);
			ai::int32 childIntVal(25);
			child_dict.SetInteger(kIntKey, childIntVal);

			dict.SetDictionary(kDictKey, child_dict);
			Dictionary new_child_dict = dict.GetDictionary(kDictKey);
			if (new_child_dict.GetInteger(kIntKey) != childIntVal)
			{
				//Failure
				AIMsgAssert(false, "Failure in child dictionary!");
			}

			//test array key
			Array arr;
			arr.push_back(Entry(intval));
			
			dict.SetArray(kArrayKey, arr);
			Array getArr = dict.Get(kArrayKey);
			
			ai::int32 getIntVal = ai::Entry(getArr[0]);
			if (getIntVal != intval)
			{
				AIMsgAssert(false, "Failure in child array!");
			}

			//test find
			auto it = dict.find(kMyRealValkey2);
			if (it != dict.end())
			{
				AIReal realValFound = (*it).second;
				if (std::fabs(realval2 - realValFound) > kEpsilon)
				{
					AIMsgAssert(false, "Value found by find() is not correct!");
				}
			}
			else
			{
				AIMsgAssert(false, "Couldn't find the expected key!");
			}

			auto it2 = dict.find(kTestNotFoundKey);//try to find an invalid key
			if (it2 != dict.end())
			{
				AIMsgAssert(false, "Shouldn't have found this key!");
			}

			//test fill style
			AIPathStyle pathStyle;
			AIPathStyleMap pathStyleMap;
			AIErr err = sAIPathStyle->GetCurrentPathStyle(&pathStyle, &pathStyleMap, nullptr, nullptr);
			if (!err)
			{
				dict[kFillStyleKey] = pathStyle.fill;
				dict[kStrokeStyleKey] = pathStyle.stroke;

				//get fill and stroke style
				auto fillStyle = ai::Entry(dict[kFillStyleKey]).FillStyleVal();
				if (fillStyle->color.kind != pathStyle.fill.color.kind)
				{
					AIMsgAssert(false, "Coundn't set/get fill style properly!");
				}

				auto strokeStyle = ai::Entry(dict[kStrokeStyleKey]).StrokeStyleVal();
				if(strokeStyle->color.kind != pathStyle.stroke.color.kind)
				{
					AIMsgAssert(false, "Coundn't set/get stroke style properly!");
				}
			}

			//range loop
			std::ostringstream ostr;
			for (auto entry : dict)
			{
				ostr << dict.GetKeyString(entry.first) << "-";
				auto type = entry.second.GetType();
				ostr << type << "-";

				switch (type)
				{
				case IntegerType:
				case BooleanType:
				case RealType:
				case StringType:
				case UnicodeStringType:
					ostr << entry.second.GetAsUnicodeString().as_UTF8();
					break;
				default:
					ostr << " Missing";
				}
			}
			auto strVal = ostr.str();
			if (strval.empty())
			{
				AIMsgAssert(false, "Error in getting values via range loop!");
			}
		}
		catch (const ai::Error& /*error*/)
		{
			AIMsgAssert(false, "An Error in Dictionary Test!");
		}
		catch (...)
		{
			AIMsgAssert(false, "Unknown Exception in Dictionary Test!");
		}
#endif //TEST_AI_DICTIONARY
	}

	bool HasDictionary(AIArtHandle art) AINOEXCEPT
	{
		return !!sAIArt->HasDictionary(art);
	}

	bool IsDictionaryEmpty(AIArtHandle art) AINOEXCEPT
	{
		return !!sAIArt->IsDictionaryEmpty(art);
	}

} //ai namespace

