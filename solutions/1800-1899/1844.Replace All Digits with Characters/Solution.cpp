// 题目：1844. 将所有数字用字符替换（Replace All Digits with Characters）
// 思路：偶数下标是字母、奇数下标是数字，顺序扫描奇数位，把 s[i] 改成"前一个字母向后偏移 s[i]-'0' 位"得到的字母。
// 时间复杂度：O(n)，只扫一遍；空间复杂度：O(1)，利用 string 的可变性原地修改（形参是值传递的副本）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string replaceDigits(string s) {  // s：字母与数字交替的输入串
        int n = s.size();  // 串长，作为循环上界
        for (int i = 1; i < n; i += 2) {  // 步长为 2 只遍历奇数下标（这些位置是数字）
            s[i] = s[i - 1] + s[i] - '0';  // 前一个字母的 ASCII 码加上数字值，得到 shift 后的字母
        }
        return s;  // 返回替换完成的字符串
    }
};