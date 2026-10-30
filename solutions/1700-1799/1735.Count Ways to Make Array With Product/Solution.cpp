// 题目：1735. 生成乘积数组的方案数（Count Ways to Make Array With Product）
// 思路：把 k 质因数分解，指数为 c 的质因子用隔板法分到 n 个位置，方案数 C(c+n-1, n-1)；各质因子的方案数相乘即该查询答案，阶乘与逆元预先打表。
// 时间复杂度：预处理 O(N·√N)，每次查询 O(k 的质因子个数)；空间复杂度：O(N) 的阶乘、逆元与质因子表。
int N = 10020;  // 预处理上界，覆盖 n、k 的最大取值
int MOD = 1e9 + 7;  // 取模的模数，防止答案超出范围
long f[10020];  // f[i] 保存 i! 对 MOD 取模的结果
long g[10020];  // g[i] 保存 i! 的模逆元
vector<int> p[10020];  // p[i] 保存 i 的所有质因子指数，例如 12 = 2^2 * 3^1 存成 {2, 1}

long qmi(long a, long k, long p) {  // 快速幂：求 a^k mod p
    long res = 1;  // 累乘结果，初始为 1
    while (k != 0) {  // 指数逐位右移直到为 0
        if ((k & 1) == 1) {  // 当前最低位为 1，这一位的 a 要乘进来
            res = res * a % p;  // 累乘并取模
        }
        k >>= 1;  // 指数右移一位
        a = a * a % p;  // 底数平方，对应下一位的权重
    }
    return res;  // 返回 a^k mod p
}

int init = []() {  // 全局初始化：借 lambda 在程序启动时完成打表
    f[0] = 1;  // 0! = 1
    g[0] = 1;  // 0! 的逆元同样是 1
    for (int i = 1; i < N; ++i) {  // 从小到大预处理每个数
        f[i] = f[i - 1] * i % MOD;  // 用 i-1 的阶乘递推出 i!
        g[i] = qmi(f[i], MOD - 2, MOD);  // 费马小定理：a^(MOD-2) 就是 a 的模逆元
        int x = i;  // 临时变量用于质因数分解，保留 i 本身供数组下标使用
        for (int j = 2; j <= x / j; ++j) {  // 只试除到 sqrt(x)，用 j <= x/j 避免乘法溢出
            if (x % j == 0) {  // j 是 x 的一个质因子
                int cnt = 0;  // 记录该质因子的指数
                while (x % j == 0) {  // 反复除尽这个质因子
                    ++cnt;  // 指数加一
                    x /= j;  // 除去一个 j
                }
                p[i].push_back(cnt);  // 记下“该质因子的指数为 cnt”
            }
        }
        if (x > 1) {  // 除完后剩下的部分大于 1，说明它本身是质数
            p[i].push_back(1);  // 这个质因子的指数为 1
        }
    }
    return 0;  // 返回值只为触发 lambda 执行，类型推导为 int 后赋给全局变量 init
}();

int comb(int n, int k) {  // 组合数 C(n, k)，用阶乘与逆元计算
    return (f[n] * g[k] % MOD) * g[n - k] % MOD;  // 等价于 n! / (k! * (n-k)!)，每步取模防溢出
}

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> waysToFillArray(vector<vector<int>>& queries) {  // queries[i] = {n, k}：长度为 n、乘积为 k 的数组方案数
        vector<int> ans;  // 按查询顺序保存答案
        for (auto& q : queries) {  // 逐个查询处理
            int n = q[0], k = q[1];  // n 是位置数，k 是目标乘积
            long long t = 1;  // 当前查询的方案数，用 long long 避免中间乘法溢出
            for (int x : p[k]) {  // 枚举 k 的每个质因子的指数 x
                t = t * comb(x + n - 1, n - 1) % MOD;  // 隔板法：把 x 个相同质因子分给 n 个位置共 C(x+n-1, n-1) 种
            }
            ans.push_back(t);  // 记录该查询的答案
        }
        return ans;  // 返回所有查询的答案
    }
};