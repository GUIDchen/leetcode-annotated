// 题目：806. 写字符串需要的行数（Number of Lines To Write String）
// 思路：按顺序累加每个字母的宽度，放不下 100 就另起一行，并把该字母的宽度作为新行的已用宽度。
// 时间复杂度：O(n)，n 为字符串长度；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> numberOfLines(vector<int>& widths, string s) {  // widths：a~z 每个字母的宽度；s：要写的字符串；返回 {行数, 最后一行宽度}
        int lines = 1, last = 0;  // lines：已用行数；last：当前行已用宽度
        for (char c : s) {  // 逐字符排版
            int w = widths[c - 'a'];  // 用字母偏移 c - 'a' 取出该字符的宽度
            if (last + w <= 100) {  // 本行还放得下
                last += w;  // 直接累加宽度
            } else {  // 放不下，需要换行
                ++lines;  // 另起一行
                last = w;  // 新行的已用宽度就是这个字符的宽度
            }  // 换行分支结束
        }  // 字符循环结束
        return {lines, last};  // 返回行数与最后一行的宽度
    }  // 方法结束
};  // 类定义结束