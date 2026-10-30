// 题目：1220. 统计元音字母序列的数目（Count Vowels Permutation）
// 思路：按题目给定的元音相邻规则做 DP，f[c] 表示以元音 c 结尾、当前长度的序列数，逐层滚动更新并取模。
// 时间复杂度：O(n)，每层只有常数次加法；空间复杂度：O(1)，只用两个长度为 5 的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countVowelPermutation(int n) {  // n：序列长度，1 <= n <= 2*10^4
        using ll = long long;  // 起别名，保证累加过程不会溢出 int
        vector<ll> f(5, 1);  // 长度 1 时每种元音结尾各 1 种；下标 0..4 依次对应 a,e,i,o,u
        const int mod = 1e9 + 7;  // 题目要求的取模值
        for (int i = 1; i < n; ++i) {  // 从长度 1 逐层递推到长度 n
            vector<ll> g(5);  // 存放长度 i+1 的状态，避免原地更新时互相污染
            g[0] = (f[1] + f[2] + f[4]) % mod;  // 只有 e/i/u 后面能接 a，所以这些结尾的序列数相加
            g[1] = (f[0] + f[2]) % mod;  // 只有 a/i 后面能接 e
            g[2] = (f[1] + f[3]) % mod;  // 只有 e/o 后面能接 i
            g[3] = f[2];  // 只有 i 后面能接 o，所以只继承 f[2]
            g[4] = (f[2] + f[3]) % mod;  // 只有 i/o 后面能接 u
            f = move(g);  // 滚动：把新一层状态换给 f，move 省去一次拷贝
        }  // 递推结束
        return accumulate(f.begin(), f.end(), 0LL) % mod;  // 所有元音结尾的序列数求和后再取模；0LL 保证用 long long 累加
    }  // 方法结束
};  // 类定义结束