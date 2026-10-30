// 题目：2944. 购买水果需要的最少金币数（Minimum Number of Coins for Fruits）
// 思路：记忆化搜索。dfs(i) 表示从第 i 个水果开始买的最小花费：付掉 prices[i-1] 后，i+1..2i 的水果免费，下一颗要花钱的水果可以是 i+1..2i+1 中的任意一个，取其中最优。
// 时间复杂度：O(n^2)，每个状态枚举 O(n) 个后继；空间复杂度：O(n)，记忆化数组 f 加上递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCoins(vector<int>& prices) {  // prices[i-1] 是第 i 个水果的价格，下标从 1 开始更方便描述赠送关系
        int n = prices.size();  // 水果个数
        int f[n + 1];  // 记忆化数组：f[i] 表示从第 i 个水果开始买的最小花费
        memset(f, 0x3f, sizeof(f));  // 用 0x3f 填满，作为「该状态还没算过」的哨兵值
        function<int(int)> dfs = [&](int i) {  // 定义递归函数 dfs(i)：从第 i 个水果开始买的最小花费
            if (i * 2 >= n) {  // 买下第 i 个水果后可免费拿到 i+1..2i，若 2i >= n 说明剩下的全免费
                return prices[i - 1];  // 只需付第 i 个水果的钱就能覆盖到末尾
            }
            if (f[i] == 0x3f3f3f3f) {  // 该状态尚未计算时才需要递推
                for (int j = i + 1; j <= i * 2 + 1; ++j) {  // 枚举下一颗「花钱买」的水果 j，它必须落在 i+1..2i+1 之间才买得到
                    f[i] = min(f[i], prices[i - 1] + dfs(j));  // 花费 = 买第 i 个水果的钱 + 从 j 开始的最优花费，取最小
                }
            }
            return f[i];  // 返回该状态的记忆化结果
        };
        return dfs(1);  // 从第 1 个水果开始买，作为递归入口
    }
};