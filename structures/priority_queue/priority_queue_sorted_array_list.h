#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include <stdexcept>

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
		if (this->size() == 0) {
            this->list_->add(new PriorityQueueItem<T>(priority, data));
        } else {
            int index = this->size()/2;
            if (this->list_->at(index)->getPriority() > priority) {
                // ide do ľava smerom k nule
                while (index > 0) {
                    int aktPrior = this->list_->at(index)->getPriority();
                    int nextPrior = this->list_->at(index - 1)-> getPriority();

                    if (aktPrior >= priority && nextPrior <= priority) {
                        //todo skontrolovať či to dalo na správnu poziciu
                        this->list_->insert(new PriorityQueueItem<T>(priority, data), index);
                        return;
                    }
                    index--;
                }
                this->list_->insert(new PriorityQueueItem<T>(priority, data), 0);

            } else if (this->list_->at(index)->getPriority() <= priority) {
                // ide do prava dalej od nuly
                while (index > this->size()) {
                    int aktPrior = this->list_->at(index)->getPriority();
                    int nextPrior = this->list_->at(index + 1)-> getPriority();

                    if (aktPrior <= priority && nextPrior >= priority) {
                        //todo skontrolovať či to dalo na správnu poziciu
                        this->list_->insert(new PriorityQueueItem<T>(priority, data), index);
                        return;
                    }
                    index++;
                }
                this->list_->add(new PriorityQueueItem<T>(priority, data));
            }
        }
	}

	template<typename T>
	inline int PriorityQueueSortedArrayList<T>::indexOfPeek()
	{
        return PriorityQueueList<T>::list_->size() - 1;
	}
}