# makes execution stop on error
set -e

libs='-lraylib -lGL -lm -lpthread -ldl -lrt -lX11'

warnings='
-pedantic -Werror -Wshadow -Wall -Wextra -Wcast-align -Wcast-qual
-Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op
-Wmissing-include-dirs -Wredundant-decls -Wstrict-overflow=5
-Wno-unused -Wno-variadic-macros -Wno-parentheses
-Wundef -fdiagnostics-show-option'

include=./src/tools

# echo $include
cc main.c -o build/main -g -I$include $libs $warnings

./build/main