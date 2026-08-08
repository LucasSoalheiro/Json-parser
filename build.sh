clear 
mkdir -p ./out/
gcc -g ./src/main.c ./src/parser/parser.c ./src/lexer/lexer.c -o ./out/main -Wall -Werror -Wextra -pedantic
valgrind ./out/main --leak-check=full

