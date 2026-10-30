// 题目：2827. 范围中美丽整数的数目（Number of Beautiful Integers in the Range）
// 思路：数位 DP + 记忆化，dfs(pos, mod, diff, lead, limit) 统计满足「数字和模 k 为 0 且奇数位个数等于偶数位个数」的后缀方案数，答案用前缀计数相减。
// 时间复杂度：O(位数 × k × 位数)，状态数约 位数×k×(2×位数) 且每位枚举 10 个数字；空间复杂度：O(位数 × k × 位数)，即记忆化数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfBeautifulIntegers(int low, int high, int k) {  // low/high：闭区间左右端点；k：数字和必须能被它整除；返回区间内美丽整数的个数
        int f[11][21][21];  // 记忆化数组：f[pos][mod][diff]，pos 最多 10 位、余数最多 20、奇偶差偏移 10 后最多 20
        memset(f, -1, sizeof(f));  // 全部置为 -1，表示这些状态还没有被计算过
        string s = to_string(high);  // 把上界转成字符串，方便按位取数字

        function<int(int, int, int, bool, bool)> dfs = [&](int pos, int mod, int diff, bool lead, bool limit) {  // 定义递归的数位 DP：pos 当前位，mod 已选数字模 k 的余数，diff 奇偶个数差（偏移 10 避免负数），lead 是否仍处于前导零，limit 是否贴着上界
            if (pos >= s.size()) {  // 递归终点：所有位都已经填完
                return mod == 0 && diff == 10 ? 1 : 0;  // 余数为 0 且奇偶个数相等（diff 回到偏移 10）时才算一个美丽整数
            }  // 终点判断结束
            if (!lead && !limit && f[pos][mod][diff] != -1) {  // 只有同时不受前导零和上界约束的状态才可复用，命中缓存就直接返回
                return f[pos][mod][diff];  // 返回之前算好的结果
            }  // 记忆化分支结束
            int ans = 0;  // 统计当前状态下合法后缀的个数
            int up = limit ? s[pos] - '0' : 9;  // 当前位的取值上限：贴着上界就只能取到 s[pos]，否则可以取到 9
            for (int i = 0; i <= up; ++i) {  // 枚举当前位放哪个数字
                if (i == 0 && lead) {  // 仍在前导零阶段：这一位不算真实数字
                    ans += dfs(pos + 1, mod, diff, true, limit && i == up);  // 保持 lead 与余数、奇偶差不变，limit 取决于本位是否顶到上限
                } else {  // 本位是真实数字，需要更新余数与奇偶差
                    int nxt = diff + (i % 2 == 1 ? 1 : -1);  // 奇数让奇偶差 +1，偶数让奇偶差 -1
                    ans += dfs(pos + 1, (mod * 10 + i) % k, nxt, false, limit && i == up);  // 进入下一位：余数按十进制左移一位后加上 i 再对 k 取模，lead 从此结束
                }  // 本位枚举结束
            }  // 所有取值枚举完毕
            if (!lead && !limit) {  // 只有不受约束的状态才值得记忆化
                f[pos][mod][diff] = ans;  // 记下结果，供后续重复调用复用
            }  // 记忆化写入结束
            return ans;  // 返回当前状态统计到的个数
        };  // 递归 lambda 定义结束（用 std::function 包住以便在内部自调用）

        int a = dfs(0, 0, 10, true, true);  // 统计 [0, high] 中的美丽整数个数：余数 0、奇偶差偏移 10、处于前导零且贴上界
        memset(f, -1, sizeof(f));  // 清空记忆化数组，下面统计另一个前缀要重新算
        s = to_string(low - 1);  // 换成 low - 1，用前缀计数相减得到区间答案
        int b = dfs(0, 0, 10, true, true);  // 统计 [0, low-1] 中的美丽整数个数
        return a - b;  // 区间 [low, high] 的答案等于两个前缀计数之差
    }  // 方法结束
};  // 类定义结束