// 题目：1411. 给 N x 3 网格图涂色的方案数（Number of Ways to Paint N × 3 Grid）
// 思路：按每行三格的颜色模式分类递推：ABA 型与 ABC 型，用 2x2 转移矩阵逐行累加。
// 时间复杂度：O(n)，只做 n-1 次常数级递推；空间复杂度：O(1)，仅保存两行的两个计数。
using ll = long long;  // 给 long long 起短别名，乘法中间结果不会溢出 int

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numOfWays(int n) {  // n 是网格行数，返回满足相邻格颜色不同的合法涂色方案数
        int mod = 1e9 + 7;  // 题目要求答案对 1e9+7 取模
        ll f0 = 6, f1 = 6;  // 第一行两类方案各 6 种：f0 为首尾同色(ABA)，f1 为三色互异(ABC)
        while (--n) {  // 每循环一次多推一行，共需推 n-1 次
            ll g0 = (f0 * 3 + f1 * 2) % mod;  // 新行的 ABA 型：由上一行 ABA 型 3 种、ABC 型 2 种转移而来
            ll g1 = (f0 * 2 + f1 * 2) % mod;  // 新行的 ABC 型：由上一行 ABA 型 2 种、ABC 型 2 种转移而来
            f0 = g0;  // 用刚算出的新值覆盖上一行
            f1 = g1;  // 同上，两组状态一起滚动更新
        }  // 结束逐行递推
        return (int) (f0 + f1) % mod;  // 两类方案数相加再取模，最后转回 int 返回
    }  // 结束题解方法
};  // 结束题解类