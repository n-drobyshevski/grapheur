:: filepath: /c:/Users/nearl/projects/sdl_test/build_and_run.bat
@echo off
gcc -o syntax syntax.c 
gcc -o test test.c 
if %errorlevel% neq 0 exit /b %errorlevel%
test