//
// Created by Tobias on 30. 4. 2022.
//
#pragma once
#include "storedData.h"

template<typename T>

class UzemnaJednotka : public StoredData<T> {
public:

    wstring &getCode() override;

    wstring &getOfficialTitle() override;

    void setCode(wstring &code) override;

    void setOfficialTitle(wstring& offTitleName) override;

    void nastavDalsiParameter(T &parameter) override;
private:
    int dataIndex = 0;

};


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
    }
    this->at(dataIndex);
    dataIndex++;
}


