@echo off
setlocal EnableDelayedExpansion

set Root=%~dp0

set ProjectName=LargeCandle3D.exe

set BinPath=Bin\
set BuildPath=Builds\
set SourcePath=Source\Maths
set LibPath=Lib\

set Compiler=g++
set CompilerFlags=-std=c++17 -Wall -Wextra -Wpedantic -I Source\ -O0 -ggdb

set LinkerFlags=-L Lib\ -lglfw3dll -lglad -lopengl32

for /R %SourcePath% %%X in (*.c *.cpp) do (
  set File=%%~X
  set File=!File:%Root%=!

  set SubBuildPath=%%~dpX
  set SubBuildPath=!SubBuildPath:%Root%=!
  set SubBuildPath=%BuildPath%!SubBuildPath!

  if NOT exist !SubBuildPath! (
    mkdir !SubBuildPath!
  )

  echo Building C++ object !File!.o
  %Compiler% %CompilerFlags% -c !File! -o %BuildPath%!File!.o
)

rem set CompiledFiles=
rem for /R %BuildPath% %%X in (*.o) do (
rem   set CompiledFiles=!CompiledFiles! %%~X
rem )
rem 
rem echo Linking C++ executable %ProjectName% 
rem %Compiler% %CompiledFiles% -o %BinPath%%ProjectName% %LinkerFlags%

endlocal