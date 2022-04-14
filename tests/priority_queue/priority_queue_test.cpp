#include "priority_queue_test.h"

namespace tests
{
    PriorityQueueTestInterface::PriorityQueueTestInterface() :
        SimpleTest("Interface")
    {
    }

    void PriorityQueueTestInterface::test()
    {
        int x = 0;
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        queue->push(0, x);
        queue->peek();
        queue->peekPriority();
        queue->pop();
        queue->assign(*queue);
        delete queue;
        this->logPass("Compiled.");
    }

    structures::PriorityQueue<int>* PriorityQueueUnsortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueUnsortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLimitedSortedArrayListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLimitedSortedArrayList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueLinkedListTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueLinkedList<int>();
    }

    structures::PriorityQueue<int>* PriorityQueueTwoListsTestInterface::makePriorityQueue()
    {
        return new structures::PriorityQueueTwoLists<int>();
    }

    structures::PriorityQueue<int>* HeapTestInterface::makePriorityQueue()
    {
        return new structures::Heap<int>();
    }

    PriorityQueueUnsortedArrayListTestOverall::PriorityQueueUnsortedArrayListTestOverall() :
        ComplexTest("PriorityQueueUnsortedArray")
    {
        addTest(new PriorityQueueUnsortedArrayListTestInterface());
    }

    PriorityQueueSortedArrayListTestOverall::PriorityQueueSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueSortedArrayList")
    {
        addTest(new PriorityQueueSortedArrayListTestInterface());
    }

    PriorityQueueLimitedSortedArrayListTestOverall::PriorityQueueLimitedSortedArrayListTestOverall() :
        ComplexTest("PriorityQueueLimitedSortedArrayList")
    {
        addTest(new PriorityQueueLimitedSortedArrayListTestInterface());
    }

    PriorityQueueLinkedListTestOverall::PriorityQueueLinkedListTestOverall() :
        ComplexTest("PriorityQueueLinkedList")
    {
        addTest(new PriorityQueueLinkedListTestInterface());
    }

    PriorityQueueTwoListsTestOverall::PriorityQueueTwoListsTestOverall() :
        ComplexTest("PriorityQueueTwoLists")
    {
        addTest(new PriorityQueueTwoListsTestInterface());
        addTest(new PriorityQueueTwoListsFunctionTest());
        addTest(new QueueTwoListsUloha2());
        addTest(new QueueTwoListsUloha2());
    }

    HeapTestOverall::HeapTestOverall() :
        ComplexTest("Heap")
    {
        addTest(new HeapTestInterface());
        addTest(new HeapQueueListFunctionTest());
        addTest(new HeapUloha2());
        addTest(new HeapUloha3());
    }

    PriorityQueueTestOverall::PriorityQueueTestOverall() :
        ComplexTest("PriorityQueue")
    {
        addTest(new PriorityQueueUnsortedArrayListTestOverall());
        addTest(new PriorityQueueSortedArrayListTestOverall());
        addTest(new PriorityQueueLimitedSortedArrayListTestOverall());
        addTest(new PriorityQueueLinkedListTestOverall());
        addTest(new PriorityQueueTwoListsTestOverall());
        addTest(new HeapTestOverall());
    }

    PriorityQueueTestFunctionsTest::PriorityQueueTestFunctionsTest() :
            SimpleTest("Complex test")
    {
    }
    void PriorityQueueTestFunctionsTest::test()
    {
        /*
        queue->push(0, x);
        queue->peek();
        queue->peekPriority();
        queue->pop();
        queue->assign(*queue);
        delete queue; */
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        for (int i = 1; i <= 10; ++i) {
            queue->push(i, i);
        }
        SimpleTest::assertTrue(queue->size() == 10,"Velkost PriorityQueue by mala byt 10 a je: " + std::to_string(queue->size()));

        structures::PriorityQueue<int>* copyQueue = this->makePriorityQueue(*queue);
        SimpleTest::assertTrue(copyQueue->size() == 10, "Testujem ci kopirovaci konstruktor funguje spravne.");
        SimpleTest::assertTrue(queue->peek() == 1, "Hodnota peek by mala byt 1 a je " + std::to_string(queue->peek()));
        SimpleTest::assertTrue(queue->peekPriority() == 1, "Hodnota peekPriority by mala byt 1 a je " + std::to_string(queue->peekPriority()));
        /*int hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 1, "Hodnota peek by mala byt 1 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 2, "Hodnota peek by mala byt 2 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 3, "Hodnota peek by mala byt 3 a je " + std::to_string(hodnota));
        */

        for (int i = 1; i <= 10; ++i) {
            SimpleTest::logInfo(std::to_string(queue->peek()) + " " + std::to_string(queue->peekPriority()) + " " + std::to_string(queue->pop()));
        }
        delete copyQueue;
        delete queue;
    }

    QueueUloha2::QueueUloha2()
            : SimpleTest("Uloha2")
    {

    }
    void QueueUloha2::test()
    {
        this->info();
        structures::Logger::getInstance().logInfo("Testovanie Uloha2!");
        // scenár A
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        cyklus('A', 35, 35, 30, *queue);
        delete queue;

        // Scenár B
        queue = this->makePriorityQueue();
        cyklus('B', 50, 30, 20, *queue);
        delete queue;

        // Scenár C
        queue = this->makePriorityQueue();
        cyklus('C', 70, 25, 5, *queue);
        delete queue;

    }
    void QueueUloha2::cyklus(char oznacenie, int podielPush, int podielPop, int podielPeek,
                             structures::PriorityQueue<int> &queue)
    {
        //da sa na define int... alebo static const int ...
        static const int OPAKOVANIA = 100000;
        static const int MAX_DATA_VALUE_IN_QUEUE = 100;
        static const int MAX_PRIORITY = 100000;

        structures::Logger::getInstance().logInfo("Zacal sa test " + std::string(1, oznacenie) + "!");
        structures::Logger::getInstance().logInfo("Celkovo Push, Celkovo Pop, Celkovo Peek, celkova dlzka Scenara " + std::string(1, oznacenie) + "!");

        int opPush = getPomer(OPAKOVANIA, podielPush);
        int opPop = getPomer(OPAKOVANIA, podielPop);
        int opPeek = getPomer(OPAKOVANIA, podielPeek);

        std::vector<char>pool;
        for (unsigned i = 0; i < opPush; i++)
        {
            pool.push_back(1);
        }
        for (unsigned i = 0; i < opPop; i++)
        {
            pool.push_back(2);
        }
        for (unsigned i = 0; i < opPeek; i++)
        {
            pool.push_back(3);
        }


        Microseconds durationPush = std::chrono::microseconds(0);
        Microseconds durationPop = std::chrono::microseconds(0);
        Microseconds durationPeek = std::chrono::microseconds(0);

        while (!pool.empty())
        {
            int index = rand() % pool.size();
            int cislo;
            int priority;
            switch (pool.at(index))
            {
                case 1:
                    cislo = rand() % MAX_DATA_VALUE_IN_QUEUE;
                    priority = rand() % MAX_PRIORITY;
                    SimpleTest::startStopwatch();
                    queue.push(priority,cislo);
                    SimpleTest::stopStopwatch();
                    durationPush += SimpleTest::getElapsedTime();

                    break;

                case 2:
                    if (queue.size() != 0) {
                        SimpleTest::startStopwatch();
                        queue.pop();
                        SimpleTest::stopStopwatch();
                        durationPop += SimpleTest::getElapsedTime();
                    }
                    break;

                case 3:
                    if (queue.size() != 0) {
                        SimpleTest::startStopwatch();
                        queue.peek();
                        SimpleTest::stopStopwatch();
                        durationPeek += SimpleTest::getElapsedTime();
                    }
                    break;

            }

            pool.erase(pool.begin() + index);
        }

        structures::Logger::getInstance().logDuration(0, durationPush + durationPop + durationPeek, std::to_string(durationPush.count() ) + "," + std::to_string(durationPop.count()) + "," + std::to_string(durationPeek.count()));
    }

    int QueueUloha2::getPomer(int const OPAKOVANIA, int pomer)
    {
        return (pomer * OPAKOVANIA) / 100;
    }

    //--------------------------------------------------- Uloha 3 ------------------------------------------------------------
    ListUloha3::ListUloha3():
            SimpleTest("Uloha3")
    {
    }
    void ListUloha3::test()
    {
        structures::Logger::getInstance().logInfo("Testovanie Uloha3!");
        static const int MAX = 1000000;
        static const int KROK = 10000;
        static const int POC_VELKOST = 1000;
        static const int POC_OPAKOVANI = 100;
        int sizeOfList;
        sizeOfList = POC_VELKOST;

        structures::Logger::getInstance().logInfo("Velkost listu, Priemerna dlzka na " + std::to_string(POC_OPAKOVANI) + " opakovani");

        //--------------------Insert-----------------
        this->infoPush();
        while (sizeOfList <= MAX)
        {
            structures::Logger::getInstance().logDuration(0, cyklusPush(sizeOfList, POC_OPAKOVANI), std::to_string(sizeOfList));
            sizeOfList += KROK;
        }

        //----------------------At-------------------

        this->infoPop();
        sizeOfList = POC_VELKOST;
        while (sizeOfList <= MAX)
        {
            structures::Logger::getInstance().logDuration(0, cyklusPop(sizeOfList, POC_OPAKOVANI), std::to_string(sizeOfList));
            sizeOfList += KROK;
        }

        //------------------RemoveAt-----------------
        this->infoPeek();
        sizeOfList = POC_VELKOST;
        while (sizeOfList <= MAX)
        {
            structures::Logger::getInstance().logDuration(0, cyklusPeek(sizeOfList, POC_OPAKOVANI), std::to_string(sizeOfList));
            sizeOfList += KROK;
        }

    }

    void ListUloha3::repairList(int SIZE, structures::PriorityQueue<int> &queue) {
        // zväčšujem a mažem listy na koncoch
        while (queue.size() != SIZE) {
            if (queue.size() < SIZE) {
                queue.add(rand() % INT16_MAX / 2);
            } else {
                queue.removeAt(queue.size() - 1);
            }
        }
    }

    //------------------------------------------------------------------------
    Microseconds ListUloha3::cyklusPush(int size, const int POC_OPAKOVANI)
    {
        structures::PriorityQueue<int>* list = this->makePriorityQueue();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            repairList(size,*list);
            duration += durationPush(rand() % INT16_MAX / 2, rand() % list->size(), *list);
        }
        delete list;
        return duration / POC_OPAKOVANI;

    }

    Microseconds ListUloha3::durationPush(int cislo, int index, structures::PriorityQueue<int> &queue)
    {
        SimpleTest::startStopwatch();
        queue.insert(cislo, index);
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    //------------------------------------------------------------------------
    Microseconds ListUloha3::cyklusPop(int size, const int POC_OPAKOVANI)
    {
        structures::PriorityQueue<int>* list = this->makePriorityQueue();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu
        repairList(size, *list); // repair list je volaná tu pretože viem že sa s listom nič pri volaní at nestane

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            duration += durationPop(rand() % size, *list);
        }
        delete list;
        return duration / POC_OPAKOVANI;
    }

    Microseconds ListUloha3::durationPop(int index, structures::PriorityQueue<int> &queue)
    {
        SimpleTest::startStopwatch();
        queue.at(index) = 7;
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    //------------------------------------------------------------------------
    Microseconds ListUloha3::cyklusPeek(int size, const int POC_OPAKOVANI)
    {
        structures::PriorityQueue<int>* list = this->makePriorityQueue();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            repairList(size,*list);
            duration += durationPeek(rand() % size, *list);
        }
        delete list;
        return duration / POC_OPAKOVANI;

    }

    Microseconds ListUloha3::durationPeek(int index, structures::PriorityQueue<int> &queue)
    {
        SimpleTest::startStopwatch();
        queue.removeAt(index);
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }
}