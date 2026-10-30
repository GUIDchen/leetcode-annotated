// 题目：2218. 从栈中取出 K 个硬币的最大面值和（Maximum Value of K Coins From Piles）
// 思路：分组背包。f[i][j] 表示前 i 个栈里取 j 枚硬币的最大面值和；每个栈只可能取顶部的前 h 枚，用前缀和枚举 h 做转移。
// 时间复杂度：O(n * k * m)，m 为单个栈的最大长度；空间复杂度：O(n * k)，即 DP 表的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {  // piles 是若干栈，k 是总共要取的硬币数
        int n = piles.size();  // 栈的个数
        vector<vector<int>> f(n + 1, vector<int>(k + 1));  // f[i][j]：前 i 个栈取 j 枚硬币的最大面值和，初始为 0
        for (int i = 1; i <= n; i++) {  // 逐个考虑第 i 个栈（对应 piles[i - 1]）
            vector<int> nums = piles[i - 1];  // 取出当前栈的硬币面值序列
            vector<int> s(nums.size() + 1);  // s[h] 表示从这个栈顶部连取 h 枚的累计面值和
            for (int j = 1; j <= nums.size(); j++) {  // 递推前缀和
                s[j] = s[j - 1] + nums[j - 1];  // 前 h 枚之和 = 前 h-1 枚之和 + 第 h 枚
            }
            for (int j = 0; j <= k; j++) {  // 枚举“前 i 个栈总共取的枚数”
                for (int h = 0; h < s.size() && h <= j; h++) {  // 枚举本栈取的枚数 h，不能超过总数 j
                    f[i][j] = max(f[i][j], f[i - 1][j - h] + s[h]);  // 分组背包转移：不取或取本栈顶部 h 枚
                }
            }
        }
        return f[n][k];  // 前 n 个栈取 k 枚的最优值即答案
    }
};
