/** 
* @file main.cpp
* @brief Функция для предоставления пользователю справки по использованию программы
*/
#include <getopt.h>
#include "ServerClientInterface.h"

#pragma one

using namespace std;

/**
* @brief Функция для получения справки по использованию программы
*/
void help(){
    std::cout << "Программа является сервером для взаимодействия с клиентом." << std::endl;
    std::cout << "Для работы программы пользователю надо указать параметры командной строки:\n" << std::endl;
    std::cout << "Параметр -i или --Ip это сетевой адрес сервера (обязательный)." << std::endl;
    std::cout << "Параметр -p или --Port это порт сервера (необязательный)." << std::endl;
    std::cout << "Параметр -d или --Db указывает на файл с базой данных клиентов." << std::endl;
    std::cout << "Параметр -l или --Log указывает файл для аутентификации (необязательный)." << std::endl;
    std::cout << "Параметр -h или --Help вводится для получения справки по использованию программы.\n" << std::endl;
}

/**
* @brief Функция для получения от оператора параметров командной строки
*/
int main (int argc, char *argv[]){

	// Опции командной строки
    const struct option long_options[] = {
        {"Ip", optional_argument, nullptr, 'i'},
        {"Port", optional_argument, nullptr, 'p'},
        {"Db", optional_argument, nullptr, 'd'},
        {"Log", optional_argument, nullptr, 'l'},
        {"Help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, 0}
    };

    // Класс для взаимодействия с клиент-сервером
    string address = "";
    int port = 0;
    string database  = "";
    string logFile = "";

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "i::p::d::l::h::", long_options, &option_index)) != -1) {

        switch (opt) {

        case 'i':
            if (optarg != nullptr) {
                address = string(optarg);
            }
            else{
                address = string("127.0.0.1");
            }
            break;
            
        case 'p':
            if (optarg != nullptr) {
                port = stoi(optarg);
            }
            else{
                port = stoi("33333");
            }
            break;
        
        case 'd':
            if (optarg != nullptr) {
                database = string(optarg);
            }
            else{
                database = string("DB.conf");
            }
            break;
        
        case 'l':
            if (optarg != nullptr) {
                logFile = string(optarg);
            }
            else{
                logFile = string("Log.conf");
            }
            break;
            
        case 'h':
            help();
            
            return 1;
        
        default:
            // Некорректная опция
            cout << "Error: Invalid option\n";
            help();
            return 2;
        }
    }

    if(address == "" or port == 0 or database == "" or logFile == ""){
        cout << "Не указаны параметры" << endl;
        help();
        return 0;
    }

	ServerClientInterface newServer;
    newServer.set_address(address);
    newServer.set_port(port);
    newServer.interaction(database, logFile);

    // ./server -i127.0.0.1 -p33333 -dDB.conf -llog.conf
	return 0;
}