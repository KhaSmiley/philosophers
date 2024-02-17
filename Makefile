# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kboulkri <kboulkri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 14:56:20 by kboulkri          #+#    #+#              #
#    Updated: 2024/02/17 16:50:06 by kboulkri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

DIR_SRCS		=	srcs

DIR_OBJS		=	.objs

SRCS_NAMES		=	monitoring.c philosophers.c utils.c philo_moves.c utils_thread.c

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

CC				=	cc

CDFLAGS 		= 	-MMD -MP

CFLAGS			=	-g3 -Wall -Werror -Wextra -pthread #-fsanitize=thread

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS) 
	$(CC)  ${INC} $(CFLAGS) $(CDFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[31;7mphilosophers\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC)  $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	rm -rf ${DIR_OBJS}

fclean:	clean
	rm -rf ${NAME}

re:	fclean all