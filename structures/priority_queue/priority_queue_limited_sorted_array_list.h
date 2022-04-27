#pragma once

#include "priority_queue_sorted_array_list.h"
#include <stdexcept>

namespace structures
{
    /// <summary> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
    template<typename T>
    class PriorityQueueLimitedSortedArrayList : public PriorityQueueSortedArrayList<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        PriorityQueueLimitedSortedArrayList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou, z ktoreho sa prevezmu vlastnosti. </param>
        PriorityQueueLimitedSortedArrayList(PriorityQueueLimitedSortedArrayList<T>& other);

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou. </summary>
        /// <param name = "priority"> Priorita vkladaneho prvku. </param>
        /// <param name = "data"> Vkladany prvok. </param>
        /// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front plny. </exception>
        void push(int priority, const T& data) override;

        /// <summary>
        ///  Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om s obmedzenou kapacitou.
        ///  V pripade, ze je prioritny front plny, odstrani polozku s najmensou prioritou z prioritneho frontu a vrati smernik na nu.
        ///  V opacnom pripade vrati nullptr.
        /// </summary>
        /// <param name = "priority"> Priorita vkladaneho prvku. </param>
        /// <param name = "data"> Vkladany prvok. </param>
        /// <returns> Smernik na odstranenu polozku alebo nullptr. </returns>
        PriorityQueueItem<T>* pushAndRemove(int priority, T data);

        /// <summary> Vrati najmensiu prioritu nachadzajucu sa v prioritnom fronte. </summary>
        /// <returns> Najmensiu priorita nachadzajuca sa v prioritnom fronte. </returns>
        int minPriority();

        /// <summary>
        ///  Pokusi sa zmenit kapacitu prioritneho frontu.
        ///  Kapacitu je mozne zmensit len ak nova kapacita nie je mensia ako aktualny pocet poloziek v prioritnom fronte.
        ///  V opacnom pripade nedojde k zmene kapacity.
        /// </summary>
        /// <param name = "capacity"> Nova kapacita. </param>
        /// <returns> true, ak sa kapacitu podarilo zmenit, false inak. </returns>
        bool trySetCapacity(size_t capacity);

    private:
        /// <summary> Kapacita prioritneho frontu. </summary>
        size_t capacity_;
    };

    template<typename T>
    PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList() :
        PriorityQueueSortedArrayList<T>(),
        capacity_(2)
    {
    }

    template<typename T>
    PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList(PriorityQueueLimitedSortedArrayList<T>& other) :
        PriorityQueueSortedArrayList<T>(other),
        capacity_(other.capacity_)
    {
    }

    template<typename T>
    inline Structure& PriorityQueueLimitedSortedArrayList<T>::assign(Structure& other)
    {
        if (this != &other) {
            auto newOther = dynamic_cast<PriorityQueueLimitedSortedArrayList<T> &>(other);
            capacity_ = newOther.capacity_;
            PriorityQueueSortedArrayList<T>::assign(other);
        }
        return *this;
    }

    template<typename T>
    void PriorityQueueLimitedSortedArrayList<T>::push(int priority, const T& data)
    {
        if (capacity_ >= this->size()) {
            throw std::logic_error("Limited queue is full! Except from PriorityQueueLimitedSortedArrayList<T>::push()");
        } else {
            PriorityQueueSortedArrayList<T>::push(priority, data);
        }
    }

    template<typename T>
    inline PriorityQueueItem<T>* PriorityQueueLimitedSortedArrayList<T>::pushAndRemove(int priority, T data)
    {
        PriorityQueueItem<T> *returnData = nullptr;
        PriorityQueueSortedArrayList<T>::push(priority, data);
        if (PriorityQueueList<T>::size() > capacity_) {
            returnData = PriorityQueueList<T>::list_->removeAt(0);
        }
        return returnData;
    }

    template<typename T>
    inline int PriorityQueueLimitedSortedArrayList<T>::minPriority()
    {
        if (this->list_->isEmpty()) {
            throw std::logic_error("Queue is empty! Except from PriorityQueueLimitedSortedArrayList<T>::minPriority()");
        } else {
            int minPriority = PriorityQueueList<T>::list_->at(0)->getPriority();
            return minPriority;
        }
    }

    template<typename T>
    inline bool PriorityQueueLimitedSortedArrayList<T>::trySetCapacity(size_t capacity)
    {
        if (capacity < this->size()) {
            return false;
        } else {
            capacity_ = capacity;
        }
    }
}