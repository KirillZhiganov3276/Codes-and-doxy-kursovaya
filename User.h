/** 
* @file User.h
* @author Жиганов К.А.
* @version 1.0
* @date 14.12.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля User
*/

#include <string>
#include  <vector>
#include <iostream>

#include "./md5/md5.h"

using namespace std;

/** 
* @brief Класс, представляющий информацию о подлюченном пользователе
* @param ID ID подлюченного клиента
* @param hash хэш-код подлюченного клиента
*/
class User{
    private:
        string ID;
        string hash;
    public:
        bool СheckLogin(vector<string> Db_ID);
        bool CheckPassword(vector<string> Db_hash, vector<string> Db_ID, string SALT);
        
        string get_ID();
        void set_ID(string ID1);

        string get_hash();
        void set_hash(string hash1);

};
