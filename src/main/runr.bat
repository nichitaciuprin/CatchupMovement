@echo off

set appname=main

build\%appname%.exe

if %errorlevel% neq 0 echo === ERROR === %errorlevel%