// 题目：1830. 使字符串有序的最少操作次数（Minimum Number of Operations to Make String Sorted）
// 思路：答案等于当前排列在「按字典序排列的全部排列」中的名次；逐位统计更小字母带来的排列数，用阶乘及其逆元去重。
// 时间复杂度：O(26 * n + N)，n 为串长、N 为预处理上界；空间复杂度：O(N)，两个阶乘/逆元数组。
const int N = 3010;  // 预处理上界：题目串长不超过 3000，留出余量
const int MOD = 1e9 + 7;  // 取模常量
long f[N];  // f[i] 表示 i! mod MOD（阶乘表）
long g[N];  // g[i] 表示 i! 的模逆元，用来代替除法

long qmi(long a, int k) {  // 快速幂：计算 a^k mod MOD
    long res = 1;  // 累乘结果
    while (k != 0) {  // 把指数按二进制逐位处理
        if ((k & 1) == 1) {  // 最低位为 1 时把当前底数乘进结果
            res = res * a % MOD;  // 乘入底数并取模
        }  // 分支结束
        k >>= 1;  // 指数右移一位
        a = a * a % MOD;  // 底数平方
    }  // 指数处理完毕
    return res;  // 返回 a^k mod MOD
}  // 函数结束

int init = []() {  // 全局 lambda：程序启动时自动执行一次，完成阶乘与逆元预处理
    f[0] = g[0] = 1;  // 0! = 1，其逆元也是 1
    for (int i = 1; i < N; ++i) {  // 依次预处理每个位置
        f[i] = f[i - 1] * i % MOD;  // f[i] = f[i-1] * i mod MOD
        g[i] = qmi(f[i], MOD - 2);  // 费马小定理：f[i] 的逆元等于 f[i]^(MOD-2)
    }  // 预处理结束
    return 0;  // lambda 返回值（仅用于初始化，无实际意义）
}();  // 立即调用该 lambda，把结果存入全局 init

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int makeStringSorted(string s) {  // s：输入字符串；返回把它变成有序字符串所需的最少操作次数（即当前排列的名次）
        int cnt[26]{};  // cnt：26 个字母各自的剩余出现次数，值初始化为 0
        for (char& c : s) {  // 统计每个字符出现的次数
            ++cnt[c - 'a'];  // 字符 c 对应的下标是 c - 'a'
        }  // 统计结束
        int n = s.size();  // 字符串长度
        long ans = 0;  // ans：累计答案
        for (int i = 0; i < n; ++i) {  // 逐位确定当前排列的名次贡献
            int m = 0;  // m：剩余字符中比 s[i] 小的字母总数
            for (int j = s[i] - 'a' - 1; ~j; --j) {  // 枚举所有比 s[i] 小的字母；j 到 -1 时 ~j 为 0 结束
                m += cnt[j];  // 累加这些字母的剩余出现次数
            }  // 内层枚举结束
            long t = m * f[n - i - 1] % MOD;  // 固定前缀后剩余位置的全排列数为 (n-i-1)!，乘以更小字母的可选个数
            for (int& v : cnt) {  // 除以各字母重复次数的阶乘（乘其逆元实现）
                t = t * g[v] % MOD;  // 乘以 g[v] 并取模
            }  // 循环结束
            ans = (ans + t + MOD) % MOD;  // 累加并取模，+MOD 防止取模后出现负数
            --cnt[s[i] - 'a'];  // 当前字符被固定，从剩余字符中移除一个
        }  // 所有位处理完毕
        return ans;  // 返回最少操作次数
    }  // 方法结束
};  // 类定义结束