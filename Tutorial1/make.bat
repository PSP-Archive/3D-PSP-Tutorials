@ECHO OFF

ECHO Compiling project...

SET path=%path%;C:\cygwin\bin;C:\cygwin\usr/local/pspdev/bin
SET PSPSDK=C:\cygwin\usr/local/pspdev

make.exe

ECHO Delete objects not needed...
DEL *.o

SET DRIVE=.\

ECHO Creating the PBP
MD %DRIVE%TUTORIAL0%%
Elf2pbpm -FILEOUT=%DRIVE%TUTORIAL1%%\EBOOT.PBP -TITLE="Tutorial 1"

ECHO Rename to EBOOT.PBP
MD %DRIVE%TUTORIAL1
MOVE out.elf %DRIVE%TUTORIAL1\EBOOT.PBP

