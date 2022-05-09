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
    virtual wstring& getCode() = 0;
    /// vráti vráti officialny nazov
    virtual wstring& getOfficialTitle() = 0;
    /// nastavy klúč
    virtual void setCode(const wstring& pCode) = 0;
    /// nastavy officialne meno uzemnej jednotky
    virtual void setOfficialTitle(const wstring& offTitleName) = 0;
    /// bude nastavovať všetky paramtetre ktoré treba
    virtual void setNextParameter(const wstring & parameter) = 0;
    /// prístup k parametrom z ulozenych dát
    virtual int getSize() {
        return data_->size();
    }
    virtual wstring& at(int index) {
        return this->data_->at(index);
    }
    /// operator prístupu
    virtual wstring& operator[](int index) {
        return this->at(index);
    }
    /// Nastavi nastavi dajsiu hlavicku, aj ked je hlavicka prazna
    /// \param headerName Meno hlavicky
    void setNextHeader(const wstring& headerName);
    /// Zízkame nazov hlavicky pre Ity stlpec
    /// \param i Stlpec ktorého chceme ziskat hlavicku
    /// \return Nazov hlavicky
    wstring& getHeaderAt(const int i);
    /// Vrati aktualnu velkost hlavicky
    /// \return Pocet stlpcov v hlavicke
    int getSizeHeader();
    /// Vrati nazov kazdeho stlpca oddeleného tabom
    /// \return wstring ktory obsahuje celhu hlavciku
    wstring& getFullHeader();

    //virtual setName(wstring name) = 0;

protected:
    structures::List<wstring> *data_;
    structures::List<wstring> *header_;

};

StoredData::StoredData() :
    data_(new structures::ArrayList<wstring>),
    header_(new structures::ArrayList<wstring>) {

}

StoredData::~StoredData() {
    data_->clear();
    delete data_;
    data_ = nullptr;
    header_->clear();
    delete header_;
    header_ = nullptr;
}

void StoredData::setNextHeader(const wstring &headerName) {
    header_->add(headerName);
}

wstring &StoredData::getHeaderAt(const int i) {
    return header_->at(i);
}

int StoredData::getSizeHeader() {
    return header_->size();
}

wstring& StoredData::getFullHeader() {
    wstringstream wstrignBuilder;
    for (auto item: *header_) {
        wstrignBuilder << item << L"\t";
    }
    wstring returnValue = wstrignBuilder.str();
    return returnValue;
}
