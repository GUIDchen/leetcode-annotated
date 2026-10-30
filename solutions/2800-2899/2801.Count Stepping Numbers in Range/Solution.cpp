// 题目：2801. 统计范围内的步进数字数目（Count Stepping Numbers in Range）
// 思路：数位 DP 记忆化搜索，先求不超过 high 的个数，再求不超过 low-1 的个数，两者相减即为区间答案。
// 时间复杂度：O(D * 10 * 10)，D 为 high 的位数；空间复杂度：O(D * 10)，即记忆化数组 f 的大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSteppingNumbers(string low, string high) {  // low、high：闭区间的下界与上界（用字符串给出，避免数值溢出）
        const int mod = 1e9 + 7;  // 取模常量，答案要对 1e9+7 取模
        int m = high.size();  // m：上界的位数，也是数位 DP 的最大深度
        int f[m + 1][10];  // 记忆化数组：f[pos][pre] 表示还剩 pos 位、前一位数字为 pre 时的方案数（VLA，按实际位数分配）
        memset(f, -1, sizeof(f));  // 全部初始化为 -1，表示「尚未计算」
        string num = high;  // num：当前正在统计的上界字符串，dfs 内部通过闭包读取它

        function<int(int, int, bool, bool)> dfs = [&](int pos, int pre, bool lead, bool limit) {  // pos：当前位；pre：上一位数字；lead：是否仍是前导零；limit：是否贴着上界
            if (pos >= num.size()) {  // 所有数位都已经填完
                return lead ? 0 : 1;  // 全是前导零代表数字 0，题目只统计正整数，故记 0；否则得到一个合法数字
            }
            if (!lead && !limit && f[pos][pre] != -1) {  // 只有不受前导零和上界约束时，状态才能安全复用
                return f[pos][pre];  // 直接返回已经算好的结果
            }
            int up = limit ? num[pos] - '0' : 9;  // 当前位能枚举到的最大值：贴紧上界时受该位限制，否则可以取 0~9
            int ans = 0;  // ans：当前状态的方案数累加器
            for (int i = 0; i <= up; ++i) {  // 枚举当前位填入的数字 i
                if (i == 0 && lead) {  // 仍处于前导零阶段，填 0 不产生实际数值
                    ans += dfs(pos + 1, pre, true, limit && i == up);  // 继续保留前导零标记，上一位数字 pre 保持不变
                } else if (pre == -1 || abs(pre - i) == 1) {  // 这是第一个非零数字，或与上一位相差恰好 1（满足步进条件）
                    ans += dfs(pos + 1, i, false, limit && i == up);  // 进入下一位，上一位更新为 i，并离开前导零状态
                }
                ans %= mod;  // 每次累加后立即取模，防止 int 溢出
            }
            if (!lead && !limit) {  // 只有不受前导零与上界约束的状态才写入记忆化表
                f[pos][pre] = ans;  // 记录该状态的结果，供后续同状态直接复用
            }
            return ans;  // 返回当前状态的方案数
        };

        int a = dfs(0, -1, true, true);  // 统计 [1, high] 内的步进数字个数
        memset(f, -1, sizeof(f));  // 上界字符串要换，先把记忆化结果清空
        for (int i = low.size() - 1; i >= 0; --i) {  // 从个位开始做「字符串减一」，把 low 变成 low-1
            if (low[i] == '0') {  // 该位是 0，需要向高位借位
                low[i] = '9';  // 借位后本位变成 9，继续看更高位
            } else {  // 该位非 0，可以直接减一
                low[i] -= 1;  // 本位减一
                break;  // 减法完成，退出循环
            }
        }
        num = low;  // 把新的上界设为 low-1
        int b = dfs(0, -1, true, true);  // 统计 [1, low-1] 内的步进数字个数
        return (a - b + mod) % mod;  // 前缀和相减得到 [low, high] 的答案，加 mod 防止出现负数
    }
};