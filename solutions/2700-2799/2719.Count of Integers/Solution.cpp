// 题目：2719. 统计整数数目（Count of Integers）
// 思路：数位 DP 求前缀和，答案 = f(num2) - f(num1 - 1)；dfs(pos, 数位和, 是否贴上界) 记忆化搜索。
// 时间复杂度：O(位数 × max_sum × 10)；空间复杂度：O(位数 × max_sum)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int count(string num1, string num2, int min_sum, int max_sum) {  // 返回 [num1, num2] 内数位和落在 [min_sum, max_sum] 的整数个数
        const int mod = 1e9 + 7;  // 题目要求的取模常量
        int f[23][220];  // 记忆化数组：f[pos][s] 表示处理到第 pos 位、数位和为 s 时的方案数，-1 表示未计算
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示所有状态都还没算过
        string num = num2;  // 先以上界 num2 作为数位 DP 的数字串

        function<int(int, int, bool)> dfs = [&](int pos, int s, bool limit) -> int {  // 记忆化搜索：pos 当前位，s 已累计的数位和，limit 表示前缀是否紧贴上界
            if (pos >= num.size()) {  // 递归出口：num 的所有位都已经填完
                return s >= min_sum && s <= max_sum ? 1 : 0;  // 数位和落在区间内就是 1 个合法数，否则计 0
            }
            if (!limit && f[pos][s] != -1) {  // 不贴上界时状态可复用：算过就直接返回缓存值
                return f[pos][s];  // 返回记忆化结果
            }
            int up = limit ? num[pos] - '0' : 9;  // 当前位能填的最大数字：贴上界时不能超过 num 的对应位，否则可取 9
            int ans = 0;  // 累计当前状态的方案数
            for (int i = 0; i <= up; ++i) {  // 枚举当前位填入的数字 i
                ans += dfs(pos + 1, s + i, limit && i == up);  // 递归下一位；只有前缀一直贴上界且当前位取到上界时 limit 才继续为真
                ans %= mod;  // 每加一次就取模，防止答案溢出
            }
            if (!limit) {  // 只有不贴上界的状态才能被记忆化复用
                f[pos][s] = ans;  // 记录当前状态的方案数
            }
            return ans;  // 返回本层方案数
        };  // lambda 定义结束，之后可当作函数调用

        int a = dfs(0, 0, true);  // 统计 0..num2 中的合法个数
        for (int i = num1.size() - 1; ~i; --i) {  // 从个位向高位做字符串减一，把下界 num1 变成 num1 - 1
            if (num1[i] == '0') {  // 当前位是 0，需要向高位借位
                num1[i] = '9';  // 借位后本位变成 9
            } else {  // 当前位不是 0，可以直接减一并停止
                num1[i] -= 1;  // 本位减一
                break;  // 没有借位，减一完成，跳出循环
            }
        }
        num = num1;  // 换下界继续用同一个 dfs 计算
        memset(f, -1, sizeof(f));  // 下界换了，清空上一轮的记忆化结果，避免状态串用
        int b = dfs(0, 0, true);  // 统计 0..(num1-1) 中的合法个数
        return (a - b + mod) % mod;  // 前缀和相减得到区间内的答案；+mod 防止减法出现负数
    }
};