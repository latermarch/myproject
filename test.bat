@echo 程序开始执行了
del *.o *.gch *.exe
g++ -I include -DCURL_STATICLIB -c -g cJSON.c test.cpp
g++  -g -o test.exe *.o -L lib -lcurl -lwldap32 -lws2_32
test.exe
pause