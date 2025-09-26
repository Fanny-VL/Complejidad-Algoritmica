@echo off
echo ========================================
echo   COMPILACION DE ALGORITMOS EN C
echo   Practica: Complejidad Algoritmica
echo ========================================
echo.

REM Crear directorio de resultados si no existe
if not exist resultados mkdir resultados

echo Compilando archivos de medicion...
gcc -Wall -Wextra -std=c99 -O2 -c src/medicion.c -o src/medicion.o
if errorlevel 1 (
    echo Error al compilar medicion.c
    pause
    exit /b 1
)

echo.
echo Compilando busqueda lineal...
gcc -Wall -Wextra -std=c99 -O2 -o busqueda_lineal.exe busqueda_lineal/busqueda_lineal.c src/medicion.o
if errorlevel 1 (
    echo Error al compilar busqueda_lineal
    pause
    exit /b 1
)

echo Compilando busqueda binaria...
gcc -Wall -Wextra -std=c99 -O2 -o busqueda_binaria.exe busqueda_binaria/busqueda_binaria.c src/medicion.o
if errorlevel 1 (
    echo Error al compilar busqueda_binaria
    pause
    exit /b 1
)

echo Compilando bubble sort...
gcc -Wall -Wextra -std=c99 -O2 -o bubble_sort.exe bubble_sort/bubble_sort.c src/medicion.o
if errorlevel 1 (
    echo Error al compilar bubble_sort
    pause
    exit /b 1
)

echo Compilando merge sort...
gcc -Wall -Wextra -std=c99 -O2 -o merge_sort.exe merge_sort/merge_sort.c src/medicion.o
if errorlevel 1 (
    echo Error al compilar merge_sort
    pause
    exit /b 1
)

echo Compilando fibonacci...
gcc -Wall -Wextra -std=c99 -O2 -o fibonacci.exe fibonacci/fibonacci.c src/medicion.o
if errorlevel 1 (
    echo Error al compilar fibonacci
    pause
    exit /b 1
)

echo Compilando programa principal...
gcc -Wall -Wextra -std=c99 -O2 -o main.exe main.c src/medicion.o
if errorlevel 1 (
    echo Error al compilar main
    pause
    exit /b 1
)

echo.
echo ========================================
echo   COMPILACION COMPLETADA EXITOSAMENTE
echo ========================================
echo.
echo Archivos ejecutables creados:
echo - busqueda_lineal.exe
echo - busqueda_binaria.exe
echo - bubble_sort.exe
echo - merge_sort.exe
echo - fibonacci.exe
echo - main.exe
echo.
echo Para ejecutar todas las pruebas:
echo   main.exe
echo.
echo Para ejecutar pruebas individuales:
echo   busqueda_lineal.exe
echo   busqueda_binaria.exe
echo   bubble_sort.exe
echo   merge_sort.exe
echo   fibonacci.exe
echo.
pause
