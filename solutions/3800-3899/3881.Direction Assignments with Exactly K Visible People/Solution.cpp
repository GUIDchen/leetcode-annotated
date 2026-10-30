// 3881. 恰好看到 K 个人的方向选择 / Direction Assignments with Exactly K Visible People
// 核心思路：预处理阶乘与阶乘逆元以求组合数，枚举左侧可见人数 a，右侧可见 b = k - a，两侧朝向各计一种。
// 复杂度：时间 O(N + k)（预处理 O(N)，单次查询 O(k)），空间 O(N)。
int N = 100001;  // 预处理规模上限
int MOD = 1e9 + 7;  // 取模常量 1e9 + 7
long long f[100001];  // 阶乘表
long long g[100001];  // 阶乘逆元表

long long qmi(long long a, long long k, long long p) {  // 快速幂：求 a^k mod p
    long long res = 1;  // 幂结果初始为 1
    while (k != 0) {  // 按二进制拆分指数 k
        if ((k & 1) == 1) {  // 当前最低位为 1
            res = res * a % p;  // 把当前底数乘入结果
        }  // if 分支结束
        k >>= 1;  // 指数右移一位
        a = a * a % p;  // 底数平方并取模
    }  // 快速幂循环结束
    return res;  // 返回 a^k mod p
}  // qmi 函数结束

int init = []() {  // 静态初始化：预处理阶乘与阶乘逆元
    f[0] = 1;  // 0! = 1
    g[0] = 1;  // 0! 的逆元为 1
    for (int i = 1; i < N; ++i) {  // 递推计算所有阶乘
        f[i] = f[i - 1] * i % MOD;  // i! = (i-1)! * i
        g[i] = qmi(f[i], MOD - 2, MOD);  // 由费马小定理求 i! 的逆元
    }  // 预处理循环结束
    return 0;  // 返回值仅用于触发初始化
}();  // 初始化 lambda 立即调用结束

long long comb(int n, int k) {  // 组合数 C(n, k)
    return f[n] * g[k] % MOD * g[n - k] % MOD;  // 阶乘与两个逆元连乘并取模
}  // comb 函数结束

class Solution {  // 定义题解类
public:  // 公有接口
    int countVisiblePeople(int n, int pos, int k) {  // 统计恰好看到 k 个人的方向方案数
        int l = pos, r = n - pos - 1;  // 左侧与右侧可用的人数
        long long ans = 0;  // 方案数累加器

        for (int a = 0; a <= min(k, l); ++a) {  // 枚举左侧被看到的人数 a
            int b = k - a;  // 右侧被看到的人数 b
            if (b <= r) {  // 右侧人数可行才计入
                ans = (ans + 2 * comb(l, a) % MOD * comb(r, b) % MOD) % MOD;  // 左右两种朝向各一种，累加组合数乘积
            }  // if 分支结束
        }  // 枚举结束
        return ans;  // 返回方案总数
    }  // 方法结束
};  // 类定义结束
