// 题目：1035. 不相交的线（Uncrossed Lines）
// 思路：连线不相交等价于保序匹配，问题就是最长公共子序列；相等时继承左上角加一，否则取上方与左方的较大值。
// 时间复杂度：O(m*n)，两重循环填表；空间复杂度：O(m*n)，二维 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {  // 求 nums1 与 nums2 之间最多能连多少条不相交的线（本质是最长公共子序列）
        int m = nums1.size(), n = nums2.size();  // 两个数组的长度
        int f[m + 1][n + 1];  // 二维 DP 表（变长数组）：f[i][j] 表示前 i 个与前 j 个元素的最长公共子序列长度
        memset(f, 0, sizeof(f));  // memset 按字节清零，相当于把所有状态的初值设为 0
        for (int i = 1; i <= m; ++i) {  // 按 nums1 的下标 i 逐行推进（1 起，0 行是空序列边界）
            for (int j = 1; j <= n; ++j) {  // 按 nums2 的下标 j 逐列推进（1 起，0 列是空序列边界）
                if (nums1[i - 1] == nums2[j - 1]) {  // 两个元素相等，可以连一条线
                    f[i][j] = f[i - 1][j - 1] + 1;  // 接在去掉这两个元素的最优解后面，长度加一
                } else {  // 两个元素不等，无法同时用上
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]);  // 取「去掉 nums1 的第 i 个」与「去掉 nums2 的第 j 个」中的较优者
                }  // 相等分支结束
            }  // 列循环结束
        }  // 行循环结束
        return f[m][n];  // 返回两个完整序列的最长公共子序列长度，即最多连线数
    }  // 方法结束
};  // 类定义结束
