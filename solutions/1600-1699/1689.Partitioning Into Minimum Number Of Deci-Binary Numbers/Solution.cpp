// 题目：1689. 十-二进制数的最少数目（Partitioning Into Minimum Number Of Deci-Binary Numbers）
// 思路：每个十-二进制数每一位非 0 即 1，数字串中最大的那一位决定了最少需要的数的个数。
// 时间复杂度：O(n)，遍历一遍数字串；空间复杂度：O(1)，只用一个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minPartitions(string n) {  // n：十进制数字串
        int ans = 0;  // ans 记录数字串中出现过的最大字符数字
        for (char& c : n) {  // 按引用遍历每个数字字符
            ans = max(ans, c - '0');  // 字符减 '0' 得到数值，再与当前最大值取较大者
        }  // 遍历循环结束
        return ans;  // 最大数字即最少需要的十-二进制数个数
    }  // 方法结束
};  // 类结束