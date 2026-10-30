// 题目：1770. 执行乘法运算的最大分数（Maximum Score from Performing Multiplication Operations）
// 思路：记忆化搜索。状态 (i, j) 表示已经从 nums 左端取走 i 个、右端取走 j 个元素；当前乘数下标 k = i + j，这一步只能取左端 nums[i] 或右端 nums[n - j - 1]，取两者较大值并记忆化。
// 时间复杂度：O(m^2)，共 m^2 个状态；空间复杂度：O(m^2)，记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {  // nums 是可以取数的数组，multipliers 是按顺序使用的乘数
        int n = nums.size(), m = multipliers.size();  // n 是 nums 的长度，m 是乘数的个数（也是必须执行的运算次数）
        int f[m][m];  // 记忆化数组，f[i][j] 表示左端取 i 个、右端取 j 个之后能获得的最大分数
        memset(f, 0x3f, sizeof f);  // memset 按字节填 0x3f，使每个 int 都变成 0x3f3f3f3f，作为「未计算」标记
        function<int(int, int)> dfs = [&](int i, int j) -> int {  // 记忆化搜索的 lambda，返回当前状态能获得的最大分数
            if (i >= m || j >= m || (i + j) >= m) return 0;  // 左右各取够 m 个（或合计已取满 m 个）时没有乘数可用，这些边界的分数为 0
            if (f[i][j] != 0x3f3f3f3f) return f[i][j];  // 该状态已经算过就直接复用（仍是 0x3f3f3f3f 说明还没被赋值）
            int k = i + j;  // k 是当前要用的乘数下标，等于已经取走的元素个数 i + j
            int a = dfs(i + 1, j) + nums[i] * multipliers[k];  // 方案一：取左端第 i 个元素与 multipliers[k] 相乘，再继续往后搜
            int b = dfs(i, j + 1) + nums[n - j - 1] * multipliers[k];  // 方案二：取右端第 j 个元素（下标 n - j - 1）与 multipliers[k] 相乘，再继续往后搜
            return f[i][j] = max(a, b);  // 两种方案取较大值，并写入记忆表
        };
        return dfs(0, 0);  // 从「左右都没取」的初始状态开始搜索
    }  // 方法结束
};  // 类定义结束