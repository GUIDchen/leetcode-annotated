// 题目：1408. 数组中的字符串匹配（String Matching in an Array）
// 思路：对每个字符串枚举其它字符串，用 find 判断它是否为对方子串；只要存在一个包含它的字符串就加入答案。
// 时间复杂度：O(n^2 * L)，n 为单词数、L 为串长；空间复杂度：O(1)，不计返回结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> stringMatching(vector<string>& words) {  // words 为待检查的字符串数组
        vector<string> ans;  // 收集所有是其它串子串的字符串
        int n = words.size();  // 字符串个数，避免重复调用 size()
        for (int i = 0; i < n; ++i) {  // 逐个考察 words[i] 是否为别的串的子串
            for (int j = 0; j < n; ++j) {  // 枚举用来包含 words[i] 的候选串
                if (i != j && words[j].find(words[i]) != string::npos) {  // 跳过自身，且 find 返回值不是 npos 说明是子串
                    ans.push_back(words[i]);  // 只记录一次，题目要求去重
                    break;  // 已确认，跳出内层循环
                }  // 判定分支结束
            }  // 内层循环结束
        }  // 外层循环结束
        return ans;  // 返回所有匹配的字符串
    }  // stringMatching 方法结束
};  // Solution 类结束