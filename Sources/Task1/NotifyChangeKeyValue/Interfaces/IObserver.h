#pragma once

#include "..\..\..\Common\Header.h"

namespace Seminar
{

	class Subject;

	class IObserver
	{

		IObserver(const IObserver&) = delete;
		IObserver(IObserver&&) = delete;
		IObserver& operator = (const IObserver&) = delete;
		IObserver& operator = (IObserver&&) = delete;

	protected:

		IObserver(void) = default;

	public:

		virtual ~IObserver(void) = default;

		virtual void Update(const Subject*,
			LPCVOID) noexcept = 0;

	};

	class Subject
	{

		Subject(const Subject&) = delete;
		Subject(Subject&&) = delete;
		Subject& operator = (const Subject&) = delete;
		Subject& operator = (Subject&&) = delete;

		std::list<IObserver*> listObservers{};

		mutable std::mutex mutex{};

	protected:

		Subject(void) = default;

	public:

		virtual ~Subject(void) = default;

		virtual Subject& Attach(IObserver*);

		virtual Subject& Detach(IObserver*);

		virtual void Notify(LPCVOID) const noexcept;

	};

}