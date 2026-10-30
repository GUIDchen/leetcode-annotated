// 题目：2999. 统计强大整数的数目（Count the Number of Powerful Integers）
// 思路：数位 DP。dfs(t) 统计 [1, t] 中「每个数位都不超过 limit 且以 s 结尾」的整数个数，答案 = dfs(finish) - dfs(start - 1)。
// 时间复杂度：O(位数 × 10)，每一位至多枚举 10 个数字；空间复杂度：O(位数)，记忆化数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {  // start / finish：闭区间端点；limit：允许出现的最大数位；s：必须是该整数的后缀
        string t = to_string(start - 1);  // 上界先取 start - 1，用前缀和思想：区间计数 = 不超过 finish 的个数 - 不超过 start - 1 的个数
        long long f[20];  // 记忆化数组：f[pos] 记录「从 pos 位开始、不贴住上界」时的合法方案数，-1 表示尚未计算
        memset(f, -1, sizeof(f));  // 把记忆化数组初始化为 -1

        auto dfs = [&](this auto&& dfs, int pos, int lim) -> long long {  // 递归 lambda：从第 pos 位开始填数；lim 表示前缀是否仍紧贴上界 t
            if (t.size() < s.size()) {  // 上界 t 的位数比后缀 s 还短，任何整数都不可能以 s 结尾
                return 0;  // 无解，返回 0
            }
            if (!lim && f[pos] != -1) {  // 不贴住上界时，状态只取决于 pos，可以复用缓存
                return f[pos];  // 直接返回缓存好的方案数
            }
            if (t.size() - pos == s.size()) {  // 剩余待填位数正好等于后缀长度，剩下的位置只能原样放 s
                return lim ? s <= t.substr(pos) : 1;  // 仍贴上界时要比较 s 与 t 的剩余部分（等长，字典序等价于数值比较）；否则 s 一定可行
            }
            long long ans = 0;  // 累计当前状态的方案数
            int up = min(lim ? t[pos] - '0' : 9, limit);  // 当前位可填的最大数字：贴上界时受 t[pos] 限制，且一律不超过 limit
            for (int i = 0; i <= up; ++i) {  // 枚举当前位的每一种取值
                ans += dfs(pos + 1, lim && i == (t[pos] - '0'));  // 递归填下一位；只有「原来就贴上界」且「本位恰好等于 t[pos]」时，下一位才继续贴上界
            }
            if (!lim) {  // 只有不贴上界的状态才能缓存（贴上界时结果依赖具体的上界 t）
                f[pos] = ans;  // 记录当前状态的方案数
            }
            return ans;  // 返回当前状态的方案数
        };  // 递归 lambda 定义结束

        long long a = dfs(0, true);  // a = [1, start - 1] 内强大整数的个数
        t = to_string(finish);  // 把上界换成 finish，再算一次
        memset(f, -1, sizeof(f));  // 上界改变，旧缓存全部失效，必须清空
        long long b = dfs(0, true);  // b = [1, finish] 内强大整数的个数
        return b - a;  // 两段前缀计数相减，得到 [start, finish] 的答案
    }
};