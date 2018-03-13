#pragma once

#include "Exceptions.h"

namespace Seminar
{

	class Convert
	{

		Convert(void) = delete;
		Convert(const Convert&) = delete;
		Convert(Convert&&) = delete;
		Convert& operator = (const Convert&) = delete;
		Convert& operator = (Convert&&) = delete;
		~Convert(void) = delete;

		static const std::size_t sizeMaxPathLen = 32767;

	public:

		static std::wstring ToLower(const std::wstring&);

		static std::wstring EnvironmentPathToAbsolutePath(const std::wstring&);

		static std::wstring ToString(const std::vector<BYTE>&);

		static std::wstring ToUnicode(const std::string&,
			bool = false);

	};

}

