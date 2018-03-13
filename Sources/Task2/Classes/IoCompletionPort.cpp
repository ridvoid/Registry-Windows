
#include "IoCompletionPort.h"

namespace Seminar
{

	IoCompletionPort::IoCompletionPort(const Settings& settings) : IoCompletionPort()
	{

		this->h = Wrap::Common::Handle::Create<Wrap::Common::Handle>({});
		this->settings = settings;

	}

	IoCompletionPort::~IoCompletionPort(void) noexcept
	{

		this->Close();

	}

	std::unique_ptr<IoCompletionPort> IoCompletionPort::Create(const Settings& settings)
	{

		std::unique_ptr<IoCompletionPort> uptrReturn(new IoCompletionPort(settings));

		uptrReturn->Create();

		return uptrReturn;

	}

	IoCompletionPort& IoCompletionPort::Create(void)
	{

		this->h = Wrap::Common::Handle::Create<Wrap::Common::Handle>(CreateIoCompletionPort(this->settings.FileHandle,
			this->settings.ExistingCompletionPort,
			this->settings.CompletionKey,
			this->settings.dwNumberOfConcurrentThreads));
		if (!*this->h)
			throw IoCompletionPortException(L"Error CreateIoCompletionPort",
				GetLastError());

		return *this;

	}

	IoCompletionPort& IoCompletionPort::Start(void)
	{

		for (DWORD i{};
			i < this->settings.dwNumberOfConcurrentThreads;
			++i)
			this->listThreads.emplace_back(std::thread{ [this] { this->Receive(); } });

		return *this;

	}

	IoCompletionPort& IoCompletionPort::Add(ULONG_PTR ulptrKey)
	{

		this->CheckKey(ulptrKey);

		if (!PostQueuedCompletionStatus(*this->h,
			{},
			ulptrKey,
			{}))
			throw IoCompletionPortException(L"Error PostQueuedCompletionStatus",
				GetLastError());

		return *this;

	}

	IoCompletionPort& IoCompletionPort::Add(HANDLE h,
		ULONG_PTR ulptrKey)
	{

		this->CheckKey(ulptrKey);

		if (!CreateIoCompletionPort(h,
			*this->h,
			ulptrKey,
			{}))
			throw IoCompletionPortException(L"Error CreateIoCompletionPort",
				GetLastError());

		return *this;

	}

	void IoCompletionPort::Receive(void) const noexcept
	{

		try
		{

			do
			{

				DWORD dwBytes{};
				ULONG_PTR key{};
				LPOVERLAPPED lpOverlapped{};

				auto bRet = GetQueuedCompletionStatus(*this->h,
					&dwBytes,
					&key,
					&lpOverlapped,
					INFINITE);
				
				if (IoCompletionPort::KeyExit::Exit == key)
					return;

				auto p = reinterpret_cast<IWorker*>(key);
				if(!p)
					throw IoCompletionPortException(L"IoCompletionPort::Receive",
						ERROR_INVALID_PARAMETER);

				bRet ? p->Run(key,
					lpOverlapped,
					dwBytes) 
					: p->SetErrCode(GetLastError());

			} while (true);

		}
		catch (...){}

	}

	void IoCompletionPort::Close(void) noexcept
	{

		try
		{

			if (!*this->h)
				return;

			for (std::size_t i{}; i < this->listThreads.size(); ++i)
			{

				try
				{

					if (!PostQueuedCompletionStatus(*this->h,
						{},
						KeyExit::Exit,
						{}))
						throw IoCompletionPortException(L"Error PostQueuedCompletionStatus",
							GetLastError());

				}
				catch (...) {}

			}

			for (auto& thread : this->listThreads)
				thread.join();

			this->listThreads.clear();

		}
		catch (...){ }
		
	}

	void IoCompletionPort::CheckKey(ULONG_PTR ulptrKey) const
	{

		if (this->KeyExit::Exit == ulptrKey)
			throw IoCompletionPortException(L"CheckKey",
				ERROR_INVALID_PARAMETER);

	}

}
