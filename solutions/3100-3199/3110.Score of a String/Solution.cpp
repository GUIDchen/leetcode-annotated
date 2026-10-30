// 题目：3110. 字符串的分数（Score of a String）
// 思路：分数定义为所有相邻字符 ASCII 码之差的绝对值之和，一次遍历累加 abs(s[i] - s[i-1]) 即可。
// 时间复杂度：O(n)，只扫一遍字符串；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int scoreOfString(string s) {  // s 是输入字符串
        int ans = 0;  // 累计的分数
        for (int i = 1; i < s.size(); ++i) {  // 从第二个字符开始，与它的前一个字符配对
            ans += abs(s[i] - s[i - 1]);  // 加上这对相邻字符 ASCII 码之差的绝对值
        }
        return ans;  // 返回字符串的总分数
    }
};