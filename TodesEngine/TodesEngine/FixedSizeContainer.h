#pragma once

#include <vector>

namespace Todes
{
	/// <summary>
	/// Template class for a container, which can be resized.
	/// Random Access (Dependent on Containter_Type).
	/// Can be filled similar to a Stack.
	/// Its size in memory will stay the same at all times.
	/// Elements cannot be erased from it.
	/// </summary>
	/// <typeparam name="Element_Type">Type of the elements saved in this container.</typeparam>
	/// <typeparam name="Container_Type">Type of the Container used for storing elements.
	/// Needs to have a "void resize(unsigned)" function and stores elements of Element_Type.</typeparam>
	template<class Element_Type, class Container_Type = std::vector<Element_Type>>
	class FixedSizeContainer
	{
	public:
		/// <summary>
		/// FixedSizeContainer constructor
		/// </summary>
		/// <param name="size">Size of the Container</param>
		explicit FixedSizeContainer(const unsigned int& size);
		~FixedSizeContainer();

		/// <summary>
		/// Resets the number of used entries.
		/// </summary>
		void reset();

		/// <summary>
		/// Checks if the Container is empty.
		/// </summary>
		/// <returns>TRUE: No entries are in use. FALSE: There are entries in use.</returns>
		bool isEmpty() const;

		/// <summary>
		/// Checks if maximum number of entries has been used.
		/// </summary>
		/// <returns>TRUE: Container is full. FALSE: Container is not full.</returns>
		bool isFull() const;

		/**
		 * \brief Get the number of elements, which can still fit in the
		 * container
		 * \return The count of free entries.
		 */

		/// <summary>
		/// Returns the number of remaining slots that can fit by elements.
		/// </summary>
		unsigned int getRemainingEntries() const;

		/// <summary>
		/// Returns the number of entries that are already filled.
		/// </summary>
		const unsigned int& getUsedEntries() const;

		/// <summary>
		/// Returns the maximal number of elements that can fit this container.
		/// </summary>
		const unsigned int& size() const;

		/// <summary>
		/// Returns the last element of the container.
		/// </summary>
		Element_Type* back();

		/// <summary>
		/// Returns the first element of the container.
		/// </summary>
		Element_Type* front();

		/// <summary>
		/// Returns the next available element.
		/// </summary>
		/// <returns>A free element if there is space left. Nullptr if not.</returns>
		Element_Type* getAvailableEntry();

		/// <summary>
		/// Returns the internal container.
		/// </summary>
		/// <returns>All data with m_entriesUsed number of valid elements.</returns>
		Container_Type& getData();

		/// <summary>
		/// Returns the internal container.
		/// </summary>
		/// <returns>All data with m_entriesUsed number of valid elements.</returns>
		const Container_Type& getData() const;

		Element_Type& operator[](const unsigned int& index);

	private:
		unsigned int m_size;
		unsigned int m_entriesUsed;

		Container_Type m_data;
	};

}

#include "FixedSizeContainer.inl"