main:
	gcc server.c func.c -o server -lws2_32
	gcc client.c func.c -o client -lws2_32
clean:
	rm -rf server.exe
	rm -rf client.exe