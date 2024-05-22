SRC = \
	main.c \
	utils/philo_init.c \
	utils/ft_atoi.c \
	utils/ft_strdup.c \
	utils/ft_isdigit.c \
	utils/get_time.c \
	utils/routines.c \
	parsing/parse.c

OBJ = $(SRC:.c=.o)

NAME = philo

CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJ)
	@cc $(CFLAGS) -fsanitize=thread -g $(OBJ) -o $(NAME) > /dev/null

fclean : clean
		@echo full cleaning of $(NAME) ...
		@$(RM) -f $(NAME)
		@sleep 0.5
		@echo $(NAME) cleaned.

clean :
		@echo cleaning $(NAME) ...
		@$(RM) -f $(OBJ)
		@sleep 0.5
		@echo $(NAME) cleaned.

re : fclean all