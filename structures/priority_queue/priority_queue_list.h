#pragma once

#include "priority_queue.h"
#include "../list/list.h"
#include <stdexcept>

namespace structures
{
    /// <summary> Spolocny predok pre vsetky prioritne fronty, ktorych implementujucim typom je zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
    template<typename T>
    class PriorityQueueList : public PriorityQueue<T>
    {
    public:
        /// <summary> Destruktor. </summary>
        ~PriorityQueueList();

        /// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom zoznamom. </summary>
        /// <returns> Pocet prvkov v prioritnom fronte implementovanom zoznamom. </returns>
        size_t size() override;

        /// <summary> Vymaze obsah prioritneho frontu implementovaneho zoznamom. </summary>
        void clear() override;

        /// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho zoznamom. </summary>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        T pop() override;

        /// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
        /// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        T& peek() override;

        /// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
        /// <returns> Priorita prvku s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany zoznamom prazdny. </exception>
        int peekPriority() override;

    protected:
        /// <summary> Konstruktor. </summary>
        /// <param name = "list"> Zoznam, do ktoreho sa budu ukladat prvky prioritneho frontu. </param>
        /// <remarks>
        /// Potomkovia ako list vlozia instanciu implicitne alebo explicitne implementovaneho zoznamu.
        /// Prioritny front implementovany zoznamom dealokuje tento objekt.
        /// </remarks>
        PriorityQueueList(List<PriorityQueueItem<T>*>* list);

        /// <summary> Vrati index v zozname, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
        /// <returns> Index prvku s najvacsou prioritou. </returns>
        /// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>
        virtual int indexOfPeek();

        /// <summary> Priradenie struktury. Pomocna metoda, ktora prebera referenciu, ktoru posle potomok. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        /// <summary>
        Structure& assignPrioQueueList(PriorityQueueList<T>& other);

    protected:
        /// <summary> Smernik na zoznam, do ktoreho sa ukladaju prvky prioritneho frontu. </summary>
        List<PriorityQueueItem<T>*>* list_;
    };

    template<typename T>
    inline PriorityQueueList<T>::PriorityQueueList(List<PriorityQueueItem<T>*>* list) :
        list_(list)
    {
    }

    template<typename T>
    inline PriorityQueueList<T>::~PriorityQueueList()
    {
        clear();
        delete list_;
        list_ = nullptr;
    }

    template<typename T>
    inline size_t PriorityQueueList<T>::size()
    {
        return list_->size();
    }

    template<typename T>
    inline void PriorityQueueList<T>::clear()
    {
        //for (auto item : xlist_)
        // delete item;
        // lest_ ->clear();

        for (auto item : *list_)
        {
            delete item;
        }
        list_->clear();
    }

    template<typename T>
    inline int PriorityQueueList<T>::indexOfPeek()
    {
        // int prioritz = int_max
        // int indexNaj = -1
        // int indexAkt = 0
        // for (auto item : *list_)
        //      if (item->getPriority() < priorytaNajve
        //          prioritaNaj = item->getPriorita()
        //          indexNaj = inedexAkt
        //      indexAkt =++
        // return indexNaj

        int prioritaNaj = INT_MAX;
        int indexNaj = -1;
        int indexAkt = 0;
        for (auto item : *list_) {
            if (item->getPriority() < prioritaNaj) {
                prioritaNaj = item->getPriority();
                indexNaj = indexAkt;
            }
            indexAkt++;
        }
        return indexNaj;
    }

    template<typename T>
    inline Structure& PriorityQueueList<T>::assignPrioQueueList(PriorityQueueList<T>& other)
    {
        // test identyty
        //clear()
        //for (auto item : *otherlist_)
        //  list ->add (new item cey kopy konstruktor)
        // return 
        if (this != &other) 
        {
            clear();
            for (auto item : *other.list_) {
                list_->add(new PriorityQueueItem<T>(*item));
            }
        }
        return *this;
    }

    template<typename T>
    inline T PriorityQueueList<T>::pop()
    {
        int index = indexOfPeek();

        if (index != -1) {
            PriorityQueueItem<T>* item = list_->removeAt(index);
            T data = item->accessData();
            delete item;
            return data;

        }
        else {
            throw std::logic_error("Priority queue is empty! Except from PriorityQueueList<T>::peek()");
        }
    }

    template<typename T>
    inline T& PriorityQueueList<T>::peek()
    {
        int index = indexOfPeek();
        if (index != -1) {
            return list_->at(index)->accessData();

        }
        else {
            throw std::logic_error("Priority queue is empty! Except from PriorityQueueList<T>::peek()");
        }
    }

    template<typename T>
    inline int PriorityQueueList<T>::peekPriority()
    {
        int index = indexOfPeek();
        if (index != -1) {
            return list_->at(index)->getPriority();

        }
        else {
            throw std::logic_error("Priority qyeue is empty! Except from PriorityQueueList<T>::peekPriority()");
        }

    }
}