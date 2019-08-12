#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashset.h"


static void hashset(void){
    HashSet *hashset = hashset_init(137);
    for (int i = 0; i < 60; ++i) {
        Element element;
        char temp[32];
        itoa(i * i * i, temp, 10);
        strcpy(element.name, temp);
        element.price = i * i + 8;
        hashset_add(hashset, &element);
    }
    hashset_traverse(hashset); // 遍历HashMap

    Element ele;
    ele.price = 12;
    strcpy(ele.name, "2744");
    INode *node = hashset_get(hashset, &ele); // HashMap查询
    printf("name: %s\n", node->element.name);
    printf("size: %d\n", hashset->size);
    hashset_delete(hashset, &ele); // HashMap删除元素
    printf("size: %d\n", hashset->size);

    hashset_clear(hashset);
}

int main() {
    hashset();
    return 0;
}

