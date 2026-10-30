// 题目：1974. 使用特殊打字机键入单词的最少时间（Minimum Time to Type Word Using Special Typewriter）
// 思路：指针初始在 'a'，依次走到每个待键入字符；环形字母表上取顺时针与逆时针距离的较小值，再为每次按键累加 1 秒。
// 时间复杂度：O(n)，只需遍历一遍单词；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minTimeToType(string word) {  // word：待键入的单词
        int ans = word.length();  // 每个字符都要按一次键，先把 n 秒按键耗时计入答案
        char a = 'a';  // 指针当前所在字符，初始位置是 'a'
        for (char c : word) {  // 按顺序键入每一个字符
            int d = abs(a - c);  // 两个字母在字母表上的直线距离
            ans += min(d, 26 - d);  // 环形字母表上取顺时针/逆时针中较近的一边，累加移动耗时
            a = c;  // 指针移到刚键入的字符，作为下一次移动的起点
        }
        return ans;  // 返回总耗时（移动时间 + 按键时间）
    }
};
