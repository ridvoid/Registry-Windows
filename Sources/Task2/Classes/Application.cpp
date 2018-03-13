
#include "Application.h"

namespace Seminar
{

	const std::wstring Application::wsDriverPath(L"%SystemRoot%\\System32\\Drivers\\ScanReg.sys"),
		Application::wsDriverName(L"ScanReg"),
		Application::wsDeviceName(L"{BA9510F6-C5A2-4755-BC94-2896E5DB3B06}"),
		Application::wsPipeName(L"\\\\.\\pipe\\{BA9510F6-C5A2-4755-BC94-2896E5DB3B06}");

	const std::wstring Application::wsInstall(L"install"),
		Application::wsScan(L"scan"),
		Application::wsUninstall(L"uninstall");

	std::mutex Application::mutex{};

	std::wofstream Application::wof{};

	const std::wstring Application::wsScanLog(L"ScanReg.log");

	UINT64 Application::uiCountBadKey{};

	Application::Application(void)
	{

		this->mapMethods[IDC_INSTALL] = &Application::OnInstall;
		this->mapMethods[IDC_SCAN] = &Application::OnScan;
		this->mapMethods[IDC_UNINSTALL] = &Application::OnUninstall;

	}

	IApplication& Application::GetInstance(void)
	{

		static Application instance;

		return instance;

	}

	int Application::Execute(void)
	{

		IApplication::Execute();

		return this->CreateWin().ReceiveMsg();

	}

	void Application::ShowHelp(void) const
	{

		std::wostringstream wos;

		wos << L"Description commands:" << std::endl;

		wos << L"install - install driver to system" << std::endl;

		wos << L"scan - scan registry" << std::endl;

		wos << L"uninstall - uninstall driver from system" << std::endl << std::endl;

		wos << L"Example: ScanReg.exe install scan uninstall" << std::endl << std::endl;

		MessageBox(this->hWnd,
			wos.str().c_str(),
			L"Help",
			MB_OK | MB_HELP);

	}

	Application& Application::CreateWin(void)
	{

		this->hWnd = CreateDialogParam(IApplication::GetInstance(),
			MAKEINTRESOURCE(IDD_DIALOG1),
			{},
			reinterpret_cast<DLGPROC>(&Application::WndProc),
			reinterpret_cast<LPARAM>(this));
		if (!this->hWnd)
			throw ResourceException(L"Error CreateDialogParam",
				GetLastError());

		return *this;

	}

	int Application::ReceiveMsg(void)
	{

		MSG msg{};
		while (GetMessage(&msg,
			{},
			{},
			{}))
			if (!IsWindow(this->hWnd) || !IsDialogMessage(this->hWnd, &msg))
				DispatchMessage(&msg);

		return static_cast<int>(msg.wParam);

	}

	BOOL CALLBACK Application::WndProc(HWND hWnd,
		UINT uiMsg,
		WPARAM wParam,
		LPARAM lParam)
	{

		static Application* pApp = {};

		switch (uiMsg)
		{

		case WM_INITDIALOG:

			(pApp = reinterpret_cast<Application*>(lParam))->ExecuteCommandLine();

			return TRUE;

		case WM_COMMAND:

			if (pApp->mapMethods.count(LOWORD(wParam)))
				(pApp->*pApp->mapMethods[LOWORD(wParam)])();

			break;

		case WM_CLOSE:

			DestroyWindow(hWnd);

			PostQuitMessage({});

		}

		return{};

	}

	void Application::ExecuteCommandLine(void)
	{

		try
		{

			this->CheckArguments();

			IApplication::ExecuteCommands();
			
		}
		catch (CommandLineArgumentException)
		{

			if (IApplication::listCommands.size())
				this->ShowHelp();

		}
		catch (const WinApiException& ex)
		{

			MessageBox(this->hWnd,
				ex.What().c_str(),
				{},
				{});

		}

	}

	IApplication& Application::CheckArguments(void)
	{

		IApplication::CheckArguments();

		for (const auto& i : IApplication::vecArguments)
			IApplication::listCommands.emplace_back(this->CreateCommand(i));

		return *this;

	}

	std::unique_ptr<ICommand> Application::CreateCommand(const std::wstring& wsName) const
	{

		if (wsName == Application::wsInstall)
		{

			DWORD dwResId{};

#ifndef _WIN64
			dwResId = IDR_RCDATA1;
#else
			dwResId = IDR_RCDATA2;
#endif

			return InstallDriver::Create(this,
				Convert::EnvironmentPathToAbsolutePath(Application::wsDriverPath),
				Application::wsDriverName,
				dwResId);
		
		}
		
		if (wsName == Application::wsScan)
		{

			Application::OpenLog();

			return Scanner::Create(this,
				Application::wsDriverName,
				Application::wsDeviceName,
				Application::wsPipeName);

		}

		if (wsName == Application::wsUninstall)
			return UninstallDriver::Create(this,
				Convert::EnvironmentPathToAbsolutePath(Application::wsDriverPath),
				Application::wsDriverName);

		throw CommandLineArgumentException(L"Invalid command line arguments");

	}

	void Application::OnInstall(void)
	{

		this->ExecuteOnCommand(Application::wsInstall).ShowInfo(L"ScanReg.sys installed");

	}

	void Application::OnScan(void)
	{

		this->ExecuteOnCommand(Application::wsScan);

	}

	void Application::OnUninstall(void)
	{

		this->ExecuteOnCommand(Application::wsUninstall).ShowInfo(L"ScanReg.sys deleted");

	}

	Application& Application::ExecuteOnCommand(const std::wstring& wsCommand)
	{

		try
		{

			IApplication::listCommands.clear();

			IApplication::listCommands.emplace_back(this->CreateCommand(wsCommand));

			IApplication::ExecuteCommands();

		}
		catch (const WinApiException& ex)
		{

			MessageBox(this->hWnd,
				ex.What().c_str(),
				{},
				{});

		}

		return *this;

	}

	void Application::ShowInfo(const std::wstring& ws) const
	{

		SetDlgItemText(this->hWnd,
			IDC_STATISTIC,
			ws.c_str());

	}

	void Application::Action(void) const
	{

		Application::CloseLog();

		this->ShowInfo(L"Scan completed");

	}

	void Application::Action(const std::wstring& ws) const
	{

		std::unique_lock<std::mutex> lock(Application::mutex);

		Application::wof << ws << std::endl;

		std::wostringstream wos;
		wos << L"Inaccessible keys: " << ++Application::uiCountBadKey;

		this->ShowInfo(wos.str());

	}

	void Application::OpenLog(void)
	{

		std::wostringstream wos;
		wos << Directory::GetCurDir() << L"\\" << Application::wsScanLog;

		Application::wof = std::wofstream(wos.str());
		if (!Application::wof)
			throw ScanRegException(L"Error open log file");

		Application::wof.imbue(std::locale("rus"));

		Application::uiCountBadKey = {};

	}

	void Application::CloseLog(void)
	{

		Application::wof.close();
		
	}

}

