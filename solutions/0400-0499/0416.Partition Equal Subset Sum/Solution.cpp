// 题目：416. 分割等和子集（Partition Equal Subset Sum）
// 思路：总和为奇数时必然无解；否则转化成 0/1 背包，f[i][j] 表示前 i 个数能否恰好凑出和 j，目标是 f[n][总和/2]。
// 时间复杂度：O(n * sum)，两层循环各遍历一次物品与和；空间复杂度：O(n * sum)，二维布尔表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canPartition(vector<int>& nums) {  // nums 是正整数数组，判断能否把它分成两个元素和相等的子集
        int s = accumulate(nums.begin(), nums.end(), 0);  // 求所有元素的总和 s
        if (s % 2 == 1) {  // 总和是奇数，就不可能均分成两份
            return false;  // 直接返回 false
        }  // 奇数分支结束
        int n = nums.size();  // n 是元素个数
        int m = s >> 1;  // 目标和是总和的一半（右移一位等价于除以 2）
        bool f[n + 1][m + 1];  // f[i][j]：只考虑前 i 个数时，能否恰好凑出和 j
        memset(f, false, sizeof(f));  // 整张表先全部置为 false
        f[0][0] = true;  // 边界：前 0 个数凑出和 0 是可行的（什么都不选）
        for (int i = 1; i <= n; ++i) {  // 逐个枚举物品（1 到 n）
            int x = nums[i - 1];  // x 是第 i 个物品的值（数组下标从 0 开始，所以要减 1）
            for (int j = 0; j <= m; ++j) {  // 枚举所有可能的和 j
                f[i][j] = f[i - 1][j] || (j >= x && f[i - 1][j - x]);  // 不选 x（继承上一行）或选 x（那就需要凑出 j - x），两者任一成立即可
            }  // 内层循环结束
        }  // 外层循环结束
        return f[n][m];  // 前 n 个数能否凑出总和的一半，就是最终答案
    }  // canPartition 方法结束
};  // Solution 类结束