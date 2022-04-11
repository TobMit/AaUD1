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
    }

    HeapTestOverall::HeapTestOverall() :
        ComplexTest("Heap")
    {
        addTest(new HeapTestInterface());
        addTest(new HeapQueueListFunctionTest());
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
}