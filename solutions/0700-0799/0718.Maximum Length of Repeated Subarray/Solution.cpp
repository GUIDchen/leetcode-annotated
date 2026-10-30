// 题目：718. 最长重复子数组（Maximum Length of Repeated Subarray）
// 核心思路：经典二维 DP。f[i][j] 表示以 nums1[i-1]、nums2[j-1] 结尾的最长公共连续子数组长度；末尾元素相同则 f[i-1][j-1] + 1，否则为 0，全程取最大值。
// 时间复杂度：O(m·n)，DP 表每个位置算一次；空间复杂度：O(m·n)，需要保存整张 DP 表。
class Solution {  // LeetCode 约定的题解类
public:  // 对外可见的接口区
    int findLength(vector<int>& nums1, vector<int>& nums2) {  // 返回两个数组的最长公共连续子数组的长度
        int m = nums1.size(), n = nums2.size();  // 两个数组的长度，用于建立 DP 表
        vector<vector<int>> f(m + 1, vector<int>(n + 1));  // f[i][j]：(m+1)×(n+1) 的 DP 表，默认全 0，多出的一行一列用来表示空前缀的边界
        int ans = 0;  // 记录遍历过程中出现过的最大匹配长度
        for (int i = 1; i <= m; ++i) {  // 枚举 nums1 的前缀长度 i
            for (int j = 1; j <= n; ++j) {  // 枚举 nums2 的前缀长度 j
                if (nums1[i - 1] == nums2[j - 1]) {  // 两个末尾元素相同，匹配长度可以在左上角的状态上继续延长
                    f[i][j] = f[i - 1][j - 1] + 1;  // 以这两个位置结尾的最长公共子数组长度
                    ans = max(ans, f[i][j]);  // 随时更新全局最大值
                }  // 结束匹配分支；元素不同时保持默认的 0，表示此处无法接续
            }  // 结束内层列循环
        }  // 结束外层行循环
        return ans;  // 返回整张表中出现过的最大长度
    }  // 结束 findLength 方法
};  // 结束 Solution 类定义