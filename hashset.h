//
// Created by Once on 2019/8/12.
//

#ifndef DATALGORITHM_HASHSET_H
#define DATALGORITHM_HASHSET_H

// 开放寻址法

// 数据实体，同时是关键字和值
typedef struct element{
    char name[128]; // 使用name作为关键字
    int price;
} Element;

// 数据记录的标记类型
typedef enum kind{
    Available, Empty, Deleted
} Kind;

// 数据记录
typedef struct inode{
    Element element;
    Kind kind;
} INode;

// HashSet对外ADT接口
typedef struct hashset{
    INode *array;
    int length; // 表长
    int size; // 有效的元素个数
} HashSet;

// HashSet函数声明
extern HashSet *hashset_init(int length);
extern int hashset_is_empty(HashSet *hashset);
extern int hashset_is_full(HashSet *hashset);
extern int hashset_add(HashSet *hashset, Element *element);
extern int hashset_delete(HashSet *hashset, Element *element);
extern INode *hashset_get(HashSet *hashset, Element *element);
extern void hashset_traverse(HashSet *hashset);
extern int hashset_clear(HashSet *hashset);


#endif //DATALGORITHM_HASHSET_H
