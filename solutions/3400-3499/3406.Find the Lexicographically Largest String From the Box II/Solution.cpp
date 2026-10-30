// 3406. 从盒子中找出字典序最大的字符串 II / Find the Lexicographically Largest String From the Box II
// 核心思路：字典序最大的答案必为 word 最大后缀的前缀，先用双指针 O(n) 求最大后缀，再按长度 n-numFriends+1 截断。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // 题解类定义
public:  // 公有接口
    string answerString(string word, int numFriends) {  // 返回 numFriends 份分割中字典序最大的那份字符串
        if (numFriends == 1) {  // 只有一份时无需切分
            return word;  // 整串就是答案
        }  // 结束特判
        string s = lastSubstring(word);  // 字典序最大的子串必是最大后缀的前缀
        return s.substr(0, min(s.length(), word.length() - numFriends + 1));  // 截取长度不超过 n-numFriends+1 的前缀作为答案
    }  // 主函数结束

    string lastSubstring(string& s) {  // 双指针 O(n) 求字典序最大的后缀
        int n = s.size();  // 字符串长度
        int i = 0, j = 1, k = 0;  // i 为当前最优后缀起点，j 为挑战者起点，k 为已匹配长度
        while (j + k < n) {  // 挑战者未越界时继续比较
            if (s[i + k] == s[j + k]) {  // 对应字符相同
                ++k;  // 匹配长度加一
            } else if (s[i + k] < s[j + k]) {  // 候选起点 i 落后
                i += k + 1;  // i 跳过已匹配的 k+1 个字符
                k = 0;  // 匹配长度清零
                if (i >= j) {  // 保证 i 始终位于 j 之前
                    j = i + 1;  // 把挑战者移到 i 之后
                }  // 结束 i 的推进分支
            } else {  // 挑战者 j 落后
                j += k + 1;  // j 跳过已匹配的 k+1 个字符
                k = 0;  // 匹配长度清零
            }  // 结束比较分支
        }  // 结束比较循环
        return s.substr(i);  // 从 i 开始的后缀即字典序最大的后缀
    }  // 结束 lastSubstring
};  // 结束题解类