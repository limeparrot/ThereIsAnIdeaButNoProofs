//
// Created by Sarmat on 28.09.2024.
//

#ifndef DATA_NORMALIZER_INTERNAL_STRUCTS_H
#define DATA_NORMALIZER_INTERNAL_STRUCTS_H

#include <iostream>

struct TableDataset1Data{
    explicit TableDataset1Data(std::wstring uid_ = L"",
                               std::wstring full_name_ = L"",std::wstring email_ = L"",
                               std::wstring sex_ = L"",std::wstring address_ = L"",
                               std::wstring birthdate_ = L"",std::wstring phone_ = L"") :
                               uid(std::move(uid_)),full_name(std::move(full_name_)),email(std::move(email_)),address(std::move(address_)),
                               sex(std::move(sex_)),birthdate(std::move(birthdate_)),phone(std::move(phone_)){

    }
   //std::pair <uint64_t,uint64_t> uid;
    std::wstring uid;
    std::wstring full_name;
    std::wstring email;
    std::wstring address;
    std::wstring sex;
    std::wstring birthdate;
    std::wstring phone;
};

struct TableDataset2Data{
    explicit TableDataset2Data(std::wstring uid_ = L"",
                                std::wstring first_name_ = L"",std::wstring middle_name_ = L"",
                                std::wstring last_name_ = L"",std::wstring birthdate_ = L"",
                                std::wstring phone_ = L"",std::wstring address_ = L"") :
                                uid(std::move(uid_)),first_name(std::move(first_name_)),middle_name(std::move(middle_name_)),
                                last_name(std::move(last_name_)),birthdate(std::move(birthdate_)),phone(std::move(phone_)),
                                address(std::move(address_)){

    }
//    std::pair <uint64_t,uint64_t> uid;
    std::wstring uid;
    std::wstring first_name;
    std::wstring middle_name;
    std::wstring last_name;
    std::wstring birthdate;
    std::wstring phone;
    std::wstring address;
};

struct TableDataset3Data{
    explicit TableDataset3Data(std::wstring uid_ = L"",
                               std::wstring name_ = L"",std::wstring email_ = L"",
                               std::wstring birthdate_ = L"",std::wstring sex_ = L"") :
                               uid(std::move(uid_)),
                               name(std::move(name_)),email(std::move(email_)),
                               birthdate(std::move(birthdate_)), sex(std::move(sex_)){

    }
//    std::pair <uint64_t,uint64_t> uid;
    std::wstring uid;
    std::wstring name;
    std::wstring email;
    std::wstring birthdate;
    std::wstring sex;
};

#endif //DATA_NORMALIZER_INTERNAL_STRUCTS_H
