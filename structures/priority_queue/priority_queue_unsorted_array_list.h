#pragma once

#include "priority_queue_list.h"

namespace structures
{
	/// <summary> Prioritny front implementovany neutriednym ArrayList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueUnsortedArrayList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueUnsortedArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany neutriednym ArrayList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueUnsortedArrayList(PriorityQueueUnsortedArrayList<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho neutriednym ArrayList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho neutriednym ArrayList-om. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany neutriednym ArrayList-om prazdny. </exception>
		T pop() override;
	};

	template<typename T>
	PriorityQueueUnsortedArrayList<T>::PriorityQueueUnsortedArrayList() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueUnsortedArrayList<T>::PriorityQueueUnsortedArrayList(PriorityQueueUnsortedArrayList<T>& other) :
		PriorityQueueUnsortedArrayList<T>()
	{
		assign(other);
	}

	template<typename T>
	inline Structure& PriorityQueueUnsortedArrayList<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assign(dynamic_cast<PriorityQueueList<T>&>(other));
	}

	template<typename T>
	void PriorityQueueUnsortedArrayList<T>::push(int priority, const T& data)
	{
		PriorityQueueList<T>::list_->add(new PriorityQueueItem<T>(priority, data));
	}

	template<typename T>
	inline T PriorityQueueUnsortedArrayList<T>::pop()
	{
		//std::swap(a,b)
		//utils::swap(a,b)
		int index = PriorityQueueList<T>::indexOfPeek();
		if (index != -1){
			int indexLast = PriorityQueueList<T>::list_->size() - 1;

			if (index != indexLast) {
				Utils::swap(PriorityQueueList<T>::list_->at(index), PriorityQueueList<T>::list_->at(indexLast));
			}
			PriorityQueueItem<T>* item = list_->removeAt(index);
			T data = item->accessData();
			delete item;
			return data;
			}
		else {
			throw std::logic_error("Prioritz qeue is empty! Except from PriorityQueueUnsortedArrayList<T>::pop()");
		}
	}
}