#include "list_test.h"

namespace tests
{
	// ListTestInterface:

	ListTestInterface::ListTestInterface(std::string name) :
		SimpleTest(std::move(name))
	{
	}

	void ListTestInterface::test()
	{
		int x = 0;
		structures::List<int>* list = this->makeList();
		list->add(x);
		list->assign(*list);
		list->clear();
		delete list->getBeginIterator();
		delete list->getEndIterator();
		list->getIndexOf(x);
		list->insert(x, x);
		list->isEmpty();
		list->operator[](0);
		list->removeAt(0);
		list->size();
		list->tryRemove(x);
		delete list;
		this->logPass("Compiled.");
	}

	// ArrayListTestInterface:

	ArrayListTestInterface::ArrayListTestInterface() :
		ListTestInterface("Interface")
	{
	}

	structures::List<int>* ArrayListTestInterface::makeList() const
	{
		return new structures::ArrayList<int>();
	}

	// LinkedListTestInterface:

	LinkedListTestInterface::LinkedListTestInterface() :
		ListTestInterface("Interface")
	{
	}

    // DoubleLInkedListTestInterface
    DoubleLinkedListTestInterface::DoubleLinkedListTestInterface() :
            ListTestInterface("Intrerface")
    {

    }

    structures::List<int>* LinkedListTestInterface::makeList() const
    {
        return new structures::LinkedList<int>();
    }
    //--------------------------- Testy funkčnosti ---------------------------------------
	ListTestFunctionsTest::ListTestFunctionsTest() : SimpleTest("Complex test")
	{
	}
	void ListTestFunctionsTest::test()
	{
		structures::List<int>* zoznam = this->makeList();
		SimpleTest::logInfo("Vkladam 4 prvky na koniec zoznamu");
		zoznam->add(10);
		zoznam->add(20);
		zoznam->add(30);
		zoznam->add(40);
		SimpleTest::assertTrue(zoznam->size() == 4, "Pole ma velkost 4");

		SimpleTest::logInfo("Vkladam dalsie 4 prvky na koniec zoznamu");
		zoznam->add(100);
		zoznam->add(200);
		zoznam->add(300);
		zoznam->add(400);


		//SimpleTest::logInfo("Aktualna velkost pola je: " + std::to_string(zoznam->size()));
		SimpleTest::assertTrue(zoznam->size() == 8, "Pole ma velkost 8");

		SimpleTest::logInfo("Vkladam 9 prvkov pomocou insert");
		for (int i = 0; i < 9; i++)
		{
			zoznam->insert(1, 0);
		}
		SimpleTest::assertTrue(zoznam->size() == 17, "Pole ma velkost 17");
		zoznam->insert(7, 0);
		zoznam->insert(77, 4);
		zoznam->insert(777, 18);
		zoznam->insert(7777, 20);
        SimpleTest::assertTrue(zoznam->size() == 21, "Pole ma velkost 21");

		SimpleTest::assertTrue(zoznam->at(0) == 7, "Mala by tam byt 7 a je tam " + std::to_string(zoznam->at(0)));
		SimpleTest::assertTrue(zoznam->at(1) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(1)));
		SimpleTest::assertTrue(zoznam->at(2) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(2)));
		SimpleTest::assertTrue(zoznam->at(3) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(3)));
		SimpleTest::assertTrue(zoznam->at(4) == 77, "Mala by tam byt 77 a je tam " + std::to_string(zoznam->at(4)));
		SimpleTest::assertTrue(zoznam->at(5) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(5)));
		SimpleTest::assertTrue(zoznam->at(6) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(6)));
		SimpleTest::assertTrue(zoznam->at(7) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(7)));
		SimpleTest::assertTrue(zoznam->at(8) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(8)));
		SimpleTest::assertTrue(zoznam->at(9) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(9)));
		SimpleTest::assertTrue(zoznam->at(10) == 1, "Mala by tam byt 1 a je tam " + std::to_string(zoznam->at(10)));
		SimpleTest::assertTrue(zoznam->at(11) == 10, "Mala by tam byt 10 a je tam " + std::to_string(zoznam->at(11)));
		SimpleTest::assertTrue(zoznam->at(12) == 20, "Mala by tam byt 20 a je tam " + std::to_string(zoznam->at(12)));
		SimpleTest::assertTrue(zoznam->at(13) == 30, "Mala by tam byt 30 a je tam " + std::to_string(zoznam->at(13)));
		SimpleTest::assertTrue(zoznam->at(14) == 40, "Mala by tam byt 40 a je tam " + std::to_string(zoznam->at(14)));
		SimpleTest::assertTrue(zoznam->at(15) == 100, "Mala by tam byt 100 a je tam " + std::to_string(zoznam->at(15)));
		SimpleTest::assertTrue(zoznam->at(16) == 200, "Mala by tam byt 200 a je tam " + std::to_string(zoznam->at(16)));
		SimpleTest::assertTrue(zoznam->at(17) == 300, "Mala by tam byt 300 a je tam " + std::to_string(zoznam->at(17)));
		SimpleTest::assertTrue(zoznam->at(18) == 777, "Mala by tam byt 777 a je tam " + std::to_string(zoznam->at(18)));
		SimpleTest::assertTrue(zoznam->at(19) == 400, "Mala by tam byt 400 a je tam " + std::to_string(zoznam->at(19)));
		SimpleTest::assertTrue(zoznam->at(20) == 7777, "Mala by tam byt 7777 a je tam " + std::to_string(zoznam->at(20)));

        SimpleTest::logInfo("Cistim zoznam");
        zoznam->clear();
        SimpleTest::assertTrue(zoznam->size() == 0, "Velkost zoznamu by mala byt 0 a je " + std::to_string(zoznam->size()));

        SimpleTest::logInfo("Vkladam 4 prvky na koniec zoznamu");
        zoznam->add(10);
        zoznam->add(20);
        zoznam->add(30);
        zoznam->add(40);
        structures::List<int>* copyZoznam = this->makeList(*zoznam);
        SimpleTest::assertTrue(zoznam->equals(*copyZoznam), "Porovnavam zoznami ci su rovnake, mali by byt.");

        SimpleTest::logInfo("Menim hodnotu v copyZozham");
        //SimpleTest::logInfo(std::to_string(copyMatica->at(4, 4)));
        copyZoznam->at(3) = 7777;
        SimpleTest::assertTrue(copyZoznam->at(3) == 7777, "Kontrolujem ci sa naozaj priradil prvok do zoznamu.");
        SimpleTest::assertFalse(zoznam->equals(*copyZoznam), "Porovnavam zoznami ci su rovnake, nemali by byt.");

        SimpleTest::logInfo("Vkladam copyZoznam do uplne noveho zoznamu pomocou assign");
        structures::List<int>* newZoznam = this->makeList();
        newZoznam->assign(*copyZoznam);
        SimpleTest::assertTrue(newZoznam->equals(*copyZoznam), "Porovnavam zoznami ci su rovnake, mali by byt.");

        newZoznam->clear();
        newZoznam->add(10);
        newZoznam->add(20);
        newZoznam->add(30);
        newZoznam->add(40);
        SimpleTest::logInfo("Testujem iterator");
        for (auto polozka: *newZoznam) {
            logInfo(std::to_string(polozka));
        }
        int zmazanyPrvok = newZoznam->removeAt(0);
        SimpleTest::assertTrue(zmazanyPrvok == 10, "Hodnota mazaneho prvku ma byt 10 a je " + std::to_string(zmazanyPrvok));
        SimpleTest::assertTrue(newZoznam->getIndexOf(40) == 2, "Vyhladavam prvok pomocou getIndexof(40) = " + std::to_string(newZoznam->getIndexOf(40)));
        SimpleTest::assertFalse(newZoznam->tryRemove(1), "Vymazavam pomocou tryRemove data ktoré tam niesu");
        SimpleTest::assertTrue(newZoznam->tryRemove(20), "Vymazavam pomocou tryRemove data ktoré tam sú");

        SimpleTest::logInfo("Testujem iterator");
        for (auto polozka: *newZoznam) {
            logInfo(std::to_string(polozka));
        }

        SimpleTest::logPass("Complet");
        delete newZoznam;
        delete copyZoznam;
        delete zoznam;
	}

// ArrayListTestOverall:

	ArrayListTestOverall::ArrayListTestOverall() :
		ComplexTest("ArrayList")
	{
		addTest(new ArrayListTestInterface());
		addTest(new ArryListFunctionTest());
        addTest(new ArrListUloha2());
        addTest(new ArrListUloha3());
	}

// LinkedListTestOverall:

	LinkedListTestOverall::LinkedListTestOverall() :
		ComplexTest("LinkedList")
	{
		addTest(new LinkedListTestInterface());
        addTest(new LinkedListFunctionTest());
        addTest(new LinListUloha2());
	}

    DoubleLinkedListOverall::DoubleLinkedListOverall() :
        ComplexTest("DoubleLinkedList")
    {
        addTest(new DoubleLinkedListTestInterface());
        addTest(new DoubleLinkedListFunctionTest());
        addTest(new DoubleLinListUloha2());
        addTest(new DoubleLinListUloha3);
    }
// ListTestOverall:

	ListTestOverall::ListTestOverall() :
		ComplexTest("List")
	{
		addTest(new ArrayListTestOverall());
		addTest(new LinkedListTestOverall());
        addTest(new DoubleLinkedListOverall());

	}


    //--------------------------------------------------- Uloha 2 ------------------------------------------------------------
    ListUloha2::ListUloha2()
            : SimpleTest("Uloha2")
    {

    }
    void ListUloha2::test()
    {
        structures::Logger::getInstance().logInfo("Testovanie Uloha2!");
        this->info();
        // scenár A
        structures::List<int>* list = this->makeList();
        cyklus('A', 20, 20, 50, 10, *list);
        delete list;

        // Scenár B
        list = this->makeList();
        cyklus('B', 35, 35, 20, 10, *list);
        delete list;

        // Scenár C
        list = this->makeList();
        cyklus('C', 45, 45, 5, 5, *list);
        delete list;

    }
    void ListUloha2::cyklus(char oznacenie, int podielInsert, int podielRemoveAt, int podielAt, int podielGetIndexOf,
                            structures::List<int> &list)
    {
        const int OPAKOVANIA = 100000;
        const int MAX_VALUE_IN_LIST = 50; // maximálna hodnota ktorá sa vloží do zoznamu, čím menšie číslo, tým väčšia pravdepodobnosť že to getIndexOf najde

        // todo rozhodnúť sa či budem hladať pre getIndexOf čísla náhodné alebo ich budem ešte ukladať niekde do zoznam a z tadiaľ budem číslo vyhľadávať

        structures::Logger::getInstance().logInfo("Zacal sa test " + std::string(1, oznacenie) + "!");
        structures::Logger::getInstance().logInfo("Celkovo insert, Celkovo RemoveAt, Celkovo at, Celkovo GetIndexOf, celkova dlzka Scenara " + std::string(1, oznacenie) + "!");

        int opInst = getPomer(OPAKOVANIA, podielInsert);
        int opRemoveAt = getPomer(OPAKOVANIA, podielRemoveAt);
        int opAt = getPomer(OPAKOVANIA, podielAt);
        int opGetIndOf = getPomer(OPAKOVANIA, podielGetIndexOf);

        std::vector<char>pool;
        for (unsigned i = 0; i < opInst; i++)
        {
            pool.push_back(1);
        }
        for (unsigned i = 0; i < opRemoveAt; i++)
        {
            pool.push_back(2);
        }
        for (unsigned i = 0; i < opAt; i++)
        {
            pool.push_back(3);
        }
        for (unsigned i = 0; i < opGetIndOf; i++)
        {
            pool.push_back(4);
        }


        Microseconds durationInsert = std::chrono::microseconds(0);
        Microseconds durationRemoveAt = std::chrono::microseconds(0);
        Microseconds durationAt = std::chrono::microseconds(0);
        Microseconds durationGetIndexOf = std::chrono::microseconds(0);

        while (!pool.empty())
        {
            int index = rand() % pool.size();
            int cislo;
            int indexL;
            switch (pool.at(index))
            {
                case 1:
                    cislo = rand() % MAX_VALUE_IN_LIST;
                    if (list.size() == 0) {
                        SimpleTest::startStopwatch();
                        list.insert(cislo, 0);
                        SimpleTest::stopStopwatch();
                        durationInsert += SimpleTest::getElapsedTime();
                    } else {
                        indexL = rand() % list.size();
                        SimpleTest::startStopwatch();
                        list.insert(cislo, indexL);
                        SimpleTest::stopStopwatch();
                        durationInsert += SimpleTest::getElapsedTime();
                    }
                    break;

                case 2:
                    if (list.size() != 0) {
                        indexL = rand() % list.size();
                        SimpleTest::startStopwatch();
                        list.removeAt(indexL);
                        SimpleTest::stopStopwatch();
                        durationRemoveAt += SimpleTest::getElapsedTime();
                    }
                    break;

                case 3:
                    if (list.size() != 0) {
                        indexL = rand() % list.size();
                        SimpleTest::startStopwatch();
                        list.at(indexL);
                        SimpleTest::stopStopwatch();
                        durationAt += SimpleTest::getElapsedTime();
                    }
                    break;
                case 4:
                    cislo = rand() % MAX_VALUE_IN_LIST;
                    SimpleTest::startStopwatch();
                    int najdene = list.getIndexOf(cislo);
                    SimpleTest::stopStopwatch();
                    durationGetIndexOf += SimpleTest::getElapsedTime();

                    /*
                    std::stringstream stringBuilder;
                    if (najdene >= 0) {
                        stringBuilder << oznacenie << " " << najdene << " " << list.at(najdene) << " " << cislo
                                  << std::endl;
                    } else {
                        stringBuilder << oznacenie << " " << najdene << " " << -1 << " " << cislo
                                  << std::endl;
                    }
                    structures::Logger::getInstance().logInfo(stringBuilder.str());*/
                    break;
            }

            pool.erase(pool.begin() + index);
        }

        structures::Logger::getInstance().logDuration(0, durationInsert + durationRemoveAt + durationAt + durationGetIndexOf, std::to_string(durationInsert.count() ) + "," + std::to_string(durationRemoveAt.count()) + "," + std::to_string(durationAt.count())+ "," + std::to_string(durationGetIndexOf.count()));
    }

    int ListUloha2::getPomer(int const OPAKOVANIA, int pomer)
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
        const int MAX = 3000;
        const int KROK = 100;
        const int POC_VELKOST = 100;
        const int POC_OPAKOVANI = 100;
        int sizeOfList;
        sizeOfList = POC_VELKOST;

        structures::Logger::getInstance().logInfo("Velkost listu, Priemerna dlzka na " + std::to_string(POC_OPAKOVANI) + " opakovani");

        //--------------------Insert-----------------
        this->infoInsert();
        while (sizeOfList <= MAX)
        {
            structures::Logger::getInstance().logDuration(0, cyklusInsert(sizeOfList, POC_OPAKOVANI), std::to_string(sizeOfList));
            sizeOfList += KROK;
        }

        //----------------------At-------------------

        this->infoAt();
        sizeOfList = POC_VELKOST;
        while (sizeOfList <= MAX)
        {
            structures::Logger::getInstance().logDuration(0, cyklusAt(sizeOfList, POC_OPAKOVANI), std::to_string(sizeOfList));
            sizeOfList += KROK;
        }

        //------------------RemoveAt-----------------
        this->infoRemoveAt();
        sizeOfList = POC_VELKOST;
        while (sizeOfList <= MAX)
        {
            structures::Logger::getInstance().logDuration(0, cyklusRemoveAt(sizeOfList, POC_OPAKOVANI), std::to_string(sizeOfList));
            sizeOfList += KROK;
        }

    }

    void ListUloha3::repairList(const int SIZE, structures::List<int> &list) {

    }

    //------------------------------------------------------------------------
    Microseconds ListUloha3::cyklusInsert(int size, const int POC_OPAKOVANI)
    {
        structures::List<int>* list = this->makeList();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            repairList(size,*list);
            duration += durationInsert(rand() % INT16_MAX /2 , rand() % list->size(), *list);
        }
        delete list;
        return duration / POC_OPAKOVANI;

    }

    Microseconds ListUloha3::durationInsert(int cislo, int index, structures::List<int> &list)
    {
        SimpleTest::startStopwatch();
        list.insert(cislo,index);
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    //------------------------------------------------------------------------
    Microseconds ListUloha3::cyklusAt(int size, const int POC_OPAKOVANI)
    {
        structures::List<int>* list = this->makeList();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu
        repairList(size, *list); // repair list je volaná tu pretože viem že sa s listom nič pri volaní at nestane

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            duration += durationAt(rand() % size, *list);
        }
        delete list;
        return duration / POC_OPAKOVANI;
    }

    Microseconds ListUloha3::durationAt(int index, structures::List<int> &list)
    {
        SimpleTest::startStopwatch();
        list.at(index) = 7;
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }

    //------------------------------------------------------------------------
    Microseconds ListUloha3::cyklusRemoveAt(int size, const int POC_OPAKOVANI)
    {
        structures::List<int>* list = this->makeList();
        Microseconds duration = std::chrono::microseconds(0); // nastaví premennú na nulu

        for (int i = 0; i < POC_OPAKOVANI; i++)
        {
            repairList(size,*list);
            duration += durationRemoveAt(rand() % size, *list);
        }
        delete list;
        return duration / POC_OPAKOVANI;

    }

    Microseconds ListUloha3::durationRemoveAt(int index, structures::List<int> &list)
    {
        SimpleTest::startStopwatch();
        list.removeAt(index);
        SimpleTest::stopStopwatch();
        return SimpleTest::getElapsedTime();
    }
}