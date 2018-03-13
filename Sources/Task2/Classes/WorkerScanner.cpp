
#include "WorkerScanner.h"

namespace Seminar
{

	WorkerScanner::WorkerScanner(IScanner* pIScanner,
		Pipe pipe) : WorkerScanner()
	{

		this->pIScanner = pIScanner;
		this->pipe = std::move(pipe);
		
	}

	std::unique_ptr<IWorker> WorkerScanner::Create(IScanner* pIScanner,
		Pipe pipe)
	{

		if (!pIScanner)
			throw WorkerScannerException(L"Create",
				ERROR_INVALID_PARAMETER);

		std::unique_ptr<WorkerScanner> uPtrTmp(new WorkerScanner(pIScanner,
			std::move(pipe)));

		uPtrTmp->pipe->Connect(reinterpret_cast<LPOVERLAPPED>(&uPtrTmp->overlapped));

		return std::unique_ptr<IWorker>(uPtrTmp.release());

	}

	void WorkerScanner::Run(ULONG_PTR ulptrKey,
		LPOVERLAPPED lpOverlapped,
		DWORD dwRead)
	{

		switch (this->overlapped.type)
		{

		case Type::Read:

			this->pIScanner->Scan({ this->overlapped.vecBuf.cbegin(),
				this->overlapped.vecBuf.cbegin() + dwRead });

		case Type::Connect:

			this->Read();
		
		}

	}

	WorkerScanner::operator HANDLE(void) const
	{

		return *this->pipe;

	}


	WorkerScanner& WorkerScanner::Connect(void)
	{

		this->overlapped = {};

		this->pipe->Connect(reinterpret_cast<LPOVERLAPPED>(&this->overlapped));

		return *this;

	}

	WorkerScanner& WorkerScanner::Read(void)
	{

		this->overlapped = Overlapped( OVERLAPPED(),
			Type::Read,
			std::vector<BYTE>(NamedPipe::sizeBuf));

		this->pipe->Read(this->overlapped.vecBuf,
			reinterpret_cast<LPOVERLAPPED>(&this->overlapped));

		return *this;

	}

}
