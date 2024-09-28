//
// Created by Sarmat on 28.09.2024.
//

#ifndef DATA_NORMALIZER_INTERNAL_STRUCTS_H
#define DATA_NORMALIZER_INTERNAL_STRUCTS_H

#include <iostream>

struct TableDataset1Data{
    explicit TableDataset1Data(std::pair <uint64_t,uint64_t> uid_,
                               std::wstring full_name_,std::wstring email_,
                               std::wstring sex_,std::wstring address_,
                               std::wstring birthdate_,std::wstring phone_) :
                               uid(uid_),full_name(full_name_),email(email_),address(address_),
                               sex(sex_),birthdate(birthdate_),phone(phone_){

    }
    std::pair <uint64_t,uint64_t> uid;
    std::wstring full_name;
    std::wstring email;
    std::wstring address;
    std::wstring sex;
    std::wstring birthdate;
    std::wstring phone;
};

struct TableDataset2Data{
    std::pair <uint64_t,uint64_t> uid;
    std::wstring first_name;
    std::wstring middle_name;
    std::wstring last_name;
    std::wstring birthdate;
    std::wstring phone;
    std::wstring address;
};

struct TableDataset3Data{
    std::pair <uint64_t,uint64_t> uid;
    std::wstring email;
    std::wstring birthdate;
    std::wstring sex;
};

#endif //DATA_NORMALIZER_INTERNAL_STRUCTS_H
