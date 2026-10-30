// 题目：204. 计数质数（Count Primes）
// 思路：埃拉托斯特尼筛法。从 2 扫到 n-1，遇到仍被标记为质数的 i 就计数，并把 i 的所有倍数标记为合数。
// 时间复杂度：O(n log log n)，调和级数量级；空间复杂度：O(n)，标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPrimes(int n) {  // 统计严格小于 n 的质数个数
        vector<bool> primes(n, true);  // 筛法标记数组：下标 i 为 true 表示 i 尚未被筛掉（暂时视为质数）
        int ans = 0;  // 质数个数计数器
        for (int i = 2; i < n; ++i) {  // 0 和 1 不是质数，所以从 2 开始扫描到 n-1
            if (primes[i]) {  // 仍为 true 说明没被更小的质数筛掉，i 必是质数
                ++ans;  // 计入答案，先计数再把倍数标记掉，不会漏掉 i 本身
                for (int j = i; j < n; j += i) primes[j] = false;  // 把 i 的所有倍数标记为合数；从 i 开始是为了少算一次乘法（i 已计过数，标掉不影响答案）
            }
        }
        return ans;  // 返回小于 n 的质数个数
    }
};