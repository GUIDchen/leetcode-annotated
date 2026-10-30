// 题目：2434. 使用机器人打印字典序最小的字符串（Using a Robot to Print the Lexicographically Smallest String）
// 思路：先用 cnt 统计各字母剩余次数，用指针 mi 维护「还没打印的最小字母」；字符逐个入栈，只要栈顶不超过 mi 就立刻出栈写入答案。
// 时间复杂度：O(26n) 即 O(n)，每个字符进出栈各一次、mi 最多前移 26 次；空间复杂度：O(n)，栈与答案各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string robotWithString(string s) {  // s：输入字符串，返回机器人打印出的字典序最小结果
        int cnt[26] = {0};  // 频次数组：下标是「字母 - 'a'」，值为该字母在 s 中剩余的个数
        for (char& c : s) ++cnt[c - 'a'];  // 先完整扫描一遍 s，把每个字母的出现次数累加上去
        char mi = 'a';  // mi 表示当前还没打印的最小字母，初始从 'a' 开始向右找
        string stk;  // 模拟机器人的栈：取出的字符先暂存在这里
        string ans;  // 机器人真正打印出来的字符按顺序拼在这里
        for (char& c : s) {  // 按原顺序把 s 的字符一个个送进机器人
            --cnt[c - 'a'];  // 当前字符已被取出，剩余次数减一，这样 cnt 始终表示「还没处理的那些字符」
            while (mi < 'z' && cnt[mi - 'a'] == 0) ++mi;  // 剩余次数为 0 的字母已经不可能再打印，向后推进 mi
            stk += c;  // 机器人把当前字符压入栈（先入栈，才符合机器的动作顺序）
            while (!stk.empty() && stk.back() <= mi) {  // 栈顶不大于剩余最小字母时，现在打印它不会让字典序变差
                ans += stk.back();  // 弹出栈顶并追加到答案
                stk.pop_back();  // 该字符已打印，从栈中移除
            }
        }
        return ans;  // 返回字典序最小的打印结果
    }
};