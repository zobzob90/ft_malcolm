NAME		= ft_malcolm

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

INCDIR		= inc
LIBFTDIR	= libft
LIBFT		= $(LIBFTDIR)/libft.a

SRCDIR		= src
SRC			= $(SRCDIR)/main.c \
			  $(SRCDIR)/socket.c \
			  $(SRCDIR)/parsing.c \
			  $(SRCDIR)/utils.c

OBJDIR		= obj
OBJ			= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES	= -I$(INCDIR) -I$(LIBFTDIR)
LDFLAGS		= -L$(LIBFTDIR) -lft

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
