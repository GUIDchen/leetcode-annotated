// 题目：2000. 反转单词前缀（Reverse Prefix of Word）
// 思路：先找到字符 ch 第一次出现的下标 i，若存在则把前缀 [0, i] 原地反转，不存在则原样返回。
// 时间复杂度：O(n)，查找与反转各扫一遍；空间复杂度：O(1)，原地修改字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string reversePrefix(string word, char ch) {  // word：输入单词；ch：需要第一次出现的字符
        int i = word.find(ch);  // 查找 ch 第一次出现的下标，找不到时返回 npos
        if (i != string::npos) {  // 找到目标字符，才需要反转前缀
            reverse(word.begin(), word.begin() + i + 1);  // 反转从下标 0 到 i（含 i）的前缀
        }
        return word;  // 返回处理后的字符串（未找到时即原串）
    }
};