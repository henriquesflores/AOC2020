#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXSIZE 500

static long values[MAXSIZE]; 

struct vector {
    long *components;
    size_t len;
};

void print_vector(struct vector *vec) {
    for (size_t i = 0; i < vec->len; i++)
        printf("%ld\n", vec->components[i]);
}

struct vector vector_from_file(const char *file_path) {
    FILE *f = fopen(file_path, "r");

    char line[MAXSIZE];
    int size = 0, number;
    while ( fgets(line, MAXSIZE, f) ) {
        sscanf(line, "%d\n", &number);
        values[size++] = number;
    }

    fclose(f);

    struct vector vals = { values, size };
    return vals;
}

void op_a(struct vector *a, struct vector *vec, long target) { 
    for (size_t i = 0; i < vec->len; i++) {
        long i1 = vec->components[i] * target;
        long i2 = vec->components[i] * vec->components[i]; 
        a->components[i] = i1 - i2;
    }
}

long find_duplicate(struct vector *vec) {
    for (size_t i = 0; i < vec->len; i++) {
        for (size_t j = i + 1; j < vec->len; j++) {
            if (vec->components[j] == vec->components[i])
                return vec->components[j];
        }
    }

    return -1;
}

long part1(struct vector *vec, long target) {
    /* a + b = 2020
     * a * b = x
     * (2020 - b) * b = x
     * (2020 - a) * a = x
     */

    long *a = malloc(vec->len * sizeof(long));
    struct vector nvals = {a, vec->len};

    op_a(&nvals, vec, target);
    long answer = find_duplicate(&nvals);
    
    free(a);
    
    return answer;
}

long part2(struct vector *vec) {
    /* a + b + c = 2020
     * a * b * c = x
     *
     * b + c = 2020 - a = y ---- I know y
     * b * c = x / a = z
     * 
     * Run part1 again
     */
    long holder[3];
    size_t k = 0;
    for (size_t i = 0; i < vec->len; i++) {
        long val = part1(vec, 2020 - vec->components[i]);
        if (val != -1) {
            holder[k++] = val * vec->components[i];
        }
    }

    assert(holder[0] == holder[1] &&
           holder[0] == holder[2] &&
           holder[1] == holder[2]  );

    return holder[0];
}

void solve(const char *file_path) {
    struct vector inputs = vector_from_file(file_path);

    long p1 = part1(&inputs, 2020);
    printf("This is the answer for the first part: %ld\n", p1);
    printf("------------------\n");

    long p2 = part2(&inputs);
    printf("This is the answer for the second part: %ld\n", p2);
}

// AOC 2020 - day 01
int main(size_t argc, char **argv) {

    if (argc == 1) {
        printf("There are no files\n");
        return 1;
    }
    
    for (size_t i = 1; i < argc; i++) {
        solve(argv[i]);
    }

    return 0;
}
