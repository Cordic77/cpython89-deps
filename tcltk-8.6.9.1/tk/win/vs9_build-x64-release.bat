setlocal
if not exist "..\..\tcltk64\bin\tk86t.dll" goto build
if not exist "..\..\tcltk64\include\tk.h" goto build
if not exist "..\..\tcltk64\lib\tk86t.lib" goto build
if not exist "..\..\tcltk64\lib\tk8.6" goto build
goto :eof

:build
nmake /nologo -f makefile.vc RC=rc MACHINE=AMD64 OPTS=msvcrt TCLDIR="..\..\tcl-core-8.6.9" INSTALLDIR="..\..\tcltk64"  all
nmake /nologo -f makefile.vc RC=rc MACHINE=AMD64 OPTS=msvcrt TCLDIR="..\..\tcl-core-8.6.9" INSTALLDIR="..\..\tcltk64"  install-binaries install-libraries
