// 题目：1510. 石子游戏 IV（Stone Game IV）
// 思路：记忆化搜索 + 博弈论：若存在完全平方数 j² 使对手在 i-j² 局面必败，则当前局面必胜；反之必败。
// 时间复杂度：O(n·√n)，每个状态枚举不足 √i 个平方数；空间复杂度：O(n)，记忆化数组 + 递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool winnerSquareGame(int n) {  // n：石子总数，返回先手是否有必胜策略
        vector<int> f(n + 1, -1);  // f[i]：剩 i 颗石子时先手是否必胜；-1 表示该状态还没计算过

        auto dfs = [&](this auto&& dfs, int i) -> bool {  // 记忆化递归：this auto&& dfs 是 C++23 显式对象参数，让 lambda 能递归调用自身
            if (i <= 0) {  // 没有石子可取，当前玩家无法行动
                return false;  // 无法行动即必败
            }  // 结束边界判断
            if (f[i] != -1) {  // 状态已经算过，直接复用记忆化结果
                return f[i];  // 返回之前存下的结论
            }  // 结束记忆化命中判断

            int k = sqrt(i);  // k：不超过 i 的最大平方数根，也就是本次可取的 j 的上界
            for (int j = 1; j <= k; j++) {  // 枚举这一手取走的完全平方数 j*j
                if (!dfs(i - j * j)) {  // 对手在新局面 i - j*j 必败，说明当前玩家存在必胜走法
                    return f[i] = true;  // 边赋值边返回「必胜」，把结果写进记忆化数组
                }  // 结束对手必败的判断
            }  // 结束平方数枚举

            return f[i] = false;  // 所有走法都会让对手必胜，因此当前局面必败
        };  // 结束 lambda 的定义

        return dfs(n);  // 从 n 颗石子的初始局面开始搜索，先手是否获胜
    }  // 结束方法
};  // 结束题解类
