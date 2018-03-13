#pragma once

#include "..\..\Common\Interfaces\ICommand.h"
#include "..\Classes\IoCompletionPort.h"
#include "..\Interfaces\IScanner.h"
#include "..\Classes\Device.h"
#include "..\..\Common\Classes\Driver.h"
#include "..\Classes\NamedPipe.h"
#include "WorkerScanner.h"
#include "..\..\Common\Classes\Registry.h"
#include "..\..\Common\Classes\Convert.h"

#if defined __cplusplus
#include <WinIoCtl.h>
#else
#include <Wdm.h>
#endif

#define IOCTL_SCAN \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_WRITE_DATA)

namespace Seminar
{

	class Scanner : public ICommand, IScanner
	{

		Scanner(void) = delete;
		Scanner(const Scanner&) = delete;
		Scanner(Scanner&&) = delete;
		Scanner& operator = (const Scanner&) = delete;
		Scanner& operator = (Scanner&&) = delete;

		std::wstring wsDriverName{}, wsDeviceName{}, wsPipeName{};

		static const BYTE bNumberOfConcurrentThreads{ 0x2 };
		
		std::atomic<BYTE> atomFinishThreads;
		
		using Worker = std::unique_ptr<IWorker>;
		std::list<Worker> listWorkers{};

		using PoolWorkers = std::unique_ptr<IoCompletionPort>;
		PoolWorkers poolWorkers{};

		using Device = std::unique_ptr<IFile>;
		Device device{};

		enum Label : BYTE { Size = 0x1, Finish = 0xFF };

		Scanner(const IReceiver*, 
			const std::wstring&,
			const std::wstring&,
			const std::wstring&) noexcept;

	public:

		virtual ~Scanner(void) noexcept;

		static std::unique_ptr<ICommand> Create(const IReceiver*, 
			const std::wstring&,
			const std::wstring&,
			const std::wstring&);

		void Execute(void) override;		

	private:
		
		Scanner& LoadDriver(void);

		Scanner& CreateThreadPool(void);

		Scanner& CreateWorkers(void);

		Scanner& Bind(void);

		Scanner& StartThreadPool(void);

		Scanner& OpenDevice(void);
		
		void Work(void) const;

		std::vector<BYTE> Scan(const std::vector<BYTE>&) override;

		Scanner& CloseDevice(void) noexcept;

		Scanner& UnloadDriver(void) noexcept;

	};

}
