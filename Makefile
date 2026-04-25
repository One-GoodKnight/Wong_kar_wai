NAME			:= 2048
BUILD_DIR		:= .build
SRC_DIR			:= src
INCLUDE_DIR		:= include

SRCS			:= 								\
	main.c										\
	game.c										\
	display.c									\
	menu.c										\
	str_utils.c									\
	movements.c									\
	random.c									\
	utils.c										\

SRCS			:= $(SRCS:%=$(SRC_DIR)/%)
OBJS			:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS			:= $(OBJS:.o=.d)

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
CPPFLAGS		:= -I $(INCLUDE_DIR) -MMD -MP
LDFLAGS 		= -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

run: all
	@./$(NAME)

.PHONY: all clean fclean re run
