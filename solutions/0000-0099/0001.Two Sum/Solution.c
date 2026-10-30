// 题目：1. 两数之和（Two Sum）
// 思路：手写哈希表（容量取 2 的幂，线性探测解决冲突），键是元素值，值是下标。
// 时间复杂度：O(n)，均摊每次插入/查询 O(1)；空间复杂度：O(n)。
#include <stdlib.h>  // malloc / calloc / free 的原型

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {  // 返回两个下标组成的数组，*returnSize 输出长度
    int capacity = 1;  // 哈希表容量，初始为 1
    while (capacity < numsSize * 2) capacity <<= 1;  // 不断翻倍，直到至少是元素个数的两倍（降低冲突概率）
    int* keys = malloc(capacity * sizeof(int));  // 存放键（元素值）
    int* vals = malloc(capacity * sizeof(int));  // 存放下标
    char* used = calloc(capacity, sizeof(char));  // 标记每个槽位是否被占用，calloc 会清零
    if (!keys || !vals || !used) {  // 任一分配失败
        free(keys);  // 释放已分配的键数组
        free(vals);  // 释放已分配的下标数组
        free(used);  // 释放已分配的占用标记
        *returnSize = 0;  // 没有结果
        return NULL;  // 返回空指针
    }
    for (int i = 0; i < numsSize; ++i) {  // 顺序扫描每个元素
        int x = nums[i];  // 当前元素
        int y = target - x;  // 还需要的补数
        unsigned int h = (unsigned int) y & (capacity - 1);  // 用位与代替取模，把补数映射到槽位
        while (used[h]) {  // 槽位被占用就线性探测
            if (keys[h] == y) {  // 探测到补数，说明找到一对
                int* res = malloc(2 * sizeof(int));  // 分配返回数组
                res[0] = vals[h];  // 补数对应的下标
                res[1] = i;  // 当前元素下标
                *returnSize = 2;  // 返回长度为 2
                free(keys);  // 释放键数组
                free(vals);  // 释放下标数组
                free(used);  // 释放占用标记
                return res;  // 返回结果
            }
            h = (h + 1) & (capacity - 1);  // 冲突：探测下一个槽位，越界后回绕
        }
        unsigned int h2 = (unsigned int) x & (capacity - 1);  // 计算当前值的插入位置
        while (used[h2]) h2 = (h2 + 1) & (capacity - 1);  // 线性探测找到空槽
        used[h2] = 1;  // 标记该槽已占用
        keys[h2] = x;  // 写入键
        vals[h2] = i;  // 写入下标
    }
    *returnSize = 0;  // 遍历完仍未找到（题目保证有解，理论上不会到这里）
    free(keys);  // 释放键数组
    free(vals);  // 释放下标数组
    free(used);  // 释放占用标记
    return NULL;  // 返回空指针
}
