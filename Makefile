##############################  SOURCE & OBJETS  ###############################

SRCS = src/test.cpp

INCLUDE = container/stack.hpp \
		  container/vector.hpp \
		  container/iterator.hpp

OBJS = $(SRCS:.cpp=.o)

################################  VARIABLES  ###################################

NAME = containe

RM = rm -f

CC = c++

GCCF = $(CC) -Wall -Wextra -Werror -std=c++98 -I includes/

##################################  RULES  #####################################

all :	$(NAME)

$(NAME):	$(INCLUDE) $(OBJS) 
			$(GCCF) $(OBJS) -o $(NAME)

%.o:	%.cpp $(INCLUDE) 
	${GCCF} -c $< -o $@ 

############################  CLEAN & RE & phony  ##############################

clean:
	${RM} ${OBJS} 

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

#################################### FIN  ######################################
