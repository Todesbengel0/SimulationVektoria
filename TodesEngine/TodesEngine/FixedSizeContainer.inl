#include <cassert>

namespace Todes
{
	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	FixedSizeContainer<Element_Type, Container_Type>::FixedSizeContainer(const unsigned int& size)
		: m_entriesUsed(0)
	{
		assert(size >= 0);

		m_data.resize(size);
		m_size = size;

		reset();
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	FixedSizeContainer<Element_Type, Container_Type>::~FixedSizeContainer()
		= default;

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	const Container_Type& FixedSizeContainer<Element_Type, Container_Type>::getData() const
	{
		return m_data;
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	Container_Type& FixedSizeContainer<Element_Type, Container_Type>::getData()
	{
		return m_data;
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	Element_Type* FixedSizeContainer<Element_Type, Container_Type>::getAvailableEntry()
	{
		return isFull() ? nullptr : &m_data[m_entriesUsed++];
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	Element_Type* FixedSizeContainer<Element_Type, Container_Type>::front()
	{
		return isEmpty() ? nullptr : &m_data[0];
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	Element_Type* FixedSizeContainer<Element_Type, Container_Type>::back()
	{
		return isEmpty() ? nullptr : &m_data[m_entriesUsed - 1];
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	const unsigned int& FixedSizeContainer<Element_Type, Container_Type>::size() const
	{
		return m_size;
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	const unsigned int& FixedSizeContainer<Element_Type, Container_Type>::getUsedEntries() const
	{
		return m_entriesUsed;
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	unsigned int FixedSizeContainer<Element_Type, Container_Type>::getRemainingEntries() const
	{
		return m_size - m_entriesUsed;
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	bool FixedSizeContainer<Element_Type, Container_Type>::isFull() const
	{
		return m_size == m_entriesUsed;
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	bool FixedSizeContainer<Element_Type, Container_Type>::isEmpty() const
	{
		return m_entriesUsed == 0;
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	void FixedSizeContainer<Element_Type, Container_Type>::reset()
	{
		m_entriesUsed = 0;
	}

	template<class Element_Type, class Container_Type /*= std::vector<Element_Type>*/>
	Element_Type& FixedSizeContainer<Element_Type, Container_Type>::operator[](const unsigned int& index)
	{
		assert(index < m_entriesUsed);
		return m_data[index];
	}
}