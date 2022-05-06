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
    virtual void setNextParameter(const T& parameter) = 0;
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
protected:
    structures::List<T> *data_;
    structures::List<wstring> *header_;

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

template<typename T>
void StoredData<T>::setNextHeader(const wstring &headerName) {
    header_->add(headerName);
}

template<typename T>
wstring &StoredData<T>::getHeaderAt(const int i) {
    return header_->at(i);
}

template<typename T>
int StoredData<T>::getSizeHeader() {
    return header_->size();
}
