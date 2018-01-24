##
## Makefile for server in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/
##
## Made by Gaëtan Léandre
## Login   <gaetan.leandre@epitech.eu>
##
## Started on  Wed May 24 12:26:31 2017 Gaëtan Léandre
## Last update Fri May 26 03:59:49 2017 Gaëtan Léandre
##

NAME			=		server

SRC				=		src/main.cpp			\
						src/Message.cpp			\
						src/Socket.cpp			\
						src/ClientSocket.cpp	\
						src/ServerSocket.cpp	\
						src/Client.cpp			\
						src/Group.cpp			\
						src/Server.cpp			\
						src/Race.cpp			\
						src/GameManager.cpp

OBJ				=		$(SRC:.cpp=.o)

CPPFLAGS		=		-Iinc -std=c++11

all				:		$(NAME)

$(NAME)			:		$(OBJ)
						g++ $(OBJ) -o $(NAME)

clean			:
						rm -f $(OBJ)

fclean			:		clean
						rm -f $(NAME)

re				:		fclean all
