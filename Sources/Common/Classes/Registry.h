#pragma once

#include "..\Header.h"
#include "Wrap.h"
#include "Exceptions.h"

namespace Seminar
{

	class Registry
	{

		Registry(void) = delete;
		Registry(const Registry&) = delete;
		Registry(Registry&&) = delete;
		Registry& operator = (const Registry&) = delete;
		Registry& operator = (Registry&&) = delete;

	public:

		enum Root : DWORD
		{

			HkeyClasessRoot = 0x80000000UL,
			HkeyCurrentUser = 0x80000001UL,
			HkeyLocalMachine = 0x80000002UL,
			HkeyUsers = 0x80000003UL,
			HkeyCurrentConfig = 0x80000005UL

		};

		enum Access : REGSAM
		{

			AllAccess = KEY_ALL_ACCESS,
			CreateLink = KEY_CREATE_LINK,
			CreateSubKey = KEY_CREATE_SUB_KEY,
			EnumerateSubKeys = KEY_ENUMERATE_SUB_KEYS,
			KeyExecute = KEY_EXECUTE,
			KeyNotify = KEY_NOTIFY,
			KeyQueryValue = KEY_QUERY_VALUE,
			KeyRead = KEY_READ,
			KeySetValue = KEY_SET_VALUE,
			KeyWow64_32Key = KEY_WOW64_32KEY,
			KeyWow64_64Key = KEY_WOW64_64KEY,
			KeyWrite = KEY_WRITE

		};

		enum Type : DWORD
		{

			RegBinary = REG_BINARY,
			RegDword = REG_DWORD,
			RegDwordLittleEndian = REG_DWORD_LITTLE_ENDIAN,
			RegDwordBigEndian = REG_DWORD_BIG_ENDIAN,
			RegExpandSz = REG_EXPAND_SZ,
			RegLink = REG_LINK,
			RegMultiSz = REG_MULTI_SZ,
			RegNone = REG_NONE,
			RegQword = REG_QWORD,
			RegQwordLittleEndian = REG_QWORD_LITTLE_ENDIAN,
			RegSz = REG_SZ

		};

		enum Notify : DWORD
		{

			RegNotifyChangeAttributes = REG_NOTIFY_CHANGE_ATTRIBUTES,
			RegNotifyChangeLastSet = REG_NOTIFY_CHANGE_LAST_SET,
			RegNotifyChangeName = REG_NOTIFY_CHANGE_NAME,
			RegNotiFyChangeSecurity = REG_NOTIFY_CHANGE_SECURITY,
			RegNotiFyChangeAll = RegNotifyChangeAttributes | RegNotifyChangeLastSet | RegNotifyChangeName | RegNotiFyChangeSecurity

		};

		struct KeyValue
		{

			std::wstring wsName{};
			Type type = Type::RegNone;
			std::vector<BYTE> vecData{};

			KeyValue(const std::wstring& wsName,
				Type type,
				const std::vector<BYTE>& vecData) : wsName(wsName), type(type), vecData(vecData) { }

			KeyValue(void) = default;

		};

	private:

		static const std::map<std::wstring, Root> mapRootKeys;

		static const std::map<std::wstring, std::wstring> mapRootKernelAndUserKeys;

		struct KeyInfo
		{

			DWORD cSubKeys{};
			DWORD cMaxSubKeyLen{};
			DWORD cMaxClassLen{};
			DWORD cValues{};
			DWORD cMaxValueNameLen{};
			DWORD cMaxValueLen{};

		};

		using Handle = std::unique_ptr<Wrap::Reg::Handle>;

		Handle h{};

		Root root = Root::HkeyCurrentUser;

		std::wstring wsName{};

		Access access = Access::KeyRead;

		explicit Registry(Root,
			const std::wstring&,
			Access) noexcept;

	public:

		virtual ~Registry(void) = default;

		static std::unique_ptr<Registry> Open(const std::wstring&,
			Access = Access::KeyRead);

	private:

		Registry& Open(void);

	public:

		std::list<std::wstring> GetSubKeys(void) const;

		std::list<KeyValue> GetValues(void) const;

		Registry& SetValue(const KeyValue&);

		Registry& DeleteValue(const std::wstring&);

		Registry& DeleteKey(const std::wstring&);

		Registry& NotifyChangeKeyValue(BOOL = {},
			Notify = Notify::RegNotifyChangeLastSet,
			HANDLE = {},
			BOOL = {});

	private:

		DWORD GetCountValues(void) const;

		DWORD GetMaxValueLen(void) const;

		DWORD GetMaxValueNameLen(void) const;

		DWORD GetCountSubKeys(void) const;

		DWORD GetMaxSubKeyLen(void) const;

		KeyInfo GetKeyInfo(void) const;

		Registry& Close(void);

		static Root StringToRootKey(const std::wstring&);

		static std::wstring RootKeyToString(Root);

	public:

		static std::wstring ToUser(const std::wstring&);

	};

}
