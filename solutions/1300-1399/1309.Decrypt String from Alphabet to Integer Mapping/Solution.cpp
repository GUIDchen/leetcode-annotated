// 题目：1309. 解码字母到整数映射（Decrypt String from Alphabet to Integer Mapping）
// 核心思路：顺序扫描编码串，遇到 "dd#" 就整体取出两位数，否则取一位数，再把 1~26 映射为 'a'~'z' 拼接。
// 时间复杂度：O(n)，每个字符只被处理一次；空间复杂度：O(n)，需要保存长度为 n 的答案字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string freqAlphabets(string s) {  // s 是待解码的编码串
        string ans = "";  // 用空字符串累积解码结果
        int i = 0, n = s.size();  // i 是读指针，n 是串长
        while (i < n) {  // 读指针未到末尾就继续
            if (i + 2 < n && s[i + 2] == '#') {  // 三位窗口形如 "dd#"，说明是两位数
                ans += char(stoi(s.substr(i, 2)) + 'a' - 1);  // 取两位数字转成整数，再换成对应字母追加
                i += 3;  // 连同 '#' 一起跳过三位
            } else {  // 否则是形如 "d" 的一位数
                ans += char(s[i] - '0' + 'a' - 1);  // 字符转数字后换成字母追加
                i += 1;  // 只前进一位
            }
        }
        return ans;  // 返回解码后的字符串
    }
};
