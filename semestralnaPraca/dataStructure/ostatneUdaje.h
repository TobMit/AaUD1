//
// Created by Tobias on 06/05/2022.
//
#pragma once
#include "storedData.h"

template<typename T>
class OstatneUdaje : public StoredData<T>{
private:
    wstring code;
    wstring offTitle;
public:
    OstatneUdaje() {
    };
    OstatneUdaje(const wstring &code, const wstring &offTitle);

    wstring &getCode() override;

    wstring &getOfficialTitle() override;

    void setCode(const wstring &pCode) override;

    void setOfficialTitle(const wstring &offTitleName) override;

    void nastavDalsiParameter(const T &parameter) override;

    int getSize() override;

};

template<typename T>
OstatneUdaje<T>::OstatneUdaje(const wstring &code, const wstring &offTitle) :
        code(code), offTitle(offTitle)
{
}

template<typename T>
wstring &OstatneUdaje<T>::getCode() {
    return code;
}

template<typename T>
wstring &OstatneUdaje<T>::getOfficialTitle() {
    return offTitle;
}

template<typename T>
void OstatneUdaje<T>::setCode(const wstring &pCode) {
    code = pCode;
}

template<typename T>
void OstatneUdaje<T>::setOfficialTitle(const wstring &offTitleName) {
    offTitle = offTitleName;
}

template<typename T>
void OstatneUdaje<T>::nastavDalsiParameter(const T &parameter) {
    this->data_->add(parameter);
}

template<typename T>
int OstatneUdaje<T>::getSize() {
    return this->data_->size();
}

