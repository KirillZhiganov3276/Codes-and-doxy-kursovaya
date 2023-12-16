/** 
* @file Errors.h
* @author Жиганов К.А.
* @version 1.0
* @date 14.12.2023
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля Errors
*/

#include <string>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/** 
* @brief Класс обработки ошибок
* @param File_Log путь к файлу с журналом ошибок 
*/
class Errors{
    public:
        string get_File_Log();
        void set_File_Log(string file);

        void error_recording(string flag, string info);

    private:
        string File_Log;
};
