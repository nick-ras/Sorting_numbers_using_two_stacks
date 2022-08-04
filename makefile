NAME = push_swap
CC = gcc
# := will expand one time
# = expanded whenever used, and is recursived so gcc can also be a variable that refer to even another variable

# LIBFT_PATH	= ./libft
# LIBFT_A	= $(LIBFT_PATH)/libft.a

LIBFTPRINTF_PATH	= ./printf
LIBFTPRINTF_A	= $(LIBFTPRINTF_PATH)/libftprintf.a
#libft.a is copied LIBFTinto this archive

SRC_DIR = ./src/
OBJ_DIR = ./obj/

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -rf

SRC_FILES	= main.c push_back.c make_lists.c \
			lis_and_sort.c find_exit.c \
			commands_1.c commands_2.c \
			libft_changed.c

OBJ_FILES	= ${SRC_FILES:.c=.o}
SRC			= $(addprefix $(SRC_DIR),$(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR),$(OBJ_FILES))
#prefix adds will result in ./src/main.c (and same for all other files in src)

$(NAME): $(OBJ) $(LIBFTPRINTF_A)
	echo "make started"
	$(CC) -o $(NAME) $^
	echo "code has been compiled!"
#targets : prerequisites
#	      recipe
## i gcc OBJ_FILES because it has all files in right
# linking, you can give it the path -L or -lft if starting with ft, or just add archive in gcc
#i could make  $(LIBFTPRINTF_A) but would have to actively compile it for it to cound be a rule(doing smth)

all: $(NAME)

#$(LIBFTPRINTF_A):
#	make -C $(PRINTF_PATH) all
#	make -C $LIBFT(LIBFT)_PATH) all
# -C goes into directory

clean:
# make -C $(LIBFT_PATH) clean
# make -C $(PRINTF_PATH) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
# $(RM) $(LIBFT_A)
# $(RM) $(LIBFTPRINTF_A)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $^
#-p will print rules and variable values
#^ is all prereq and < is first prereq
# if several prerequities, the first depends on date on the second, and if the first is older, the recipe below will be executed. The default value for .LIBPATTERNS is ‘lib%.so lib%.a’
#$@ - The file name of the target. which will be directory + x.o

re: fclean all

.PHONY:		all clean fclean re
#Because the rm command does not create a file named clean, probably no such file will ever exist. Therefore, the rm command will be executed every time you say ‘make clean’.