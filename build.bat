:: build.bat
@echo off
g++ src\xafety.cpp -IC:\WpdPack\Include -LC:\WpdPack\Lib -lwpcap -lpacket -o bin\xafety.exe
