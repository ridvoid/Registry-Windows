#pragma once

#include "..\Classes\Wrap.h"

namespace Seminar
{

	class IFile
	{

		IFile(const IFile&) = delete;
		IFile(IFile&&) = delete;
		IFile& operator = (const IFile&) = delete;
		IFile& operator = (IFile&&) = delete;

	protected:

		using Handle = std::unique_ptr<Wrap::Common::Handle>;
		Handle h {};

		IFile(void) : h(Wrap::Common::Handle::Create<Wrap::Common::Handle>({})) { }

	public:

		virtual ~IFile(void) = default;

	protected:

		template<typename T, typename Param>
		static std::unique_ptr<IFile> Create(const Param& param)
		{

			std::unique_ptr<IFile> uPtrReturn(new T(param));

			uPtrReturn->Create();

			return uPtrReturn;

		}

	protected:

		virtual IFile& Create(void) = 0;

	public:

		virtual DWORD Write(const std::vector<BYTE>& vecBuf,
			LPOVERLAPPED lpOverlapped = {}) const
		{

			DWORD dwReturn{};

			if (!WriteFile(*this->h,
				vecBuf.data(),
				static_cast<DWORD>(vecBuf.size()),
				&dwReturn,
				lpOverlapped))
			{

				auto dwErrCode = GetLastError();
				if (dwErrCode != ERROR_IO_PENDING)
					throw IFileException(L"Error WriteFile",
						dwErrCode);

			}

			return dwReturn;

		}

		virtual DWORD Read(std::vector<BYTE>& vecBuf,
			LPOVERLAPPED lpOverlapped = {}) const
		{

			DWORD dwReturn{};

			if (!ReadFile(*this->h,
				vecBuf.data(),
				static_cast<DWORD>(vecBuf.size()),
				&dwReturn,
				lpOverlapped))
			{

				auto dwErrCode = GetLastError();
				if (dwErrCode != ERROR_IO_PENDING)
					throw IFileException(L"Error ReadFile",
						dwErrCode);

			}

			return dwReturn;

		}

		virtual operator HANDLE(void) const noexcept
		{

			return *this->h;

		}

		virtual bool operator !(void) const noexcept
		{

			return !*this->h;

		}

		virtual IFile& Connect(LPOVERLAPPED = {}) const = 0;

		virtual IFile& Disconnect(void) const = 0;

		virtual DWORD DeviceIoControl(DWORD,
			const std::vector<BYTE>&,
			std::vector<BYTE>&&,
			LPOVERLAPPED = {}) const = 0;

	};

}
