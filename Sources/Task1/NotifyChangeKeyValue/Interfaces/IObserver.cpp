#include "IObserver.h"

namespace Seminar
{

	Subject& Subject::Attach(IObserver* pObserver)
	{

		std::unique_lock<std::mutex> lock(this->mutex);

		this->listObservers.emplace_back(pObserver);

		return *this;

	}

	Subject& Subject::Detach(IObserver* pObserver)
	{

		std::unique_lock<std::mutex> lock(this->mutex);

		this->listObservers.remove(pObserver);

		return *this;

	}

	void Subject::Notify(LPCVOID lpcv) const noexcept
	{

		std::unique_lock<std::mutex> lock(this->mutex);

		for (const auto i : this->listObservers)
			i->Update(this,
				lpcv);

	}

}
