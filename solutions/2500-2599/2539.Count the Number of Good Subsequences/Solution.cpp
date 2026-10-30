// 题目：2539. 好子序列的个数（Count the Number of Good Subsequences）
// 思路：设每个字符出现次数为 cnt[c]，枚举「子序列中各字符出现的统一次数」i；对频率 ≥ i 的字符
// 有 C(cnt[c], i) 种选法再加 1 种不选，全部相乘后减 1（去掉空串）累加。时间 O(26·maxcnt + N log MOD)，空间 O(N)。
int N = 10001;  // 预处理规模：字符串长度上限 10000，多留一位
int MOD = 1e9 + 7;  // 取模常量
long f[10001];  // f[i] 存放 i! mod MOD
long g[10001];  // g[i] 存放 i! 的逆元 mod MOD

long qmi(long a, long k, long p) {  // 快速幂：求 a^k mod p
    long res = 1;  // res 为累乘结果，初始为 1
    while (k != 0) {  // 指数还没归零就继续
        if ((k & 1) == 1) {  // 当前二进制最低位为 1
            res = res * a % p;  // 把这一位对应的 a 乘进答案
        }  // if 结束
        k >>= 1;  // 指数右移一位，处理下一位
        a = a * a % p;  // 底数平方，对应权值翻倍
    }  // 循环结束
    return res;  // 返回 a^k mod p
}  // 函数结束

int init = []() {  // 全局初始化：用立即执行的 lambda 预先把阶乘与逆阶乘算好
    f[0] = 1;  // 0! = 1
    g[0] = 1;  // 0! 的逆元也是 1
    for (int i = 1; i < N; ++i) {  // 从 1 递推到 N-1
        f[i] = f[i - 1] * i % MOD;  // 阶乘递推：f[i] = f[i-1] * i
        g[i] = qmi(f[i], MOD - 2, MOD);  // 由费马小定理，逆元等于 f[i] 的 MOD-2 次幂
    }  // 递推结束
    return 0;  // 返回 0 只是为了让 lambda 有返回值，值本身不使用
}();  // 定义后立刻调用，静态初始化阶段就完成预处理

int comb(int n, int k) {  // 组合数 C(n, k) mod MOD
    return (f[n] * g[k] % MOD) * g[n - k] % MOD;  // 分子乘上两个逆阶乘，相当于整体做除法，全程模运算
}  // 函数结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countGoodSubsequences(string s) {  // 统计 26 个字母的出现次数，花括号初始化全 0
        int cnt[26]{};  // mx 记录最大频率，s 非空所以至少为 1
        int mx = 1;  // 遍历字符串中每个字符
        for (char& c : s) {  // 映射到 0..25 后先自增，再更新最大频率
            mx = max(mx, ++cnt[c - 'a']);  // 统计结束
        }  // ans 存答案，用 long 防止中间乘法溢出
        long ans = 0;  // 枚举子序列中各字符出现的统一次数 i
        for (int i = 1; i <= mx; ++i) {  // x 累乘本轮各字母的选择方案数
            long x = 1;  // 遍历 26 个字母
            for (int j = 0; j < 26; ++j) {  // 出现次数不少于 i 才能从里面挑出 i 个
                if (cnt[j] >= i) {  // C(cnt[j], i) 种选法，加 1 表示该字母一个都不选
                    x = (x * (comb(cnt[j], i) + 1)) % MOD;  // if 结束
                }  // 字母遍历结束
            }  // x 里包含所有字母都不选的空串，减 1 后累加进答案
            ans = (ans + x - 1) % MOD;  // i 枚举结束
        }  // 返回不同好子序列的个数
        return ans;  // 方法结束
    }  // 类定义结束
};