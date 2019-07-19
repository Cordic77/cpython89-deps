setlocal
if not exist "..\..\tcltk64\bin\tk86tg.dll" goto build
if not exist "..\..\tcltk64\include\tk.h" goto build
if not exist "..\..\tcltk64\lib\tk86tg.lib" goto build
if not exist "..\..\tcltk64\lib\tk8.6" goto build
goto :eof

:build
nmake /nologo -f makefile.vc RC=rc MACHINE=AMD64 OPTS=symbols,msvcrt TCLDIR="..\..\tcl-core-8.6.9" INSTALLDIR="..\..\tcltk64" DEBUGFLAGS="-wd4456 -wd4457 -wd4458 -wd4459 -wd4996" all
nmake /nologo -f makefile.vc RC=rc MACHINE=AMD64 OPTS=symbols,msvcrt TCLDIR="..\..\tcl-core-8.6.9" INSTALLDIR="..\..\tcltk64" DEBUGFLAGS="-wd4456 -wd4457 -wd4458 -wd4459 -wd4996" install-binaries install-libraries
