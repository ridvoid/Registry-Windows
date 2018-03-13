
#include "NamedPipe.h"

namespace Seminar
{

	NamedPipe::NamedPipe(const Settings& settings) : settings(settings){ }
	
	std::unique_ptr<IFile> NamedPipe::Create(const Settings& settings)
	{

		return IFile::Create<NamedPipe, Settings>(settings);

	}

	IFile& NamedPipe::Create(void)
	{

		IFile::h = Wrap::Common::Handle::Create<Wrap::Common::Handle>(CreateNamedPipe(this->settings.wsName.c_str(),
			this->settings.dwOpenMode,
			this->settings.dwPipeMode,
			this->settings.nMaxInstances,
			this->settings.nOutBufferSize,
			this->settings.nInBufferSize,
			this->settings.nDefaultTimeOut,
			this->settings.lpSecurityAttributes));
		if (!*IFile::h)
			throw NamedPipeException(L"Error CreateNamedPipe",
				GetLastError());

		return *this;

	}

	IFile& NamedPipe::Connect(LPOVERLAPPED lpOverlapped) const
	{
		
		if (!ConnectNamedPipe(*IFile::h,
			lpOverlapped))
		{

			auto dwErrCode = GetLastError();
			if(dwErrCode != ERROR_IO_PENDING)
				throw NamedPipeException(L"Error ConnectNamedPipe",
					dwErrCode);

		}

		return *const_cast<NamedPipe*>(this);

	}

	IFile& NamedPipe::Disconnect(void) const
	{

		if(!DisconnectNamedPipe(*IFile::h))
			throw NamedPipeException(L"Error DisconnectNamedPipe",
					GetLastError());

		return *const_cast<NamedPipe*>(this);

	}

	DWORD NamedPipe::DeviceIoControl(DWORD,
		const std::vector<BYTE>&,
		std::vector<BYTE>&&,
		LPOVERLAPPED) const
	{

		throw NamedPipeException(L"DeviceIoControl",
			ERROR_NOT_SUPPORTED);

	}

}
