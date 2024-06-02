//
// Created by yaros on 17.02.2024.
//
#include "unordered_set.h"
# include <stdint.h>
# include <assert.h>
# include <malloc.h>
# include <stdio.h>
# include <stdbool.h>
#include "../../algorithms/array/array.h"
#include "../../algorithms/algorithm.h"


unordered_array_set unordered_array_set_create(size_t capacity){
    return (unordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

static void unordered_array_set_shrinkToFit(unordered_array_set *a) {
    if (a->size < a->capacity / 4) {
        a->data = (int*)realloc(a->data, sizeof(int)*a->capacity / 2);
        a->capacity /= 2;
    }
}

static void unordered_array_set_give_more_memory(unordered_array_set *a){
    if (a->size == a->capacity){
        a->data = (int*)realloc(a->data, sizeof(int)*a->capacity * 2);
        a->capacity *= 2;
    }
}

unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set result = unordered_array_set_create(size);

    for (size_t i = 0; i < size; i++) {
        unordered_array_set_insert(&result, a[i]);
    }
    return result;
}

size_t unordered_array_set_in(unordered_array_set set, int value) {
    return linearSearch_(set.data, set.size, value);
}

size_t unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    if (subset.size > set.size) {
        return set.size;
    }

    size_t coincidence = 0;

    for (size_t i = 0; i < set.size; i++) {
        for (size_t j = 0; j < subset.size; j++) {
            if (subset.data[j] == set.data[i + j]) {
                coincidence++;
            } else {
                coincidence = 0;
                break;
            }

            if (coincidence == subset.size) {
                return i;
            }
        }
    }

    return set.size;
}

bool unordered_array_set_is_Equal(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }

    size_t coincidence = 0;

    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(set2, set1.data[i]) != set2.size) {
            coincidence++;
        }
    }

    return coincidence == set1.size;
}

void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (unordered_array_set_in(*set, value) == set->size) {
        unordered_array_set_give_more_memory(set);
        unordered_array_set_isAbleAppend(set);
        set->data[set->size++] = value;
    }
}

void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t value_index = unordered_array_set_in(*set, value);
    if (value_index == set->size) {
        return;
    } else {
        for (size_t i = value_index; i < set->size - 1; i++) {
            set->data[i] = set->data[i + 1];
        }

        set->size--;
        unordered_array_set_shrinkToFit(set);
    }
}

unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set result = unordered_array_set_create(set1.size + set2.size);
    for (size_t i = 0; i < set1.size; i++)
        result.data[i] = set1.data[i];
    for (size_t i = 0; i < set2.size; i++)
        unordered_array_set_insert(&result, set2.data[i]);
    unordered_array_set_shrinkToFit(&result);
    return result;
}

unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set result = unordered_array_set_create(set1.size);

    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(set2, set1.data[i]) != set2.size) {
            unordered_array_set_insert(&result, set1.data[i]);
        }
    }

    unordered_array_set_shrinkToFit(&result);

    return result;
}

unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set result = unordered_array_set_create(set1.size);

    for (size_t i = 0; i < set1.size; i++) {
        if (unordered_array_set_in(set2, set1.data[i]) == set2.size) {
            unordered_array_set_insert(&result, set1.data[i]);
        }
    }

    unordered_array_set_shrinkToFit(&result);

    return result;
}

unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universeSet) {
    unordered_array_set result = unordered_array_set_create(universeSet.size);

    for (size_t i = 0; i < universeSet.size; i++) {
        if (unordered_array_set_in(set, universeSet.data[i]) == set.size) {
            unordered_array_set_insert(&result, universeSet.data[i]);
        }
    }

    unordered_array_set_shrinkToFit(&result);

    return result;
}

unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set difference1 = unordered_array_set_difference(set1, set2);
    unordered_array_set difference2 = unordered_array_set_difference(set2, set1);
    unordered_array_set result = unordered_array_set_union(difference1, difference2);
    unordered_array_set_delete(&difference1);
    unordered_array_set_delete(&difference2);
    return result;
}

void unordered_array_set_print(unordered_array_set set) {
    outputArray_(set.data, set.size);
}

void unordered_array_set_delete(unordered_array_set *set) {
    free(set->data);
    set->size = 0;
    set->capacity = 0;
}

unordered_array_set *getMemArrayOfUnorderedSet(int nSet, int setSize){
    unordered_array_set *us_set = (unordered_array_set*) malloc(sizeof(unordered_array_set) * nSet);
    for (int i = 0; i < nSet; i++)
        us_set[i] = unordered_array_set_create(setSize);
    return us_set;
}

void generate_permutations(int *P, int n, int *M, int i,\
                           int size, unordered_array_set *us_set, int us_set_size) {
    for (int j = 0; j < size; j++) {
        int x = M[j];
        unordered_array_set_insert(&P, x);
        P[i] = x;
        if (i + 1 == n) {
            unordered_array_set un_p = unordered_array_set_create_from_array(P, n);
            for (int k = 0; k < us_set_size; k++){
                if (us_set[k].size != n){
                    us_set[k] = un_p;
                    //unordered_array_set_print(us_set[k]);
                    break;
                }
            }
        } else {
            int m[n - 1];
            for (int k = 0; k < j; k++)
                m[k] = M[k];
            for (int k = j + 1; k < size; k++)
                m[k - 1] = M[k];
            generate_permutations(P, n, m, i + 1, size - 1, us_set, us_set_size);
        }
    }
}

unordered_array_set *getAllPermutationUnorderedSet(unordered_array_set u_set, int setSize){
    unsigned _factorial = factorial(setSize);
    unordered_array_set *us_set = getMemArrayOfUnorderedSet(_factorial, setSize);
    int M[setSize];
    for (int i = 0; i < setSize; i++) {
        M[i] = u_set.data[i];
    }
    int P[setSize];
    int us_set_size = 0;
    generate_permutations(P, setSize, M, 0, setSize, us_set, _factorial);
    //printSetOfUnorderedSet(us_set, _factorial);
    return us_set;
}

void printSetOfUnorderedSet(unordered_array_set *us_set, int us_set_size){
    for(int i = 0; i < us_set_size; i++){
        printf("%d:  ", i);
        unordered_array_set_print(us_set[i]);
    }
}