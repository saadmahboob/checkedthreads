#include <stdlib.h>
#include "imp.h"

/* TODO: add a seed */

/* based on GNU std::random_shuffle */
void ct_random_shuffle(int* p, int n) {
    int i;
    for(i=1; i<n; ++i) {
        /* swap p[i] with a random element in [0,i] */
        int j = rand() % (i+1);
        int tmp = p[j];
        p[j] = p[i];
        p[i] = tmp;
    }
}

int* ct_rand_perm(int n) {
    int* p = (int*)malloc(n*sizeof(int));
    int i;
    for(i=0; i<n; ++i) {
        p[i] = i;
    }
    ct_random_shuffle(p, n);
    return p;
}

void ct_shuffle_init(int num_threads) {
    (void)num_threads;
}

void ct_shuffle_fini(void) {
}

void ct_shuffle_for(int n, ct_ind_func f, void* context) {
    int* perm = ct_rand_perm(n);
    int i;
    for(i=0; i<n; ++i) {
        f(perm[i], context);
    }
    free(perm);
}

ct_imp g_ct_shuffle_imp = {
    "shuffle",
    &ct_shuffle_init,
    &ct_shuffle_fini,
    &ct_shuffle_for,
};