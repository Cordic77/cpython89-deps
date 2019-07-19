setlocal
if not exist "..\..\tcltk64\lib\tix8.4.3\tix84g.dll" goto build
goto :eof

:build
nmake /nologo -f makefile.vc MACHINE=AMD64 DEBUG=1 NODEBUG=0 TCL_DBGX=g TK_DBGX=g TCL_MAJOR=8 TCL_MINOR=6 TCL_PATCH=9 BUILDDIRTOP="Debug_AMD64_VC9" TCL_DIR="..\..\tcl-core-8.6.9" TK_DIR="..\..\tk-8.6.9" INSTALL_DIR="..\..\tcltk64" all install
