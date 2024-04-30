prog: main.o background.o botton.o perso.o background_perso.o
	gcc main.o background.o botton.o perso.o background_perso.o -o prog -lSDL -g -lSDL_image -lSDL_ttf -lSDL_mixer -lm

main.o: main.c
	gcc -c main.c -o main.o -g

background.o: background.c
	gcc -c background.c -o background.o -g

botton.o: botton.c
	gcc -c botton.c -o botton.o -g

perso.o: perso.c
	gcc -c perso.c -o perso.o -g

background_perso.o: background_perso.c
	gcc -c background_perso.c -o background_perso.o -g 
	
