setlocal
if not exist "..\..\tcltk\bin\tcl86t.dll" goto build
if not exist "..\..\tcltk\bin\tclsh86t.exe" goto build
if not exist "..\..\tcltk\include\tcl.h" goto build
if not exist "..\..\tcltk\lib\tcl8" goto build
if not exist "..\..\tcltk\lib\tcl8.6" goto build
if not exist "..\..\tcltk\lib\tcl86t.lib" goto build
goto :eof

:build
nmake -f makefile.vc MACHINE=IX86 OPTS=msvcrt INSTALLDIR="..\..\tcltk" INSTALL_DIR="..\..\tcltk"  core shell dlls
nmake -f makefile.vc MACHINE=IX86 OPTS=msvcrt INSTALLDIR="..\..\tcltk" INSTALL_DIR="..\..\tcltk"  install-binaries install-libraries
