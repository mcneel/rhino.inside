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

#include "AITypes.h"
#include "AIAssert.hpp"
#include "IAILiteralString.h"

/**
	Usage:

	struct Widget 
	{
		ai::int32 id = -1;
		bool processed = false;
		std::string name;
	};

	std::unique_ptr<Widget> CreateWidget();

	void ProcessWidget()
	{
		auto widget1 = CreateWidget();
		auto widget2 = CreateWidget();

		ai::Expects(widget1 != nullptr); // Throws by default

		ai::Expects(widget2 != nullptr, "Widget should not be NULL"); // Throws with custom message

		ai::Expects(widget1->id != -1, "Wrong widget id", ai::ContractPolicy::kAssert); // Only Assert

		ai::Expects(!widget1->name.empty(), "Wrong widget name", ai::ContractPolicy::kAssert); // Only Assert

		// ...
		// ...

		ai::Ensures(widget1->processed == true, "Widget should be processed", ai::ContractPolicy::kAssertAndThrow); // Assert and Throw

		ai::Ensures(widget2->processed == true, ai::ContractPolicy::kAssertAndThrow); // Assert and Throw
	}
*/

namespace ai
{
	namespace Contract
	{
		constexpr ai::LiteralString kDefaultPreconditionMsg {"Failed Precondition"};
		constexpr ai::LiteralString kDefaultPostconditionMsg {"Failed Postcondition"};

		/**
			Exception class for Contract violation
		*/
		struct Violation : public ai::LogicError
		{
			explicit Violation(const char* message) : ai::LogicError(kBadParameterErr, message)
			{
			}
		};
		
		/**
			Contract policy types
		*/
		struct AssertPolicy {};
		struct ThrowPolicy {};
		struct AssertAndThrowPolicy {};

		/**
			Contract verification
		*/
		template <typename T> /* Assert */
		inline void Check(T condition, const char* msg, AssertPolicy)
		{
			AIMsgAssert(condition, msg);
		}

		template <typename T> /* Throw */
		inline void Check(T condition, const char* msg, ThrowPolicy)
		{
			if (!condition)
			{
				throw Violation{msg};
			}
		}

		template <typename T> /* Assert and Throw */
		inline void Check(T condition, const char* msg, AssertAndThrowPolicy)
		{
			if (!condition)
			{
				AIMsgAssert(false, msg);
				throw Violation{msg};
			}
		}

	} // namespace Contract

	namespace ContractPolicy
	{
		// Instances of the Contract policy types
		constexpr Contract::AssertPolicy			kAssert {};
		constexpr Contract::ThrowPolicy				kThrow {};
		constexpr Contract::AssertAndThrowPolicy	kAssertAndThrow {};

	} // namespace ContractPolicy

	template <typename T, typename Policy = Contract::ThrowPolicy>
	inline void Expects(T condition, const char* msg = Contract::kDefaultPreconditionMsg, Policy policy = ContractPolicy::kThrow)
	{
		Contract::Check(condition, msg, policy);
	}

	template <typename T, typename Policy>
	inline void Expects(T condition, Policy policy)
	{
		Contract::Check(condition, Contract::kDefaultPreconditionMsg, policy);
	}

	template <typename T, typename Policy = Contract::ThrowPolicy>
	inline void Ensures(T condition, const char* msg = Contract::kDefaultPostconditionMsg, Policy policy = ContractPolicy::kThrow)
	{
		Contract::Check(condition, msg, policy);
	}

	template <typename T, typename Policy>
	inline void Ensures(T condition, Policy policy)
	{
		Contract::Check(condition, Contract::kDefaultPostconditionMsg, policy);
	}

} // namespace ai