// 题目：1464. 数组中两元素的最大乘积（Maximum Product of Two Elements in an Array）
// 核心思路：一次遍历同时维护最大值 max 与次大值 submax，答案就是 (max - 1) * (submax - 1)。
// 时间复杂度：O(n)，只需扫描一遍数组；空间复杂度：O(1)，只用两个额外变量。
int maxProduct(int* nums, int numsSize) {  // nums 是输入数组，numsSize 是长度；返回挑出的两个元素各自减一后的乘积
    int max = 0;  // 记录目前为止的最大值
    int submax = 0;  // 记录目前为止的次大值（严格小于 max）
    for (int i = 0; i < numsSize; i++) {  // 顺序扫描每个元素
        int num = nums[i];  // 当前元素，先取出来避免重复写 nums[i]
        if (num > max) {  // 比现有最大值还大，说明最大值、次大值都要往后挪
            submax = max;  // 原来的最大值降级为次大值
            max = num;  // 当前元素成为新的最大值
        } else if (num > submax) {  // 没超过最大值，但仍可能刷新次大值
            submax = num;  // 更新次大值
        }  // 无操作分支，两个条件都不成立时保持原状
    }  // 遍历结束，max 与 submax 就是整个数组最大的两个数
    return (max - 1) * (submax - 1);  // 题目要求两个元素各自减一后相乘，取最大的两个数即得最大乘积
}  // 函数结束