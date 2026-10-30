// 题目：2427. 公因子的数目（Number of Common Factors）
// 核心思路：a 与 b 的公因子一定是最大公因数 g = gcd(a, b) 的因子，因此只需枚举 1..g，统计能整除 g 的个数。
// 时间复杂度：O(g)，最坏 O(min(a, b))；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int commonFactors(int a, int b) {  // a、b 是两个正整数，返回它们的公因子数目
        int g = gcd(a, b);  // 最大公因数 g：任何公因子都必然整除 g
        int ans = 0;  // 公因子计数器
        for (int x = 1; x <= g; ++x) {  // 枚举 1..g，g 的每一个因子就是 a、b 的一个公因子
            ans += g % x == 0;  // 布尔表达式为真时相当于加 1，省掉一个 if 分支
        }  // 枚举结束
        return ans;  // 返回公因子的数目
    }  // 方法结束
};  // 类定义结束