# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 16:23:37 by ineimatu          #+#    #+#              #
#    Updated: 2024/06/17 12:57:32 by ineimatu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT = client
SERVER = server

SRCS = 	server.c utils.c
SRCC = 	client.c utils.c

OBJ_S = $(SRCS:.c=.o)
OBJ_C = $(SRCC:.c=.o)

DEP_S = $(SRCS:.c=.d)
DEP_C = $(SRCC:.c=.d)

CC = cc
INCLUDES = -I minitalk.h
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

all: $(CLIENT) $(SERVER)

$(SERVER): $(OBJ_S)
	$(CC) $(CFLAGS) $(OBJ_S) -o $(SERVER)

$(CLIENT): $(OBJ_C)
	$(CC) $(CFLAGS)  $(OBJ_C) -o $(CLIENT)	

-include $(DEP_S) $(DEP_C)

%.o : %.c Makefile minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_C) $(DEP_C) $(OBJ_S) $(DEP_S)

fclean: clean
	rm -rf $(CLIENT) $(SERVER) 

re: fclean all

.PHONY: all clean fclean re
