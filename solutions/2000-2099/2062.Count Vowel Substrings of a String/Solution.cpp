// 题目：2062. 统计字符串中的元音子字符串（Count Vowel Substrings of a String）
// 思路：枚举子串左端点 i，再向右扩展右端点 j；遇到非元音立即中断，用集合去重后判断是否集齐 5 个元音。
// 时间复杂度：O(n^2)，每个左端点最多向右扩 n 步；空间复杂度：O(1)，集合最多只存 5 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countVowelSubstrings(string word) {  // word：只含英文小写字母的字符串
        int ans = 0;  // 统计满足条件的子串个数
        int n = word.size();  // 字符串长度，避免在循环里反复求
        for (int i = 0; i < n; ++i) {  // 枚举子串的左端点 i
            unordered_set<char> t;  // 当前这段子串里出现过的元音集合
            for (int j = i; j < n; ++j) {  // 从 i 开始向右扩展右端点 j
                char c = word[j];  // 取当前字符
                if (!isVowel(c)) break;  // 一旦遇到非元音，更长的子串也不可能全是元音，直接中断
                t.insert(c);  // 把当前元音加入集合（重复元音自动去重）
                ans += t.size() == 5;  // 五种元音齐全时，这个子串才算符合条件
            }
        }
        return ans;  // 返回符合条件的子串总数
    }

    bool isVowel(char c) {  // 辅助函数：判断一个字符是否为元音
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';  // 属于五个元音之一即为真
    }
};