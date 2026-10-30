// 题目：3106. 满足距离约束且字典序最小的字符串（Lexicographically Smallest String After Operations With Constraint）
// 思路：字典序优先看靠左的字符，于是从左到右贪心：每位都尝试换成比自己小的字符中最小的那个，只要环形距离不超过剩余预算 k 就换掉并扣减预算。
// 时间复杂度：O(n * 26) 即 O(n)，每位最多试 26 个候选；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string getSmallestString(string s, int k) {  // s：输入字符串；k：可用的总代价；返回字典序最小的结果
        for (int i = 0; i < s.size(); ++i) {  // 从左到右逐位处理，越靠左的位越影响字典序
            char c1 = s[i];  // 当前这一位的字符
            for (char c2 = 'a'; c2 < c1; ++c2) {  // 从小到大尝试所有比 c1 小的候选字符
                int d = min(c1 - c2, 26 - c1 + c2);  // 环形字母表上的最小距离：直接前移，或绕一圈走过去
                if (d <= k) {  // 剩余预算够付出这段距离
                    s[i] = c2;  // 把这一位改成更小的字符
                    k -= d;  // 扣掉本次消耗的预算
                    break;  // 这一位已经最小化，转去处理下一位
                }
            }
        }
        return s;  // 返回字典序最小的结果串
    }
};