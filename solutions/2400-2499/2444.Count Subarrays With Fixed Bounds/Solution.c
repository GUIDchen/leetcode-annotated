// 题目：2444. 统计定界子数组的数目（Count Subarrays With Fixed Bounds）
// 思路：以 i 为右端点，记录最近一次 minK、maxK 与越界值的位置 k，合法左端点个数为 max(0, min(j1, j2) - k)。
// 时间复杂度：O(n)，只从左到右扫一遍数组；空间复杂度：O(1)，只用常数个下标与累加器。
long long countSubarrays(int* nums, int numsSize, int minK, int maxK) {  // 返回「最小值恰为 minK 且最大值恰为 maxK」的连续子数组个数
    long long ans = 0;  // 累计答案；子数组个数可达 O(n^2)，必须用 64 位整型
    int j1 = -1, j2 = -1, k = -1;  // j1：minK 最近出现的下标；j2：maxK 最近出现的下标；k：越界元素最近出现的下标
    for (int i = 0; i < numsSize; ++i) {  // i 是当前枚举的右端点，从左到右推进
        if (nums[i] < minK || nums[i] > maxK) k = i;  // 当前值越界，任何包含它的子数组都不合法，用 k 记下这道「墙」
        if (nums[i] == minK) j1 = i;  // 刷新 minK 出现的最新位置
        if (nums[i] == maxK) j2 = i;  // 刷新 maxK 出现的最新位置
        int m = j1 < j2 ? j1 : j2;  // 取更靠左的那个（即更晚出现的那个）：它决定左端点最多能伸到哪
        if (m > k) ans += (long long) (m - k);  // 左端点落在 (k, m] 内都合法，共有 m-k 个；若 m 不超过 k 则本右端点无解
    }
    return ans;  // 返回所有右端点贡献之和，即合法子数组总数
}
