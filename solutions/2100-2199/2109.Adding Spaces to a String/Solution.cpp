// 题目：2109. 向字符串添加空格（Adding Spaces to a String）
// 思路：spaces 已升序，用一个指针 j 指向下一个要插空格的位置，同时遍历原串，遇到目标下标先补空格再拼字符。
// 时间复杂度：O(n + m)，n 为字符串长度、m 为空格个数；空间复杂度：O(n)，结果字符串额外占用 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string addSpaces(string s, vector<int>& spaces) {  // s 是原字符串，spaces 是升序排列的「需要在其前面插入空格」的下标
        string ans = "";  // ans 用来拼接结果字符串
        for (int i = 0, j = 0; i < s.size(); ++i) {  // i 遍历 s，j 指向 spaces 中下一个待处理的下标
            if (j < spaces.size() && i == spaces[j]) {  // 当前位置正是要插入空格的位置（j 未越界才比较）
                ans += ' ';  // 先追加一个空格
                ++j;  // 处理完这一个空格位置，指针后移
            }  // if 分支结束
            ans += s[i];  // 再追加原字符串的当前字符
        }  // 遍历结束
        return ans;  // 返回添加空格后的字符串
    }  // 方法结束
};  // 题解类结束