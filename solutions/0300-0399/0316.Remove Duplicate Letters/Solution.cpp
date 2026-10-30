// 题目：316. 去除重复字母（Remove Duplicate Letters）
// 思路：贪心 + 单调栈。记录每个字符最后出现的位置，扫描时若栈顶字符更大且后面还会出现，就把它弹掉，并用位掩码去重。
// 时间复杂度：O(n)，每个字符最多入栈、出栈一次；空间复杂度：O(1)，只有 26 个字母相关的数组与标记。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeDuplicateLetters(string s) {  // s：输入字符串
        int n = s.size();  // 字符串长度
        int last[26] = {0};  // last[c]：字符 c 最后一次出现的下标，初始全 0
        for (int i = 0; i < n; ++i) {  // 一遍扫描记录每个字符的最后位置
            last[s[i] - 'a'] = i;  // 字符减 'a' 映射到 0..25 作为数组下标
        }
        string ans;  // 单调栈：维护当前字典序最小的结果
        int mask = 0;  // 位掩码：第 i 位为 1 表示字母 i 已经在栈中
        for (int i = 0; i < n; ++i) {  // 从左到右扫描字符串
            char c = s[i];  // 当前字符
            if ((mask >> (c - 'a')) & 1) {  // 用位运算判断当前字符是否已经在栈中
                continue;  // 已在栈中说明是重复出现，直接跳过，避免结果出现重复字母
            }
            while (!ans.empty() && ans.back() > c && last[ans.back() - 'a'] > i) {  // 栈顶更大且后面还会再出现，就可以弹掉它让位给更小的当前字符
                mask ^= 1 << (ans.back() - 'a');  // 清除栈顶字符的「已入栈」标记
                ans.pop_back();  // 弹掉栈顶字符
            }
            ans.push_back(c);  // 把当前字符压入栈
            mask |= 1 << (c - 'a');  // 标记该字符已入栈
        }
        return ans;  // 栈内即为字典序最小且去重的结果
    }
};