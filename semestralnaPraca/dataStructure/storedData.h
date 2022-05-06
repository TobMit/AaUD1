//
// Created by Tobias on 30. 4. 2022.
//
#pragma once
#include "string"
#include "../structures/list/array_list.h"

using namespace std;

///Virtualny trieda ktorú bude dedit kazda trieda ktora uchovava ulozene data
template<typename T >
class StoredData {
public:
    /// destruktor
    StoredData();

    virtual ~StoredData();
    /// vrati klus ktory sa bude pouzivat v tabulke
    virtual wstring& getCode() = 0;
    /// vráti vráti officialny nazov
    virtual wstring& getOfficialTitle() = 0;
    /// nastavy klúč
    virtual void setCode(const wstring& pCode) = 0;
    /// nastavy officialne meno uzemnej jednotky
    virtual void setOfficialTitle(const wstring& offTitleName) = 0;
    /// bude nastavovať všetky paramtetre ktoré treba
    virtual void nastavDalsiParameter(const T& parameter) = 0;
    /// prístup k parametrom z ulozenych dát
    virtual int getSize() {
        return data_->size();
    }
    virtual T& at(int index) {
        return this->data_->at(index);
    }
    /// operator prístupu
    virtual T& operator[](int index) {
        return this->at(index);
    }

protected:
    structures::List<T> *data_;

};

template<typename T>
StoredData<T>::StoredData() :
    data_(new structures::ArrayList<T>()){

}

template<typename T>
StoredData<T>::~StoredData() {
    delete data_;
    data_ = nullptr;
}
