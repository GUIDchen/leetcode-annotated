// 题目：217. 存在重复元素（Contains Duplicate）
// 核心思路：先原地排序，重复元素必然相邻，再线性扫描相邻对即可判断。
// 时间复杂度：O(n log n)，qsort 的排序开销；空间复杂度：O(log n)，qsort 的递归栈开销。
int cmp(const void* a, const void* b) {  // qsort 需要的比较函数：a、b 是指向被比较元素的指针
    return *(int*) a - *(int*) b;  // 转成 int* 后解引用相减：负数表示 a 小，正数表示 a 大
}  // 比较函数结束

bool containsDuplicate(int* nums, int numsSize) {  // 判断数组中是否存在重复元素
    qsort(nums, numsSize, sizeof(int), cmp);  // 先原地升序排序，排序后重复元素必相邻
    for (int i = 1; i < numsSize; i++) {  // 从第二个元素开始，与它的前一个元素比较
        if (nums[i - 1] == nums[i]) {  // 相邻两元素相等，说明存在重复
            return 1;  // 返回 true（C 中用 1 表示）
        }  // if 结束
    }  // 循环结束
    return 0;  // 全部相邻都不相等，没有重复元素
}  // 函数结束