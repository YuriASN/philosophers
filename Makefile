NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -g #-fsanitize=thread
SRC = end_philo.c init.c main.c run_threads.c utils.c

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -g $(SRC) -o $(NAME)
	@echo "\033[95mPhilosophers compiled!\033[m"

clean:
	@/bin/rm -f *.o
	@echo "\033[93mClean done!\033[m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[93mfclean done!\033[m"

re: fclean all
