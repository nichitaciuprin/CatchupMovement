@echo off

set warnings=^
-pedantic -Werror -Wshadow -Wall -Wextra -Wcast-align -Wcast-qual ^
-Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op ^
-Wmissing-include-dirs -Wredundant-decls -Wstrict-overflow=5 ^
-Wno-unused -Wno-variadic-macros -Wno-parentheses ^
-Wundef -fdiagnostics-show-option

set libs=-lraylib -lpthread
set include=src\tools
set appname=test
set exefile=build/%appname%.exe

if not exist build (mkdir build)
cc %appname%.c -o %exefile% -g -I%include% %libs% %warnings%
if errorlevel 1 exit /b %errorlevel%
%exefile%