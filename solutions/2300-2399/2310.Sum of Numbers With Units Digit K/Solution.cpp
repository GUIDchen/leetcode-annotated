// 题目：2310. 个位数字为 K 的整数之和（Sum of Numbers With Units Digit K）
// 思路：取 i 个加数时个位之和是 k·i，剩余部分 num − k·i 必须是 10 的倍数；从小到大枚举 i，第一个可行者即最少个数。
// 时间复杂度：O(num)，最坏枚举 num 次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumNumbers(int num, int k) {  // num 是目标和，k 是每个加数要求的个位数字
        if (num == 0) return 0;  // num 为 0 时一个数都不用取，最少个数就是 0
        for (int i = 1; i <= num; ++i) {  // 枚举加数个数 i，从小到大找，第一个可行的即为最优
            int t = num - k * i;  // t 是 num 扣掉 i 个个位数字后的部分，只能由十位及以上贡献
            if (t >= 0 && t % 10 == 0) return i;  // t 非负且是 10 的倍数，说明这些数能凑出 num，返回当前最小个数
        }
        return -1;  // 枚举完仍凑不出，返回 -1
    }
};  // 类定义结束，最后一个分号收尾