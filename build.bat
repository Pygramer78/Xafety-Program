:: build.bat
@echo off
g++ src\xafety.cpp -Ilibs -IC:\WpdPack\Include -LC:\WpdPack\Lib -lwpcap -lpacket -o bin\xafety.exe
g++ -c libs/xafetylib.h bin/XP/xafetylib.o
ar rcs bin/XP/xafetylib.a bin/XP/xafetylib.o