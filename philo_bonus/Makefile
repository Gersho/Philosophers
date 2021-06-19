SRCS		= mutex.c philo_obj.c philo_tools.c args.c main.c parse_tools.c time.c


OBJS			= $(SRCS:.c=.o)

NAME			= philo
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

all:			$(NAME)

%.o: 			%.c	philo.h
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		philo_

philo_:			$(OBJS) philo.h
				$(CC) $(CFLAGS) -Iphilo.h -o philo $(OBJS)

clean:			
				$(RM) $(OBJS)

fclean:			clean
				$(RM) philo

re:			fclean all

.PHONY:		re fclean clean all philo_