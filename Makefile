CC=cc
FLAGS=-Wall -Wextra -Werror -g
DEPS=srcs/main.o $(patsubst %.c, %.o, $(wildcard lib/*.c))

a.out: $(DEPS)
	$(CC) $(FLAGS) $^ -o $@ -lm

%.o: %.c includes/*.h
	$(CC) $(FLAGS) -c $< -o $@ -I includes

fclean:
	find . -name "*.o" -delete
	rm a.out

