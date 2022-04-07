#pragma once

#include "../test.h"
#include "../../structures/list/array_list.h"
#include "../../structures/list/linked_list.h"
#include "../../structures/list/double_linked_list.h"
//#include "../../structures/heap_monitor.h"

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
	/// Test ktory skontroluje ci funguje add a insert v V oboch implementáciach Listu
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
    /// Testovanie pre úlohu 2
    /// </summary>
    class ListUloha2
            :public SimpleTest
    {
    public:
        ListUloha2();
        void test() override;
    private:
        void cyklus(char oznacenie, int podielInsert, int podielRemoveAt, int podielAt, int podielGetIndexOf,structures::List<int> &list);
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
}