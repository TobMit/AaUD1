#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"
#include "../../structures/list/double_linked_list.h"
#include "../../structures/heap_monitor.h"

namespace tests
{
	/// <summary>
	/// Zavola vsetky metody z rozhrania listu avsak nekontroluje ich spravnost.
	/// Zabezpeci, ze vsetky metody budu prelozene kompilatorom.
	/// </summary>
	class ListTestInterface
		: public SimpleTest
	{
	public:
		ListTestInterface(std::string name);
		void test() override;

	protected:
		virtual structures::List<int>* makeList() const = 0;
	};

	/// <summary>
	/// Zavola vsetky metody ArrayListu.
	/// </summary>
	class ArrayListTestInterface
		: public ListTestInterface
	{
	public:
		ArrayListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

	/// <summary>
	/// Zavola vsetky metody LinkedListu.
	/// </summary>
	class LinkedListTestInterface
		: public ListTestInterface
	{
	public:
		LinkedListTestInterface();

	protected:
		structures::List<int>* makeList() const override;
	};

    /// <summary>
    /// Zavola vsetky metody DoubleLinkedList.
    /// </summary>
    class DoubleLinkedListTestInterface
            : public ListTestInterface
    {
    public:
        DoubleLinkedListTestInterface();

    protected:
        structures::List<int>* makeList() const override
        {
            return new structures::DoubleLinkedList<int>();
        };
    };


	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList.
	/// </summary>
	class ArrayListTestOverall
		: public ComplexTest
	{
	public:
		ArrayListTestOverall();
	};

	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju LinkedList.
	/// </summary>
	class LinkedListTestOverall
		: public ComplexTest
	{
	public:
		LinkedListTestOverall();
	};

    /// <summary>
    /// Zahrna v sebe vsetky testy, ktore testuju DobuleLinkedList.
    /// </summary>
    class DoubleLinkedListOverall
            : public ComplexTest
    {
    public:
        DoubleLinkedListOverall();
    };
	/// <summary>
	/// Zahrna v sebe vsetky testy, ktore testuju ArrayList a LinkedList a DoubleLinkedList.
	/// </summary>
	class ListTestOverall :
		public ComplexTest
	{
	public:
		ListTestOverall();
	};
//--------------------------------TESTY FUNKCNOSTI --------------------------------------
	/// <summary>
	/// Test ktorý overí správnu implementáciu testu
	/// </summary>
	class ListTestFunctionsTest
		: public SimpleTest {
	public:
		ListTestFunctionsTest();
		void test() override;

    protected:
        virtual structures::List<int>* makeList() const = 0;
        virtual structures::List<int>* makeList(structures::List<int>& other) const = 0;
	};

    class ArryListFunctionTest
            :public ListTestFunctionsTest {
    protected:
        structures::List<int> *makeList() const override {
            return new structures::ArrayList<int>();
        };
        structures::List<int> *makeList(structures::List<int> &other) const override {
            structures::ArrayList<int>& arrayList = dynamic_cast<structures::ArrayList<int>&>(other);
            return new structures::ArrayList<int>(arrayList);
        };

    };

    class LinkedListFunctionTest
            :public ListTestFunctionsTest {
    protected:
        structures::List<int> *makeList() const override {
            return new structures::LinkedList<int>();
        };
        structures::List<int> *makeList(structures::List<int> &other) const override {
            structures::LinkedList<int>& linkedList = dynamic_cast<structures::LinkedList<int>&>(other);
            return new structures::LinkedList<int>(linkedList);
        };
    };

    class DoubleLinkedListFunctionTest
            :public ListTestFunctionsTest {
    protected:
        structures::List<int> *makeList() const override {
            return new structures::DoubleLinkedList<int>();
        };
        structures::List<int> *makeList(structures::List<int> &other) const override {
            structures::DoubleLinkedList<int>& doubleLinkedList = dynamic_cast<structures::DoubleLinkedList<int>&>(other);
            return new structures::DoubleLinkedList<int>(doubleLinkedList);
        };
    };

    //------------------------------------ Uloha 2 ------------------------------------------------

    /// <summary>
    /// Uloha 2
    /// </summary>
    class ListUloha2
            :public SimpleTest
    {
    public:
        ListUloha2();
        void test() override;
    private:
        void cyklus(char oznacenie, int podielInsert, int podielRemoveAt, int podielAt, int podielGetIndexOf, structures::List<int> &list);
        int getPomer(int const OPAKOVANIA, int pomer);
    protected:
        virtual structures::List<int> *makeList() const = 0;
        virtual void info() const = 0;
    };


    class ArrListUloha2
            : public ListUloha2
    {
    protected:
        structures::List<int> *makeList() const override
        {
            return new structures::ArrayList<int>();
        };

        void info() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie ArrList!");
        }
    };

    class DoubleLinListUloha2
            : public ListUloha2
    {
    protected:
        structures::List<int> *makeList() const override
        {
            return new structures::DoubleLinkedList<int>();
        };
        void info() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie DoubleLinList!");
        }
    };

    class LinListUloha2
            : public ListUloha2
    {
    protected:
        structures::List<int> *makeList() const override
        {
            return new structures::LinkedList<int>();
        };
        void info() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie LinList!");
        }
    };

    //------------------------------------------- Uloha 3 -----------------------------------------------
    /// <summary>
    /// Uloha 3
    /// </summary>
    class ListUloha3
            :public SimpleTest
    {
    public:
        ListUloha3();
        void test() override;
    private:
        Milliseconds cyklusInsert(int size, const int POC_OPAKOVANI);
        Milliseconds durationInsert(int cislo, int index, structures::List<int> &list);

        Milliseconds cyklusAt(int size, const int POC_OPAKOVANI);
        Milliseconds durationAt(int index, structures::List<int> &list);

        Milliseconds cyklusRemoveAt(int size, const int POC_OPAKOVANI);
        Milliseconds durationRemoveAt(int index, structures::List<int> &list);

        /// repairList udrzuje velkost daného listu na potrebnej dlzke. Keď treba, tak list zväčší a naplni hodnotami a ked je velky tak zmensi
        /// \param SIZE - velkost listu ktora sa ma udrziavat
        /// \param list - list kotry sa ma opravit
        void repairList(int SIZE, structures::List<int> &list);
    protected:
        virtual structures::List<int> *makeList() const = 0;
        virtual void infoInsert() const = 0;
        virtual void infoAt() const = 0;
        virtual void infoRemoveAt() const = 0;

    };

    class ArrListUloha3
            : public ListUloha3
    {
    protected:
        structures::List<int> *makeList() const override
        {
            return new structures::ArrayList<int>();
        };

        void infoAt() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie ArrList - at");
        }
        void infoInsert() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie ArrList - Insert");
        }
        void infoRemoveAt() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie ArrList - RemoveAt");
        }
    };

    class DoubleLinListUloha3
            : public ListUloha3
    {
    protected:
        structures::List<int> *makeList() const override
        {
            return new structures::DoubleLinkedList<int>();
        };

        void infoAt() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie DoubleLinList - at");
        }
        void infoInsert() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie DoubleLinList - Insert");
        }
        void infoRemoveAt() const override
        {
            structures::Logger::getInstance().logInfo("Testovanie DoubleLinList - RemoveAt");
        }
    };
}