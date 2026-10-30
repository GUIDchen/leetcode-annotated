// 题目：1839. 所有元音按顺序排布的最长子字符串（Longest Substring Of All Vowels in Order）
// 思路：先做行程编码把 word 压成 (字符, 连续长度) 序列，再逐个检查相邻 5 段是否恰为 a,e,i,o,u；是则把 5 段长度相加更新答案。
// 时间复杂度：O(n)，行程编码与五段检查都是线性；空间复杂度：O(n)，存放行程序列。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestBeautifulSubstring(string word) {  // word 是只含小写字母的字符串，返回满足 a→e→i→o→u 递增的最长美丽子串长度
        vector<pair<char, int>> arr;  // 行程编码数组，每项是 (字符, 该字符连续出现的次数)
        int n = word.size();  // 字符串长度
        for (int i = 0; i < n;) {  // 手动控制下标的遍历，i 指向当前这一段的起点
            int j = i;  // j 用来寻找当前段的结束位置
            while (j < n && word[j] == word[i]) ++j;  // 跳过所有与 word[i] 相同的字符，j 停在段尾之后
            arr.push_back({word[i], j - i});  // 记录一段：字符 word[i] 连续出现了 j - i 次
            i = j;  // 从下一段的起点继续
        }  // 行程编码结束
        int ans = 0;  // 记录最长美丽子串的长度
        for (int i = 0; i < (int) arr.size() - 4; ++i) {  // 枚举起始段，需保证后面还剩 4 段，(int) 强转避免 size_t 相减下溢
            auto& [a, v1] = arr[i];  // 第 i 段：字符 a 及它的长度 v1
            auto& [b, v2] = arr[i + 1];  // 第 i+1 段：字符 b 及它的长度 v2
            auto& [c, v3] = arr[i + 2];  // 第 i+2 段：字符 c 及它的长度 v3
            auto& [d, v4] = arr[i + 3];  // 第 i+3 段：字符 d 及它的长度 v4
            auto& [e, v5] = arr[i + 4];  // 第 i+4 段：字符 e 及它的长度 v5
            if (a == 'a' && b == 'e' && c == 'i' && d == 'o' && e == 'u') {  // 五段字符依次是 a,e,i,o,u，说明拼成的子串是美丽子串
                ans = max(ans, v1 + v2 + v3 + v4 + v5);  // 美丽子串必须取满这 5 段才最长，用总长度更新答案
            }  // if 结束
        }  // 检查结束
        return ans;  // 返回最长长度
    }  // 方法结束
};  // 类定义结束