all: play.bin
crt.o: crt.S
	gcc-arm -c crt.S

play.o: play.c
	gcc-arm -c play.c

ball.o: ball.c
	gcc-arm -c ball.c

racket.o: racket.c
	gcc-arm -c racket.c

game.o: game.c
	gcc-arm -c game.c

block.o: block.c
	gcc-arm -c block.c

box.o: box.c
	gcc-arm -c box.c

display.o: display.c
	gcc-arm -c display.c

hp.o: hp.c
	gcc-arm -c hp.c

barrage.o: barrage.c
	gcc-arm -c barrage.c

play.bin: crt.o play.o ball.o racket.o game.o block.o box.o display.o hp.o barrage.o
	ld-arm -o play.out -T gcc.ls crt.o play.o ball.o racket.o game.o block.o box.o display.o hp.o barrage.o
	objcopy-arm -O binary play.out play.bin

clean:
	/bin/rm -f *.o *.bin *.out
