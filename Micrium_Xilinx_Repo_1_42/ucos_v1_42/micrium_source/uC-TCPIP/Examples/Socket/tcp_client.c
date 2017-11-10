/*
*********************************************************************************************************
*                                             uC/TCP-IP
*                                      The Embedded TCP/IP Suite
*
*                         (c) Copyright 2004-2015; Micrium, Inc.; Weston, FL
*
*                  All rights reserved.  Protected by international copyright laws.
*
*                  uC/TCP-IP is provided in source form to registered licensees ONLY.  It is
*                  illegal to distribute this source code to any third party unless you receive
*                  written permission by an authorized Micrium representative.  Knowledge of
*                  the source code may NOT be used to develop a similar product.
*
*                  Please help us continue to provide the Embedded community with the finest
*                  software available.  Your honesty is greatly appreciated.
*
*                  You can find our product's user manual, API reference, release notes and
*                  more information at: https://doc.micrium.com
*
*                  You can contact us at: http://www.micrium.com
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                               EXAMPLE
*
*                                           TCP ECHO CLIENT
*
* Filename      : tcp_client.c
* Version       : V3.03.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : (1) This example shows how to create a TCP client using IPv4 or IPv6 string address.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <Source/net_cfg_net.h>
#include  <Source/net_sock.h>
#include  <Source/net_app.h>
#include  <Source/net_util.h>
#include  <Source/net_ascii.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*********************************************************************************************************
*/

#define  TCP_SERVER_PORT  10001
#define  TX_BUF_SIZE         16


/*
*********************************************************************************************************
*                                           App_TCP_Client()
*
* Description : TCP Echo client:
*
*                   (a) Open a socket.
*                   (b) Configure socket's address.
*                   (c) Connect socket.
*                   (d) Transmit data to the server.
*                   (e) Receive echo response from the server
*                   (f) Close socket.
*
* Argument(s) : p_ip_addr   Pointer to a string that contains the IP address of the server.
*
* Return(s)   : DEF_OK,   No error, message sent and echo received.
*
*               DEF_FAIL, Otherwise.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  App_TCP_Client (CPU_CHAR  *p_ip_addr)
{
#if   defined(NET_IPv6_MODULE_EN)
    NET_IPv6_ADDR             server_addr;
#elif defined(NET_IPv4_MODULE_EN)
    NET_IPv4_ADDR             server_addr;
#endif
    NET_SOCK_ADDR             server_sock_addr;
    NET_SOCK_ADDR_LEN         server_sock_addr_len;
    NET_IP_ADDR_FAMILY        ip_family;
    NET_SOCK_PROTOCOL_FAMILY  protocol_family;
    NET_SOCK_ADDR_FAMILY      sock_addr_family;
    NET_IP_ADDR_LEN           ip_addr_len;
    NET_SOCK_ID               sock;
    NET_SOCK_DATA_SIZE        tx_size;
    NET_SOCK_DATA_SIZE        tx_rem;
    CPU_CHAR                  tx_buf[] = "This is a TCP message";
    NET_SOCK_RTN_CODE         rx_size;
    NET_SOCK_DATA_SIZE        rx_rem;
    CPU_INT08U               *p_buf;
    NET_ERR                   err;


                                                                /* ---------------- CONVERT IP ADDRESS ---------------- */
    ip_family = NetASCII_Str_to_IP(p_ip_addr,
                                  &server_addr,
                                   sizeof(server_addr),
                                  &err);
    switch (err) {
        case NET_ASCII_ERR_NONE:
             break;

        case NET_ASCII_ERR_IP_FAMILY_NOT_PRESENT:
        case NET_ASCII_ERR_INVALID_CHAR_SEQ:
        default:
             return (DEF_FAIL);
    }

    switch (ip_family) {
        case NET_IP_ADDR_FAMILY_IPv4:
             sock_addr_family = NET_SOCK_ADDR_FAMILY_IP_V4;
             protocol_family  = NET_SOCK_PROTOCOL_FAMILY_IP_V4;
             ip_addr_len      = NET_IPv4_ADDR_SIZE;
             break;

        case NET_IP_ADDR_FAMILY_IPv6:
             sock_addr_family = NET_SOCK_ADDR_FAMILY_IP_V6;
             protocol_family  = NET_SOCK_PROTOCOL_FAMILY_IP_V6;
             ip_addr_len      = NET_IPv6_ADDR_SIZE;
             break;

        case NET_IP_ADDR_FAMILY_UNKNOWN:
        default:
             return (DEF_FAIL);
    }


                                                                /* ------------------- OPEN SOCKET -------------------- */
    sock = NetSock_Open(protocol_family,
                        NET_SOCK_TYPE_STREAM,
                        NET_SOCK_PROTOCOL_TCP,
                       &err);
    if (err != NET_SOCK_ERR_NONE) {
        return (DEF_FAIL);
    }


                                                                /* ------------ CONFIGURE SOCKET'S ADDRESS ------------ */
    NetApp_SetSockAddr(        &server_sock_addr,
                                sock_addr_family,
                                TCP_SERVER_PORT,
                       (void *)&server_addr,
                                ip_addr_len,
                               &err);
    switch (err) {
        case NET_APP_ERR_NONE:
            break;


        case NET_APP_ERR_FAULT:
        case NET_APP_ERR_NONE_AVAIL:
        case NET_APP_ERR_INVALID_ARG:
        default:
            NetSock_Close(sock, &err);
            return (DEF_FAIL);
    }


                                                                /* ------------------ CONNECT SOCKET ------------------ */
    NetSock_Conn(sock, &server_sock_addr, sizeof(server_sock_addr), &err);
    if (err != NET_SOCK_ERR_NONE) {
        NetSock_Close(sock, &err);
        return (DEF_FAIL);
    }


    p_buf  = (CPU_INT08U *)tx_buf;
    tx_rem =  sizeof(tx_buf);
    do {
        tx_size = NetSock_TxDataTo(                  sock,
                                   (void           *)p_buf,
                                                     tx_rem,
                                                     NET_SOCK_FLAG_NONE,
                                   (NET_SOCK_ADDR *)&server_sock_addr,
                                                     NET_SOCK_ADDR_SIZE,
                                                    &err);
        switch (err) {
            case NET_SOCK_ERR_NONE:
                 tx_rem -= tx_size;
                 p_buf   = (CPU_INT08U *)(p_buf + tx_size);
                 break;

            case NET_ERR_FAULT_LOCK_ACQUIRE:
            case NET_ERR_TX:
                 NetApp_TimeDly_ms(5, &err);
                 break;

            default:
                 NetSock_Close(sock, &err);
                 return (DEF_FAIL);
        }
    } while (tx_rem > 0);


    rx_rem = TX_BUF_SIZE;


                                                                /* ----- WAIT UNTIL RECEIVING DATA FROM A CLIENT ------ */
    rx_rem =  TX_BUF_SIZE;
    p_buf  = (CPU_INT08U *)tx_buf;
    do {
        server_sock_addr_len = sizeof(server_sock_addr);
        rx_size              = NetSock_RxDataFrom(sock,
                                          (void *)p_buf,
                                                  rx_rem,
                                                  NET_SOCK_FLAG_NONE,
                                                 &server_sock_addr,
                                                 &server_sock_addr_len,
                                                  DEF_NULL,
                                                  DEF_NULL,
                                                  DEF_NULL,
                                                 &err);
        switch (err) {
            case NET_SOCK_ERR_NONE:
                 rx_rem -=  rx_size;
                 p_buf   = (CPU_INT08U *)(p_buf + rx_size);
                 break;

            case NET_ERR_FAULT_LOCK_ACQUIRE:
            case NET_ERR_RX:
                 NetApp_TimeDly_ms(5, &err);
                 break;

            default:
                 NetSock_Close(sock, &err);
                 return (DEF_FAIL);
        }
    } while (tx_rem > 0);


                                                                /* ------------------- CLOSE SOCKET ------------------- */
    NetSock_Close(sock, &err);

    return (DEF_OK);
}
