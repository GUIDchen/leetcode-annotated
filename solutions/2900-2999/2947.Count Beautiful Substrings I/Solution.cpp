// 题目：2947. 统计美丽子字符串 I（Count Beautiful Substrings I）
// 思路：枚举子串左右端点，边扩展右端点边累加元音个数，再用子串长度减去元音数得到辅音数；满足「元音数 == 辅音数且两者乘积能被 k 整除」就计数。
// 时间复杂度：O(n^2)，枚举所有子串；空间复杂度：O(1)，只用定长 26 的标记数组和几个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int beautifulSubstrings(string s, int k) {  // s 是待统计的字符串，k 是题目给定的整除参数
        int n = s.size();  // 字符串长度
        int vs[26]{};  // 26 个字母的元音标记表：0 表示辅音，1 表示元音
        string t = "aeiou";  // 元音字母集合
        for (char c : t) {  // 遍历元音集合，逐个在标记表中置位
            vs[c - 'a'] = 1;  // c - 'a' 是该字母在标记表中的下标
        }
        int ans = 0;  // 记录美丽子串的个数
        for (int i = 0; i < n; ++i) {  // 枚举子串左端点 i
            int vowels = 0;  // 固定左端点后，重新累计当前子串中的元音数
            for (int j = i; j < n; ++j) {  // 枚举子串右端点 j，子串为 s[i..j]
                vowels += vs[s[j] - 'a'];  // 把 s[j] 是否为元音累加进当前子串的元音数
                int consonants = j - i + 1 - vowels;  // 子串长度减去元音数即为辅音数
                if (vowels == consonants && vowels * consonants % k == 0) {  // 元音数与辅音数相等，且两者乘积能被 k 整除
                    ++ans;  // 找到一个美丽子串，计数加一
                }
            }
        }
        return ans;  // 返回美丽子串总数
    }
};