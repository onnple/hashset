//
// Created by Once on 2019/8/12.
//

#include "hashset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 散列表开放寻址法实现 HashSet

HashSet *hashset_init(int length){
    if(length <= 0){
        perror("length for the hash set should be greater than 0");
        return NULL;
    }
    HashSet *hashset = (HashSet*)malloc(sizeof(HashSet));
    if(!hashset){
        perror("alloc mem for hash set error");
        return NULL;
    }
    hashset->length = length;
    hashset->size = 0;
    hashset->array = (INode*)malloc(sizeof(INode) * length);
    if(!hashset->array){
        perror("alloc mem for array error");
        free(hashset);
        return NULL;
    }
    for (int i = 0; i < length; ++i) {
        hashset->array[i].kind = Empty;
    }
    return hashset;
}

int hashset_is_empty(HashSet *hashset){
    if(hashset == NULL)
        return 1;
    return hashset->size == 0;
}

int hashset_is_full(HashSet *hashset){
    if(hashset == NULL)
        return 0;
    return hashset->size == hashset->length;
}

static int hash_code(char key[]){
    int value = 0, len = strlen(key);
    for (int i = 0; i < len; ++i) {
        value += key[i];
    }
    return value;
}

static int hash(HashSet *hashset, char key[]){
    return hash_code(key) % hashset->length;
}

int hashset_add(HashSet *hashset, Element *element){
    if(hashset == NULL || element == NULL)
        return 0;
    if(hashset->size == hashset->length){
        perror("hash set is full");
        return 0;
    }
    INode *node = hashset_get(hashset, element);
    if(node->kind != Available){
        node->kind = Available;
        node->element.price = element->price;
        strcpy(node->element.name, element->name);
        hashset->size++;
    }
    else{
        node->element.price = element->price;
    }
    return 1;
}

int hashset_delete(HashSet *hashset, Element *element){
    if(hashset == NULL || hashset->size == 0 || element == NULL)
        return 0;
    INode *node = hashset_get(hashset, element);
    if(node->kind == Available){
        node->kind = Deleted;
        hashset->size--;
    }
    return 1;
}

// 1、线性探测法
static INode *hash_linear_probing(HashSet *hashset, Element *element){
    int index = hash(hashset, element->name);
    INode *node = &hashset->array[index];
    int i = 0;
    while(node->kind != Empty && strcmp(element->name, node->element.name) != 0){
        index += ++i;
        index %= hashset->length;
        node = &hashset->array[index];
    }
    return node;
}

// 2、平方探测法
static INode *hash_square_probing(HashSet *hashset, Element *element){
    int index = hash(hashset, element->name);
    INode *node = &hashset->array[index];
    int i = 0;
    while(node->kind != Empty && strcmp(element->name, node->element.name) != 0){
        ++i;
        index += i * i;
        index %= hashset->length;
        node = &hashset->array[index];
    }
    return node;
}

// 3、双散列法
static int hash2(char key[], int R){
    return R - (hash_code(key) % R);
}

static INode *hash_double_hashing(HashSet *hashset, Element *element){
    int R = ((hashset->length - 3) / 2 - 1) + 3;
    int index = hash(hashset, element->name);
    INode *node = &hashset->array[index];
    int i = 0;
    while(node->kind != Empty && strcmp(element->name, node->element.name) != 0){
        index += ++i * hash2(element->name, R);
        index %= hashset->length;
        node = &hashset->array[index];
    }
    return node;
}

INode *hashset_get(HashSet *hashset, Element *element){
    if(hashset == NULL || element == NULL)
        return NULL;
//    return hash_linear_probing(hashset, element);
    return hash_square_probing(hashset, element);
//    return hash_double_hashing(hashset, element);
}

void hashset_traverse(HashSet *hashset){
    if(hashset == NULL)
        return;
    for (int i = 0; i < hashset->length; ++i) {
        if(hashset->array[i].kind == Empty)
            printf("[Empty] ");
        else if(hashset->array[i].kind == Deleted)
            printf("[Deleted] ");
        else
            printf("(%s) ", hashset->array[i].element.name);
    }
    printf("\n");
}

int hashset_clear(HashSet *hashset){
    if(hashset == NULL)
        return 0;
    free(hashset->array);
    free(hashset);
    return 1;
}
