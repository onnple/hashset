# 散列表HashSet
散列表开放寻址法实现HashMap，原文地址：  

## 开放寻址的三种寻址法
### 1、线性探测
static INode *hash_linear_probing(HashSet *hashset, Element *element)

### 2、平方探测
static INode *hash_square_probing(HashSet *hashset, Element *element)

### 3、双散列
static INode *hash_double_hashing(HashSet *hashset, Element *element)


## HashSet函数操作
### 1、初始化HashSet
extern HashSet *hashset_init(int length);

### 2、判断HashSet是否为空
extern int hashset_is_empty(HashSet *hashset);

### 3、判断HashSet是否已满
extern int hashset_is_full(HashSet *hashset);

### 4、添加元素到HashSet
extern int hashset_add(HashSet *hashset, Element *element);

### 5、从HashSet删除元素
extern int hashset_delete(HashSet *hashset, Element *element);

### 6、搜索元素
extern INode *hashset_get(HashSet *hashset, Element *element);

### 7、遍历HashSet
extern void hashset_traverse(HashSet *hashset);

### 8、释放和清空HashSet
extern int hashset_clear(HashSet *hashset);
