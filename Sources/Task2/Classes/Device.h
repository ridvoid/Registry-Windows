
#pragma once
#include "..\..\Common\Classes\File.h"


namespace Seminar
{

	class Device : public File
	{

		Device(void) = default;
		Device(const Device&) = delete;
		Device(Device&&) = delete;
		Device& operator = (const Device&) = delete;
		Device& operator = (Device&&) = delete;

	public:

		using File::File;

		virtual ~Device(void) = default;

		static std::unique_ptr<IFile> Create(const std::wstring&);

	public:

		DWORD DeviceIoControl(DWORD,
			const std::vector<BYTE>&,
			std::vector<BYTE>&&,
			LPOVERLAPPED = {}) const override;

	};

}