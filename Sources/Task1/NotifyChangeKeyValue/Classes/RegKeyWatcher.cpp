#include "RegKeyWatcher.h"

namespace Seminar
{

	RegKeyWatcher::RegKeyWatcher(const std::wstring& wsName,
		Registry::Notify notify) noexcept : wsName(wsName), notify(notify) { }

	RegKeyWatcher::~RegKeyWatcher(void) noexcept
	{

		this->Close();

	}

	std::unique_ptr<IWatcher> RegKeyWatcher::Create(const std::wstring& wsName,
		Registry::Notify notify)
	{

		std::unique_ptr<RegKeyWatcher> uptrTmp(new RegKeyWatcher(wsName,
			notify));

		uptrTmp->OpenKey().CreateEvents().CreateThread();

		return std::unique_ptr<IWatcher>(uptrTmp.release());

	}

	RegKeyWatcher& RegKeyWatcher::Watch(void)
	{

		this->key->NotifyChangeKeyValue({},
			this->notify,
			*this->events[Index::Change],
			TRUE);

		return *this;

	}

	RegKeyWatcher& RegKeyWatcher::OpenKey(void)
	{

		this->key = Registry::Open(this->wsName);

		return *this;

	}

	RegKeyWatcher& RegKeyWatcher::CreateEvents(void)
	{

		this->events = Events(Index::Count);

		for (std::size_t i{}; i < Index::Count; ++i)
			this->events[i] = AutoEvent::Create();

		return *this;

	}

	RegKeyWatcher& RegKeyWatcher::CreateThread(void)
	{

		this->thread = std::thread{ [this] { static_cast<const RegKeyWatcher*>(this)->Watch(); } };

		return *this;

	}

	void RegKeyWatcher::Watch(void) const
	{

		try
		{
		
			std::vector<HANDLE> vecHandles(this->events.size());
			for (std::size_t i{}; i < vecHandles.size(); ++i)
				vecHandles[i] = *this->events[i];
			
			while (Wrap::Common::Handle::Wait(vecHandles,
				{}) == static_cast<DWORD>(Index::Change))
					Subject::Notify({});

		}
		catch (const WinApiException& ex)
		{

			std::wcout << ex.What() << std::endl;

		}
		catch (const std::exception& ex)
		{

			std::cout << ex.what() << std::endl;

		}
		catch (...)
		{

			std::wcout << L"Unhandled exception..." << std::endl;

		}

	}

	void RegKeyWatcher::Close(void) noexcept
	{

		try
		{

			if (!this->thread.native_handle())
				return;

			this->events[Index::Exit]->Set();

			this->thread.join();

		}
		catch (...) { }

	}

}
