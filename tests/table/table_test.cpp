#include "table_test.h"
#include "../../structures/table/binary_search_tree.h"
#include "../../structures/table/hash_table.h"
#include "../../structures/table/linked_table.h"
#include "../../structures/table/sorted_sequence_table.h"
#include "../../structures/table/table.h"
#include "../../structures/table/treap.h"
#include "../../structures/table/unsorted_sequence_table.h"

namespace tests
{
	TableTestInterface::TableTestInterface() :
		SimpleTest("Interface")
	{
	}

	void TableTestInterface::test()
	{
		int x = 0;
		structures::Table<int, int>* table = this->makeTable();
		table->equals(*table);
		table->assign(*table);
		table->insert(0, 0);
		table->find(0);
		table->remove(0);
		table->tryFind(0, x);
		table->containsKey(0);
		delete table;
		this->logPass("Compiled.");
	}

	structures::Table<int, int>* BinarySearchTreeTestInterface::makeTable()
	{
		return new structures::BinarySearchTree<int, int>();
	}

	structures::Table<int, int>* HashTableTestInterface::makeTable()
	{
		return new structures::HashTable<int, int>();
	}

	structures::Table<int, int>* LinkedTableTestInterface::makeTable()
	{
		return new structures::LinkedTable<int, int>();
	}

	structures::Table<int, int>* SortedSequenceTableTestInterface::makeTable()
	{
		return new structures::SortedSequenceTable<int, int>();
	}

	structures::Table<int, int>* TreapTestInterface::makeTable()
	{
		return new structures::Treap<int, int>();
	}

	structures::Table<int, int>* UnsortedSequenceTableTestInterface::makeTable()
	{
		return new structures::UnsortedSequenceTable<int, int>();
	}

	BinarySearchTreeTestOverall::BinarySearchTreeTestOverall() :
		ComplexTest("BinarySearchTree")
	{
		addTest(new BinarySearchTreeTestInterface());
        addTest(new BSTFunctionTest());
        addTest(new BSTUloha2());
        addTest(new BSTUloha3());
	}

	HashTableTestOverall::HashTableTestOverall() :
		ComplexTest("HashTable")
	{
		addTest(new HashTableTestInterface());
	}

	LinkedTableTestOverall::LinkedTableTestOverall() :
		ComplexTest("LinkedTable")
	{
		addTest(new LinkedTableTestInterface());
	}

	SortedSequenceTableTestOverall::SortedSequenceTableTestOverall() :
		ComplexTest("SortedSequenceTable")
	{
		addTest(new SortedSequenceTableTestInterface());
        addTest(new SSTFunctionTest());
        addTest(new SSTUloha2());
        addTest(new SSTUloha3());
	}

	TreapTestOverall::TreapTestOverall() :
		ComplexTest("Treap")
	{
		addTest(new TreapTestInterface());
	}

	UnsortedSequenceTableTestOverall::UnsortedSequenceTableTestOverall() :
		ComplexTest("UnsortedSequenceTable")
	{
		addTest(new UnsortedSequenceTableTestInterface());
	}

	TableTestOverall::TableTestOverall() :
		ComplexTest("Table")
	{
		addTest(new BinarySearchTreeTestOverall());
		addTest(new HashTableTestOverall());
		addTest(new LinkedTableTestOverall());
		addTest(new SortedSequenceTableTestOverall());
		addTest(new TreapTestOverall());
		addTest(new UnsortedSequenceTableTestOverall());
	}

    // ---------------------------- Testy funkcnosti --------------------------------
    TableFunctionsTest::TableFunctionsTest() :
            SimpleTest("Complex test")
    {
    }
    void TableFunctionsTest::test()
    {
        /*
        structures::Table<int, int>* table = this->makeTable();
        for (int i = 1; i <= 10; ++i) {
            table->push(i, i);
        }
        */
        /*for (int i = 1; i <= 100; ++i) {
            // vkladanie s nahodnou prioritov
            int cislo = rand()%1000;
            table->push(cislo, cislo);
        }*/
        /*
        SimpleTest::assertTrue(table->size() == 10, "Velkost PriorityQueue by mala byt 10 a je: " + std::to_string(table->size()));

        structures::Table<int, int>* copyTable = this->makeTable(*table);
        SimpleTest::assertTrue(copyTable->size() == 10, "Testujem ci kopirovaci konstruktor funguje spravne.");
        SimpleTest::assertTrue(table->peek() == 1, "Hodnota peek by mala byt 1 a je " + std::to_string(table->peek()));
        SimpleTest::assertTrue(table->peekPriority() == 1, "Hodnota peekPriority by mala byt 1 a je " + std::to_string(table->peekPriority()));
        int hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 1, "Hodnota pop by mala byt 1 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 2, "Hodnota pop by mala byt 2 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 3, "Hodnota pop by mala byt 3 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 4, "Hodnota pop by mala byt 4 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 5, "Hodnota pop by mala byt 5 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 6, "Hodnota pop by mala byt 6 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 7, "Hodnota pop by mala byt 7 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 8, "Hodnota pop by mala byt 8 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 9, "Hodnota pop by mala byt 9 a je " + std::to_string(hodnota));
        hodnota = table->pop();
        SimpleTest::assertTrue(hodnota == 10, "Hodnota pop by mala byt 10 a je " + std::to_string(hodnota));

        structures::Table<int, int>* assignQueue = this->makeTable();
        assignQueue->assign(*copyTable);
        SimpleTest::assertTrue(assignQueue->size() == 10, "Testujem ci kopirovaci konstruktor funguje spravne.");
        SimpleTest::logInfo(" \"Ocna\" kontrola copyTable assign. Cisla v riadkoch maju bit rovnake a ist od 1 do 10 ");
        for (int i = 1; i <= 10; ++i) {
            int peek = copyTable->peek();
            int peekPr = copyTable->peekPriority();
            SimpleTest::logInfo(std::to_string(peek) + " " + std::to_string(peekPr) + " " + std::to_string(copyTable->pop()));
            //na macos mi to zoborie aj takto ale vo visual to nefunguje správne
            //SimpleTest::logInfo(std::to_string(copyTable->peek()) + " " + std::to_string(copyTable->peekPriority()) + " " + std::to_string(copyTable->pop()));
        }

        SimpleTest::logPass("Complet");
        delete assignQueue;
        delete copyTable;
        delete table;*/
    }

    //--------------------------------------------------- Uloha 2 ------------------------------------------------------------
    TableUloha2::TableUloha2()
            : SimpleTest("Uloha2")
    {

    }
    void TableUloha2::test()
    {
        for (int i = 0; i < 40000; ++i) {
            nonUsedKey.push_back(i);
        }
        this->info();
        structures::Logger::getInstance().logInfo("Testovanie Uloha2!");
        // scenár A
        structures::Table<int, int>* pTable = this->makeTable();
        cyklus('A', 20, 20, 60, *pTable);
        delete pTable;

        nonUsedKey.clear();
        usedKey.clear();
        for (int i = 0; i < 40000; ++i) {
            nonUsedKey.push_back(i);
        }
        // Scenár B
        pTable = this->makeTable();
        cyklus('B', 40, 40, 20, *pTable);
        delete pTable;

    }
    void TableUloha2::cyklus(char oznacenie, int podielInsert, int podielRemove, int podielTryFind,
                             structures::Table<int, int> &pTable)
    {
        static const int OPAKOVANIA = 100000;
        static const int MAX_DATA_VALUE_IN_TABLE = 100;

        structures::Logger::getInstance().logInfo("Zacal sa Scenar " + std::string(1, oznacenie) + "!");
        structures::Logger::getInstance().logInfo("Celkovo Insert, Celkovo Remove, Celkovo TryFind, celkova dlzka Scenara!");

        int opInsert = getPomer(OPAKOVANIA, podielInsert);
        int opRemove = getPomer(OPAKOVANIA, podielRemove);
        int opTryFind = getPomer(OPAKOVANIA, podielTryFind);

        std::vector<char>pool;
        for (unsigned i = 0; i < opInsert; i++)
        {
            pool.push_back(1);
        }
        for (unsigned i = 0; i < opRemove; i++)
        {
            pool.push_back(2);
        }
        for (unsigned i = 0; i < opTryFind; i++)
        {
            pool.push_back(3);
        }


        Microseconds durationInsert = std::chrono::microseconds(0);
        Microseconds durationRemove = std::chrono::microseconds(0);
        Microseconds durationTryFind = std::chrono::microseconds(0);

        while (!pool.empty())
        {
            int index = rand() % pool.size();
            int cislo = rand() % MAX_DATA_VALUE_IN_TABLE;
            switch (pool.at(index))
            {
                case 1:
                    if (pTable.isEmpty()) {
                        SimpleTest::startStopwatch();
                        pTable.insert(0, cislo);
                        SimpleTest::stopStopwatch();
                        durationInsert += SimpleTest::getElapsedTime();
                    } else {
                        int key = insertKey();
                        SimpleTest::startStopwatch();
                        pTable.insert(key, cislo);
                        SimpleTest::stopStopwatch();
                        durationInsert += SimpleTest::getElapsedTime();
                    }

                    break;

                case 2:
                    if (!pTable.isEmpty()) {
                        int key = removeKey();
                        SimpleTest::startStopwatch();
                        pTable.remove(key);
                        SimpleTest::stopStopwatch();
                        durationRemove += SimpleTest::getElapsedTime();
                    }
                    break;

                case 3:
                    if (!pTable.isEmpty()) {
                        int key = getUsedKey();
                        SimpleTest::startStopwatch();
                        pTable.tryFind(key, cislo);
                        SimpleTest::stopStopwatch();
                        durationTryFind += SimpleTest::getElapsedTime();
                    }
                    break;

            }

            pool.erase(pool.begin() + index);
        }

        structures::Logger::getInstance().logDuration(0, durationInsert + durationRemove + durationTryFind, std::to_string(durationInsert.count() ) + "," + std::to_string(durationRemove.count()) + "," + std::to_string(durationTryFind.count()));
    }

    int TableUloha2::getPomer(int const OPAKOVANIA, int pomer)
    {
        return (pomer * OPAKOVANIA) / 100;
    }
    int TableUloha2::insertKey() {
        int index = rand() % nonUsedKey.size();
        int key = nonUsedKey.at(index);
        nonUsedKey.erase(nonUsedKey.begin() + index);
        usedKey.push_back(key);
        return key;
    }

    int TableUloha2::removeKey() {
        int index = rand() % usedKey.size();
        int key = usedKey.at(index);
        usedKey.erase(usedKey.begin() + index);
        nonUsedKey.push_back(key);
        return key;
    }

    int TableUloha2::getUsedKey() {
        return usedKey.at(rand() % usedKey.size());;
    }

    //--------------------------------------------------- Uloha 3 ------------------------------------------------------------
    TableUloha3::TableUloha3():
            SimpleTest("Uloha3")
    {
    }
    void TableUloha3::test()
    {
        structures::Logger::getInstance().logInfo("Testovanie Uloha3!");
        static const int MAX = 10000;
        static const int KROK = 1000;
        static const int POC_VELKOST = 1000;
        static const int POC_OPAKOVANI = 100;
        static const int MAX_KEY = MAX;
        int sizeOfTable = POC_VELKOST;

        for (int i = 0; i < MAX_KEY; ++i) {
            nonUsedKey.push_back(i);
        }

        structures::Logger::getInstance().logInfo("Vysledne casi sú priemerom " + std::to_string(POC_OPAKOVANI) + " opakovi");
        structures::Logger::getInstance().logInfo("Velkost Table,Insert,Remove,TryFind");


        structures::Table<int, int> *pTable = this->makeTable();
        while (sizeOfTable <= MAX) {
            //----------------- Insert ------------------
            Microseconds insertDuration = cyklusInsert(sizeOfTable, POC_OPAKOVANI, *pTable);
            //------------------ Remove -----------------
            Microseconds removeDuration = cyklusRemove(sizeOfTable, POC_OPAKOVANI, *pTable);
            //---------------- TryFind -----------------
            Microseconds tryFindDuration = cyklusTryFind(sizeOfTable, POC_OPAKOVANI, *pTable);
            
            structures::Logger::getInstance().logDuration(0, tryFindDuration, std::to_string(insertDuration.count())+ " " +
                                                                              std::to_string(removeDuration.count()));
            sizeOfTable += KROK;
        }
        delete pTable;
    }

    void TableUloha3::repairTable(const int SIZE, structures::Table<int, int> &pTable) {
        while (pTable.size() != SIZE) {
            if (pTable.size() < SIZE) {
                pTable.insert(insertKey(), rand() % INT_MAX / 2);
            } else {
                pTable.remove(removeKey());
            }

        }
    }

    //------------------------------------------------------------------------
    Microseconds TableUloha3::cyklusInsert(int size, const int POC_OPAKOVANI, structures::Table<int, int> &pTable)
    {
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            repairTable(size, pTable);
            duration += durationInsert(insertKey(), rand() % INT_MAX / 2, pTable);
        }

        return duration / POC_OPAKOVANI;

    }

    Microseconds TableUloha3::durationInsert(int key, int cislo, structures::Table<int, int> &pTable)
    {
        SimpleTest::startStopwatch();
        pTable.insert(key, cislo);
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    //------------------------------------------------------------------------
    Microseconds TableUloha3::cyklusRemove(int size, const int POC_OPAKOVANI, structures::Table<int, int> &pTable)
    {
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            repairTable(size, pTable);
            duration += durationRemove(removeKey() , pTable);
        }

        return duration / POC_OPAKOVANI;
    }

    Microseconds TableUloha3::durationRemove(int key, structures::Table<int, int> &pTable)
    {
        SimpleTest::startStopwatch();
        pTable.remove(key);
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    //------------------------------------------------------------------------
    Microseconds TableUloha3::cyklusTryFind(int size, const int POC_OPAKOVANI, structures::Table<int, int> &pTable)
    {
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu
        repairTable(size, pTable);

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            duration += durationPeek(getUsedKey(), rand() % INT_MAX / 2, pTable);
        }
        return duration / POC_OPAKOVANI;

    }

    Microseconds TableUloha3::durationPeek(int key, int cislo, structures::Table<int, int> &pTable)
    {
        SimpleTest::startStopwatch();
        pTable.tryFind(key, cislo);
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    int TableUloha3::insertKey() {
        int index = rand() % nonUsedKey.size();
        int key = nonUsedKey.at(index);
        nonUsedKey.erase(nonUsedKey.begin() + index);
        usedKey.push_back(key);
        return key;
    }

    int TableUloha3::removeKey() {
        int index = rand() % usedKey.size();
        int key = usedKey.at(index);
        usedKey.erase(usedKey.begin() + index);
        nonUsedKey.push_back(key);
        return key;
    }

    int TableUloha3::getUsedKey() {
        return usedKey.at(rand() % usedKey.size());;
    }
}