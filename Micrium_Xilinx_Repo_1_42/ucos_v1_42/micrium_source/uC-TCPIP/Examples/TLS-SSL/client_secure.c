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
*                                           TLS/SSL CLIENT

*
* Filename      : client_secure.c
* Version       : V3.03.01
* Programmer(s) : AA
*********************************************************************************************************
* Note(s)       : (1) This example show how to connect a client to a server using TLS/SSL
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <Secure/Mocana/net_secure_mocana.h>
#include  <Source/net_sock.h>
#include  <Source/net_app.h>
#include  <Source/net_ascii.h>
#include  <Source/net_util.h>
#include  <lib_str.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*********************************************************************************************************
*/

                                                            /* CA certificate:                                          */
                                                            /*      (1) Can be obtained on CA website.                  */
                                                            /*      (2) Can be generated using a tool such as OpenSSL.  */
CPU_CHAR *p_cert =
                "MIIDVDCCAjygAwIBAgIDAjRWMA0GCSqGSIb3DQEBBQUAMEIxCzAJBgNVBAYTAlVT"
                "MRYwFAYDVQQKEw1HZW9UcnVzdCBJbmMuMRswGQYDVQQDExJHZW9UcnVzdCBHbG9i"
                "YWwgQ0EwHhcNMDIwNTIxMDQwMDAwWhcNMjIwNTIxMDQwMDAwWjBCMQswCQYDVQQG"
                "EwJVUzEWMBQGA1UEChMNR2VvVHJ1c3QgSW5jLjEbMBkGA1UEAxMSR2VvVHJ1c3Qg"
                "R2xvYmFsIENBMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2swYYzD9"
                "9BcjGlZ+W988bDjkcbd4kdS8odhM+KhDtgPpTSEHCIjaWC9mOSm9BXiLnTjoBbdq"
                "fnGk5sRgprDvgOSJKA+eJdbtg/OtppHHmMlCGDUUna2YRpIuT8rxh0PBFpVXLVDv"
                "iS2Aelet8u5fa9IAjbkU+BQVNdnARqN7csiRv8lVK83Qlz6cJmTM386DGXHKTubU"
                "1XupGc1V3sjs0l44U+VcT4wt/lAjNvxm5suOpDkZALeVAjmRCw7+OC7RHQWa9k0+"
                "bw8HHa8sHo9gOeL6NlMTOdReJivbPagUvTLrGAMoUgRx5aszPeE4uwc2hGKceeoW"
                "MPRfwCvocWvk+QIDAQABo1MwUTAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBTA"
                "ephojYn7qwVkDBF9qn1luMrMTjAfBgNVHSMEGDAWgBTAephojYn7qwVkDBF9qn1l"
                "uMrMTjANBgkqhkiG9w0BAQUFAAOCAQEANeMpauUvXVSOKVCUn5kaFOSPeCpilKIn"
                "Z57QzxpeR+nBsqTP3UEaBU6bS+5Kb1VSsyShNwrrZHYqLizz/Tt1kL/6cdjHPTfS"
                "tQWVYrmm3ok9Nns4d0iXrKYgjy6myQzCsplFAMfOEVEiIuCl6rYVSAlk6l5PdPcF"
                "PseKUgzbFbS9bZvlxrFUaKnjaZC2mqUPuLk/IH2uSrW4nOQdtqvmlKXBx4Ot2/Un"
                "hw4EbNX/3aBd7YdStysVAq45pmp06drE57xNNB6pXE0zX5IJL4hmXXeXxx12E6nV"
                "5fEWCRE11azbJHFwLJhWC9kXtNHjUStedejV0NxPNO3CBWaAocvmMw==";


/*
*********************************************************************************************************
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

CPU_BOOLEAN  AppClientCertTrustCallBackFnct (void                             *p_cert_dn,
                                             NET_SOCK_SECURE_UNTRUSTED_REASON  reason);



/*
*********************************************************************************************************
*                                          AppClientConnect()
*
* Description : (1) Initialize a client secure socket:
*
*                   (a) Install CA certificate.
*                   (b) Open a TCP socket.
*                   (c) Configure socket's option to be secure.
*                   (d) Connect the socket, establish a secure connection with the server.
*
* Argument(s) : none.
*
* Return(s)   : Socket ID, if successfully connected.
*
*               -1,        Otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT16S  AppClientConnect (void)
{
    NET_SOCK_ID         sock_id;
    NET_SOCK_ADDR_IPv4  addr_server;
    CPU_INT32U          len_addr_server;
    CPU_INT32U          len;
    NET_ERR             err;

                                                                /* -------------- INSTALL CA CERTIFICATE -------------- */
    len = Str_Len(p_cert);
    NetSecure_CA_CertIntall(p_cert, len, NET_SOCK_SECURE_CERT_KEY_FMT_PEM, &err);


                                                                /* ------------------ OPEN THE SOCKET ----------------- */
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

                                                                /* ------------ CONFIGURE SOCKET AS SECURE ------------ */
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


   (void)NetSock_CfgSecureClientCommonName(sock_id,             /* Configure the common name of the server ...          */
                                          "domain_name.com",    /* certificate, most of the time it is the Domain name. */
                                          &err);
    switch (err) {
        case NET_SOCK_ERR_NONE:
             break;

        default:
             NetApp_SockClose(sock_id, 1, &err);
             return (-1);
    }

                                                                /* Configure the callback function to call if the ...   */
                                                                /* ... server certificate is not trusted. So the  ...   */
                                                                /* ... connection can be allow even if the        ...   */
                                                                /* ... certificate is not trusted.                      */
   (void)NetSock_CfgSecureClientTrustCallBack(sock_id,
                                             &AppClientCertTrustCallBackFnct,
                                             &err);
    switch (err) {
        case NET_SOCK_ERR_NONE:
             break;

        default:
             NetApp_SockClose(sock_id, 1, &err);
             return (-1);
    }


                                                                /* ------------- ESTABLISH TCP CONNECTION ------------- */
    Mem_Clr((void *)&addr_server, NET_SOCK_ADDR_SIZE);


    addr_server.AddrFamily = NetASCII_Str_to_IP((CPU_CHAR  *)"98.139.211.125",
                                                (void      *)addr_server.Addr,
                                                (CPU_INT08U )sizeof(addr_server.Addr),
                                                            &err);
    addr_server.Port       = NET_UTIL_HOST_TO_NET_16(12345);
    len_addr_server        = sizeof(addr_server);

    (void)NetApp_SockConn(                  sock_id,            /* Connect to server using TLS/SSL.                     */
                          (NET_SOCK_ADDR *)&addr_server,
                                            len_addr_server,
                                            3,
                                            5,
                                            5,
                                           &err);
    switch (err) {
        case NET_SOCK_ERR_NONE:
             break;

        default:
             NetApp_SockClose(sock_id, 1, &err);
             return (-1);
    }

    /* Now all the data transfered on this socket is encrypted.                 */
    /* You just have to use any socket API such as NetApp_Rx() or NetApp_Tx().  */

    return (sock_id);
}



/*
*********************************************************************************************************
*                                   AppClientCertTrustCallBackFnct()
*
* Description : Function called when the server's certificate is not trusted.
*
* Argument(s) : p_cert_dn   Pointer to certificate distinguish name.
*
*               reason      Reason why the certificate is not trusted:
*
*                               NET_SOCK_SECURE_UNTRUSTED_BY_CA
*                               NET_SOCK_SECURE_EXPIRE_DATE
*                               NET_SOCK_SECURE_INVALID_DATE
*                               NET_SOCK_SECURE_SELF_SIGNED
*                               NET_SOCK_SECURE_UNKNOWN
*
*
* Return(s)   : DEF_OK,   The connection can be established even if the certificated is not trusted.
*
*               DEF_FAIL, Connection refused.
*
* Caller(s)   : Secure Layer when establishing a connection.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  AppClientCertTrustCallBackFnct (void                             *p_cert_dn,
                                             NET_SOCK_SECURE_UNTRUSTED_REASON  reason)
{
    return (DEF_OK);
}



