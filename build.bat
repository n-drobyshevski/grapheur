@echo off
echo Building Project...
gcc main.c syntax/syntax.c lexical/lexical.c evaluation/evaluateur.c graphics/gestionGraphique.c -o grapheur.exe -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf 
if errorlevel 1 (
    echo Build failed.
    pause
    exit /b 1
)
echo Build succeeded: grapheur.exe
