// 题目：1458. 两个子序列的最大点积（Max Dot Product of Two Subsequences）
// 思路：动态规划，f[i][j] 表示 nums1 前 i 个与 nums2 前 j 个元素能得到的最大点积；转移为「丢掉 nums1[i-1]」「丢掉 nums2[j-1]」「把这两个元素配成一对」三者取最大，配成一对时前缀点积为负就从 0 重新开始。
// 时间复杂度：O(m×n)，状态数是 m×n 且转移 O(1)；空间复杂度：O(m×n)，需要二维 dp 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：两个输入数组，点积只在非空子序列上计算
        int m = nums1.size(), n = nums2.size();  // m、n 分别是两个数组的长度
        int f[m + 1][n + 1];  // f[i][j]：nums1 前 i 个元素与 nums2 前 j 个元素的最大点积
        memset(f, 0xc0, sizeof f);  // 0xc0 逐字节填充出很小的负数（约 -1e9），表示该状态还没选出任何一对元素
        for (int i = 1; i <= m; ++i) {  // 枚举 nums1 的前缀长度 i
            for (int j = 1; j <= n; ++j) {  // 枚举 nums2 的前缀长度 j
                int v = nums1[i - 1] * nums2[j - 1];  // 把当前这一对元素相乘，得到它们的点积
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);  // 先考虑不使用 nums1[i-1] 或不使用 nums2[j-1] 的两种情况
                f[i][j] = max(f[i][j], max(0, f[i - 1][j - 1]) + v);  // 再考虑用上这一对：前缀点积为负时不如从 0 开始，所以取 max(0, 前缀)
            }  // 内层 for 循环体结束
        }  // 内层 for 循环体结束
        return f[m][n];  // 返回两个数组都取完整长度时的最大点积
    }  // 方法体结束
};  // 类定义结束
