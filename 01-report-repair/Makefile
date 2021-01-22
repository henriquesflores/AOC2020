SAMPLE = sample.txt
INPUT = input.txt

main: main.c
	gcc main.c -o main

input: main $(INPUT) 
	./main $(INPUT)

sample: main $(SAMPLE)
	./main $(SAMPLE)
