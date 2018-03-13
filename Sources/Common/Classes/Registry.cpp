
#include "Registry.h"

namespace Seminar
{

	const std::map<std::wstring, Registry::Root> Registry::mapRootKeys =
	{

		{ L"HKEY_CLASSES_ROOT", Root::HkeyClasessRoot },

		{ L"HKEY_CURRENT_USER", Root::HkeyCurrentUser },

		{ L"HKEY_LOCAL_MACHINE", Root::HkeyLocalMachine },

		{ L"HKEY_USERS", Root::HkeyUsers },

		{ L"HKEY_CURRENT_CONFIG", Root::HkeyCurrentConfig }

	};

	const std::map<std::wstring, std::wstring> Registry::mapRootKernelAndUserKeys = 
	{

		{ L"\\Registry\\Machine", L"HKEY_LOCAL_MACHINE" },

		{ L"\\Registry\\User", L"HKEY_USERS" },

	};

	Registry::Registry(Root root,
		const std::wstring& wsName,
		Access access) noexcept 
		: 
		root(root),
		wsName(wsName),
		access(access)
		{ }

	std::unique_ptr<Registry> Registry::Open(const std::wstring& wsName,
		Access access)
	{

		std::unique_ptr<Registry> uptrReturn{};

		auto sizePos = wsName.find('\\');
		if (sizePos == std::wstring::npos)
			uptrReturn = std::unique_ptr<Registry> (new Registry(Registry::StringToRootKey(wsName),
				{},
				access));
		else
			uptrReturn = std::unique_ptr<Registry>(new Registry(Registry::StringToRootKey(wsName.substr({}, sizePos)),
				wsName.substr(sizePos + 1),
				access));

		uptrReturn->Open();

		return uptrReturn;

	}

	Registry& Registry::Open(void)
	{

		auto lResult = RegOpenKeyEx(reinterpret_cast<HKEY>(this->root),
			this->wsName.c_str(),
			{},
			this->access | Access::KeyWow64_64Key,
			*this->Close().h);
		if (*this->h != lResult)
			throw RegistryException(L"Error RegOpenKeyEx",
				lResult);

		return *this;

	}

	std::list<std::wstring> Registry::GetSubKeys(void) const
	{

		auto dwCountSubKeys = this->GetCountSubKeys();

		auto dwMaxSubKeyLen = this->GetMaxSubKeyLen();

		std::list<std::wstring> listReturn{};

		for (DWORD i{}; i < dwCountSubKeys; ++i)
		{

			std::wstring wsName(dwMaxSubKeyLen + sizeof(WCHAR), 
				{});

			auto cchValue = static_cast<DWORD>(dwMaxSubKeyLen + sizeof(WCHAR));

			auto lResult = ::RegEnumKeyEx(*this->h,
				i,
				&wsName[0],
				&cchValue,
				{},
				{},
				{},
				{});
			if (*this->h != lResult)
			{

				if (lResult != ERROR_NO_MORE_ITEMS)
					throw RegistryException(L"Error RegEnumKeyEx",
						lResult);
				else
					break;

			}

			std::wostringstream stream;
			stream << Registry::RootKeyToString(this->root) << L"\\";

			if (this->wsName.length())
				stream << this->wsName << L"\\" << wsName.c_str();
			else
				stream << wsName.c_str();

			listReturn.emplace_back(stream.str());

		}

		return listReturn;

	}

	std::list<Registry::KeyValue> Registry::GetValues(void) const
	{

		auto dwCountValues = this->GetCountValues();

		auto dwMaxValueLen = this->GetMaxValueLen();

		auto dwMaxValueNameLen = this->GetMaxValueNameLen();

		std::list<KeyValue> listReturn{};

		for (DWORD i{}; i < dwCountValues; ++i)
		{

			std::wstring wsName(dwMaxValueNameLen + 1,
				{});

			auto cchValue = static_cast<DWORD>(dwMaxValueNameLen + sizeof(WCHAR));

			std::vector<BYTE> vecData(dwMaxValueLen);

			Type type{};

			auto cbData = dwMaxValueLen;

			auto lResult = RegEnumValue(*this->h,
				i,
				&wsName[0],
				&cchValue,
				{},
				reinterpret_cast<DWORD*>(&type),
				vecData.data(),
				&cbData);
			if (*this->h != lResult)
			{

				if (lResult != ERROR_NO_MORE_ITEMS)
					throw RegistryException(L"Error RegEnumValue",
						lResult);
				else
					break;

			}

			if (!cchValue)
				wsName = L"Default";

			vecData.resize(cbData);

			listReturn.emplace_back(wsName.c_str(),
				type,
				vecData);

		}

		return listReturn;

	}

	Registry& Registry::SetValue(const KeyValue& value)
	{

		auto lResult = RegSetValueEx(*this->h,
			value.wsName.c_str(),
			{},
			value.type,
			value.vecData.data(),
			static_cast<DWORD>(value.vecData.size()));
		if (*this->h != lResult)
			throw RegistryException(L"Error RegSetValueEx",
				lResult);

		return *this;

	}

	Registry & Registry::DeleteValue(const std::wstring& wsName)
	{

		auto lResult = RegDeleteValue(*this->h,
			wsName.c_str());
		if (*this->h != lResult)
			throw RegistryException(L"Error RegDeleteValue",
				lResult);

		return *this;

	}

	Registry & Registry::DeleteKey(const std::wstring& wsName)
	{

		auto lResult = RegDeleteKey(*this->h,
			wsName.c_str());
		if (*this->h != lResult)
			throw RegistryException(L"Error RegDeleteKey",
				lResult);

		return *this;

	}

	Registry& Registry::NotifyChangeKeyValue(BOOL bWatchThree,
		Notify notify,
		HANDLE hEvent,
		BOOL bAsynchronous)
	{

		auto lResult = RegNotifyChangeKeyValue(*this->h,
			bWatchThree,
			notify,
			hEvent,
			bAsynchronous);
		if (*this->h != lResult)
			throw RegistryException(L"Error RegNotifyChangeKeyValue",
				lResult);

		return *this;

	}

	DWORD Registry::GetCountValues(void) const
	{

		return this->GetKeyInfo().cValues;

	}

	DWORD Registry::GetMaxValueLen(void) const
	{

		return this->GetKeyInfo().cMaxValueLen;

	}

	DWORD Registry::GetMaxValueNameLen(void) const
	{

		return this->GetKeyInfo().cMaxValueNameLen;

	}

	DWORD Registry::GetCountSubKeys(void) const
	{

		return this->GetKeyInfo().cSubKeys;

	}

	DWORD Registry::GetMaxSubKeyLen(void) const
	{

		return this->GetKeyInfo().cMaxSubKeyLen;

	}

	Registry::KeyInfo Registry::GetKeyInfo(void) const
	{

		KeyInfo ki{};

		auto lResult = ::RegQueryInfoKey(*this->h,
			{},
			{},
			{},
			&ki.cSubKeys,
			&ki.cMaxSubKeyLen,
			{},
			&ki.cValues,
			&ki.cMaxValueNameLen,
			&ki.cMaxValueLen,
			{},
			{});
		if (*this->h != lResult)
			throw RegistryException(L"Error RegQueryInfoKey",
				lResult);

		return ki;

	}

	Registry& Registry::Close(void)
	{

		this->h = Wrap::Reg::Handle::Create({});

		return *this;

	}

	Registry::Root Registry::StringToRootKey(const std::wstring& wsName)
	{

		return Registry::mapRootKeys.find(wsName)->second;

	}

	std::wstring Registry::RootKeyToString(Root root)
	{

		return (std::find_if(Registry::mapRootKeys.cbegin(),
			Registry::mapRootKeys.cend(),
			[root](const std::pair<std::wstring, Registry::Root>& pair)
		{

			return root == pair.second;

		}))->first;

	}

	std::wstring Registry::ToUser(const std::wstring& wsName)
	{

		for (const auto& i : Registry::mapRootKernelAndUserKeys)
		{

			auto pos = wsName.find(i.first);
			if (pos == std::wstring::npos)
				continue;

			std::wostringstream wos;
			wos << i.second << wsName.substr(i.first.length());
			return wos.str();

		}

		throw RegistryException(L"ToUser",
			ERROR_INVALID_PARAMETER);

	}

}
