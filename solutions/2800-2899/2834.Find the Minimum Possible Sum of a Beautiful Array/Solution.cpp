// 题目：2834. 找出美丽数组的最小和（Find the Minimum Possible Sum of a Beautiful Array）
// 思路：要让和最小就从 1 开始贪心取数。取 m = target / 2，则 1..m 之间任意两个不同数之和都 <= target（target 为偶数时 m + m 虽然等于 target，但集合里只有一个 m），全部可以选；而 m+1..target-1 中的每个数都会与前面某个已选数凑成 target，必须整段跳过，于是后续从 target 开始继续取。
// 时间复杂度：O(1)，只有常数次算术运算；空间复杂度：O(1)，只用了几个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumPossibleSum(int n, int target) {  // n：数组长度；target：任意两数之和都不能等于它
        const int mod = 1e9 + 7;  // 结果需要对 1e9+7 取模
        int m = target / 2;  // 可安全选取的前缀上界：1..m 中任意两数之和都不超过 target
        if (n <= m) {  // 需要的个数没超过安全前缀
            return (1LL + n) * n / 2 % mod;  // 直接取 1..n，等差数列求和；用 1LL 避免乘法溢出
        }
        long long a = (1LL + m) * m / 2 % mod;  // 第一部分：1..m 全部取走时的和
        long long b = (1LL * target + target + n - m - 1) * (n - m) / 2 % mod;  // 第二部分：从 target 起连续取 (n-m) 个数，即 target..(target+n-m-1) 的和
        return (a + b) % mod;  // 两段相加再取模就是最小和
    }
};