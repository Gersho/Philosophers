SRCS		= args.c debug_philo.c main.c parse_tools.c time.c philo_tools.c


OBJS			= $(SRCS:.c=.o)

NAME			= philo_bonus
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

all:			$(NAME)

%.o: 			%.c	philo.h
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		philo_

philo_:			$(OBJS) philo.h
				$(CC) $(CFLAGS) -Iphilo.h -o philo_bonus $(OBJS)

clean:			
				$(RM) $(OBJS)

fclean:			clean
				$(RM) philo_bonus

re:			fclean all

.PHONY:		re fclean clean all philo_