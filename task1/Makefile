NAME = task1

INC = -I ./
SRC = main.cpp threads_process.cpp workers.cpp

all:
	@g++ -o $(NAME) $(INC) $(SRC) -lpthread
	@echo "\033[32mProgram \033[1;32m$(NAME)\033[1;0m\033[32m created\033[0m"

rm:
	@/bin/rm -rf $(NAME)
	@echo "\033[31mProgram \033[1;31m$(NAME)\033[1;0m\033[31m removed\033[0m"

re: rm all

.PHONY: all, rm, re
