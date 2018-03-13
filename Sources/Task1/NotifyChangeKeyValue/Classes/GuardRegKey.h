#pragma once

#include "..\Interfaces\IObserver.h"
#include "..\Classes\RegKeyWatcher.h"
#include "..\..\..\Common\Interfaces\ICommand.h"
#include "..\..\..\Common\Interfaces\IReceiver.h"
#include "RegKeyBuilderUnit.h"
#include "RemoveRegValue.h"
#include "AddRegValue.h"
#include "ChangeRegValue.h"

namespace Seminar
{

	class GuardRegKey : IObserver, public ICommand, IReceiver
	{

		GuardRegKey(void) = delete;
		GuardRegKey(const GuardRegKey&) = delete;
		GuardRegKey& operator = (const GuardRegKey&) = delete;
		GuardRegKey(GuardRegKey&&) = delete;
		GuardRegKey& operator = (GuardRegKey&&) = delete;

		static std::mutex mutex;

		using Builder = std::unique_ptr<IBuilderUnit>;
		Builder builder{};

		using Key = std::shared_ptr<IUnit>;
		Key currentKey{}, modifyKey{};

		using RegValue = std::shared_ptr<IUnit>;
		
		using Watcher = std::unique_ptr<IWatcher>;
		Watcher watcher{};

		using Restore = std::unique_ptr<ICommand>;

		using ListValues = std::list<std::shared_ptr<IUnit>>;

		std::wstring wsName{};

		explicit GuardRegKey(const std::wstring&) noexcept;

	public:

		virtual ~GuardRegKey(void) = default;

		static std::unique_ptr<ICommand> Create(const std::wstring&);

		void Execute(void) override;

	private:

		void Update(const Subject*,
			LPCVOID) noexcept override;

		GuardRegKey& CreateBuilder(void);

		GuardRegKey& SaveCurrentValues(void);

		GuardRegKey& CreateWatcher(void);

		GuardRegKey& SaveModifyValues(void);

		GuardRegKey& RestoreValues(void);

		template<typename T>
		static Restore GetRestore(const IReceiver* pReceiver,
			const ListValues& left,
			const ListValues& right,
			const std::wstring& wsName)
		{

			Restore restore{};

			for (const auto& i : left)
			{

				auto cit = std::find_if(right.cbegin(),
					right.cend(),
					[&i](const RegValue& regValue)
				{

					return i->GetName() == regValue->GetName() &&
						i->GetType() == regValue->GetType() &&
						i->GetData() == regValue->GetData();

				});

				if (cit == right.cend())
				{

					restore = IRestoreRegValue::Create<T>(pReceiver,
						wsName,
						i);

					break;

				}

			}

			return restore;

		}

	private:

		void Action(void) const override;

		void Action(const std::wstring&) const override;

	};

}