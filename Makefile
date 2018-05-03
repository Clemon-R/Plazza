##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

MAIN	=	src/main.cpp	\
		src/main/process/master/master_none.cpp	\
		src/launcher.cpp

SRC_GRAPHIC	=	$(addprefix src/main/graphic/,	\
			sfml.cpp)

GUI	=	src/main.cpp	\
		src/main/process/master/master_ui.cpp	\
		src/launcher_ui.cpp	\
		$(SRC_GRAPHIC)

SRC_UTILS	=	$(addprefix src/utils/,	\
			commands/command.cpp	\
			commands/parser.cpp	\
			utils.cpp	\
			)

SRC	=	$(addprefix src/main/,	\
			process/master/master.cpp	\
			process/slave/slave.cpp		\
			network/server/server.cpp	\
			network/client/client.cpp	\
			)

SRC_TESTS	=	$(addprefix tests/,	\
			ut_master.cpp	\
			)

OBJ	=	$(SRC:.cpp=.o)	\
		$(SRC_UTILS:.cpp=.o)

OBJ_MAIN	=	$(MAIN:.cpp=.o)

OBJ_GUI	=	$(GUI:.cpp=.o)

OBJ_TESTS	=	$(SRC_TESTS:.cpp=.o)

CXX	=	g++

CXXFLAGS	+=	-Iinclude -lpthread -std=c++14 -g3

FLAGSGRAPHIC	=	-lsfml-window -lsfml-system -lsfml-graphics

NAME	=	plazza

NAME_TESTS	=	unit-tests

all:	$(NAME)

$(NAME):	$(OBJ) $(OBJ_MAIN)
	$(CXX) $(OBJ) $(OBJ_MAIN) -o $(NAME) $(CXXFLAGS)

ui:	$(OBJ) $(OBJ_GUI)
	$(CXX) $(OBJ) $(OBJ_GUI) -o $(NAME) $(CXXFLAGS) $(FLAGSGRAPHIC)

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