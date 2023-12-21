cd /d %~dp0
cd ..

@rem foldery domyslnie ustawione na standardowo zainstalowany VSCode i Msys2
set VSCODE_EXE="C:\Users\%USERNAME%\AppData\Local\Programs\Microsoft VS Code\code.exe"
set MSYS2_ROOT=C:\msys64

@rem kto uzywa innych folderow ustawia to na podstawie nazwy komputera
@If "%computername%"=="DREAM-WORKS-BIG" (
	echo "to jest komputer PC-JAREK !"
	set VSCODE_EXE="D:\Apps\Microsoft_VS_Code\Code.exe"
	set MSYS2_ROOT=C:\Apps\msys64
)

@rem ustawiam środowisko
@rem   czysty PATH bez ustawien komputera
@rem   tylko VSC + kompilator + ninja + cmake
set PATH=C:\Windows\System32;C:\Windows\SysWOW64\wbem;%MSYS2_ROOT%\clang64\bin;%MSYS2_ROOT%\usr\bin
set BLUE_DIR=D:\delphi\aparaty\USG_USB\U32\binX
@rem 
@rem set GRPC_NOT_USE_SYSTEM_SSL_ROOTS=True
@rem set GRPC_DEFAULT_SSL_ROOTS_FILE_PATH=d:\c.txt
@rem

%VSCODE_EXE% .\
exit

cd bin
iscan3.exe

pause
