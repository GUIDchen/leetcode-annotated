// 题目：1460. 通过翻转子数组使两个数组相等（Make Two Arrays Equal by Reversing Subarrays）
// 思路：反转任意子数组不改变元素的多重集合，所以两个数组能互相转化当且仅当排序后完全相同；此处用 qsort 排序后逐位比较。
// 时间复杂度：O(n log n)，主要开销在排序；空间复杂度：O(log n)，qsort 的递归栈开销。
int compare(const void* a, const void* b) {  // qsort 需要的比较函数：按升序比较两个 int
    return (*(int*) a - *(int*) b);  // 返回差值：负数表示 a 应排在 b 之前，正数表示之后
}  // 比较函数结束

bool canBeEqual(int* target, int targetSize, int* arr, int arrSize) {  // target、arr 为两个待比较数组，Size 为各自长度；判断能否通过翻转子数组使二者相等
    qsort(target, targetSize, sizeof(int), compare);  // 先把 target 原地升序排序
    qsort(arr, arrSize, sizeof(int), compare);  // 再把 arr 原地升序排序
    for (int i = 0; i < targetSize; ++i) {  // 逐位比较排序后的两个数组
        if (target[i] != arr[i]) {  // 发现某一位不同，说明元素集合不同
            return false;  // 元素不匹配则不可能通过翻转得到，返回 false
        }  // if 语句块结束
    }  // for 循环体结束
    return true;  // 所有位都相同，说明元素一致，总能用翻转把 arr 变成 target，返回 true
}  // 函数体结束