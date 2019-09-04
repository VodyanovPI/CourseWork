#pragma once

/**
 * @file NTP.h
 * @author В.О. Водянов
 * @version 0.1
 * @date 01.08.2019
 * @copyright ИБСТ ПГУ
 * @brief Заголовочный файл для модуля NTP, выполняющего запрос к NTP серверу
 */

#include <vector>
#include <string>

/**
 * @brief Перечисление режимов работы программы
 */
enum Mode
{
    DIFF,  //!< Вывод разницы
    SYNC   //!< Синхронизация
};

/**
 * @brief Перечисление возможных ошибок
 */
enum Error
{
    MODE_UNDEFINED,      //!< Режим работы программы не определён
    NTP_REQUEST_FAIL,    //!< NTP запрос не удался
    SET_SYS_TIME_ERROR,  //!< Ошибка при установке системного времени
    GET_SYS_TIME_ERROR,  //!< Ошибка при получении системного времени
    SOCKET_ERROR         //!< Ошибка сокета
};

/**
 * @brief Класс для работы с NTP сервером,
 * метод get_time_diff возвращает разность сетевого и системного времени,
 * метод sync синхронизирует системное и сетевое время
 * @warning Системное и сетевое время не должны отличатся более чем не 34 года
 */
class NTP
{
private:
    std::vector<std::string> servers; //!< Список NTP серверов
    int sock; //!< дескриптор сокета
    /**
     * @brief Устанавливает соединение с NTP сервером
     * @param[in] ntp_serv имя или ip адресс NTP сервера
     * @return true в случае успеха, иначе false
     */
    bool server_connect(const std::string &ntp_serv);
    /**
     * @brief Отправляет NTP пакет на сервер,
     * @return true в случае успеха, иначе false
     * @throw Error в случае ошибки
     */
    bool send_ntp_pack();
    /**
     * @brief Принимает ответ от NTP сервер,
     * если флаг set_time_flag установлен в true, устанавливает системное время,
     * если указатель new_sys_time не нулевой, то по нему записывается новое системное время. 
     * @param [out] t_diff разность сетевого и системного времени
     * @param [in] set_time_flag флаг
	 * @param new_sys_time указатель на время
     * @return true в случае успеха, иначе false
     * @throw Error в случае ошибки
     */
    bool recv_ntp_pack(int64_t &t_diff, bool set_time_flag, time_t *new_sys_time);
    /**
     * @brief Выполняет запрос к NTP серверу,
     * если флаг set_time_flag установлен в true, устанавливает системное время,
     * если указатель new_sys_time не нулевой, то по нему записывается новое системное время. 
     * @param [out] t_diff разность сетевого и системного времени
     * @param [in] set_time_flag флаг
     * @param new_sys_time указатель на время
     * @return true в случае успеха, иначе false
     * @throw Error в случае ошибки
     */
    bool ntp_request(int64_t &t_diff, bool set_time_flag, time_t *new_sys_time);
public:
    /**
     * @brief Конструктор
     * @param [in] serv_list список NTP серверов
     */
    NTP(const std::vector<std::string> &serv_list);
    /**
     * @brief Cинхронизирует системное и сетевое время
     * @return Новое системное время
     * @throw Error в случае ошибки
     */
    time_t sync();
    /**
     * @brief Получить разность сетевого и системного времени
     * @return разность сетевого и системного времени в 1/2^32 долях секунды
     * @throw Error в случае ошибки
     */
    int64_t get_time_diff();
    ~NTP();
};

/**
 * @brief NTP пакет
 */
struct ntp_packet
{
    uint8_t li_vn_mode;      //!< Список NTP серверов
    uint8_t stratum;
    uint8_t poll;
    uint8_t precision;
    uint32_t rootDelay;
    uint32_t rootDispersion;
    uint32_t refId;
    uint64_t refTm;          //!< Время обновления
    uint64_t origTm;         //!< Начальное время
    uint64_t rxTm;           //!< Время приёма 
    uint64_t txTm;           //!< Время отправки 
} __attribute__((packed));

/**
 * @brief Конвертирует метку времени из формата NTP в формат timespec
 * @param [in] t_ntp NTP метка времени
 * @param tp указатель на структуру timespec
 */
inline void ntp_to_ts(const uint64_t t_ntp, timespec *tp)
{
    tp->tv_sec = (t_ntp >> 32) - 2208988800U;
    uint64_t f_sec = 0x00000000FFFFFFFF & t_ntp;
    f_sec *= 1000000000;
    f_sec >>= 32;
    tp->tv_nsec = f_sec;
}

/**
 * @brief Конвертирует метку времени из формата timespec в формат NTP
 * @param [out] t_ntp NTP метка времени
 * @param tp указатель на структуру timespec
 */
inline void ts_to_ntp(uint64_t &t_ntp, const timespec *tp)
{
    t_ntp = tp->tv_sec + 2208988800U;
    t_ntp <<= 32;
    uint64_t f_sec = tp->tv_nsec;
    f_sec <<= 32;
    f_sec /= 1000000000;
    t_ntp += f_sec;
}