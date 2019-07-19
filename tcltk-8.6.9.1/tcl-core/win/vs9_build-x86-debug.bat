setlocal
if not exist "..\..\tcltk\bin\tcl86tg.dll" goto build
if not exist "..\..\tcltk\bin\tclsh86tg.exe" goto build
if not exist "..\..\tcltk\include\tcl.h" goto build
if not exist "..\..\tcltk\lib\tcl8" goto build
if not exist "..\..\tcltk\lib\tcl8.6" goto build
if not exist "..\..\tcltk\lib\tcl86tg.lib" goto build
goto :eof

:build
nmake -f makefile.vc MACHINE=IX86 OPTS=symbols,msvcrt INSTALLDIR="..\..\tcltk" INSTALL_DIR="..\..\tcltk" DEBUGFLAGS="-wd4456 -wd4457 -wd4458 -wd4459 -wd4996" core shell dlls
nmake -f makefile.vc MACHINE=IX86 OPTS=symbols,msvcrt INSTALLDIR="..\..\tcltk" INSTALL_DIR="..\..\tcltk" DEBUGFLAGS="-wd4456 -wd4457 -wd4458 -wd4459 -wd4996" install-binaries install-libraries
