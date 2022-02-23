#pragma once

#include "stack.h"
#include "../list/linked_list.h"

namespace structures
{
    /// <summary> Explicitny zasobník. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zasobniku. </typepram>
    template<typename T>
    class ExplicitStack : public Stack<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        ExplicitStack();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Explicitny zasobník, z ktoreho sa prevezmu vlastnosti. </param>
        ExplicitStack(ExplicitStack<T>& other);

        /// <summary> Destruktor. </summary>
        ~ExplicitStack();

        /// <summary> Vrati pocet prvkov v zasobniku. </summary>
        /// <returns> Pocet prvkov v zasobniku. </returns>
        size_t size() override;

        /// <summary> Operator priradenia. </summary>
        /// <param name = "other"> Zasobnik, z ktoreho ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa tento zasobnik nachadza po priradeni. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vymaze zasobnik. </summary>
        void clear() override;

        /// <summary> Prida prvok do zasobnika. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void push(const T& data) override;

        /// <summary> Odstrani prvok na vrchole zasobnika. </summary>
        /// <returns> Prvok na vrchole zasobnika. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>
        T pop() override;

        /// <summary> Vrati prvok na vrchole zasobnika. </summary>
        /// <returns> Prvok na vrchole zasobnika. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak je zasobnik prazdny. </exception>
        T& peek() override;

    protected:
        /// <summary> Zoznam, pomocou ktoreho je implementovany zasobnik. </summary>
        LinkedList<T>* list_;
    };

    template<typename T>
    ExplicitStack<T>::ExplicitStack() :
        Stack<T>(),
        list_(new LinkedList<T>())
    {
    }

    template<typename T>
    ExplicitStack<T>::ExplicitStack(ExplicitStack<T>& other) :
        ExplicitStack()
    {
        assign(other);
    }

    template<typename T>
    ExplicitStack<T>::~ExplicitStack()
    {
        //TODO 05: ExplicitStack
    }

    template<typename T>
    inline Structure& ExplicitStack<T>::assign(Structure& other)
    {
        //TODO 05: ExplicitStack
        throw std::runtime_error("ExplicitStack<T>::assign: Not implemented yet.");
    }

    template<typename T>
    inline bool ExplicitStack<T>::equals(Structure& other)
    {
        //TODO 05: ExplicitStack
        throw std::runtime_error("ExplicitStack<T>::equals: Not implemented yet.");
    }

    template<typename T>
    size_t ExplicitStack<T>::size()
    {
        //TODO 05: ExplicitStack
        throw std::runtime_error("ExplicitStack<T>::size: Not implemented yet.");
    }

    template<typename T>
    inline void ExplicitStack<T>::clear()
    {
        //TODO 05: ExplicitStack
        throw std::runtime_error("ExplicitStack<T>::clear: Not implemented yet.");
    }

    template<typename T>
    inline void ExplicitStack<T>::push(const T& data)
    {
        //TODO 05: ExplicitStack
        throw std::runtime_error("ExplicitStack<T>::push: Not implemented yet.");
    }

    template<typename T>
    inline T ExplicitStack<T>::pop()
    {
        //TODO 05: ExplicitStack
        throw std::runtime_error("ExplicitStack<T>::pop: Not implemented yet.");
    }

    template<typename T>
    inline T& ExplicitStack<T>::peek()
    {
        //TODO 05: ExplicitStack
        throw std::runtime_error("ExplicitStack<T>::peek: Not implemented yet.");
    }
}