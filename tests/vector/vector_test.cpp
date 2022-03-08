#include "vector_test.h"
#include "../../structures/vector/vector.h"
#include "../../structures/heap_monitor.h"

namespace tests
{
// VectorTestInterface:

    VectorTestInterface::VectorTestInterface() :
        SimpleTest("Interface")
    {
    }

    void VectorTestInterface::test()
    {
        structures::Vector* vector = new structures::Vector(10);
        vector->size();
        vector->assign(*vector);
        vector->equals(*vector);
        vector->at(0);
        vector->getBytePointer(0);
        structures::Vector::copy(*vector, 0, *vector, 0, 1);
        delete vector;
        SimpleTest::logPass("Compiled.");
    }

    //vectorTestAt:

    VectorTestAt::VectorTestAt():
        SimpleTest("Vector test at")
    {
    }

    void VectorTestAt::test()

    {
        structures::Logger::getInstance().logInfo("Zacal sa test!");
        SimpleTest::startStopwatch();


        structures::Vector* testVector = new structures::Vector(10);

        SimpleTest::assertTrue(testVector->size() == 10, "Testujem Vector::size()");
        for (int i = 0; i < 10; i++)
        {
            testVector->at(i) = i;
        }

        for (int i = 0; i < 10; i++)
        {
            SimpleTest::assertTrue(testVector->at(i) == i, "Testujem Vector::at(" + std::to_string(i) + ")");
            SimpleTest::assertTrue(*(testVector->getBytePointer(i)) == i, "Testujem Vector::getBytePointer(" + std::to_string(i) + ")");
        }

        delete testVector;

        SimpleTest::stopStopwatch();
        structures::Logger::getInstance().logDuration(0, SimpleTest::getElapsedTime(), "..a trval tolkoto!");
    }


// Vector test Copyconstruct
    VectorTestCopyConstruct::VectorTestCopyConstruct() : SimpleTest("Vector Test copy construct")
    {
    }
    void VectorTestCopyConstruct::test()
    {
        structures::Vector* testVector = new structures::Vector(10);
        for (int i = 0; i < 10; i++) {
            testVector->at(i) = i;
        }

        structures::Vector* copyVector = new structures::Vector(*testVector);
        SimpleTest::assertTrue(testVector->equals(*copyVector), "Testujem, ci Copirovaci constructor funguje.");
        copyVector->at(0) = 10;
        SimpleTest::assertFalse(testVector->equals(*copyVector), "Testujem, ci funguje equals, (vectory su rozlicne)");
        testVector->assign(*copyVector);
        SimpleTest::assertTrue(testVector->equals(*copyVector), "Testujem, ci assign funguje");


        //delete testVector;
        //delete copyVector;
    }
    


// VectorTestOverall:

    VectorTestOverall::VectorTestOverall() :
        ComplexTest("Vector")
    {
        addTest(new VectorTestInterface());
        addTest(new VectorTestAt());
        addTest(new VectorTestCopyConstruct());
    }
}