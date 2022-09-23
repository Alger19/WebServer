echo_server.exe: HttpServer.c
	gcc -o echo_server.exe HttpServer.c -lpthread