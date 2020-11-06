# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nvan-win <nvan-win@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/18 22:46:35 by nvan-win      #+#    #+#                  #
#    Updated: 2020/09/18 14:17:44 by nvan-win      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
HEADER_FILE = libft.h
REG_OBJ_FILES =		ft_memset.o \
					ft_bzero.o \
					ft_memcpy.o \
					ft_memccpy.o \
					ft_memmove.o \
					ft_memchr.o \
					ft_memcmp.o \
					ft_strlen.o \
					ft_strlcpy.o \
					ft_strlcat.o \
					ft_strchr.o \
					ft_strrchr.o \
					ft_strnstr.o \
					ft_strncmp.o \
					ft_atoi.o \
					ft_isalpha.o \
					ft_isdigit.o \
					ft_isalnum.o \
					ft_isascii.o \
					ft_isprint.o \
					ft_toupper.o \
					ft_tolower.o \
					ft_calloc.o \
					ft_strdup.o \
					ft_substr.o \
					ft_strjoin.o \
					ft_strtrim.o \
					ft_split.o \
					ft_itoa.o \
					ft_strmapi.o \
					ft_putchar_fd.o \
					ft_putstr_fd.o \
					ft_putendl_fd.o \
					ft_putnbr_fd.o \
					get_next_line.o
BONUS_OBJ_FILES =	ft_lstnew.o \
					ft_lstadd_front.o \
					ft_lstsize.o \
					ft_lstlast.o \
					ft_lstadd_back.o \
					ft_lstdelone.o \
					ft_lstclear.o \
					ft_lstiter.o \
					ft_lstmap.o

ifdef WITH_BONUS
OBJ_FILES = $(REG_OBJ_FILES) $(BONUS_OBJ_FILES)
else
OBJ_FILES = $(REG_OBJ_FILES)
endif

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $(NAME) $^
	ranlib $(NAME)

%.o: %.c $(HEADER_FILE)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(REG_OBJ_FILES) $(BONUS_OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	$(MAKE) WITH_BONUS=1 all

.PHONY: all clean fclean re
