//
// Created by Tobias on 30. 4. 2022.
//
#pragma once
#include "storedData.h"


class UzemnaJednotka : public StoredData {
public:
    UzemnaJednotka();

    UzemnaJednotka(const wstring &sortNumber,const wstring &code,const wstring &officialTitle,const wstring &mediumTitle,
                   const wstring &shortTitle,const wstring &note);

    wstring &getCode() override;

    wstring &getOfficialTitle() override;

    void setCode(const wstring &code) override;

    void setOfficialTitle(const wstring& offTitleName) override;

    void setNextParameter(const wstring &parameter) override;

    int getSize() override;

private:
    int dataIndex = 0;

};


UzemnaJednotka::UzemnaJednotka()
{
    for (int i = 0; i < getSize(); ++i) {
        StoredData::data_->add(L"");
    }
}


UzemnaJednotka::UzemnaJednotka(const wstring& sortNumber, const wstring& code, const wstring& officialTitle, const wstring& mediumTitle,
                                  const wstring& shortTitle,const wstring& note) {
    StoredData::data_->add(sortNumber);
    StoredData::data_->add(code);
    StoredData::data_->add(officialTitle);
    StoredData::data_->add(mediumTitle);
    StoredData::data_->add(shortTitle);
    StoredData::data_->add(note);
}


wstring &UzemnaJednotka::getCode() {
    return StoredData::at(1);
}


wstring &UzemnaJednotka::getOfficialTitle() {
    return StoredData::at(2);
}


void UzemnaJednotka::setCode(const wstring& code) {
    StoredData::at(1) = code;
}


void UzemnaJednotka::setOfficialTitle(const wstring& offTitleName) {
    StoredData::at(2) = offTitleName;
}


void UzemnaJednotka::setNextParameter(const wstring& parameter) {
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


int UzemnaJednotka::getSize() {
    return 6;
}


