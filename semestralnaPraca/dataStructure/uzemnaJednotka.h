//
// Created by Tobias on 30. 4. 2022.
//
#pragma once
#include "storedData.h"


class UzemnaJednotka : public StoredData {
public:
    UzemnaJednotka();

    UzemnaJednotka(const string &sortNumber,const string &code,const string &officialTitle,const string &mediumTitle,
                   const string &shortTitle,const string &note);

    string &getCode() override;

    string &getOfficialTitle() override;

    void setCode(const string &code) override;

    void setOfficialTitle(const string& offTitleName) override;

    void setNextParameter(const string &parameter) override;

    int getSize() override;

private:
    int dataIndex = 0;

};


UzemnaJednotka::UzemnaJednotka()
{
    for (int i = 0; i < getSize(); ++i) {
        StoredData::data_->add("");
    }
}


UzemnaJednotka::UzemnaJednotka(const string& sortNumber, const string& code, const string& officialTitle, const string& mediumTitle,
                                  const string& shortTitle,const string& note) {
    StoredData::data_->add(sortNumber);
    StoredData::data_->add(code);
    StoredData::data_->add(officialTitle);
    StoredData::data_->add(mediumTitle);
    StoredData::data_->add(shortTitle);
    StoredData::data_->add(note);
}


string &UzemnaJednotka::getCode() {
    return StoredData::at(1);
}


string &UzemnaJednotka::getOfficialTitle() {
    return StoredData::at(2);
}


void UzemnaJednotka::setCode(const string& code) {
    StoredData::at(1) = code;
}


void UzemnaJednotka::setOfficialTitle(const string& offTitleName) {
    StoredData::at(2) = offTitleName;
}


void UzemnaJednotka::setNextParameter(const string& parameter) {
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


