@echo off
REM Check for the existence of the executable and run it if available
echo Running Grapheur application...
if exist "grapheur.exe" (
    start "" grapheur.exe
) else (
    echo Error: grapheur.exe not found.
)