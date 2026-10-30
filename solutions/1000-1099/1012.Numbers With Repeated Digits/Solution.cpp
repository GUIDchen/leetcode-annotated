// 题目：1012. 至少有 1 位重复的数字（Numbers With Repeated Digits）
// 思路：数位 DP + 状态压缩。用总数 n 减去「各位数字互不相同」的合法数字个数，mask 记录已用过的数字，每层枚举填入的数字并禁止重复。
// 时间复杂度：O(m * 2^10 * 10)，m 为 n 的十进制位数；空间复杂度：O(m * 2^10)，为记忆化数组的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numDupDigitsAtMostN(int n) {  // n：统计上界，返回 [1, n] 中至少有 1 位重复的数字个数
        string s = to_string(n);  // 把上界转成字符串，便于按位枚举
        int m = s.size();  // 数字的位数，也就是数位 DP 的层数
        int f[m][1 << 10];  // 记忆化数组：f[i][mask] 表示第 i 位、已用数字集合为 mask 时的合法方案数
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示该状态还没被计算过
        auto dfs = [&](this auto&& dfs, int i, int mask, bool lead, bool limit) -> int {  // 递归 lambda：i 当前位数，mask 已用数字的位图，lead 是否仍处于前导零，limit 是否贴着上界
            if (i >= m) {  // 所有位都填完了，递归到底
                return lead ^ 1;  // lead 为真说明整个数是 0，不计入合法数；否则记 1 个合法数
            }
            if (!lead && !limit && f[i][mask] != -1) {  // 不受前导零与上界约束时，状态只由 (i, mask) 决定，可直接复用记忆结果
                return f[i][mask];  // 返回已经算过的结果，避免重复递归
            }
            int up = limit ? s[i] - '0' : 9;  // 当前位的枚举上界：贴着上界就取 n 的这一位，否则可以取到 9
            int ans = 0;  // 累计当前状态下的合法方案数
            for (int j = 0; j <= up; ++j) {  // 枚举当前位填入的数字 j
                if (lead && j == 0) {  // 仍处在前导零阶段且填 0：这个数字还没有真正开始
                    ans += dfs(i + 1, mask, true, limit && j == up);  // 继续保留前导零，mask 不变；填 0 后仍等值于上界，所以 limit 继续看 j == up
                } else if (mask >> j & 1 ^ 1) {  // 该数字尚未使用过（mask 的第 j 位为 0），填它才不会产生重复
                    ans += dfs(i + 1, mask | (1 << j), false, limit && j == up);  // 把 j 记入已用集合，进入下一位；只有贴着上界时才可能继续受限
                }
            }
            if (!lead && !limit) {  // 只有无前导零、无上界约束的状态才可以记忆化
                f[i][mask] = ans;  // 存下结果，供后续相同状态复用
            }
            return ans;  // 返回当前状态的合法方案数
        };  // lambda 定义结束
        return n - dfs(0, 0, true, true);  // 用总数 n 减去「各位互不相同」的个数，得到至少有 1 位重复的数字个数
    }
};
