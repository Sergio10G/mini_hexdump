# VARS	--------------------------------------------------------------

NAME		:=	hexdump

SRC_DIR		:=	src

INC_DIR		:=	inc

OBJ_DIR		:=	obj

SRCS		:=	$(shell find $(SRC_DIR) -type f -name *.c)

OBJS		:=	$(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,${SRCS:.c=.o})

INC			:=	-I$(INC_DIR)

CC			:=	gcc

CFLAGS		:=	-Wall -Werror -Wextra

RM			:=	rm -f

GREEN		:=	\033[1;32m
PINK		:=	\033[1;35m
BLUE		:=	\033[1;36m
RESET		:=	\033[1;0m

MAKEFLAGS	+=	--silent

vpath	%.c	$(SRC_DIR)

# RULES	--------------------------------------------------------------

all				:	$(NAME)

$(OBJ_DIR)/%.o	:	%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME)			:	$(OBJS)
					@echo "$(BLUE)Compiling hexdump...$(RESET)"
					$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
					@echo "$(GREEN)Hexdump succesfully compiled!$(RESET)"

clean			:	
					$(RM) $(OBJS)
					@echo "$(PINK)Object files removed!$(RESET)"

fclean			:	clean
					$(RM) $(NAME)
					@echo "$(BLUE)Hexdump removed!$(RESET)"

re				:	fclean all

.PHONY			:	all clean fclean re
