# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sbos <sbos@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/20 12:12:37 by sbos          #+#    #+#                  #
#    Updated: 2022/06/20 14:09:26 by sbos          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

################################################################################

NAME := libget_next_line.a

CC := cc

OBJ_DIR := obj

CFLAGS := -Wall -Wextra -Werror
CFLAGS += #-O3 # -O1 adds tail recursion detection, which I need, so we might as well turn the optimizing up to 11 with -O3

HEADERS :=
SOURCES := get_next_line.c get_next_line_utils.c

################################################################################

# ifdef STDIN
# SOURCES += stdin.c
# else
# LIBS := -L$(HOME)/.brew/Cellar/criterion/2.3.3/lib -lcriterion
# endif

################################################################################

FCLEANED_FILES := $(NAME)

# ifdef DEBUG
HEADERS +=\
	$(addprefix $(HOME)/Documents/Programming/libctester/, $(shell $(MAKE) -C $(HOME)/Documents/Programming/libctester/ -f headers.mk get_headers))

CFLAGS += -g3 -Wconversion -I$(HOME)/.brew/Cellar/criterion/2.3.3/include
CFLAGS += -fsanitize=address
FCLEANED_FILES +=
# endif

################################################################################

ifdef CUSTOM_MAIN
SOURCES +=
CFLAGS += -DCUSTOM_MAIN=1
endif

################################################################################

OBJECT_PATHS := $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

################################################################################

# Only cleans when MAKE_DATA changes.
DATA_FILE := .make_data
MAKE_DATA := $(CFLAGS) $(SOURCES)
PRE_RULES :=

ifneq ($(shell echo "$(MAKE_DATA)"), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES += clean
endif

################################################################################

.PHONY: all
all: $(PRE_RULES) $(NAME)

$(NAME): $(OBJECT_PATHS)
	ar rs $(NAME) $(OBJECT_PATHS)
	@echo "$(MAKE_DATA)" > $(DATA_FILE)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

################################################################################

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/

.PHONY: fclean
fclean: clean
	rm -f $(FCLEANED_FILES)

.PHONY: re
re: fclean all

################################################################################
