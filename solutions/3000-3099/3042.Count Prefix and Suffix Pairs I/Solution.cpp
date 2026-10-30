// 题目：3042. 统计前后缀下标对 I（Count Prefix and Suffix Pairs I）
// 核心思路：枚举所有 i < j，用 string::find 判前缀、rfind 判后缀，判断 words[i] 是否同时是 words[j] 的前缀与后缀。
// 时间复杂度：O(n^2 * L)，n 为单词数、L 为单词长度；空间复杂度：O(L)，只额外拷贝了当前两个字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    int countPrefixSuffixPairs(vector<string>& words) {  // words：待统计的字符串数组，返回同时满足前缀与后缀关系的下标对数目
        int ans = 0;  // ans：累计满足条件的有序下标对 (i, j) 数量
        int n = words.size();  // n：字符串总数，作为两层循环的上界
        for (int i = 0; i < n; ++i) {  // 枚举作为前缀/后缀候选的短串 words[i]
            string s = words[i];  // s：当前候选串，下面要反复拿它与 words[j] 比较
            for (int j = i + 1; j < n; ++j) {  // 只枚举 i 之后的 j，保证每个下标对只被统计一次
                string t = words[j];  // t：待检查的长串 words[j]
                if (t.find(s) == 0 && t.rfind(s) == t.length() - s.length()) {  // find(s) == 0 说明 s 是 t 的前缀；rfind(s) 落在末尾说明 s 也是 t 的后缀
                    ++ans;  // 两个条件同时成立，说明 (i, j) 是一对合法的前后缀下标对
                }
            }
        }
        return ans;  // 返回统计到的下标对总数
    }  // 方法结束
};  // 题解类结束