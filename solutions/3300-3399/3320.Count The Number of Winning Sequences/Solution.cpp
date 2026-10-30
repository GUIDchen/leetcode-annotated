// 题目：3320. 统计能获胜的出招序列数（Count The Number of Winning Sequences）
// 思路：记忆化搜索。dfs(i, j, k) 表示已出 i 招、Bob 净胜分记为 j + n、上一招为 k 的方案数；每轮枚举与上一招不同的三招之一并用 calc 累加 Bob 的得分，
// 剩余轮数已追不上当前领先分时剪枝。时间复杂度：O(n^2 · 3 · 3)，n 为序列长度；空间复杂度：O(n^2 · 4)，即记忆化表大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countWinningSequences(string s) {  // s：Bob 的出招序列
        int n = s.size();  // 序列长度，也就是总轮数
        int d[26]{};  // 字母到下标的映射表，'A' 为原点；'F' 落在 0 号位
        d['W' - 'A'] = 1;  // 'W' 映射为 1
        d['E' - 'A'] = 2;  // 'E' 映射为 2
        int span = n + n + 1;  // Bob 净胜分范围是 [-n, n]，统一加偏移 n 存成非负下标，共 2n+1 种
        vector<int> f(1LL * n * span * 4, -1);  // 记忆化表：下标 i*span*4 + j*4 + k，初始 -1 表示该状态尚未计算
        auto at = [&](int i, int j, int k) -> int& { return f[(1LL * i * span + j) * 4 + k]; };  // 把三维状态压成一维下标并返回引用，方便直接读和写
        auto calc = [](int x, int y) -> int {  // calc(x, y)：Bob 出 x、我出 y 时 Bob 的得分（1 表示 Bob 赢，0 平，-1 表示我赢）
            if (x == y) {  // 出招相同即为平局
                return 0;  // 平局双方都不得分
            }
            if (x < y) {  // 下标小的招式对下标大的招式，只有下面一种例外
                return x == 0 && y == 2 ? 1 : -1;  // F(0) 克 E(2)，Bob 得 1 分；其余情况 Bob 失分
            }
            return x == 2 && y == 0 ? -1 : 1;  // E(2) 被 F(0) 克时 Bob 失分；其余大下标招式胜出得 1 分
        };
        const int mod = 1e9 + 7;  // 取模常量，答案对 1e9+7 取余
        auto dfs = [&](this auto&& dfs, int i, int j, int k) -> int {  // i：已出到第 i 轮；j：Bob 得分 + n；k：我上一轮出的招式（3 表示还没出过）
            if (n - i <= j - n) {  // 剩余轮数 <= 当前 Bob 的领先分：最多只能追平，反超不了
                return 0;  // 剪枝：这类分支不可能让我获胜，直接贡献 0 种方案
            }
            if (i >= n) {  // 已出完全部 n 轮
                return j - n < 0 ? 1 : 0;  // 最终 Bob 净胜分为负（j - n < 0），说明我赢了，才算一种方案
            }
            if (at(i, j, k) != -1) {  // 该状态算过就直接复用
                return at(i, j, k);  // 返回记忆化结果
            }
            int ans = 0;  // 累计当前状态下的方案数
            for (int l = 0; l < 3; ++l) {  // 枚举本轮我出的招式 0 / 1 / 2
                if (l == k) {  // 不能连续两轮出同一招
                    continue;  // 跳过与上一轮相同的招式
                }
                ans = (ans + dfs(i + 1, j + calc(d[s[i] - 'A'], l), l)) % mod;  // 递归下一轮：把 Bob 本轮得分并入偏移量，结果累加后取模
            }
            return at(i, j, k) = ans;  // 结果写入记忆化表并返回
        };
        return dfs(0, n, 3);  // 从第 0 轮、Bob 净胜分 0（偏移 n）、无上一招开始搜索
    }
};
