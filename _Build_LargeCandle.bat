@echo off
setlocal EnableDelayedExpansion

set Root=%~dp0

set ProjectName=LargeCandle3D.exe

set BinPath=Bin\
set BuildPath=Builds\
set SourcePath=Source\LC3\
set LibPath=Lib\

set Compiler=g++
set CompilerFlags=-std=c++17 -Wall -Wextra -Wpedantic -I %SourcePath%

set LinkerFlags=-L.

for /R %SourcePath% %%X in (*.c *.cpp) do (
  set File=%%~X
  set File=!File:%Root%=!

  set SubBuildPath=%%~dpX
  set SubBuildPath=!SubBuildPath:%Root%=!
  set SubBuildPath=%BuildPath%!SubBuildPath!

  if NOT exist !SubBuildPath! (
    mkdir !SubBuildPath!
  )

  %Compiler% %CompilerFlags% -c !File! -o %BuildPath%!File!.o
)

set CompiledFiles=
for /R %BuildPath% %%X in (*.o) do (
  set CompiledFiles=!CompiledFiles! %%~X
)

%Compiler% %CompiledFiles% -o %BinPath%%ProjectName% %LinkerFlags%

endlocal