// 题目：877. 石子游戏（Stone Game）
// 核心思路：区间博弈加记忆化搜索，f[i][j] 表示在区间 [i, j] 上先手能领先对手的最大分差，取走一端后减去对手在剩余区间的最优分差。
// 时间复杂度：O(n^2)，共 O(n^2) 个区间、每个区间 O(1) 转移；空间复杂度：O(n^2)，记忆化表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool stoneGame(vector<int>& piles) {  // piles：每堆石子数量，两人轮流从剩下的区间两端取走一堆，问先手是否必胜
        int n = piles.size();  // 区间长度，也是记忆化表的边长
        int f[n][n];  // 记忆化表：f[i][j] 表示区间 [i, j] 上先手能领先对手的分差（变长数组是 GNU 扩展）
        memset(f, 0, sizeof(f));  // 全部清零，0 同时充当「该状态还没算过」的哨兵
        auto dfs = [&](this auto&& dfs, int i, int j) -> int {  // 递归 lambda：this auto&& dfs 让 lambda 能把自身作为参数递归调用
            if (i > j) {  // 区间为空，没有石子可取
                return 0;  // 分差为 0
            }  // if 结束
            if (f[i][j]) {  // 该状态已经算过（分差非 0）
                return f[i][j];  // 直接返回缓存值，避免重复搜索同一区间
            }  // if 结束
            return f[i][j] = max(piles[i] - dfs(i + 1, j), piles[j] - dfs(i, j - 1));  // 取左端或取右端，减去对手在剩余区间上的领先分差；两人都最优，所以取较大者并写入缓存
        };  // dfs 定义结束
        return dfs(0, n - 1) > 0;  // 整个区间上的先手分差为正即必胜（本题还可用数学结论直接返回 true）
    }  // stoneGame 结束
};  // Solution 类结束
