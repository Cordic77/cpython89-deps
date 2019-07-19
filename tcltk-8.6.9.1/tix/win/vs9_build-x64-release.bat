setlocal
if not exist "..\..\tcltk64\lib\tix8.4.3\tix84.dll" goto build
goto :eof

:build
nmake /nologo -f makefile.vc MACHINE=AMD64 DEBUG=0 NODEBUG=1 TCL_MAJOR=8 TCL_MINOR=6 TCL_PATCH=9 BUILDDIRTOP="Release_AMD64_VC9" TCL_DIR="..\..\tcl-core-8.6.9" TK_DIR="..\..\tk-8.6.9" INSTALL_DIR="..\..\tcltk64" all install
