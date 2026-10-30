// 题目：1175. 质数排列（Prime Arrangements）
// 思路：1..n 中质数有 cnt 个，质数只能与质数互换位置，所以答案是 cnt! × (n-cnt)!，用埃氏筛统计 cnt 并边乘边取模。
// 时间复杂度：O(n log log n)，埃氏筛加阶乘；空间复杂度：O(n)，筛法使用的布尔数组。
using ll = long long;  // 类型别名：阶乘结果会超过 int，所以统一用 64 位整数
const int MOD = 1e9 + 7;  // 取模常量，题目要求结果对 1e9+7 取模

class Solution {  // 题解类
public:
    int numPrimeArrangements(int n) {  // 求质数排布数
        int cnt = count(n);  // 先统计 1..n 中有多少个质数
        ll ans = f(cnt) * f(n - cnt);  // 质数、合数各自内部全排列，方案数相乘
        return (int) (ans % MOD);  // 取模后转回 int 返回
    }  // 方法结束

    ll f(int n) {  // 计算 n 的阶乘并取模
        ll ans = 1;  // 累乘结果从 1 开始
        for (int i = 2; i <= n; ++i) ans = (ans * i) % MOD;  // 逐个相乘，边乘边取模防止溢出
        return ans;  // 返回阶乘结果
    }  // 方法结束

    int count(int n) {  // 用埃氏筛统计 1..n 中质数的个数
        vector<bool> primes(n + 1, true);  // 布尔数组标记每个数是否为质数，先全部当作是
        int cnt = 0;  // 质数计数器
        for (int i = 2; i <= n; ++i) {  // 从 2 开始向下筛
            if (primes[i]) {  // i 仍然是质数
                ++cnt;  // 质数个数加一
                for (int j = i + i; j <= n; j += i) primes[j] = false;  // 把 i 的所有倍数标记为非质数
            }  // if 结束
        }  // for 结束
        return cnt;  // 返回质数个数
    }  // 方法结束
};  // 类定义结束