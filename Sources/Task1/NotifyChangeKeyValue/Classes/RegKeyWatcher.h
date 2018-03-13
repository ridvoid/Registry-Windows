#pragma once

#include "..\Interfaces\IWatcher.h"
#include "AutoEvent.h"
#include "..\..\..\Common\Classes\Registry.h"
#include "..\..\..\Common\Classes\Convert.h"

namespace Seminar
{

	class RegKeyWatcher : public IWatcher
	{

		RegKeyWatcher(void) = default;
		RegKeyWatcher(const RegKeyWatcher&) = delete;
		RegKeyWatcher& operator = (const RegKeyWatcher&) = delete;
		RegKeyWatcher(RegKeyWatcher&&) = delete;
		RegKeyWatcher& operator = (RegKeyWatcher&&) = delete;

		std::wstring wsName{};

		Registry::Notify notify{};

		using Key = std::unique_ptr<Registry>;
		Key key{};

		enum Index : std::size_t { Exit, Change, Count };
		
		using Events = std::vector<std::unique_ptr<IEvent>>;
		Events events{};

		std::thread thread{};

		explicit RegKeyWatcher(const std::wstring&,
			Registry::Notify) noexcept;

	public:

		virtual ~RegKeyWatcher(void) noexcept;

		static std::unique_ptr<IWatcher> Create(const std::wstring&,
			Registry::Notify);

		RegKeyWatcher& Watch(void) override;

	private:

		RegKeyWatcher& OpenKey(void);

		RegKeyWatcher& CreateEvents(void);

		RegKeyWatcher& CreateThread(void);

		void Watch(void) const;

		void Close(void) noexcept;

	};

}