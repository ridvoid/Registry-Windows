#pragma once

#include "..\..\Common\Header.h"

namespace Seminar
{

	class IWorker
	{

		IWorker(const IWorker&) = delete;
		IWorker(IWorker&&) = delete;
		IWorker& operator = (const IWorker&) = delete;
		IWorker& operator = (IWorker&&) = delete;

		DWORD dwErrCode{};

	public:

		IWorker(void) = default;

		virtual ~IWorker(void) = default;

		virtual void Run(ULONG_PTR,
			LPOVERLAPPED,
			DWORD) = 0;
		
		virtual IWorker& SetErrCode(DWORD dwErrCode)
		{

			this->dwErrCode = dwErrCode;

			return *this;

		}

		virtual operator HANDLE(void) const = 0;

	};

}
