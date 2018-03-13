#include "..\..\Common\Classes\Exceptions.h"

namespace Seminar
{

	class Directory
	{

		Directory(void) = delete;
		Directory(const Directory&) = delete;
		Directory(Directory&&) = delete;
		Directory& operator = (const Directory&) = delete;
		Directory& operator = (Directory&&) = delete;
		~Directory(void) = delete;

		static const std::size_t sizeMaxPathLen{ 32767 };

	public:


		static std::wstring GetCurDir(void);

	};

}