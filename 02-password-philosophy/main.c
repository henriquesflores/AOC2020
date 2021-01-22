#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXBUFFER 1000

struct Policy {
    size_t lower;
    size_t upper;
    char constrain;
    char password[MAXBUFFER];
};

static struct Policy policies[MAXBUFFER];
static int size;

void print_policy(struct Policy *p) {
    printf("lower constrain: %ld\n", p->lower);
    printf("upper constrain: %ld\n", p->upper);
    printf("letter constrined: %c\n", p->constrain);
    printf("password: %s\n", p->password);
}

void policy_from_file(const char *file_path) {
   FILE *f = fopen(file_path, "r"); 

   char line[2 * MAXBUFFER];
   char pass[MAXBUFFER];
   size_t l, u;
   char c;
   while ( fgets(line, 2 * MAXBUFFER, f) ) {
       sscanf(line, "%ld-%ld %c: %s", &l, &u, &c, pass);
       if (u < l) {
           printf("Upper constrain is lower than lower constrain\n");
           exit(1);
       }
       policies[size].lower = l;
       policies[size].upper = u;
       policies[size].constrain = c;
       strcpy(policies[size].password, pass);
       size++;
   } 

   fclose(f);
}

size_t str_count(char *src, char c) {
    unsigned int count = 0;
    for (size_t i = 0; i < strlen(src); i++) 
        count += src[i] == c ? 1 : 0; 

    return count;
}

size_t is_policy_valid(struct Policy *p) {
    size_t n = str_count(p->password, p->constrain);
    if (p->lower <= n && n <= p->upper) {
       return 1;
    } else {
       return 0;
    } 
}

size_t valid_policies(struct Policy p[]) {
    size_t how_many = 0;
    for (size_t i = 0; i < size; i++) {
        how_many += is_policy_valid(&p[i]);
    }

    return how_many;
}

size_t new_valid_policies(struct Policy p[]) {
    size_t how_many = 0;
    for (size_t i = 0; i < size; i++) { 
        char a1 = p[i].password[p[i].lower - 1];
        char a2 = p[i].password[p[i].upper - 1];
        int c1 = (a1 == p[i].constrain || a2 == p[i].constrain);
        int c2 = (a1 == p[i].constrain && a2 == p[i].constrain);
        how_many += c1 && !c2 ? 1 : 0;
    }

    return how_many;
}

void solve(const char *file_path) {
    policy_from_file(file_path);
    
    size_t valid = valid_policies(policies);
    printf("Part 1: %ld\n", valid);

    valid = new_valid_policies(policies);
    printf("Part 2: %ld\n", valid);
}

// AOC-2020 Day 2
int main(size_t argc, char **argv) {

    if (argc != 2) {
        printf("Wrong usage\n");
        return 1;
    }

    solve(argv[1]);

	return 0;
}
