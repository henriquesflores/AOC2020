SAMPLE = sample.txt
INPUT  = input.txt

main: main.c
	gcc main.c -o main

sample: main $(SAMPLE)
	./main $(SAMPLE)

input: main $(INPUT)
	./main $(INPUT)
