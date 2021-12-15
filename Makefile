NAME := get_next_line

CC := cc

OBJ_DIR := obj

CFLAGS := -Wall -Wextra -Werror
CFLAGS += #-O3 # -O1 adds tail recursion detection, which I need, so we might as well turn the optimizing up to 11 with -O3

HEADERS :=
SOURCES := get_next_line.c get_next_line_utils.c
BONUS_SOURCES := get_next_line_bonus.c get_next_line_utils_bonus.c

ifdef STDIN
SOURCES += stdin.c
BONUS_SOURCES += stdin.c
else
LIBS := -L$(HOME)/.brew/Cellar/criterion/2.3.3/lib -lcriterion
SOURCES += test.c
BONUS_SOURCES += test.c
endif

ifdef ADD_BONUS
SOURCES := $(BONUS_SOURCES)
endif

FCLEANED_FILES := $(NAME)


# ifdef DEBUG
HEADERS +=
CFLAGS += -g3 -Wconversion -I$(HOME)/.brew/Cellar/criterion/2.3.3/include
CFLAGS += -fsanitize=address
FCLEANED_FILES +=
# endif

ifdef CUSTOM_MAIN
LIBS +=
SOURCES +=
CFLAGS += -DCUSTOM_MAIN=1
endif

OBJECT_PATHS := $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

# Only cleans when MAKE_DATA changes.
DATA_FILE := .make_data
MAKE_DATA := $(CFLAGS) $(SOURCES)
PRE_RULES :=
ifneq ($(shell echo "$(MAKE_DATA)"), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES += clean
endif


all: $(PRE_RULES) $(NAME)

$(NAME): $(OBJECT_PATHS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJECT_PATHS) -o $(NAME)
	@echo "$(MAKE_DATA)" > $(DATA_FILE)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/

fclean: clean
	rm -f $(FCLEANED_FILES)

re: fclean all

bonus:
	@$(MAKE) ADD_BONUS=1 all

.PHONY: all clean fclean re bonus
