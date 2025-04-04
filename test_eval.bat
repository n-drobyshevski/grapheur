@echo off
REM Compile the evaluation test
gcc tests\evaluation_test.c evaluation\evaluateur.c syntax\syntax.c lexical\lexical.c -o tests\evaluation_test.exe
if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b 1
)

REM Run the evaluation test executable
echo Running evaluation tests...
tests\evaluation_test.exe