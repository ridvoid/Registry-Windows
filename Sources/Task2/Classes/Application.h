#pragma once

#include "..\..\..\Sources\Task2\Classes\Scanner.h"
#include "..\..\Common\Interfaces\IReceiver.h"
#include "..\..\Common\Interfaces\IApplication.h"
#include "..\..\Common\Classes\InstallDriver.h"
#include "..\..\Common\Classes\UninstallDriver.h"
#include "..\..\Task2\Classes\Directory.h"
#include "..\..\..\Projects\Task2\ScanReg\ScanReg\resource.h"

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "comctl32.lib")

namespace Seminar
{

	class Application : public IApplication, IReceiver
	{

		Application(void);
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator = (const Application&) = delete;
		Application& operator = (Application&&) = delete;

		static const std::wstring wsDriverPath, 
			wsDriverName, 
			wsDeviceName,
			wsPipeName;

		static const std::wstring wsInstall,
			wsScan,
			wsUninstall;

		static std::mutex mutex;

		static std::wofstream wof;

		static const std::wstring wsScanLog;

		static UINT64 uiCountBadKey;

		HWND hWnd{};

		std::map<UINT, void(Application::*)(void)> mapMethods{};

	public:

		virtual ~Application(void) = default;

		static IApplication& GetInstance(void);

		int Execute(void) override;

		void ShowHelp(void) const override;

	private:

		Application& CreateWin(void);

		int ReceiveMsg(void);

		static BOOL CALLBACK WndProc(HWND,
			UINT,
			WPARAM,
			LPARAM);

		void ExecuteCommandLine(void);

		IApplication& CheckArguments(void) override;

		std::unique_ptr<ICommand> CreateCommand(const std::wstring&) const override;

		void OnInstall(void);

		void OnScan(void);

		void OnUninstall(void);

		Application& ExecuteOnCommand(const std::wstring&);

		void ShowInfo(const std::wstring&) const;
		
		void Action(void) const override;

		void Action(const std::wstring&) const override;
		
		static void OpenLog(void);

		static void CloseLog(void);


	};

}
