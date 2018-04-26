##
## EPITECH PROJECT, 2018
## plazza
## File description:
## Makefile
##

SRC	=	$(addprefix src/,	\
		main.cpp	\
		)

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS	+=	-Iinclude -std=c++14

NAME	=	plazza

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all