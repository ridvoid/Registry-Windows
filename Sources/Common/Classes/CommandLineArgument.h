#pragma once


#include "Exceptions.h"

namespace Seminar
{

	class CommandLineArgument
	{

		CommandLineArgument(void) = delete;
		CommandLineArgument(const CommandLineArgument&) = delete;
		CommandLineArgument(CommandLineArgument&&) = delete;
		CommandLineArgument& operator = (const CommandLineArgument&) = delete;
		CommandLineArgument& operator = (CommandLineArgument&&) = delete;
		~CommandLineArgument(void) = delete;

	public:

		static std::vector<std::wstring> GetCommandLines(void);

	};

}
