# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anakin <anakin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 21:34:42 by anakin            #+#    #+#              #
#    Updated: 2025/07/28 13:30:12 by anakin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
RM = rm -f

# Directories
SRCDIR = src
INCDIR = inc
OBJDIR = obj

# Source files
SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/parsing/parsing.c \
       $(SRCDIR)/parsing/valid_input.c \
       $(SRCDIR)/philo/create_philos.c \
       $(SRCDIR)/philo/create_threads.c \
       $(SRCDIR)/philo/join_threads.c \
       $(SRCDIR)/philo/spread_forks.c \
       $(SRCDIR)/jobs/philo_routine.c \
       $(SRCDIR)/jobs/take_fork.c \
       $(SRCDIR)/jobs/return_fork.c \
       $(SRCDIR)/jobs/eat.c \
       $(SRCDIR)/jobs/sleep.c \
       $(SRCDIR)/jobs/think.c \
       $(SRCDIR)/utils/ft_atoi.c \
       $(SRCDIR)/utils/free_philos.c \
       $(SRCDIR)/utils/monitor.c \
       $(SRCDIR)/utils/timing.c \
       $(SRCDIR)/utils/uusleep.c \
       $(SRCDIR)/utils/setup_mutex.c \
       $(SRCDIR)/utils/setup.c \
       $(SRCDIR)/utils/destruct.c

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Header files
INCLUDES = -I$(INCDIR)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re