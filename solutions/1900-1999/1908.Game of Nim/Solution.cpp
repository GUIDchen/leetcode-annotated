// 题目：1908. Nim 游戏 II（Game of Nim）🔒
// 思路：博弈 DP + 记忆化。把各堆数量按八进制编码成整数作为状态，枚举「取哪堆、取几个」，只要存在一步让对手必败则当前必胜。
// 时间复杂度：O(状态数 × 堆数 × 每堆石子数)；空间复杂度：O(状态数)，记忆化表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool nimGame(vector<int>& piles) {  // piles：每堆石子的数量
        unordered_map<int, int> memo;  // 记忆化表：局面编码 → 该局面下先手是否必胜
        int p[8] = {1};  // p[i] = 8^i；每堆最多 7 个石子、最多 8 堆，所以可用八进制把各堆数量拼成一个整数
        for (int i = 1; i < 8; ++i) {  // 预处理 8 的幂
            p[i] = p[i - 1] * 8;  // 逐次乘 8 递推
        }  // 结束预处理循环
        auto f = [&](vector<int>& piles) {  // lambda：把当前各堆石子数编码成唯一的整数状态
            int st = 0;  // 状态编码，初始为 0
            for (int i = 0; i < piles.size(); ++i) {  // 按顺序逐堆累加
                st += piles[i] * p[i];  // 第 i 堆乘以 8^i，保证不同堆的顺序信息不会丢失
            }  // 结束累加循环
            return st;  // 返回编码后的状态
        };  // lambda 结束
        function<bool(vector<int>&)> dfs = [&](vector<int>& piles) {  // 递归函数：当前局面轮到先手时是否必胜
            int st = f(piles);  // 先把当前局面编码
            if (memo.count(st)) {  // 算过就直接查表，避免重复搜索
                return memo[st];  // 返回记忆化结果
            }  // 结束查表分支
            for (int i = 0; i < piles.size(); ++i) {  // 枚举取哪一堆
                for (int j = 1; j <= piles[i]; ++j) {  // 枚举从该堆取走 j 个（Nim 规则允许一次取任意正数）
                    piles[i] -= j;  // 走出这一步：把该堆石子数减 j
                    if (!dfs(piles)) {  // 对手在新局面下必败，说明当前局面必胜
                        piles[i] += j;  // 返回前先恢复现场，保证 piles 不被破坏
                        return memo[st] = true;  // 记录并返回「必胜」
                    }  // 结束必胜分支
                    piles[i] += j;  // 这一步不能取胜，恢复现场后继续尝试别的取法
                }  // 结束取石子数循环
            }  // 结束选堆循环
            return memo[st] = false;  // 所有走法都会让对手必胜，因此当前局面必败
        };  // lambda 结束
        return dfs(piles);  // 从初始局面开始判断先手胜负
    }  // 结束题解方法
};  // 结束题解类