/*
** main.c for main in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/src/
**
** Made by Gaëtan Léandre
** Login   <gaetan.leandre@epitech.eu>
**
** Started on  Wed May 24 12:31:16 2017 Gaëtan Léandre
** Last update	Wed Jun 07 00:00:11 2017 Gaëtan Léandre
*/

#include <ServerSocket.hh>

int             main()
{
    ServerSocket    server;

    if (server.init())
        server.launchLoop();
    return (0);
}
