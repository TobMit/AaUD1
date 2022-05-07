//
// Created by Tobias on 30. 4. 2022.
//
#pragma once

#include <sstream>
#include "string"
#include "../structures/list/array_list.h"
#include "../../structures/heap_monitor.h"

using namespace std;

///Virtualny trieda ktorú bude dedit kazda trieda ktora uchovava ulozene data
class StoredData {
public:
    StoredData();
    /// destruktor
    virtual ~StoredData();
    /// vrati klus ktory sa bude pouzivat v tabulke
    virtual string& getCode() = 0;
    /// vráti vráti officialny nazov
    virtual string& getOfficialTitle() = 0;
    /// nastavy klúč
    virtual void setCode(const string& pCode) = 0;
    /// nastavy officialne meno uzemnej jednotky
    virtual void setOfficialTitle(const string& offTitleName) = 0;
    /// bude nastavovať všetky paramtetre ktoré treba
    virtual void setNextParameter(const string & parameter) = 0;
    /// prístup k parametrom z ulozenych dát
    virtual int getSize() {
        return data_->size();
    }
    virtual string& at(int index) {
        return this->data_->at(index);
    }
    /// operator prístupu
    virtual string& operator[](int index) {
        return this->at(index);
    }
    /// Nastavi nastavi dajsiu hlavicku, aj ked je hlavicka prazna
    /// \param headerName Meno hlavicky
    void setNextHeader(const string& headerName);
    /// Zízkame nazov hlavicky pre Ity stlpec
    /// \param i Stlpec ktorého chceme ziskat hlavicku
    /// \return Nazov hlavicky
    string& getHeaderAt(const int i);
    /// Vrati aktualnu velkost hlavicky
    /// \return Pocet stlpcov v hlavicke
    int getSizeHeader();
    /// Vrati nazov kazdeho stlpca oddeleného tabom
    /// \return string ktory obsahuje celhu hlavciku
    string& getFullHeader();
protected:
    structures::List<string> *data_;
    structures::List<string> *header_;

};

StoredData::StoredData() :
    data_(new structures::ArrayList<string>),
    header_(new structures::ArrayList<string>) {

}

StoredData::~StoredData() {
    delete data_;
    data_ = nullptr;
    delete header_;
    header_ = nullptr;
}

void StoredData::setNextHeader(const string &headerName) {
    header_->add(headerName);
}

string &StoredData::getHeaderAt(const int i) {
    return header_->at(i);
}

int StoredData::getSizeHeader() {
    return header_->size();
}

string& StoredData::getFullHeader() {
    stringstream wstrignBuilder;
    for (auto item: *header_) {
        wstrignBuilder << item << "\t";
    }
    string returnValue = wstrignBuilder.str();
    return returnValue;
}
