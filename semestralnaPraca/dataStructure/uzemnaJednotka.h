//
// Created by Tobias on 30. 4. 2022.
//
#pragma once
#include "storedData.h"


class UzemnaJednotka : public StoredData {
public:
    UzemnaJednotka();

    UzemnaJednotka(const wstring &pSortNumber, const wstring &pCode, const wstring &pOfficialTitle, const wstring &pMediumTitle,
                   const wstring &pShortTitle, const wstring &pNote);

    wstring getCode() override;

    wstring getOfficialTitle() override;

    void setCode(const wstring pCode) override;

    void setOfficialTitle(const wstring pOffTitleName) override;

    void setNextParameter(const wstring parameter) override;

    int getSize() override;

    ~UzemnaJednotka() override;

    wstring &at(int index) override;

private:
    int dataIndex = 0;
    wstring sortNumber;
    wstring code;
    wstring officialTitle;
    wstring mediumTitle;
    wstring shortTitle;
    wstring note;

};


inline UzemnaJednotka::UzemnaJednotka()
{
}


inline UzemnaJednotka::UzemnaJednotka(const wstring& pSortNumber, const wstring& pCode, const wstring& pOfficialTitle, const wstring& pMediumTitle,
                               const wstring& pShortTitle, const wstring& pNote) {
    sortNumber = pSortNumber;
    code = pCode;
    officialTitle = pOfficialTitle;
    mediumTitle = pMediumTitle;
    sortNumber = pShortTitle;
    note = pNote;
}


inline wstring UzemnaJednotka::getCode() {
    return code;
}


inline wstring UzemnaJednotka::getOfficialTitle() {
    return officialTitle;
}


inline void UzemnaJednotka::setCode(const wstring pCode) {
    code = pCode;
}


inline void UzemnaJednotka::setOfficialTitle(const wstring pOffTitleName) {
    officialTitle = pOffTitleName;
}


inline void UzemnaJednotka::setNextParameter(const wstring parameter) {
    switch (dataIndex) {
        case 0:
            sortNumber = parameter;
            break;
        case 1:
            code = parameter;
            break;
        case 2:
            officialTitle = parameter;
            break;
        case 3:
            mediumTitle = parameter;
            break;
        case 4:
            shortTitle = parameter;
            break;
        case 5:
            note = parameter;
            break;
        default:
            return;

    }
    dataIndex++;
}


inline int UzemnaJednotka::getSize() {
    return 6;
}

inline UzemnaJednotka::~UzemnaJednotka() {

}

inline wstring &UzemnaJednotka::at(int index) {
    switch (index) {
        case 0:
            return sortNumber;
            break;
        case 1:
            return code;
            break;
        case 2:
            return officialTitle;
            break;
        case 3:
            return mediumTitle;
            break;
        case 4:
            return shortTitle;
            break;
        case 5:
            return note;
            break;

    }
}


