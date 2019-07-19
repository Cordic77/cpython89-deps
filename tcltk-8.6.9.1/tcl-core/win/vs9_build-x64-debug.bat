setlocal
if not exist "..\..\tcltk64\bin\tcl86tg.dll" goto build
if not exist "..\..\tcltk64\bin\tclsh86tg.exe" goto build
if not exist "..\..\tcltk64\include\tcl.h" goto build
if not exist "..\..\tcltk64\lib\tcl8" goto build
if not exist "..\..\tcltk64\lib\tcl8.6" goto build
if not exist "..\..\tcltk64\lib\tcl86tg.lib" goto build
goto :eof

:build
nmake -f makefile.vc MACHINE=AMD64 OPTS=symbols,msvcrt INSTALLDIR="..\..\tcltk64" INSTALL_DIR="..\..\tcltk64" DEBUGFLAGS="-wd4456 -wd4457 -wd4458 -wd4459 -wd4996" core shell dlls
nmake -f makefile.vc MACHINE=AMD64 OPTS=symbols,msvcrt INSTALLDIR="..\..\tcltk64" INSTALL_DIR="..\..\tcltk64" DEBUGFLAGS="-wd4456 -wd4457 -wd4458 -wd4459 -wd4996" install-binaries install-libraries
