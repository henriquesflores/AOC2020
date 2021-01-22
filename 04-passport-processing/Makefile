INPUT = input.txt
SAMPLE = sample.txt

main: main.c
	gcc main.c -o main

input: main $(INPUT)
	./main $(INPUT)

sample: main $(SAMPLE)
	./main $(SAMPLE)

debug: main.c
	gcc main.c -o main -ggdb
	gdb ./main
