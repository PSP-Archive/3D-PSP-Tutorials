@ECHO OFF

ECHO COmpiling project...

SET path=%path%;C:\cygwin\bin;C:\cygwin\usr/local/pspdev/bin
SET PSPSDK=C:\cygwin\usr/local/pspdev

make.exe

ECHO Delete objects not needed...
DEL *.o

SET DRIVE=.\

ECHO Creating the PBP
MD %DRIVE%TUTORIAL0%%
Elf2pbpm -FILEOUT=%DRIVE%TUTORIAL0%%\EBOOT.PBP -TITLE="Tutorial 0"

ECHO Rename to EBOOT.PBP
MD %DRIVE%TUTORIAL0
MOVE out.elf %DRIVE%TUTORIAL0\EBOOT.PBP

