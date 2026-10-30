// 题目：3945. 计算数字频率得分（Digit Frequency Score）
// 思路：反复取 n 的个位数字累加，再把 n 除以 10 丢掉个位，直到 n 变成 0。
// 复杂度：时间 O(log n)（十进制位数），空间 O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int digitFrequencyScore(int n) {  // n：待处理的正整数，返回它十进制各位数字之和
        int ans = 0;  // ans 累加每一位上的数字
        for (; n > 0; n /= 10) {  // 每轮处理一个数位：n 为 0 时结束，步进是 n /= 10
            ans += n % 10;  // n % 10 取出当前最低位数字并累加
        }
        return ans;  // 返回所有数位之和
    }
};