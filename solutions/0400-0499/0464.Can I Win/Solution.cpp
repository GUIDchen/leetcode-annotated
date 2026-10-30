// 题目：464. 我能赢吗（Can I Win）
// 思路：状态压缩 + 记忆化搜索。用 mask 记录已被选走的数字，dfs(mask) 表示当前轮到的人能否必胜。
// 时间复杂度：O(k·2^k)，k 为可选数字个数（不超过 20）；空间复杂度：O(2^k)，记忆化表最多存 2^k 个状态。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canIWin(int maxChoosableInteger, int desiredTotal) {  // maxChoosableInteger：可选数字上界；desiredTotal：累计和达到即胜
        if ((1 + maxChoosableInteger) * maxChoosableInteger / 2 < desiredTotal) {  // 所有可选数字之和都到不了目标，先手必输
            return false;  // 直接返回 false
        }  // 结束特判
        unordered_map<int, int> f;  // 记忆化表：mask 表示已选数字集合，值表示该局面下先手是否必胜
        function<bool(int, int)> dfs = [&](int mask, int s) {  // dfs：mask 为已选数字位图，s 为当前累计和
            if (f.contains(mask)) {  // 该局面算过，直接取缓存结果
                return f[mask];  // 返回缓存值
            }  // 结束缓存判断
            for (int i = 0; i < maxChoosableInteger; ++i) {  // 枚举数字 1..maxChoosableInteger，第 i 位对应数字 i+1
                if (mask >> i & 1 ^ 1) {  // 第 i 位为 0 说明数字 i+1 还没被选走
                    if (s + i + 1 >= desiredTotal || !dfs(mask | 1 << i, s + i + 1)) {  // 本步直接达标，或走完后对手处于必败态，则当前局面必胜
                        return f[mask] = true;  // 记录必胜并返回
                    }  // 结束必胜分支
                }  // 结束可选判断
            }  // 结束枚举
            return f[mask] = false;  // 所有走法都让对手必胜，则当前局面必败
        };  // 结束 lambda
        return dfs(0, 0);  // 从「没有数字被选、累计和为 0」开局
    }  // 结束 canIWin
};  // 结束 Solution 类