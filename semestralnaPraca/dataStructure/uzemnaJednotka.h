//
// Created by Tobias on 30. 4. 2022.
//
#pragma once
#include "storedData.h"

template<typename T>

class UzemnaJednotka : public StoredData<T> {
public:
    UzemnaJednotka();

    UzemnaJednotka(wstring &sortNumber, wstring &code, wstring &officialTitle, wstring &mediumTitle, wstring &shortTitle, wstring &note);

    wstring &getCode() override;

    wstring &getOfficialTitle() override;

    void setCode(wstring &code) override;

    void setOfficialTitle(wstring& offTitleName) override;

    void nastavDalsiParameter(T &parameter) override;

    int getSize() override;

private:
    int dataIndex = 0;

};


template<typename T>
UzemnaJednotka<T>::UzemnaJednotka()
{
}

template<typename T>
UzemnaJednotka<T>::UzemnaJednotka(wstring &sortNumber, wstring &code, wstring &officialTitle, wstring &mediumTitle,
                                  wstring &shortTitle, wstring &note) {
    StoredData<T>::data_->add(sortNumber);
    StoredData<T>::data_->add(code);
    StoredData<T>::adata_->add(officialTitle);
    StoredData<T>::data_->add(mediumTitle);
    StoredData<T>::data_->add(shortTitle);
    StoredData<T>::data_->add(note);
}

template<typename T>
wstring &UzemnaJednotka<T>::getCode() {
    return StoredData<T>::at(1);
}

template<typename T>
wstring &UzemnaJednotka<T>::getOfficialTitle() {
    return StoredData<T>::at(2);
}

template<typename T>
void UzemnaJednotka<T>::setCode(wstring &code) {
    StoredData<T>::at(1) = code;
}

template<typename T>
void UzemnaJednotka<T>::setOfficialTitle(wstring &offTitleName) {
    StoredData<T>::at(1) = offTitleName;
}

template<typename T>
void UzemnaJednotka<T>::nastavDalsiParameter(T &parameter) {
    if (dataIndex == 1 || dataIndex == 2) {
        dataIndex = 3;

    // ak to nepatir do rozsahu tabulky tak to budem ignorovať
    // obchádzam to takto aby som nemusel vyhadzovať vynimku
    } else if (dataIndex < getSize()) {
        this->at(dataIndex);
        dataIndex++;
    }
}

template<typename T>
int UzemnaJednotka<T>::getSize() {
    return 6;
}


