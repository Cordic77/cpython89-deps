setlocal
if not exist "..\..\tcltk64\bin\tcl86t.dll" goto build
if not exist "..\..\tcltk64\bin\tclsh86t.exe" goto build
if not exist "..\..\tcltk64\include\tcl.h" goto build
if not exist "..\..\tcltk64\lib\tcl8" goto build
if not exist "..\..\tcltk64\lib\tcl8.6" goto build
if not exist "..\..\tcltk64\lib\tcl86t.lib" goto build
goto :eof

:build
nmake -f makefile.vc MACHINE=AMD64 OPTS=msvcrt INSTALLDIR="..\..\tcltk64" INSTALL_DIR="..\..\tcltk64"  core shell dlls
nmake -f makefile.vc MACHINE=AMD64 OPTS=msvcrt INSTALLDIR="..\..\tcltk64" INSTALL_DIR="..\..\tcltk64"  install-binaries install-libraries
