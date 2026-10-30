// 题目：2567. 修改两个元素的最小分数（Minimum Score by Changing Two Elements）
// 思路：先排序；把两个元素改成任意值相当于「丢掉两个元素」，剩下 n-2 个元素的最小分数由最大值减最小值决定，枚举丢掉的三种位置组合取最小跨度。
// 时间复杂度：O(n log n)，主要开销是 qsort；空间复杂度：O(log n)，快排递归栈的额外开销。
#define min(a, b) (((a) < (b)) ? (a) : (b))  // 手写 min 宏：a 更小就取 a，否则取 b（判题环境不保证提供 min 函数）

int cmp(const void* a, const void* b) {  // qsort 需要的比较函数
    return *(int*) a - *(int*) b;  // 先转成 int 指针再取值，升序返回差值
}

int minimizeSum(int* nums, int numsSize) {  // nums：待修改数组；numsSize：元素个数
    qsort(nums, numsSize, sizeof(int), cmp);  // 排序后，最小分数只与首尾元素有关，便于直接取下标
    return min(nums[numsSize - 1] - nums[2], min(nums[numsSize - 2] - nums[1], nums[numsSize - 3] - nums[0]));  // 三种丢弃方式：丢最小的两个、各丢首尾一个、丢最大的两个，取跨度最小者
}