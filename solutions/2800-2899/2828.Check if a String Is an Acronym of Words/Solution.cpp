// 题目：2828. 判别首字母缩略词（Check if a String Is an Acronym of Words）
// 思路：按顺序把每个单词的首字母拼成一个新串，再与 s 比较是否完全相等。
// 时间复杂度：O(n)，n 为所有单词长度之和；空间复杂度：O(m)，m 为单词个数，用于存放拼接出的缩略词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isAcronym(vector<string>& words, string s) {  // words：单词列表；s：待判断的缩略词；返回 s 是否为这些单词首字母的拼接
        string t;  // 用来接收各单词首字母的空串
        for (auto& w : words) {  // 按题目给定的顺序遍历每个单词（用引用避免字符串拷贝）
            t += w[0];  // 取出该单词的首字母，追加到缩略词末尾，顺序必须与 words 一致
        }  // 所有单词遍历完毕
        return t == s;  // 拼接结果与 s 完全相同才符合缩略词的定义
    }  // 方法结束
};  // 类定义结束