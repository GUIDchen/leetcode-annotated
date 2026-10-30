// 题目：673. 最长递增子序列的个数（Number of Longest Increasing Subsequence）
// 思路：O(n^2) 动态规划，f[i] 表示以 i 结尾的最长递增子序列长度，cnt[i] 表示该长度的方案数，两者一起转移并在遍历中维护全局最优。
// 时间复杂度：O(n^2)，双重循环枚举所有数对；空间复杂度：O(n)，两个长度为 n 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findNumberOfLIS(vector<int>& nums) {  // nums：输入数组
        int n = nums.size();  // 数组长度
        int mx = 0, ans = 0;  // mx：当前全局最长长度；ans：该长度的方案总数
        vector<int> f(n, 1);  // f[i]：以 nums[i] 结尾的最长递增子序列长度，单元素时长度为 1
        vector<int> cnt(n, 1);  // cnt[i]：达到 f[i] 长度的方案数，初始只有它自己这一种
        for (int i = 0; i < n; ++i) {  // 依次计算以每个位置结尾的答案
            for (int j = 0; j < i; ++j) {  // 枚举 i 之前的所有位置作为前驱
                if (nums[j] < nums[i]) {  // 只有严格递增才允许接在 j 后面
                    if (f[i] < f[j] + 1) {  // 找到更长的接法，长度与方案数都要覆盖
                        f[i] = f[j] + 1;  // 更新以 i 结尾的最长长度
                        cnt[i] = cnt[j];  // 方案数改为前驱 j 的方案数
                    } else if (f[i] == f[j] + 1) {  // 另一种接法也能达到同样长度
                        cnt[i] += cnt[j];  // 方案数累加
                    }
                }
            }
            if (mx < f[i]) {  // 出现了更长的递增子序列
                mx = f[i];  // 更新全局最长长度
                ans = cnt[i];  // 方案总数重置为当前位置的方案数
            } else if (mx == f[i]) {  // 与全局最长长度相同的另一种结尾
                ans += cnt[i];  // 把它的方案数累加进总数
            }
        }
        return ans;  // 返回最长递增子序列的个数
    }
};