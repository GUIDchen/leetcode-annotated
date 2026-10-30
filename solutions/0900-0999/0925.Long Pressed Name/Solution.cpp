// 题目：925. 长按键入（Long Pressed Name）
// 思路：双指针按「字符段」比对，两串同一段的字符必须相同，且 name 中该段长度不能超过 typed 中该段的长度。
// 时间复杂度：O(m+n)，两个指针各自只前进一次；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isLongPressedName(string name, string typed) {  // name：原本要输入的名字；typed：实际键入的字符序列
        int m = name.length(), n = typed.length();  // m、n 分别是两个串的长度
        int i = 0, j = 0;  // 双指针：i 扫描 name，j 扫描 typed
        while (i < m && j < n) {  // 两个串都没扫完时继续比对
            if (name[i] != typed[j]) {  // 同一段的首字符必须一致，否则不可能是长按造成的差异
                return false;  // 返回 false 表示不匹配
            }  // if 结束
            int x = i + 1;  // 从 i 往后找 name 中这段相同字符的结束位置
            while (x < m && name[x] == name[i]) {  // 统计 name 中该字符的连续长度
                ++x;  // 继续往后找
            }  // 内层 while 结束
            int y = j + 1;  // 从 j 往后找 typed 中这段相同字符的结束位置
            while (y < n && typed[y] == typed[j]) {  // 统计 typed 中该字符的连续长度
                ++y;  // 继续往后找
            }  // 内层 while 结束
            if (x - i > y - j) {  // typed 中这一段比 name 中的短，说明这个字符少按了
                return false;  // 返回 false
            }  // if 结束
            i = x;  // name 跳到下一段的起点
            j = y;  // typed 跳到下一段的起点
        }  // 外层 while 结束
        return i == m && j == n;  // 两串必须同时扫完，否则有一方还剩字符（多按或漏按）
    }  // 方法结束
};  // 类定义结束