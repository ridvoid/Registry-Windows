#pragma once

#include "..\Interfaces\IScanner.h"
#include "..\Interfaces\IWorker.h"
#include "..\Classes\NamedPipe.h"
#include "..\..\Common\Classes\Convert.h"

namespace Seminar
{

	class WorkerScanner : public IWorker
	{

		WorkerScanner(void) = default;
		WorkerScanner(const WorkerScanner&) = delete;
		WorkerScanner(WorkerScanner&&) = delete;
		WorkerScanner& operator = (const WorkerScanner&) = delete;
		WorkerScanner& operator = (WorkerScanner&&) = delete;

		IScanner* pIScanner{};

		using Pipe = std::unique_ptr<IFile>;
		Pipe pipe{};

		enum class Type : BYTE { Connect = 1, Read };

		struct Overlapped
		{

			OVERLAPPED overrlapped{};

			Type type = { Type::Connect };

			std::vector<BYTE> vecBuf{};

			Overlapped(const OVERLAPPED& overrlapped = {},
				Type type = { Type::Connect },
				const std::vector<BYTE>& vecBuf = {}) : 
				overrlapped(overrlapped), type(type), vecBuf(vecBuf){ }

		};

		Overlapped overlapped{};

		WorkerScanner(IScanner*,
			Pipe);

	public:

		virtual ~WorkerScanner(void) = default;

		static std::unique_ptr<IWorker> Create(IScanner*,
			Pipe);
		
		void Run(ULONG_PTR,
			LPOVERLAPPED,
			DWORD) override;

		operator HANDLE(void) const override;

	private:

		WorkerScanner& Connect(void);

		WorkerScanner& Read(void);

	};

}
