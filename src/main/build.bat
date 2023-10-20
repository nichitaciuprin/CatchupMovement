@echo off

@REM set libs1=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
@REM set libs=-lraylib -lpthread -lGL -lm -ldl -lrt
set libs=-lraylib -lpthread

set warnings=^
-pedantic -Werror -Wshadow -Wall -Wextra -Wcast-align -Wcast-qual ^
-Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op ^
-Wmissing-include-dirs -Wredundant-decls -Wstrict-overflow=5 ^
-Wno-unused -Wno-variadic-macros -Wno-parentheses ^
-Wundef -fdiagnostics-show-option

set optimisationlevel=-O3

set include=src

set appname=main

if not exist build (mkdir build)
cc %appname%.c -o build/%appname%.exe -g -I%include% %libs% %warnings% %optimisationlevel%
if errorlevel 1 exit /b %errorlevel%
build\%appname%.exe