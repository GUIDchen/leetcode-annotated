// 题目：1163. 按字典序排在最后的子串（Last Substring in Lexicographical Order）
// 思路：双指针比较后缀，i 指向当前最优后缀起点、j 指向竞争者，k 记录已匹配长度，跳过被淘汰的起点。
// 时间复杂度：O(n)；空间复杂度：O(1)。
class Solution {  // LeetCode 题解类
public:  // 解题方法对外公开
    string lastSubstring(string s) {  // 返回字典序最大的子串（即字典序最大的后缀）
        int n = s.size();  // 字符串长度
        int i = 0;  // i：当前候选最大后缀的起点
        for (int j = 1, k = 0; j + k < n;) {  // j 是竞争者起点，k 是两者已匹配的长度
            if (s[i + k] == s[j + k]) {  // 当前位相同，继续比较下一位
                ++k;  // 已匹配长度加一
            } else if (s[i + k] < s[j + k]) {  // 竞争者更大
                i += k + 1;  // i 跳到 i+k+1，i..i+k 这些起点不可能再最大
                k = 0;  // 重新开始匹配
                if (i >= j) {  // i 追上或超过 j
                    j = i + 1;  // 让 j 始终位于 i 之后
                }  // 结束 i 越界修正
            } else {  // 候选者更大
                j += k + 1;  // j 跳到 j+k+1，整段被淘汰的起点一起跳过
                k = 0;  // 重新开始匹配
            }  // 结束比较分支
        }  // 结束比较循环
        return s.substr(i);  // 从最大后缀起点截取到末尾
    }  // 方法结束
};  // 类定义结束