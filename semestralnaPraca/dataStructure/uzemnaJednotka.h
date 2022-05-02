//
// Created by Tobias on 30. 4. 2022.
//
#pragma once
#include "storedData.h"

template<typename T>

class UzemnaJednotka : public StoredData<T> {
public:
    UzemnaJednotka();

    UzemnaJednotka(const wstring &sortNumber,const wstring &code,const wstring &officialTitle,const wstring &mediumTitle,
                   const wstring &shortTitle,const wstring &note);

    wstring &getCode() override;

    wstring &getOfficialTitle() override;

    void setCode(const wstring &code) override;

    void setOfficialTitle(const wstring& offTitleName) override;

    void nastavDalsiParameter(const T &parameter) override;

    int getSize() override;

private:
    int dataIndex = 0;

};


template<typename T>
UzemnaJednotka<T>::UzemnaJednotka()
{
    for (int i = 0; i < getSize(); ++i) {
        StoredData<T>::data_->add(L"");
    }
}

template<typename T>
UzemnaJednotka<T>::UzemnaJednotka(const wstring& sortNumber, const wstring& code, const wstring& officialTitle, const wstring& mediumTitle,
                                  const wstring& shortTitle,const wstring& note) {
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
void UzemnaJednotka<T>::setCode(const wstring& code) {
    StoredData<T>::at(1) = code;
}

template<typename T>
void UzemnaJednotka<T>::setOfficialTitle(const wstring& offTitleName) {
    StoredData<T>::at(2) = offTitleName;
}

template<typename T>
void UzemnaJednotka<T>::nastavDalsiParameter(const T& parameter) {
    if (dataIndex == 1 || dataIndex == 2) {
        dataIndex = 3;
    }
    // ak to nepatir do rozsahu tabulky tak to budem ignorovať
    // obchádzam to takto aby som nemusel vyhadzovať vynimku
    if (dataIndex < getSize()) {
        this->at(dataIndex) = parameter;
        dataIndex++;
    }
}

template<typename T>
int UzemnaJednotka<T>::getSize() {
    return 6;
}


