// 题目：15. 三数之和（3Sum）
// 思路：先排序，固定第一个数 i，再用左右双指针在 i 右边夹逼找两数；排序后可用 nums[i] <= 0 提前结束，并用相邻比较去重。
// 时间复杂度：O(n^2)，外层枚举 + 内层双指针；空间复杂度：O(n)，结果数组最多 O(n^2) 个三元组（不计返回值的额外空间为 O(1)）。
int cmp(const void* a, const void* b) {  // qsort 需要的比较函数
    return *(int*) a - *(int*) b;  // 转成 int 指针取值后作差，升序排列
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {  // 返回三元组数组，*returnSize 输出组数
    *returnSize = 0;  // 结果个数从 0 开始
    int cap = 1000;  // 结果数组的初始容量
    int** ans = (int**) malloc(sizeof(int*) * cap);  // 存放每个三元组的指针数组
    *returnColumnSizes = (int*) malloc(sizeof(int) * cap);  // 每个三元组的长度（这里恒为 3）

    qsort(nums, numsSize, sizeof(int), cmp);  // 先排序，后面才能用双指针和跳过重复值

    for (int i = 0; i < numsSize - 2 && nums[i] <= 0; ++i) {  // 枚举第一个数；它大于 0 时后面不可能再凑成和为 0
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // 与上一个数相同，跳过以免产出重复三元组
        int j = i + 1, k = numsSize - 1;  // 左右指针分别指向 i 之后区间的最小值与最大值
        while (j < k) {  // 两指针未相遇就继续找
            int sum = nums[i] + nums[j] + nums[k];  // 当前三数之和
            if (sum < 0) {  // 和太小，需要更大的数
                ++j;  // 左指针右移
            } else if (sum > 0) {  // 和太大，需要更小的数
                --k;  // 右指针左移
            } else {  // 恰好为 0，找到一组解
                if (*returnSize >= cap) {  // 容量不够了
                    cap *= 2;  // 容量翻倍
                    ans = (int**) realloc(ans, sizeof(int*) * cap);  // 扩容指针数组
                    *returnColumnSizes = (int*) realloc(*returnColumnSizes, sizeof(int) * cap);  // 同步扩容长度数组
                }
                ans[*returnSize] = (int*) malloc(sizeof(int) * 3);  // 为这一组三元组分配 3 个 int
                ans[*returnSize][0] = nums[i];  // 第一个数
                ans[*returnSize][1] = nums[j];  // 第二个数
                ans[*returnSize][2] = nums[k];  // 第三个数
                (*returnColumnSizes)[*returnSize] = 3;  // 记录该组长度为 3
                (*returnSize)++;  // 结果组数加一

                ++j;  // 左指针右移，继续找下一组
                --k;  // 右指针左移
                while (j < k && nums[j] == nums[j - 1]) ++j;  // 跳过左指针处的重复值，避免重复三元组
                while (j < k && nums[k] == nums[k + 1]) --k;  // 跳过右指针处的重复值
            }
        }
    }
    return ans;  // 返回所有不重复的三元组
}
