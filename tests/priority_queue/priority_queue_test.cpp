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
        addTest(new PriorityQueueSortedArrayListFunctionTest());
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
        addTest(new QueueTwoListsUloha3);
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
        srand(time(NULL));
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
        structures::PriorityQueue<int>* queue = this->makePriorityQueue();
        for (int i = 1; i <= 10; ++i) {
            queue->push(i, i);
        }

        /*for (int i = 1; i <= 100; ++i) {
            // vkladanie s nahodnou prioritov
            int cislo = rand()%1000;
            queue->push(cislo, cislo);
        }*/

        SimpleTest::assertTrue(queue->size() == 10,"Velkost PriorityQueue by mala byt 10 a je: " + std::to_string(queue->size()));

        structures::PriorityQueue<int>* copyQueue = this->makePriorityQueue(*queue);
        SimpleTest::assertTrue(copyQueue->size() == 10, "Testujem ci kopirovaci konstruktor funguje spravne.");
        SimpleTest::assertTrue(queue->peek() == 1, "Hodnota peek by mala byt 1 a je " + std::to_string(queue->peek()));
        SimpleTest::assertTrue(queue->peekPriority() == 1, "Hodnota peekPriority by mala byt 1 a je " + std::to_string(queue->peekPriority()));
        int hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 1, "Hodnota pop by mala byt 1 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 2, "Hodnota pop by mala byt 2 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 3, "Hodnota pop by mala byt 3 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 4, "Hodnota pop by mala byt 4 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 5, "Hodnota pop by mala byt 5 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 6, "Hodnota pop by mala byt 6 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 7, "Hodnota pop by mala byt 7 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 8, "Hodnota pop by mala byt 8 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 9, "Hodnota pop by mala byt 9 a je " + std::to_string(hodnota));
        hodnota = queue->pop();
        SimpleTest::assertTrue(hodnota == 10, "Hodnota pop by mala byt 10 a je " + std::to_string(hodnota));

        structures::PriorityQueue<int>* assignQueue = this->makePriorityQueue();
        assignQueue->assign(*copyQueue);
        SimpleTest::assertTrue(assignQueue->size() == 10, "Testujem ci kopirovaci konstruktor funguje spravne.");
        SimpleTest::logInfo(" \"Ocna\" kontrola copyQueue assign. Cisla v riadkoch maju bit rovnake a ist od 1 do 10 ");
        for (int i = 1; i <= 10; ++i) {
            int peek = copyQueue->peek();
            int peekPr = copyQueue->peekPriority();
            SimpleTest::logInfo(std::to_string(peek) + " " + std::to_string(peekPr) + " " + std::to_string(copyQueue->pop()));
            //na macos mi to zoborie aj takto ale vo visual to nefunguje správne
            //SimpleTest::logInfo(std::to_string(copyQueue->peek()) + " " + std::to_string(copyQueue->peekPriority()) + " " + std::to_string(copyQueue->pop()));
        }

        SimpleTest::logPass("Complet");
        delete assignQueue;
        delete copyQueue;
        delete queue;
    }

    //--------------------------------------------------- Uloha 2 ------------------------------------------------------------
    PriorityQueueUloha2::PriorityQueueUloha2()
            : SimpleTest("Uloha2")
    {

    }
    void PriorityQueueUloha2::test()
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
    void PriorityQueueUloha2::cyklus(char oznacenie, int podielPush, int podielPop, int podielPeek,
                                     structures::PriorityQueue<int> &pQueue)
    {
        static const int OPAKOVANIA = 100000;
        static const int MAX_DATA_VALUE_IN_QUEUE = 100;
        static const int MAX_PRIORITY = 100000;

        structures::Logger::getInstance().logInfo("Zacal sa Scenar " + std::string(1, oznacenie) + "!");
        structures::Logger::getInstance().logInfo("Celkovo Push, Celkovo Pop, Celkovo Peek, celkova dlzka Scenara!");

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
                    pQueue.push(priority, cislo);
                    SimpleTest::stopStopwatch();
                    durationPush += SimpleTest::getElapsedTime();

                    break;

                case 2:
                    if (!pQueue.isEmpty()) {
                        SimpleTest::startStopwatch();
                        pQueue.pop();
                        SimpleTest::stopStopwatch();
                        durationPop += SimpleTest::getElapsedTime();
                    }
                    break;

                case 3:
                    if (!pQueue.isEmpty()) {
                        SimpleTest::startStopwatch();
                        pQueue.peek();
                        SimpleTest::stopStopwatch();
                        durationPeek += SimpleTest::getElapsedTime();
                    }
                    break;

            }

            pool.erase(pool.begin() + index);
        }

        structures::Logger::getInstance().logDuration(0, durationPush + durationPop + durationPeek, std::to_string(durationPush.count() ) + "," + std::to_string(durationPop.count()) + "," + std::to_string(durationPeek.count()));
    }

    int PriorityQueueUloha2::getPomer(int const OPAKOVANIA, int pomer)
    {
        return (pomer * OPAKOVANIA) / 100;
    }

    //--------------------------------------------------- Uloha 3 ------------------------------------------------------------
    PriorityQueueUloha3::PriorityQueueUloha3():
            SimpleTest("Uloha3")
    {
    }
    void PriorityQueueUloha3::test()
    {
        structures::Logger::getInstance().logInfo("Testovanie Uloha3!");
        static const int MAX = 1000000;
        static const int KROK = 10000;
        static const int POC_VELKOST = 1000;
        static const int POC_OPAKOVANI = 100;
        int sizeOfQueue;
        sizeOfQueue = POC_VELKOST;

        structures::Logger::getInstance().logInfo("Velkost PriorityQueue, Priemerna dlzka na " + std::to_string(POC_OPAKOVANI) + " opakovani, Extra meranie pre PQ2");

        //----------------- Push -----------------
        this->infoPush();
        while (sizeOfQueue <= MAX)
        {
            structures::Logger::getInstance().logDuration(0, cyklusPush(sizeOfQueue, POC_OPAKOVANI), std::to_string(sizeOfQueue));
            sizeOfQueue += KROK;
        }

        //------------------ Pop -----------------

        this->infoPop();
        sizeOfQueue = POC_VELKOST;
        while (sizeOfQueue <= MAX)
        {
            cyklusPop(sizeOfQueue, POC_OPAKOVANI, isPQ2L()), std::to_string(sizeOfQueue);
            sizeOfQueue += KROK;
        }

        //---------------- Peek -----------------
        this->infoPeek();
        sizeOfQueue = POC_VELKOST;
        while (sizeOfQueue <= MAX)
        {
            structures::Logger::getInstance().logDuration(0, cyklusPeek(sizeOfQueue, POC_OPAKOVANI), std::to_string(sizeOfQueue));
            sizeOfQueue += KROK;
        }

    }

    void PriorityQueueUloha3::repairQueue(int SIZE, int MAX_PRIOR, structures::PriorityQueue<int> &pQueue) {
        // zväčšujem a mažem data v queue na koncoch
        while (pQueue.size() != SIZE) {
            if (pQueue.size() < SIZE) {
                pQueue.push(rand() % MAX_PRIOR, rand() % INT16_MAX / 2);
            } else {
                pQueue.pop();
            }
        }
    }

    //------------------------------------------------------------------------
    Microseconds PriorityQueueUloha3::cyklusPush(int size, const int POC_OPAKOVANI)
    {
        structures::PriorityQueue<int>* pQueue = this->makePriorityQueue();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            repairQueue(size, size, *pQueue);
            duration += durationPush(rand() % INT_MAX / 2, rand() % pQueue->size(), *pQueue);
        }
        delete pQueue;
        //return duration / POC_OPAKOVANI;
        return duration;

    }

    Microseconds PriorityQueueUloha3::durationPush(int priority, int cislo, structures::PriorityQueue<int> &pQueue)
    {
        SimpleTest::startStopwatch();
        pQueue.push(priority, cislo);
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    //------------------------------------------------------------------------
    Microseconds PriorityQueueUloha3::cyklusPop(int size, const int POC_OPAKOVANI, bool extraMeranie)
    {
        structures::PriorityQueue<int>* pQueue = this->makePriorityQueue();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu
        Microseconds durationExtra = std::chrono::microseconds(0);

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            repairQueue(size, size, *pQueue);
            duration += durationPop(*pQueue);
        }

        if (extraMeranie) {
            for (int i = 0; i < POC_OPAKOVANI; i++)
            {
                repairQueue(size, size, *pQueue);
                durationExtra += durationPop(*pQueue);
            }

            structures::Logger::getInstance().logDuration(0,durationExtra / POC_OPAKOVANI, std::to_string(size) + "," +  std::to_string((duration / POC_OPAKOVANI).count()));

        } else {
            structures::Logger::getInstance().logDuration(0,duration / POC_OPAKOVANI,std::to_string(size));
        }

        delete pQueue;
        //return duration / POC_OPAKOVANI;
        return std::chrono::microseconds(0);
    }

    Microseconds PriorityQueueUloha3::durationPop(structures::PriorityQueue<int> &pQueue)
    {
        SimpleTest::startStopwatch();
        pQueue.pop();
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    //------------------------------------------------------------------------
    Microseconds PriorityQueueUloha3::cyklusPeek(int size, const int POC_OPAKOVANI)
    {
        structures::PriorityQueue<int>* pQueue = this->makePriorityQueue();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu
        repairQueue(size, size, *pQueue);

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            duration += durationPeek(*pQueue);
        }
        delete pQueue;
        //return duration / POC_OPAKOVANI;
        return duration;

    }

    Microseconds PriorityQueueUloha3::durationPeek(structures::PriorityQueue<int> &pQueue)
    {
        SimpleTest::startStopwatch();
        pQueue.peek();
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }
}