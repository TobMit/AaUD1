#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include <cmath>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
        delete shortList_;
        delete longList_;
        shortList_ = nullptr;
        longList_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
        //todo skontolovať či to roby deep copy
        if (this != &other) {
            clear();
            PriorityQueueTwoLists<T> &newOther = dynamic_cast<PriorityQueueTwoLists<T> &>(other);
            shortList_->assign(*newOther.shortList_);
            for (auto item : *newOther.longList_) {
                longList_->add(item);
            }
        }
        return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
        return shortList_->size() + longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
        //todo skontorlovať memory leaky
		shortList_->clear();
        for (auto item : *longList_) {
            delete item;
        }
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{
        PriorityQueueItem<T>* tryPush = shortList_->pushAndRemove(priority, data);
        if (tryPush != nullptr) {
            longList_->add(tryPush);
        }
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{
        //todo skontrolovať memleaky
        static const int DEFAULT_NAHODNOTA = 4;
        if (shortList_->size() != 0 && longList_->size() != 0) {
            return shortList_->pop();
        } else {
            int newSize = sqrt(longList_->size());
            if (newSize >= DEFAULT_NAHODNOTA) {
                shortList_->trySetCapacity(newSize);
            }
            LinkedList<PriorityQueueItem<T>*>* newList = new LinkedList<PriorityQueueItem<T>*>();

            while (!longList_->isEmpty()) {
                auto removeItem = longList_->removeAt(0);
                auto tryPush = shortList_->pushAndRemove(removeItem->getPriority(),removeItem->accessData());
                delete removeItem;
                if (tryPush == nullptr) {
                    newList->add(tryPush);
                }
            }
            delete longList_;
            longList_ = newList;



        }
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
        return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
        return shortList_->peekPriority();
	}
}