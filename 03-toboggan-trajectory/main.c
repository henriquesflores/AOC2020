#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define NPATHS  5   
#define tree   '#'
#define square '.'

struct Vector {
    uint32_t x; // x coordinate is mod width
    uint32_t y;
};

void printvec(struct Vector *v) {
    printf("(%d, %d)\n", v->x, v->y);
}

// Maybe should have made this into its own structure
static char *map = NULL;
static uint32_t width  = 0;
static uint32_t height = 0;

// Should have read and parsed the structure
char *read_file(const char *filepath) {
    FILE *f = fopen(filepath, "r");

    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *contents = malloc(filesize * sizeof(char) + 1);
    size_t bytread = fread(contents, 1, filesize, f);

    assert(bytread == filesize);
    contents[filesize] = 0;

    fclose(f);
    return contents;
}

size_t linelen(char *p) {
    size_t count = 0;
    while(*p++ != '\n') {
        count++;
    }
    return count;
}

uint32_t max_height(char *m) {
    uint32_t nrow = 0;
    size_t N = strlen(m);
    for (size_t i = 0; i < N; i++) 
        nrow += (*m++ == '\n') ? 0 : 1; 
    
    return nrow / width;
}

void update(struct Vector *u, const struct Vector *v) {
    u->x += v->x; 
    u->y += v->y;
}

uint32_t index_map(struct Vector *u) {
    // This should be a number between
    // 0 < w < 120
    uint32_t h = (width + 1) * (u->y - 1);
    return (u->x - 1) % width + h;
}

size_t is_tree(struct Vector *v) {
    uint32_t index = index_map(v);
    return map[index] == tree ? 1 : 0;
}

uint32_t part1(struct Vector u, const struct Vector *v) {
    uint32_t ntree = 0;
    while (u.y < height) {
        update(&u, v); 
        ntree += is_tree(&u);
    }

    return ntree;
}

uint64_t prod(uint32_t *xs, uint32_t xsize) {
    uint32_t p = 1;
    for (int i = 0; i < xsize; i++)
        p *= xs[i];

    return p;
}

void solve(const char *filepath) {
    map    = read_file(filepath); 
    width  = linelen(map);
    height = max_height(map);

    struct Vector v[NPATHS] = { {1, 1}
                              , {3, 1}
                              , {5, 1}
                              , {7, 1}
                              , {1, 2} 
                              };

    struct Vector here = {1, 1}; 

    uint32_t ntrees[NPATHS] = {0};
    for (size_t i = 0; i < NPATHS; i++) {
        ntrees[i] = part1(here, &v[i]);
        printf("For (%d, %d): %d\n", v[i].x, v[i].y, ntrees[i]);
    }
    
    uint64_t ntree_prod = prod(ntrees, NPATHS);
    printf("Part 2: %ld\n", ntree_prod);

    free(map);
}

// AOC-2020 Day 3
int main(size_t argc, char **argv) {

    if (argc != 2) {
        puts("Wrong usage");
        return 1;
    }

   
    solve(argv[1]);

	return 0;
}
