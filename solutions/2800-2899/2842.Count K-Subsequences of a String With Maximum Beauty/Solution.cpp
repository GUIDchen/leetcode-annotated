// 题目：2842. 统计一个字符串的 k 子序列美丽值最大的数目（Count K-Subsequences of a String With Maximum Beauty）
// 思路：一个子序列的美丽值只取决于选中的字符种数，故只选频次最大的 k 种字母；频次降序排序后，对最后一个并列频次用组合数挑选，再乘各自的频次。
// 时间复杂度：O(n + 26 log 26 + k^2)，统计频次、排序与杨辉三角递推；空间复杂度：O(k^2)，组合数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countKSubsequencesWithMaxBeauty(string s, int k) {  // s 是原字符串，k 是子序列中要求的字符种数
        int f[26]{};  // 每个字母在 s 中出现的次数，全部初始化为 0
        int cnt = 0;  // s 中不同字母的种数
        for (char& c : s) {  // 遍历字符串统计每个字母的频次
            if (++f[c - 'a'] == 1) {  // 该字母第一次出现，说明遇到了一种新字母
                ++cnt;  // 不同字母种数加 1
            }
        }
        if (cnt < k) {  // 不同字母不足 k 种，凑不出长度为 k 的子序列
            return 0;  // 方案数为 0
        }
        vector<int> vs(cnt);  // 只收集出现过的字母的频次
        for (int i = 0, j = 0; i < 26; ++i) {  // 枚举 26 个小写字母
            if (f[i]) {  // 该字母在 s 中出现过
                vs[j++] = f[i];  // 把它的频次放入数组
            }
        }
        sort(vs.rbegin(), vs.rend());  // 频次从大到小排序，优先选频次高的字母
        const int mod = 1e9 + 7;  // 结果需要对 1e9+7 取模
        long long ans = 1;  // 方案数，用乘法逐步累积
        int val = vs[k - 1];  // 被选中的字母中频次最小的那个值，可能并列
        int x = 0;  // 频次恰好等于 val 的字母个数
        for (int v : vs) {  // 统计并列在分界线上的字母个数
            x += v == val;  // 相等则累加，不等则加 0
        }
        for (int v : vs) {  // 处理频次严格大于 val 的字母
            if (v == val) {  // 遇到分界线上的频次就停止
                break;  // 退出循环，剩下的交给组合数处理
            }
            --k;  // 这类字母必须入选，待选名额减 1
            ans = ans * v % mod;  // 每个字母可在各自频次个位置中任选一处贡献，累乘
        }
        int c[x + 1][x + 1];  // 组合数表，用杨辉三角递推 C(i, j)
        memset(c, 0, sizeof(c));  // 先把整张表清零
        for (int i = 0; i <= x; ++i) {  // 逐行递推
            c[i][0] = 1;  // 任意 i 选 0 个的方案数都是 1
            for (int j = 1; j <= i; ++j) {  // 只算 j <= i 的部分
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;  // 杨辉三角递推公式，同时取模
            }
        }
        auto qpow = [&](long long a, int n) {  // 快速幂：计算 a^n mod mod
            long long ans = 1;  // 累积结果
            for (; n; n >>= 1) {  // 按二进制位从低到高处理指数，指数为 0 时停止
                if (n & 1) {  // 当前二进制位为 1，需要把当前底数乘进结果
                    ans = ans * a % mod;  // 累乘并取模
                }
                a = a * a % mod;  // 底数平方，为下一位做准备
            }
            return ans;  // 返回 a^n mod mod
        };
        ans = (ans * c[x][k] % mod) * qpow(val, k) % mod;  // 从 x 个并列字母中选 k 个，每个有 val 种位置选择，连乘取模
        return ans;  // 返回美丽值最大的 k 子序列个数
    }
};