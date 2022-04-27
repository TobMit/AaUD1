#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include <stdexcept>
#include "iostream"

namespace structures
{
	/// <summary> Prioritny front implementovany utriednym ArrayList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueSortedArrayList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueSortedArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueSortedArrayList(PriorityQueueSortedArrayList<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

        void degug(){
            for(auto item : *this->list_) {
                std::cout << item->getPriority() << std::endl;
            }
        }

	protected:
		/// <summary> Vrati index v utriedenom ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>
		int indexOfPeek() override;
	};

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList(PriorityQueueSortedArrayList<T>& other) :
        PriorityQueueSortedArrayList<T>()
	{
        assign(other);
	}

	template<typename T>
	inline Structure& PriorityQueueSortedArrayList<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueList<T> &>(other));
	}

	template<typename T>
	inline void PriorityQueueSortedArrayList<T>::push(int priority, const T& data)
	{
        if (this->isEmpty()){
            this->list_->add(new PriorityQueueItem<T>(priority, data));
            return;
        }
        int index;
        int hornaHranica = this->size()-1;
        int dolnaHranica = 0;
        while (true) {
            index = (dolnaHranica + hornaHranica )/2;
            if (this->list_->at(index)->getPriority() == priority) {
                this->list_->insert(new PriorityQueueItem<T>(priority, data), index);
                return;
            } else {
                if (dolnaHranica == hornaHranica) {
                    this->list_->insert(new PriorityQueueItem<T>(priority, data), dolnaHranica);
                    return;
                } else {
                    if (this->list_->at(index)->getPriority() > priority) {
                        dolnaHranica = index + 1;
                    } else {
                        hornaHranica = index;
                    }
                }
            }
        }



	}

	template<typename T>
	inline int PriorityQueueSortedArrayList<T>::indexOfPeek()
	{
        return PriorityQueueList<T>::list_->size() - 1;
	}
}