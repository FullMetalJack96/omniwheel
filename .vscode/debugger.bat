set PATH=C:\Users\msobc\.vscode\HusarionTools\bin\;%PATH%
cd c:\Users\msobc\Documents\AGH\4th semester\Lego\Soft\code\test || exit 1
start /wait st-flash write myproject.bin 0x08010000 || exit 1
start st-util
arm-none-eabi-gdb %*