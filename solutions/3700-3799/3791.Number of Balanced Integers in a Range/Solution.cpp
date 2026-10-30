// 3791. 给定范围内平衡整数的数目 / Number of Balanced Integers in a Range
// 核心思路：数位 DP，dfs(pos, diff, lim) 统计偶数位数字和减奇数位数字和为 0 的填法，用 f 数组记忆化后做前缀和差分。
// 复杂度：时间 O(位数 × 差值范围 × 10)，空间 O(位数 × 差值范围)。
class Solution {  // 定义 LeetCode 题解类
public:  // 公开成员
    string num;  // 当前上界数字的字符串形式
    long long f[20][181];  // 记忆化数组：位置与差值（加偏移 base）对应的方案数
    static constexpr int base = 90;  // 差值偏移量，使所有差值都能映射为非负下标

    long long dfs(int pos, int diff, bool lim) {  // 从第 pos 位开始填数，diff 为偶数位和减奇数位和，lim 表示是否贴着上界
        if (pos >= (int) num.size()) {  // 所有数位已经填完
            return diff == 0 ? 1LL : 0LL;  // 差值为 0 才计入答案
        }  // 结束递归边界
        if (!lim && f[pos][diff + base] != -1) {  // 不受上界限制且已算过，直接复用记忆值
            return f[pos][diff + base];  // 返回缓存结果
        }  // 结束缓存判断
        int up = lim ? num[pos] - '0' : 9;  // 当前位可填的上限：贴住上界时取 num[pos]，否则为 9
        long long res = 0;  // 当前状态的方案数
        for (int i = 0; i <= up; ++i) {  // 枚举当前位填入的数字
            res += dfs(pos + 1, diff + i * (pos % 2 == 0 ? 1 : -1), lim && i == up);  // 从左起下标为偶数的位对应题目的奇数位，取正号，反之取负号；同时更新上界限制
        }  // 结束枚举
        if (!lim) {  // 只有不受上界限制的状态才能记忆化
            f[pos][diff + base] = res;  // 记录当前状态的方案数
        }  // 结束记忆化判断
        return res;  // 返回方案数
    }  // 结束 dfs

    long long countBalanced(long long low, long long high) {  // 统计区间 [low, high] 内平衡整数的个数
        if (high < 11) {  // 平衡数至少两位，high 小于 11 时区间内无平衡数
            return 0;  // 直接返回 0
        }  // 结束边界判断
        low = max(low, 11LL);  // 把下界抬到最小的两位数 11

        num = to_string(low - 1);  // 先计算前缀 [1, low-1] 的答案
        memset(f, -1, sizeof(f));  // 清空记忆化数组
        long long a = dfs(0, 0, true);  // 上界为 low-1 时的平衡数个数

        num = to_string(high);  // 再计算前缀 [1, high] 的答案
        memset(f, -1, sizeof(f));  // 重新清空记忆化数组
        long long b = dfs(0, 0, true);  // 上界为 high 时的平衡数个数

        return b - a;  // 两前缀之差即为区间答案
    }  // 结束函数
};  // 结束类
