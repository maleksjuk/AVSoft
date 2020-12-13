NAME = task2

FLAGS = --std=c++11 -g3 #-Wall -Wextra -Werror

INC = -I ./
SRC = main.cpp employee.cpp department.cpp parser.cpp pugixml.cpp menu.cpp

all:
	@g++ $(FLAGS) -o $(NAME) $(INC) $(SRC)
	@echo "\033[32mProgram \033[1;32m$(NAME)\033[1;0m\033[32m created\033[0m"

rm:
	@/bin/rm -rf $(NAME)
	@echo "\033[31mProgram \033[1;31m$(NAME)\033[1;0m\033[31m removed\033[0m"

re: rm all

.PHONY: all, rm, re
