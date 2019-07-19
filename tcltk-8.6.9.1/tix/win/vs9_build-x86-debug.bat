setlocal
if not exist "..\..\tcltk\lib\tix8.4.3\tix84g.dll" goto build
goto :eof

:build
nmake /nologo -f makefile.vc MACHINE=IX86 DEBUG=1 NODEBUG=0 TCL_DBGX=g TK_DBGX=g TCL_MAJOR=8 TCL_MINOR=6 TCL_PATCH=9 BUILDDIRTOP="Debug_VC9" TCL_DIR="..\..\tcl-core-8.6.9" TK_DIR="..\..\tk-8.6.9" INSTALL_DIR="..\..\tcltk" all install
