@echo off

rem Compile the test
gcc tests\syntax_test.c syntax\syntax.c lexical\lexical.c -o tests\syntax_test.exe
if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b 1
)

rem Run the test executable
echo Running tests...
tests\syntax_test.exe
