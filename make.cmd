windres -i main.rc -o main.o
g++ main.cpp main.o -o "Toggle Sprint.exe"
pause