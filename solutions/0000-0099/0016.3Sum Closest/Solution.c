// 题目：16. 最接近的三数之和（3Sum Closest）
// 思路：排序后固定第一个数，用左右双指针夹逼；每步用 |t - target| 更新最优解，命中 target 立即返回。
// 时间复杂度：O(n^2)，外层枚举 + 内层双指针；空间复杂度：O(1)，除排序外只用常数个变量。
int cmp(const void* a, const void* b) {  // qsort 需要的比较函数
    return (*(int*) a - *(int*) b);  // 转成 int 指针取值后作差，升序排列
}

int threeSumClosest(int* nums, int numsSize, int target) {  // 返回和值最接近 target 的三数之和
    qsort(nums, numsSize, sizeof(int), cmp);  // 排序后才能用双指针单调收缩
    int ans = 1 << 30;  // 用一个足够大的数初始化“目前最优和”
    for (int i = 0; i < numsSize; ++i) {  // 枚举第一个数
        int j = i + 1, k = numsSize - 1;  // 左右指针指向 i 右侧区间的最小值与最大值
        while (j < k) {  // 两指针未相遇就继续
            int t = nums[i] + nums[j] + nums[k];  // 当前三数之和
            if (t == target) {  // 正好等于目标
                return t;  // 已是最优，直接返回
            }
            if (abs(t - target) < abs(ans - target)) {  // 当前和比已知最优更接近目标
                ans = t;  // 更新最优解
            }
            if (t > target) {  // 和偏大，需要更小的数
                --k;  // 右指针左移
            } else {  // 和偏小，需要更大的数
                ++j;  // 左指针右移
            }
        }
    }
    return ans;  // 返回最接近 target 的和
}
