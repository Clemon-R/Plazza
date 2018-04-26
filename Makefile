##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

MAIN	=	src/main.cpp

GUI	=	src/main_ui.cpp
	
SRC	=	$(addprefix src/main/,	\
			master.cpp	\
			)

SRC_TESTS	=	$(addprefix tests/,	\
			)

OBJ	=	$(SRC:.cpp=.o)

OBJ_MAIN	=	$(MAIN:.cpp=.o)

OBJ_GUI	=	$(GUI:.cpp=.o)

OBJ_TESTS	=	$(SRC_TESTS:.cpp=.o)

CXX	=	g++

CXXFLAGS	+=	-Iinclude -std=c++14

NAME	=	plazza

NAME_TESTS	=	unit-tests

all:	$(NAME)

$(NAME):	$(OBJ) $(OBJ_MAIN)
	$(CXX) $(OBJ) $(OBJ_MAIN) -o $(NAME) $(CXXFLAGS)

ui:	$(OBJ) $(OBJ_GUI)
	$(CXX) $(OBJ) $(OBJ_GUI) -o $(NAME) $(CXXFLAGS)

$(NAME_TESTS):	tests_run

tests_run:	$(OBJ) $(OBJ_TESTS)
	$(CXX) $(OBJ) $(OBJ_TESTS) -o $(NAME_TESTS) $(CXXFLAGS) -lcriterion --coverage

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_MAIN)
	rm -f $(OBJ_GUI)
	rm -f $(OBJ_TESTS)

fclean:	clean
	rm -f $(NAME)
	rm -f $(NAME_TESTS)

re:	fclean all

.PHONY:	ui tests_run