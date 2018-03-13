//---------------------------------------------------------------------------

#pragma once
#include "..\..\..\Sources\Common\Header.h"

//---------------------------------------------------------------------------

namespace Seminar
{

	class WinApiException
	{

		std::wstring wsText{};
		DWORD dwErrCode{};

	public:

		WinApiException(void) = delete;
		WinApiException(const WinApiException&) = default;
		WinApiException(WinApiException&&) = default;
		WinApiException& operator = (const WinApiException&) = default;
		WinApiException& operator = (WinApiException&&) = default;

		explicit WinApiException(const std::wstring&,
			DWORD = {}) noexcept;

		virtual ~WinApiException(void) = default;

		virtual std::wstring What(void) const;

		DWORD GetErrCode(void) const noexcept;

	};

	class HandleException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class NotSupportedException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class RegistryException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class IEventException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class CommandLineArgumentException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};
	
	class DriverException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};
	
	class ResourceException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class ConvertException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class FileException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class IFileException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class DeviceException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class IoCompletionPortException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};
	
	class NamedPipeException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class WorkerScannerException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class ScanRegException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

	class DirectoryException : public WinApiException
	{

	public:

		using WinApiException::WinApiException;

	};

}
