#include "Scanner.h"

namespace Seminar
{

	Scanner::Scanner(const IReceiver* IReceiver, 
		const std::wstring& wsDriverName,
		const std::wstring& wsDeviceName,
		const std::wstring& wsPipeName) noexcept
		: 
		ICommand(IReceiver),
		wsDriverName(wsDriverName), 
		wsDeviceName(wsDeviceName), 
		wsPipeName(wsPipeName)
		{ }

	Scanner::~Scanner(void) noexcept
	{

		this->CloseDevice().UnloadDriver();

	}

	std::unique_ptr<ICommand> Scanner::Create(const IReceiver* IReceiver, 
		const std::wstring& wsDriverName,
		const std::wstring& wsDeviceName,
		const std::wstring& wsPipeName)
	{

		return std::unique_ptr<ICommand>(new Scanner(IReceiver,
			wsDriverName,
			wsDeviceName,
			wsPipeName));

	}

	void Scanner::Execute(void)
	{

		static_cast<const Scanner&>(this->LoadDriver().CreateThreadPool().CreateWorkers().Bind().StartThreadPool().OpenDevice()).Work();

	}

	Scanner& Scanner::LoadDriver(void)
	{

		Driver::Load(this->wsDriverName);

		return *this;

	}

	Scanner& Scanner::CreateThreadPool(void)
	{

		IoCompletionPort::Settings settings{};
		settings.dwNumberOfConcurrentThreads = Scanner::bNumberOfConcurrentThreads;

		this->poolWorkers = IoCompletionPort::Create(settings);

		return *this;

	}

	Scanner& Scanner::CreateWorkers(void)
	{

		for (BYTE i{}; i < Scanner::bNumberOfConcurrentThreads; ++i)
		{

			NamedPipe::Settings settings{};
			settings.wsName = this->wsPipeName;
			settings.dwOpenMode = PIPE_ACCESS_INBOUND | FILE_FLAG_OVERLAPPED;
			settings.dwPipeMode = PIPE_TYPE_BYTE | PIPE_WAIT;
			settings.nMaxInstances = Scanner::bNumberOfConcurrentThreads;

			this->listWorkers.emplace_back(WorkerScanner::Create(this,
				NamedPipe::Create(settings)));

		}

		return *this;

	}

	Scanner& Scanner::Bind(void)
	{

		for (const auto& i : this->listWorkers)
			this->poolWorkers->Add(*i,
				reinterpret_cast<ULONG_PTR>(i.get()));

		return *this;

	}

	Scanner& Scanner::StartThreadPool(void)
	{

		this->poolWorkers->Start();

		return *this;

	}

	Scanner& Scanner::OpenDevice(void)
	{

		this->device = Seminar::Device::Create(this->wsDeviceName);

		return *this;

	}

	void Scanner::Work(void)const
	{

		this->device->DeviceIoControl(IOCTL_SCAN,
			{},
			{});

	}

	std::vector<BYTE> Scanner::Scan(const std::vector<BYTE>& vecBuf)
	{

		std::wstring wsKey{};

		try
		{

			wsKey = Registry::ToUser(Convert::ToString(vecBuf));
			
			Registry::Open(wsKey);

		}
		catch (const WinApiException& ex)
		{
			
			if (vecBuf.size() == Label::Size && vecBuf[0] == Label::Finish)
			{

				++this->atomFinishThreads;
				if (Scanner::bNumberOfConcurrentThreads == this->atomFinishThreads.load())
					ICommand::OnAction();

			}
			else
			{

				std::wostringstream wos;

				wos << wsKey << L" -> " << ex.What();
				
				ICommand::OnAction(wos.str());

			}
				
		}

		return{};

	}

	Scanner& Scanner::CloseDevice(void) noexcept
	{

		try
		{

			this->device = {};

		}
		catch (...) {}

		return *this;

	}

	Scanner& Scanner::UnloadDriver(void) noexcept
	{

		try
		{

			Driver::Unload(this->wsDriverName);

			return *this;

		}
		catch (...) {}

		return *this;

	}

}
