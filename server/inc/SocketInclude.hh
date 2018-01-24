//
// SocketInclude.hh for socketInclude in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Thu May 25 01:59:18 2017 Gaëtan Léandre
// Last update Fri May 26 01:16:26 2017 Gaëtan Léandre
//


#ifndef                         SOCKET_INCLUDE_H__
#define                         SOCKET_INCLUDE_H__

        typedef         int             SOCKET;

        #if                             defined (WIN32)

                #include                        <winsock2.h>

                typedef         int             socklen_t;

        #else

            #include                            <sys/types.h>
            #include                            <sys/socket.h>
            #include                            <netinet/in.h>
            #include                            <arpa/inet.h>
            #include                            <unistd.h>
            #include                            <strings.h>

            #define                             INVALID_SOCKET -1
            #define                             SOCKET_ERROR -1
            #define                             closesocket(s) close (s)

            typedef int SOCKET;
            typedef struct sockaddr_in SOCKADDR_IN;
            typedef struct sockaddr SOCKADDR;

        #endif

#endif
