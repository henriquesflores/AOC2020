INPUT  = input.txt
SAMPLE = sample.txt

main: main.c
	gcc main.c -o main

sample: main $(SAMPLE)
	./main $(SAMPLE)

input: main $(INPUT)
	./main $(INPUT)
