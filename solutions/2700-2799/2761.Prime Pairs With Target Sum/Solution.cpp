// 题目：2761. 和等于目标值的质数对（Prime Pairs With Target Sum）
// 思路：先用埃氏筛标记 [2, n - 1] 内的质数，再在 x <= n / 2 的范围枚举 x，检查 n - x 是否也是质数，是就记录 (x, n - x)。
// 时间复杂度：O(n log log n)，筛法加上 O(n) 的枚举；空间复杂度：O(n)，需要一个长度 n 的质数标记数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findPrimePairs(int n) {  // n 是目标和，返回所有和为 n 的质数对
        bool primes[n];  // primes[i] 标记 i 是否为质数；这里沿用了 doocs 的变长数组写法（GCC 扩展，空间开在栈上）
        memset(primes, true, sizeof(primes));  // 按字节把整块内存置 1；bool 只占一个字节，所以等价于全部初始化为 true
        for (int i = 2; i < n; ++i) {  // 埃氏筛：i 从 2 扫到 n - 1
            if (primes[i]) {  // i 仍被标记为质数，说明它没有被更小的质数筛掉
                for (int j = i + i; j < n; j += i) {  // 从 i 的两倍开始，步长为 i，把所有 i 的倍数标成合数
                    primes[j] = false;  // i * k 一定不是质数
                }  // 当前质数 i 的倍数全部标记完毕
            }  // 本轮的质数判断结束
        }  // 筛法完成，primes 中只剩下质数为 true
        vector<vector<int>> ans;  // ans 收集所有满足 x + y = n 的质数对
        for (int x = 2; x <= n / 2; ++x) {  // x 只枚举到 n / 2，避免把 (x, y) 和 (y, x) 重复统计
            int y = n - x;  // 另一个加数 y 由 n - x 唯一确定
            if (primes[x] && primes[y]) {  // x 和 y 都要在筛表范围（x >= 2、y <= n - 2）内且都是质数
                ans.push_back({x, y});  // 找到一组合法质数对，按 x 递增的顺序放入答案
            }  // 当前 x 判断结束
        }  // 所有可能的较小加数都枚举完了
        return ans;  // 返回按第一个数递增排列的质数对
    }  // 方法结束
};  // 类定义结束