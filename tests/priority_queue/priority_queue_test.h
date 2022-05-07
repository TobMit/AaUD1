#pragma once

#include "../test.h"
#include "../../structures/priority_queue/priority_queue.h"
#include "../../structures/priority_queue/priority_queue_list.h"
#include "../../structures/priority_queue/heap.h"
#include "../../structures/priority_queue/priority_queue_limited_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_linked_list.h"
#include "../../structures/priority_queue/priority_queue_sorted_array_list.h"
#include "../../structures/priority_queue/priority_queue_two_lists.h"
#include "../../structures/priority_queue/priority_queue_unsorted_array_list.h"
#include "../../structures/heap_monitor.h"

namespace tests
{
    /// <summary>
    /// Zavola vsetky metody z rozhrania prioritneho frontu avsak nekontroluje ich spravnost.
    /// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
    /// </summary>
    class PriorityQueueTestInterface
        : public SimpleTest
    {
    public:
        PriorityQueueTestInterface();
        void test() override;

    protected:
        virtual structures::PriorityQueue<int>* makePriorityQueue() = 0;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueUnsortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueSortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueLimitedSortedArrayListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueLinkedListTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class PriorityQueueTwoListsTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zavola vsetky metody prioritneho frontu.
    /// </summary>
    class HeapTestInterface
        : public PriorityQueueTestInterface
    {
    protected:
        structures::PriorityQueue<int>* makePriorityQueue() override;
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueUnsortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueUnsortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueSortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueSortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueLimitedSortedArrayListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueLimitedSortedArrayListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueLinkedListTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueLinkedListTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class PriorityQueueTwoListsTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueTwoListsTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju dany prioritny front.
    /// </summary>
    class HeapTestOverall
        : public ComplexTest
    {
    public:
        HeapTestOverall();
    };

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju prioritny front.
    /// </summary>
    class PriorityQueueTestOverall
        : public ComplexTest
    {
    public:
        PriorityQueueTestOverall();
    };

    //-------------------------------- TESTY FUNKCNOSTI --------------------------------------
    /// <summary>
    /// Test ktory skontroluje ci funguje add a insert v V oboch implementáciach pQueue
    /// </summary>
    class PriorityQueueTestFunctionsTest
            : public SimpleTest {
    public:
        PriorityQueueTestFunctionsTest();
        void test() override;

    protected:
        virtual structures::PriorityQueue<int> * makePriorityQueue() const = 0;
        virtual structures::PriorityQueue<int> * makePriorityQueue(structures::PriorityQueue<int> &other) const = 0;
    };

    class HeapQueueListFunctionTest
            :public PriorityQueueTestFunctionsTest {
    protected:
        structures::PriorityQueue<int> * makePriorityQueue() const override {
            return new structures::Heap<int>();
        };
        structures::PriorityQueue<int> * makePriorityQueue(structures::PriorityQueue<int> &other) const override {
            structures::Heap<int>& priorityQueue = dynamic_cast<structures::Heap<int>&>(other);
            return new structures::Heap<int>(priorityQueue);
        };
    };

    class PriorityQueueTwoListsFunctionTest
            :public PriorityQueueTestFunctionsTest {
    protected:
        structures::PriorityQueue<int> * makePriorityQueue() const override {
            return new structures::PriorityQueueTwoLists<int>();
        };
        structures::PriorityQueue<int> * makePriorityQueue(structures::PriorityQueue<int> &other) const override {
            structures::PriorityQueueTwoLists<int>& priorityQueue = dynamic_cast<structures::PriorityQueueTwoLists<int>&>(other);
            return new structures::PriorityQueueTwoLists<int>(priorityQueue);
        };
    };

    class PriorityQueueSortedArrayListFunctionTest
            :public PriorityQueueTestFunctionsTest {
    protected:
        structures::PriorityQueue<int> * makePriorityQueue() const override {
            return new structures::PriorityQueueSortedArrayList<int>();
        };
        structures::PriorityQueue<int> * makePriorityQueue(structures::PriorityQueue<int> &other) const override {
            structures::PriorityQueueSortedArrayList<int>& priorityQueue = dynamic_cast<structures::PriorityQueueSortedArrayList<int>&>(other);
            return new structures::PriorityQueueSortedArrayList<int>(priorityQueue);
        };
    };
    //------------------------------------ Uloha 2 ------------------------------------------------

    /// <summary>
    /// Testovanie pre úlohu 2
    /// </summary>
    class PriorityQueueUloha2
            :public SimpleTest
    {
    public:
        PriorityQueueUloha2();
        void test() override;
    private:
        void
        cyklus(char oznacenie, int podielPush, int podielPop, int podielPeek, structures::PriorityQueue<int> &pQueue);
        int getPomer(int const OPAKOVANIA, int pomer);
    protected:
        virtual structures::PriorityQueue<int> *makePriorityQueue() const = 0;
        virtual void info() const = 0;
    };


    class HeapUloha2
            : public PriorityQueueUloha2
    {
    protected:
        structures::PriorityQueue<int> *makePriorityQueue() const override
        {
            return new structures::Heap<int>();
        };

        void info() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie Heap!");
        }
    };

    class QueueTwoListsUloha2
            : public PriorityQueueUloha2
    {
    protected:
        structures::PriorityQueue<int> *makePriorityQueue() const override
        {
            return new structures::PriorityQueueTwoLists<int>();
        };
        void info() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie PriorityQueueTwoList!");
        }
    };


    //------------------------------------------- Uloha 3 -----------------------------------------------
    class PriorityQueueUloha3
            :public SimpleTest
    {
    public:
        PriorityQueueUloha3();
        void test() override;
    private:
        Milliseconds cyklusPush(int size, const int POC_OPAKOVANI);
        Milliseconds durationPush(int priority, int cislo, structures::PriorityQueue<int> &pQueue);

        Milliseconds cyklusPop(int size, const int POC_OPAKOVANI, bool extraMeranie);
        Milliseconds durationPop(structures::PriorityQueue<int> &pQueue);

        Milliseconds cyklusPeek(int size, const int POC_OPAKOVANI);
        Milliseconds durationPeek(structures::PriorityQueue<int> &pQueue);

        /// rapairQue udrzuje velkost daného frontu na potrebnej dlzke. Keď treba, tak front zväčší a naplni hodnotami a ked je velky tak zmensi
        /// \param SIZE - velkost listu ktora sa ma udrziavat
        /// \param pQueue - list kotry sa ma opravit
        void repairQueue(int SIZE, int MAX_PRIOR, structures::PriorityQueue<int> &pQueue);
    protected:
        virtual structures::PriorityQueue<int> *makePriorityQueue() const = 0;
        virtual void infoPush() const = 0;
        virtual void infoPop() const = 0;
        virtual void infoPeek() const = 0;
        virtual bool isPQ2L() const = 0;

    };

    class HeapUloha3
            : public PriorityQueueUloha3
    {
    protected:
        structures::PriorityQueue<int> *makePriorityQueue() const override
        {
            return new structures::Heap<int>();
        };

        void infoPush() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie Heap - Push");
        }
        void infoPop() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie Heap - Pop");
        }
        void infoPeek() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie Heap - Peek");
        }
        bool isPQ2L() const override
        {
            return false;
        }
    };

    class QueueTwoListsUloha3
            : public PriorityQueueUloha3
    {
    protected:
        structures::PriorityQueue<int> *makePriorityQueue() const override
        {
            return new structures::PriorityQueueTwoLists<int>();
        };

        void infoPush() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie PriorityQueueTwoList - Push");
        }
        void infoPop() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie PriorityQueueTwoList - Pop");
        }
        void infoPeek() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie PriorityQueueTwoList - Peek");
        }
        bool isPQ2L() const override
        {
            return true;
        }
    };
}