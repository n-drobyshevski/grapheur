
@echo off
gcc -o syntax syntax.c 
if %errorlevel% neq 0 exit /b %errorlevel%
syntax