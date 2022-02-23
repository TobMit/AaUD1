#pragma once

#include "sequence_table.h"
#include "../list/array_list.h"
#include "../utils.h"

namespace structures
{

	/// <summary> Sekvencna neutriedena tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class UnsortedSequenceTable : public SequenceTable<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		UnsortedSequenceTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> NonortedSequenceTable, z ktorej sa prevezmu vlastnosti. </param>
		UnsortedSequenceTable(UnsortedSequenceTable<K, T>& other);

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati prvok tabulky na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Prvok tabulky na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do presahuje rozsah sekvencnej tabulky. </exception> 
		TableItem<K, T>& getItemAtIndex(int index);

		/// <summary> Vymeni prvky na indexoch. </summary>
		/// <param name = "indexFirst"> Index prveho prvku. </param>
		/// <param name = "indexSecond"> Index druheho prvku. </param>
		void swap(int indexFirst, int indexSecond);
	};

	template<typename K, typename T>
	inline UnsortedSequenceTable<K, T>::UnsortedSequenceTable() :
		SequenceTable<K, T>(new ArrayList<TableItem<K, T>*>())
	{
	}

	template<typename K, typename T>
	inline UnsortedSequenceTable<K, T>::UnsortedSequenceTable(UnsortedSequenceTable<K, T>& other) :
		UnsortedSequenceTable()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline bool UnsortedSequenceTable<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equals(dynamic_cast<UnsortedSequenceTable<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline TableItem<K, T>& UnsortedSequenceTable<K, T>::getItemAtIndex(int index)
	{
		//TODO 08: UnsortedSequenceTable
		throw std::runtime_error("UnsortedSequenceTable<K, T>::getItemAtIndex: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void UnsortedSequenceTable<K, T>::swap(int indexFirst, int indexSecond)
	{
		Utils::swap(getItemAtIndex(indexFirst), getItemAtIndex(indexSecond));
	}
}