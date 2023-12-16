/**
* @file User.cpp
*/
#include "User.h"

/**
* @brief Геттер для атрибута ID
*/
string User::get_ID(){
    return ID;
}

/**
* @brief Сеттер для атрибута ID
*/
void User::set_ID(string ID1){
    ID = ID1;

}

/**
* @brief Геттер для атрибута hash
*/
string User::get_hash(){
    return hash;
}

/**
* @brief Сеттер для атрибута hash
*/
void User::set_hash(string hash1){
    hash = hash1;
}

/**
* @brief Функция для проверки ID подключенного клиента
* @return Возвращает true - если в БД есть ID подключенного клиента, иначе false
*/
bool User::СheckLogin(vector<string> Db_ID){
    for (size_t i = 0; i < Db_ID.size(); ++i) {
        if (Db_ID[i] == ID){
            return 1;
        }
    }

    return 0;
    
}

/**
* @brief Функция для проверки пароля подключенного клиента
* @return Возвращает true - если пароль подлюченнго клиента совпадает с паролем из БД, иначе false
*/
bool User::CheckPassword(vector<string> Db_password, vector<string> Db_ID, string SALT){
    int t = 0;
    for (size_t i = 0; i < Db_ID.size(); ++i) {
        if (Db_ID[i] == ID){
            t = i;
        }
    }
    
    string hashMD5 = SALT + Db_password[t];
    string HASHMD5 = MD5_hash(hashMD5);
    
    if (HASHMD5 == hash){
        return 1;
    }
    else{
        return 0;
    }
}