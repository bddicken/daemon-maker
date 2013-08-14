all:
	gcc -o dm -g daemon-maker.c

clean:
	rm -rf dm
