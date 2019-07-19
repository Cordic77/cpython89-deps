setlocal
if not exist "..\..\tcltk\bin\tk86t.dll" goto build
if not exist "..\..\tcltk\include\tk.h" goto build
if not exist "..\..\tcltk\lib\tk86t.lib" goto build
if not exist "..\..\tcltk\lib\tk8.6" goto build
goto :eof

:build
nmake /nologo -f makefile.vc RC=rc MACHINE=IX86 OPTS=msvcrt TCLDIR="..\..\tcl-core-8.6.9" INSTALLDIR="..\..\tcltk"  all
nmake /nologo -f makefile.vc RC=rc MACHINE=IX86 OPTS=msvcrt TCLDIR="..\..\tcl-core-8.6.9" INSTALLDIR="..\..\tcltk"  install-binaries install-libraries
