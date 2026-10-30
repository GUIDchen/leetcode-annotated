// 题目：848. 字母移位（Shifting Letters）
// 思路：从右往左累加位移量，第 i 个字母实际移动的是 shifts[i..n-1] 之和，累加后对 26 取模。
// 时间复杂度：O(n)，只扫一遍字符串；空间复杂度：O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string shiftingLetters(string s, vector<int>& shifts) {  // s 是待移位的小写字母串，shifts[i] 表示前 i + 1 个字母都要移动的位数；返回移位后的字符串
        long long t = 0;  // 累计位移量，用 long long 防止 shifts 之和溢出
        int n = s.size();  // 字符串长度
        for (int i = n - 1; ~i; --i) {  // 从右往左遍历；~i 等价于 i >= 0 的简写
            t += shifts[i];  // 累加当前位置的位移，t 就是 s[i] 实际要移动的总步数
            int j = (s[i] - 'a' + t) % 26;  // 字母相对 'a' 的偏移加位移后对 26 取模，得到新字母的偏移
            s[i] = 'a' + j;  // 把新字母写回原字符串
        }  // 从右往左遍历结束
        return s;  // 返回移位后的字符串
    }  // 方法结束
};  // 类定义结束