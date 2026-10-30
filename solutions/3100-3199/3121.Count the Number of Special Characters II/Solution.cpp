// 题目：3121. 统计特殊字母的数量 II（Count the Number of Special Characters II）
// 思路：分别记录每个字符「第一次出现」与「最后一次出现」的位置；字母 c 特殊当且仅当小写 c 的最后一次出现在大写 C 的第一次出现之前。
// 时间复杂度：O(n + 26)，n 为字符串长度；空间复杂度：O(1)，两个大小固定的数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numberOfSpecialChars(string word) {  // word：输入字符串，返回满足条件的特殊字母个数
        vector<int> first('z' + 1);  // first[c]：字符 c 第一次出现的位置（1 起计，0 表示没出现过）
        vector<int> last('z' + 1);  // last[c]：字符 c 最后一次出现的位置（1 起计，0 表示没出现过）
        for (int i = 1; i <= word.size(); ++i) {  // 用 1 起计的下标扫描，便于用 0 表示「未出现」
            int j = word[i - 1];  // 取出当前位置的字符
            if (first[j] == 0) {  // 这个字符之前没出现过
                first[j] = i;  // 记录它第一次出现的位置
            }  // 结束首次出现判断
            last[j] = i;  // 无论是否首次出现，都更新最后一次出现的位置
        }  // 结束扫描
        int ans = 0;  // 记录特殊字母的个数
        for (int i = 0; i < 26; ++i) {  // 枚举 26 个字母
            if (last['a' + i] && last['a' + i] < first['A' + i]) {  // 小写出现过，且小写最后一次出现早于大写第一次出现
                ++ans;  // 该字母特殊，计数加一
            }  // 结束条件判断
        }  // 结束字母枚举
        return ans;  // 返回特殊字母的数量
    }  // 结束 numberOfSpecialChars
};  // 类定义结束
