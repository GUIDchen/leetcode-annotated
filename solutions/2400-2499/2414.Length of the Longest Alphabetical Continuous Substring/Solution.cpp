// 题目：2414. 最长的字母序连续子字符串的长度（Length of the Longest Alphabetical Continuous Substring）
// 思路：顺次比较相邻字符，若 s[i]-s[i-1]==1 则把当前连续段长度自增并刷新答案，否则把长度重置为 1。
// 时间复杂度：O(n)，字符串只扫描一遍；空间复杂度：O(1)，只用常数个计数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestContinuousSubstring(string s) {  // s 是只含小写字母的字符串，返回最长字母序连续子串的长度
        int ans = 1, cnt = 1;  // ans 记录最长长度；cnt 记录当前连续段长度，单个字符也算长度 1
        for (int i = 1; i < s.size(); ++i) {  // 从第二个字符开始，与前一个字符比较
            if (s[i] - s[i - 1] == 1) {  // ASCII 码相差 1 表示字母序连续
                ans = max(ans, ++cnt);  // 先把 cnt 自增，再与 ans 取较大值
            } else {  // 连续性中断
                cnt = 1;  // 重新从 1 开始计数
            }
        }
        return ans;  // 返回最长字母序连续子串的长度
    }  // 方法定义结束
};  // 类定义结束
