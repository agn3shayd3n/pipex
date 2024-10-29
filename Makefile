# *************************************************************************** # 
#                                                                             #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: agnesgar <agnesgar@student.42madrid.com>   #+#  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2024-10-20 16:56:07 by agnesgar          #+#    #+#             #
#    Updated: 2024-10-20 16:56:07 by agnesgar         ###   ########.fr       #
#                                                                             #
#  ************************************************************************** #

SRCS = pipex.c pipex_utils.c
OBJS = ${SRCS:.c=.o}
NAME = pipex
LIBFT_PATH = ./libft/
LIBFT = ${LIBFT_PATH}libft.a
RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all:		${NAME}

${NAME}:	${OBJS} ${LIBFT}
			@${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}
			@echo "${GREEN}PIPEX COMPILED.${RESET}"

${LIBFT}:	
			@make -C ${LIBFT_PATH} --silent
			@echo "${GREEN}LIBFT COMPILED.${RESET}"

clean:
	@${RM} ${OBJS}
	@make clean -C ${LIBFT_PATH}
	@echo "${YELLOW}ClEANED OBJECT FILES.${RESET}"

fclean:	clean
	@${RM} ${NAME}
	@make fclean -C ${LIBFT_PATH}
	@echo "${YELLOW}CLEANED EXECUTABLE & LIB.${RESET}"

re:		fclean all

.PHONY: all clean fclean re