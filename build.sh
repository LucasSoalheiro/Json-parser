clear 
mkdir -p ./out/
gcc -g ./src/main.c ./src/parser.c -o ./out/main -Wall -Werror -Wextra -pedantic
valgrind ./out/main --leak-check=full

