// 题目：3746. 等量移除后的字符串最小长度（Minimum String Length After Balanced Removals）
// 核心思路：每次移除都要求子串中 'a' 与 'b' 数量相等，等价于一次消耗一个 'a' 和一个 'b'；最多配对 min(a, b) 次，剩下的必然只有同一种字符，故答案为两字符数量之差的绝对值。
// 复杂度：时间 O(n)，只需扫一遍字符串统计 'a' 的个数；空间 O(1)，仅用常数个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minLengthAfterRemovals(string s) {  // s 只由 'a' 和 'b' 组成，返回任意次等量移除后可能的最小长度
        int a = 0;  // a 记录字符 'a' 出现的次数，先初始化为 0
        for (char c : s) {  // 用范围 for 逐个取出字符串 s 中的字符 c
            if (c == 'a') {  // 当前字符是 'a' 时计数加一，否则它一定是 'b'
                ++a;  // 'a' 的个数自增
            }  // if 分支结束
        }  // 遍历结束，此时 a 是 'a' 的总数
        int b = s.size() - a;  // 字符串只含 'a' 和 'b'，剩下的就是 'b' 的个数
        return abs(a - b);  // 一次移除同时消掉一个 'a' 和一个 'b'，多出来的那部分再也删不掉，故答案为两者之差
    }  // 方法结束
};  // 类定义结束
