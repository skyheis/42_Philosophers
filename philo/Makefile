# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiannit <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 17:49:20 by ggiannit          #+#    #+#              #
#    Updated: 2023/03/17 09:46:30 by ggiannit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####### NAME #########

NAME = philo
PRNAME = philo

BNUS = bonus

INCLUDE = include

###### VARIABLE ######

SRCS = main.c free_printph.c utils_n_checks.c init_all.c

OBJS = ${SRCS:.c=.o}

CC = cc
AR = ar
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -pthread

###### COLORS ########

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

######## EXT #########

# make a .o file using a .c file
# $< for the .c file
# $@ for the .o file

# .inextention.outextention:

#.c.o:
%.o: %.c
	@echo "$(GREEN)Compiling:$(BLUE) $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -c $< -o $@

####### RULES ########

all: ${NAME}

${NAME}: ${OBJS}
	@echo "$(YELLOW)- Program Name: $(WHITE)${PRNAME}$(DEF_COLOR)"
	@echo "$(YELLOW)- Compiler: $(WHITE)${CC}$(DEF_COLOR)"
	@echo "$(YELLOW)- Flags: $(WHITE)${CFLAGS}$(DEF_COLOR)"
	@${CC} ${CFLAGS} -o $(PRNAME) $(OBJS) $(ARINC) 

clean:
	@${RM} ${OBJS} 
	@echo "$(RED)All $(CYAN)$(PRNAME)$(RED)'s objects removed with $(WHITE)${RM}$(DEF_COLOR) 🧹" 

fclean: clean
	@${RM} ${PRNAME} 
	@echo "$(RED)..and $(CYAN)${PRNAME} $(RED)as been removed$(DEF_COLOR) 🚮"

re: fclean all

.PHONY: all clean fclean re .c.o
.SUFFIXES: .c .o 
