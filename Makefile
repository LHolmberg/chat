server:
	gcc `pkg-config --cflags gtk+-3.0` -o server SERVER.c `pkg-config --libs gtk+-3.0`

client:
	gcc `pkg-config --cflags gtk+-3.0` -o client CLIENT.c `pkg-config --libs gtk+-3.0`
