/**
 * @file main.cpp
 * @author В.О. Водянов
 * @version 0.1
 * @date 01.08.2019
 * @copyright ИБСТ ПГУ
 * @brief Главный модуль
 */

/**
 * @mainpage Клиент службы времени NTP
 * Использование
 *
 * Вывести разницу сетевого и системного времени:
 * @code
 * ntp diff [ntp_server] ...
 * @endcode
 * Cинхронизировать системное и сетевое время:
 * @code
 * ntp sync [ntp_server] ...
 * @endcode
 * @author Водянов
 * @version 0.1
 * @date 01.08.2019
 * @copyright ИБСТ ПГУ
 * @warning Реализована упращённая версия протокола NTP - SNTP
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

#include "NTP.h"

using namespace std;

/**
 * @brief Печатает на стандартный вывод время с точностью до милисекунд
 * @param [in] t_ntp время в 1/2^32 долях секунды
 */
void print_ntp_time(uint64_t t_ntp)
{
    bool f = false;
    uint64_t sec = t_ntp >> 32;
    uint64_t msec = 0x00000000FFFFFFFF & t_ntp;
    msec *= 1000;
    msec >>= 32;
    if(sec/3600 != 0)
    {
        cout << (sec/3600) << "h ";
        f = true;
    }
    if((sec%3600)/60 != 0)
    {
        cout << (sec%3600)/60 << "m ";
        f = true;
    }
    if(sec%60)
    {
        cout << (sec%60) << "s ";
        f = true;
    }
    if(msec)
    {
        cout << (msec) << "ms";
        f = true;
    }
    if(!f)
        cout << 0;
}

int main(int argc, char** argv)
{
    try {
        vector<string> servers;
        Mode mode;
        int64_t time_diff;
        time_t new_time;

        if(argc < 2)
            throw MODE_UNDEFINED;

        if(strcmp(argv[1], "diff") == 0)
            mode = DIFF;
        else if(strcmp(argv[1], "sync") == 0)
            mode = SYNC;
        else
            throw MODE_UNDEFINED;

        if(argc == 2)
            servers = {"0.ru.pool.ntp.org", "1.ru.pool.ntp.org", "2.ru.pool.ntp.org", "3.ru.pool.ntp.org"};
        for(int i = 2; i < argc; i++)
            servers.push_back(argv[i]);

        NTP ntp(servers);

        switch(mode)
        {
        case SYNC:
            new_time = ntp.sync();
            cout << "Время было синхронизированно" << endl;
            cout << "Новое системное время: " << put_time(localtime(&new_time), "%d.%m.%Y %H:%M:%S %Z");
            cout << endl;
            break;
        case DIFF:
            time_diff = ntp.get_time_diff();

            cout << "Системное время ";
            if(time_diff > 0)
                cout << "отстаёт от сетевого на ";
            else
                cout << "опережает сетевое на ";

            print_ntp_time(llabs(time_diff));
            cout << endl;
        }
    }
    catch(Error e)
    {
        switch (e)
        {
        case MODE_UNDEFINED:
            cerr << "Ошибка: Не указан режим работы программы" << endl;
            break;
        case NTP_REQUEST_FAIL:
            cerr << "Ошибка: Не удалоь выполнить запрос к ntp серверу" << endl;
            break;
        case SET_SYS_TIME_ERROR:
            perror("Не удалось установить системное время");
            break;
        case GET_SYS_TIME_ERROR:
            perror("Не удалось получить системное время");
            break;
        case SOCKET_ERROR:
            perror("Socket error");
            break;
        }
        return 1;
    }

    return 0;
}