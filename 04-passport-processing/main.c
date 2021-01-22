#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define NKEYS 7
const char *keys[] = 
    { "byr"
    , "iyr"
    , "eyr"
    , "hgt"
    , "hcl"
    , "ecl"
    , "pid"
    };

char *readfile(const char *file) {
    FILE *f = fopen(file, "r");

    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = malloc(filesize * sizeof(char) + 1);
    size_t bytes = fread(buffer, 1, filesize, f);

    assert(bytes == filesize);
    buffer[filesize] = 0;

    fclose(f);
    return buffer;
}

typedef struct {
    char **cstrs;
    size_t used;
    size_t capacity;
} SV_Vector;

void push_cstr(SV_Vector *user, char *loc) {
    if (user->capacity >= user->used + sizeof(loc)) {
        user->cstrs[user->used] = loc;
        user->used += 1;
    } else {
        user->cstrs = realloc(user->cstrs, (user->capacity + 10) * sizeof(char **));
        user->capacity = (user->capacity + 10);
        user->cstrs[user->used] = loc;
        user->used += 1; 
    }
}

void printsv(SV_Vector *vs) {
    for (size_t i = 0; i < vs->used; i++) {
        printf("%s\n", vs->cstrs[i]);
    }
}

SV_Vector parse_users(char *input) {
    SV_Vector us = {NULL, 0, 0};
    
    char *udup = NULL;
    char *user = input;
    while (user) {
        char *next = strstr(user, "\n\n");
        if (next) {
            size_t len = next - user; 
            udup = strndup(user, len + 1);
            user = next + 2;
            push_cstr(&us, udup);
        } else {
            udup = strdup(user);
            push_cstr(&us, udup);
            break;
        }
    }

    return us;
}

void sv_vec_free(SV_Vector *vs) {
    for (size_t i = 0; i < vs->used; i++) {
        free(vs->cstrs[i]);
    }
}

uint32_t count_valid(const char **keys, SV_Vector *us) {
    uint32_t valid = 0;
    for (size_t i = 0; i < us->used; i++) {
        size_t pass_valid = 0;
        for (size_t j = 0; j < NKEYS; j++) {
            pass_valid += strstr(us->cstrs[i], keys[j]) ? 1 : 0;
        }

        if (pass_valid == NKEYS) 
            valid += 1;
    }

    return valid;
}

// AOC-2020 Day 04
int main(size_t argc, char **argv) {
    
    const char *file; 
    if (argc != 2) {
        puts("Wrong usage!");
        return 1;
    } else {
        file = argv[1];
    }

    char *contents = readfile(file); 
    SV_Vector users = parse_users(contents);
    uint32_t answer = count_valid(keys, &users);

    printf("Part 1: %d\n", answer);

       
    free(contents);
    sv_vec_free(&users);
	return 0;
}
