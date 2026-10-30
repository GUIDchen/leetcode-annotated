// 题目：3287. 求出数组中最大序列值（Find the Maximum Sequence Value of Array）
// 思路：分别用前后缀 DP 求出「前 i 个数选 k 个能得到哪些按位或值」与「i 之后选 k 个能得到哪些按位或值」，再枚举分割点取两段按位或值的最大异或。
// 时间复杂度：O(n·k·2^7)；空间复杂度：O(n·k·2^7)，用来存 f 与 g 两张布尔表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxValue(vector<int>& nums, int k) {  // nums：原数组；k：序列长度（选 k 个数，相邻两项差的绝对值不超过 2k）
        int m = 1 << 7;  // 值域上界：nums[i] < 2^7，按位或的结果同样落在 [0, 127]
        int n = nums.size();  // 数组长度

        vector<vector<vector<bool>>> f(n + 1, vector<vector<bool>>(k + 2, vector<bool>(m, false)));  // f[i][j][x]：从前 i 个数中选 j 个，能否按位或得到 x
        f[0][0][0] = true;  // 边界：选 0 个数时按位或为 0

        for (int i = 0; i < n; i++) {  // 前缀 DP：按位置顺序逐个推进
            for (int j = 0; j <= k; j++) {  // 已选个数，最多选 k 个
                for (int x = 0; x < m; x++) {  // 枚举当前可能得到的按位或值
                    if (f[i][j][x]) {  // 只有可达状态才能继续转移
                        f[i + 1][j][x] = true;  // 不选 nums[i]：状态原样带到 i+1
                        f[i + 1][j + 1][x | nums[i]] = true;  // 选 nums[i]：按位或上它，同时个数加一
                    }  // if 结束
                }  // 按位或值枚举结束
            }  // 选取个数枚举结束
        }  // 前缀 DP 结束

        vector<vector<vector<bool>>> g(n + 1, vector<vector<bool>>(k + 2, vector<bool>(m, false)));  // g[i][j][y]：从下标 i 起的后缀中选 j 个，能否按位或得到 y
        g[n][0][0] = true;  // 边界：后缀为空时按位或为 0

        for (int i = n; i > 0; i--) {  // 后缀 DP：从后往前推进
            for (int j = 0; j <= k; j++) {  // 已选个数，最多选 k 个
                for (int y = 0; y < m; y++) {  // 枚举后缀可能得到的按位或值
                    if (g[i][j][y]) {  // 只有可达状态才能继续转移
                        g[i - 1][j][y] = true;  // 不选 nums[i-1]：后缀起点前移到 i-1
                        g[i - 1][j + 1][y | nums[i - 1]] = true;  // 选 nums[i-1]：按位或上它，同时个数加一
                    }  // if 结束
                }  // 按位或值枚举结束
            }  // 选取个数枚举结束
        }  // 后缀 DP 结束

        int ans = 0;  // 答案：两段按位或值的最大异或结果

        for (int i = k; i <= n - k; i++) {  // 枚举分割点：前缀取 [0,i) 的 k 个，后缀取 [i,n) 的 k 个
            for (int x = 0; x < m; x++) {  // 枚举前缀按位或值
                if (f[i][k][x]) {  // 该前缀状态可达才继续
                    for (int y = 0; y < m; y++) {  // 枚举后缀按位或值
                        if (g[i][k][y]) {  // 该后缀状态可达
                            ans = max(ans, x ^ y);  // 用两段按位或值的异或刷新答案
                        }  // if 结束
                    }  // 后缀值枚举结束
                }  // if 结束
            }  // 前缀值枚举结束
        }  // 分割点枚举结束

        return ans;  // 返回最大异或值
    }  // maxValue 结束
};  // Solution 类结束
