/**
 * @file NTP.cpp
 * @author В.О. Водянов
 * @version 0.1
 * @date 01.08.2019
 * @copyright ИБСТ ПГУ
 * @brief Реализация модуля NTP, выполняющего запрос к NTP серверу
 * @warning Реализована упращённая версия протокола NTP - SNTP
 */

#include <byteswap.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

#include "NTP.h"

using namespace std;

NTP::NTP(const vector<string> &serv_list): servers(serv_list)
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        throw SOCKET_ERROR;
    
    struct timeval timeout = {.tv_sec = 1, .tv_usec = 0};

    if(setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*) &timeout, sizeof(timeout)) < 0)
        throw SOCKET_ERROR;

    if(setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*) &timeout, sizeof(timeout)) < 0)
        throw SOCKET_ERROR;
}

bool NTP::server_connect(const string &ntp_serv)
{
    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(123);
    hostent *host = gethostbyname(ntp_serv.c_str());
    if(host == nullptr)
        return false;
    server_addr.sin_addr = * reinterpret_cast<in_addr*> (host->h_addr);
    if(connect(sock, (sockaddr*) &server_addr, sizeof(server_addr)) == -1)
        return false;
    return true;
}

bool NTP::send_ntp_pack()
{
    uint64_t txClientTm;
    timespec tp;
    ntp_packet npack = {};
    npack.li_vn_mode = 0x23;
    if(clock_gettime(CLOCK_REALTIME, &tp) == -1)
        throw GET_SYS_TIME_ERROR;
    ts_to_ntp(txClientTm, &tp);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    npack.txTm = bswap_64(txClientTm);
#else
    npack.txTm = txClientTm;
#endif
    if(send(sock, &npack, sizeof(npack), 0) == -1)
        return false;
    return true;
}

bool NTP::recv_ntp_pack(int64_t &t_diff, bool set_time_flag, time_t *new_sys_time)
{
    uint64_t rxClientTm, txClientTm, rxServerTm, txServerTm;
    ntp_packet npack;
    timespec tp;
    if(recv(sock, &npack, sizeof(npack), 0) < (int) sizeof(npack))
        return false;
    if(clock_gettime(CLOCK_REALTIME, &tp) == -1)
        throw GET_SYS_TIME_ERROR;
    ts_to_ntp(rxClientTm, &tp);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    txClientTm = bswap_64(npack.origTm);
    rxServerTm = bswap_64(npack.rxTm);
    txServerTm = bswap_64(npack.txTm);
#else
    txClientTm = npack.origTm;
    rxServerTm = npack.rxTm;
    txServerTm = npack.txTm;
#endif
    t_diff = (int64_t)((rxServerTm - txClientTm) + (txServerTm - rxClientTm)) / 2;
    if(set_time_flag)
    {
        ntp_to_ts(rxClientTm + t_diff, &tp);
        if(clock_settime(CLOCK_REALTIME, &tp))
            throw SET_SYS_TIME_ERROR;
        if(new_sys_time != nullptr)
            *new_sys_time = tp.tv_sec;
    }
    return true;
}

bool NTP::ntp_request(int64_t &t_diff, bool set_time_flag, time_t *new_sys_time)
{
    for(const string &ntp_serv : servers)
    {
        if(!server_connect(ntp_serv))
            continue;
        if(!send_ntp_pack())
            continue;
        if(recv_ntp_pack(t_diff, set_time_flag, new_sys_time))
            return true;
    }
    return false;
}

time_t NTP::sync()
{
    time_t new_time;
    int64_t t_diff;
    if(!ntp_request(t_diff, true, &new_time))
        throw NTP_REQUEST_FAIL;
    return new_time;
}

int64_t NTP::get_time_diff()
{
    int64_t t_diff;
    if(!ntp_request(t_diff, false, nullptr))
        throw NTP_REQUEST_FAIL;
    return t_diff;
}

NTP::~NTP()
{
    close(sock);
}