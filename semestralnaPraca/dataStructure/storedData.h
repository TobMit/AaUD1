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
    virtual ~StoredData(){
        delete data_;
        data_ = nullptr;
    };
    /// vrati klus ktory sa bude pouzivat v tabulke
    virtual wstring& getCode() = 0;
    /// vráti vráti officialny nazov
    virtual wstring& getOfficialTitle() = 0;
    /// nastavy klúč
    virtual void setCode(wstring& code) = 0;
    /// nastavy officialne meno uzemnej jednotky
    virtual void setOfficialTitle(wstring& offTitleName) = 0;
    /// bude nastavovať všetky paramtetre ktoré treba
    virtual void nastavDalsiParameter(T& parameter) = 0;
    /// prístup k parametrom z ulozenych dát
    virtual T& at(int index) {
        return this->data_->at(index);
    }
    /// operator prístupu
    virtual T& operator[](int index) {
        return this->at(index);
    }

private:
    structures::ArrayList<T>* data_;

};