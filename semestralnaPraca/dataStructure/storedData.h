//
// Created by Tobias on 30. 4. 2022.
//
#pragma once

#include <sstream>
#include "string"
#include "../structures/list/array_list.h"

using namespace std;

///Virtualny trieda ktorú bude dedit kazda trieda ktora uchovava ulozene data
class StoredData {
public:
    StoredData();
    /// destruktor
    virtual ~StoredData();
    /// vrati klus ktory sa bude pouzivat v tabulke
    virtual wstring getCode() const = 0;
    /// vráti vráti officialny nazov
    virtual wstring getOfficialTitle() const = 0;
    /// nastavy klúč
    virtual void setCode(const wstring pCode) = 0;
    /// nastavy officialne meno uzemnej jednotky
    virtual void setOfficialTitle(const wstring pOffTitleName) = 0;
    /// bude nastavovať všetky paramtetre ktoré treba
    virtual void setNextParameter(const wstring parameter) = 0;
    /// prístup k parametrom z ulozenych dát
    virtual int getSize() = 0;

    virtual wstring& at(int index) = 0;
    /// operator prístupu
    wstring operator[](int index) {
        return this->at(index);
    }

};

inline StoredData::~StoredData() {

}

inline StoredData::StoredData() {

}



