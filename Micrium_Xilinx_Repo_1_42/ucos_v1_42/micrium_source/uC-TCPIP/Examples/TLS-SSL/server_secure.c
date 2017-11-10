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
*                                           TLS/SSL SERVER

*
* Filename      : server_secure.c
* Version       : V3.03.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : (1) This example show how to create a server using TLS/SSL
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <Source/net_sock.h>
#include  <Source/net_app.h>
#include  <Source/net_util.h>
#include  <Source/net_bsd.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*********************************************************************************************************
*/

                                        /* Certificate-Key pair can be obtained:                                        */
                                        /*      (1) Generating a self signed certificate using a tool such as OpenSSL.  */
                                        /*      (2) Purchasing an TLS/SSL certificate from a Certificates authorities.  */

#define APP_CFG_SECURE_CERT                                      \
"MIIEEjCCAvqgAwIBAgIBBzANBgkqhkiG9w0BAQUFADAaMRgwFgYDVQQDEw9WYWxp\
Y29yZS1EQzEtQ0EwHhcNMTEwMzE4MTcwMTQyWhcNMjEwMzE1MTcwMTQyWjCBkDEL\
MAkGA1UEBhMCVVMxCzAJBgNVBAgTAkNBMQ8wDQYDVQQHEwZJcnZpbmUxHjAcBgNV\
BAoTFVZhbGljb3JlIFRlY2hub2xvZ2llczEhMB8GA1UEAxMYbGFuLWZ3LTAxLnZh\
bGljb3JlLmxvY2FsMSAwHgYJKoZIhvcNAQkBFhFhZG1pbkBsb2NhbGRvbWFpbjCC\
ASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALwGOahytiwshzz1s/ngxy1+\
+VrXZYjKSEzMYbJCUhK9xA5fz8pGtOZIXI+CasZPSbXv+ZDLGpSpeFnOL49plYRs\
vmTxg2n3AlZbP6pD9OPU8rmufsTvXAmQGxxIkdmWiXYJk0pbj+U698me6DKMV/sy\
3ekQaQC2I2nr8uQw8RhuNhhlkWyjBWdXnS2mLNLSan2Jnt8rumtAi3B+vF5Vf0Fa\
kLJNt45R0f5jjuab+qw4PKMZEQbqe0XTNzkxdD0XNRBdKlajffoZPBJ7xkfuKUA3\
cMjXKzetABoKvsv+ElfvqlrI9RXvTXy52EaQmVhiOyBHrScq4RbwtDQsd59Qmk0C\
AwEAAaOB6zCB6DAJBgNVHRMEAjAAMBEGCWCGSAGG+EIBAQQEAwIGQDA0BglghkgB\
hvhCAQ0EJxYlRWFzeS1SU0EgR2VuZXJhdGVkIFNlcnZlciBDZXJ0aWZpY2F0ZTAd\
BgNVHQ4EFgQUrq5KF11M9rpKm75nAs+MaiK0niYwUQYDVR0jBEowSIAU2Q9eGjzS\
LZhvlRRKO6c4Q5ATtuChHqQcMBoxGDAWBgNVBAMTD1ZhbGljb3JlLURDMS1DQYIQ\
T9aBcT0uXoxJmC0ohp7oSTATBgNVHSUEDDAKBggrBgEFBQcDATALBgNVHQ8EBAMC\
BaAwDQYJKoZIhvcNAQEFBQADggEBAAUMm/9G+mhxVIYK4anc34FMqu88NQy8lrh0\
loNfHhIEKnerzMz+nQGidf+KBg5K5U2Jo8e9gVnrzz1gh2RtUFvDjgosGIrgYZMN\
yreNUD2I7sWtuWFQyEuewbs8h2MECs2xVktkqp5KPmJGCYGhXbi+zuqi/19cIsly\
yS01kmexwcFMXyX4YOVbG+JFHy1b4zFvWgSDULj14AuKfc8RiZNvMRMWR/Jqlpr5\
xWQRSmkjuzQMFavs7soZ+kHp9vnFtY2D6gF2cailk0sdG0uuyPBVxEJ2meifG6eb\
o3FQzdtIrB6oMFHEU00P38SJq+mrDItPDRXNLa2Nrtc1EJtmjws="


#define APP_CFG_SECURE_KEY                                       \
"MIIEogIBAAKCAQEAvAY5qHK2LCyHPPWz+eDHLX75WtdliMpITMxhskJSEr3EDl/P\
yka05khcj4Jqxk9Jte/5kMsalKl4Wc4vj2mVhGy+ZPGDafcCVls/qkP049Tyua5+\
xO9cCZAbHEiR2ZaJdgmTSluP5Tr3yZ7oMoxX+zLd6RBpALYjaevy5DDxGG42GGWR\
bKMFZ1edLaYs0tJqfYme3yu6a0CLcH68XlV/QVqQsk23jlHR/mOO5pv6rDg8oxkR\
Bup7RdM3OTF0PRc1EF0qVqN9+hk8EnvGR+4pQDdwyNcrN60AGgq+y/4SV++qWsj1\
Fe9NfLnYRpCZWGI7IEetJyrhFvC0NCx3n1CaTQIDAQABAoIBAEbbqbr7j//RwB2P\
EwZmWWmh4mMDrbYBVYHrvB2rtLZvYYVxQiOexenK92b15TtbAhJYn5qbkCbaPwrJ\
E09eoQRI3u+3vKigd/cHaFTIS2/Y/qhPRGL/OZY5Ap6EEsMHYkJjlWh+XRosQNlw\
01zJWxbFsq90ib3E5k+ypdStRQ7JQ9ntvDAP6MDp3DF2RYf22Tpr9t3Oi2mUirOl\
piOEB55wydSyIhSHusbms3sp2uvQBYJjZP7eENEQz55PebTzl9UF2dgJ0wJFS073\
rvp46fibcch1L7U6v8iUNaS47GTs3MMyO4zda73ufhYwZLU5gL8oEDY3tf/J8zuC\
mNurr0ECgYEA8i1GgstYBFSCH4bhd2mLu39UVsIvHaD38mpJE6avCNOUq3Cyz9qr\
NzewG7RyqR43HsrVqUSQKzlAGWqG7sf+jkiam3v6VW0y05yqDjs+SVW+ZN5CKyn3\
sMZV0ei4MLrfxWneQaKy/EUTJMlz3rLSDM/hpJoA/gOo9BIFRf2HPkkCgYEAxsGq\
LYU+ZEKXKehVesh8rIic4QXwzeDmpMF2wTq6GnFq2D4vWPyVGDWdORcIO2BojDWV\
EZ8e7F2SghbmeTjXGADldYXQiQyt4Wtm+oJ6d+/juKSrQ1HIPzn1qgXDNLPfjd9o\
9lX5lGlRn49Jrx/kKQAPTcnCa1IirIcsmcdiy+UCgYBEbOBwUi3zQ0Fk0QJhb/Po\
LSjSPpl7YKDN4JP3NnBcKRPngLc1HU6lElny6gA/ombmj17hLZsia1GeHMg1LVLS\
NtdgOR5ZBrqGqcwuqzSFGfHqpBXEBl6SludmoL9yHUreh3QhzWuO9aFcEoNnl9Tb\
g9z4Wf8Pxk71byYISYLt6QKBgERActjo3ZD+UPyCHQBp4m45B246ZQO9zFYdXVNj\
gE7eTatuR0IOkoBawN++6gPByoUDTWpcsvjF9S6ZAJH2E97ZR/KAfijh4r/66sTx\
k26mQRPB8FHQvqv/kj3NdsgdUJJeeqPEyEzPkcjyIoJxuB7gN2El/I5wCRon3Qf9\
sQ6FAoGAfVOaROSAtq/bq9JIL60kkhA9sr3KmX52PnOR2hW0caWi96j+2jlmPT93\
4A2LIVUo6hCsHLSCFoWWiyX9pIqyYTn5L1EmeBO0+E8BH9F/te9+ZZ53U+quwc/X\
AZ6Pseyhj7S9wkI5hZ9SO1gcK4rWrAK/UFOIzzlACr5INr723vw="


#define  APP_CFG_SECURE_CERT_LEN      (sizeof(APP_CFG_SECURE_CERT) - 1)
#define  APP_CFG_SECURE_KEY_LEN       (sizeof(APP_CFG_SECURE_KEY)  - 1)



/*
*********************************************************************************************************
*                                            AppServerInit()
*
* Description : (1) Initialize server's listen socket to accept only connection over TLS/SSL:
*
*                   (a) Open a socket.
*                   (b) Configure socket's option to be secure.
*                   (c) Bind.
*                   (d) Listen.
*
* Argument(s) : none.
*
* Return(s)   : Socket ID, if no error.
*
*               -1,        Otherwise.
*
* Caller(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT16S  AppServerInit (void)
{
    NET_SOCK_ID         sock_id;
    NET_SOCK_ADDR_IPv4  addr_server_ip;
    NET_SOCK_ADDR_LEN   addr_len;
    NET_ERR             err;


                                                                /* -------------------- OPEN SOCK --------------------- */
    sock_id = NetApp_SockOpen(NET_SOCK_ADDR_FAMILY_IP_V4,
                              NET_SOCK_TYPE_STREAM,
                              NET_SOCK_PROTOCOL_TCP,
                              3,
                              5,
                              &err);
    switch (err) {
        case NET_APP_ERR_NONE:
             break;

        default:
             return (-1);
    }


                                                                /* --------------- CFG SOCK SECURE OPT----------------- */
   (void)NetSock_CfgSecure(sock_id,                             /* First the socket option secure must be set.          */
                           DEF_YES,
                          &err);
    switch (err) {
        case NET_SOCK_ERR_NONE:
             break;

        default:
             NetApp_SockClose(sock_id, 1, &err);
             return (-1);
    }


   (void)NetSock_CfgSecureServerCertKeyInstall(sock_id,         /* Set certificate and key on the socket.               */
                                               APP_CFG_SECURE_CERT,
                                               APP_CFG_SECURE_CERT_LEN,
                                               APP_CFG_SECURE_KEY,
                                               APP_CFG_SECURE_KEY_LEN,
                                               NET_SOCK_SECURE_CERT_KEY_FMT_PEM,
                                               DEF_NO,
                                              &err);
    switch (err) {
        case NET_SOCK_ERR_NONE:
             break;

        default:
             NetApp_SockClose(sock_id, 1, &err);
             return (-1);
    }


                                                                /* -------------------- BIND SOCK --------------------- */
    addr_len = sizeof(addr_server_ip);

    Mem_Set((void *)&addr_server_ip,
                     0u,
                     addr_len);

    addr_server_ip.AddrFamily = NET_SOCK_ADDR_FAMILY_IP_V4;
    addr_server_ip.Port       = NET_UTIL_HOST_TO_NET_16(12345);
    addr_server_ip.Addr       = NET_UTIL_HOST_TO_NET_32(INADDR_ANY);

   (void)NetApp_SockBind(                  sock_id,
                         (NET_SOCK_ADDR *)&addr_server_ip,
                                           addr_len,
                                           3,
                                           5,
                                          &err);
    switch (err) {
        case NET_APP_ERR_NONE:
            break;

        default:
            NetApp_SockClose(sock_id, 1, &err);
            return (-1);
    }


                                                                /* ------------------- LISTEN SOCK -------------------- */
   (void)NetApp_SockListen(sock_id, 1, &err);
    switch(err) {
        case NET_APP_ERR_NONE:
             break;

        default:
            NetApp_SockClose(sock_id, 1, &err);
            return (-1);
    }

    /* Now all socket returned from accept() will use TLS/SSL.  */
    /* So all the data transfered on child socket is encrypted. */
    /* You just have to use any socket API such as :            */
    /*      NetApp_Accept(), NetApp_Rx(), NetApp_Tx().          */


    return (sock_id);
}
