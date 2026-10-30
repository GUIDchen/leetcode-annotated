// 题目：2255. 统计是给定字符串前缀的字符串数目（Count Prefixes of a Given String）
// 思路：逐个检查 words 中的字符串是否为 s 的前缀，用 C++20 的 starts_with 直接比较，把为真的个数累加起来。
// 时间复杂度：O(Σ|w|)，每个单词只与 s 的前 |w| 个字符比较；空间复杂度：O(1)，只用一个计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPrefixes(vector<string>& words, string s) {  // words 是候选前缀列表，s 是被检查的字符串
        int ans = 0;  // ans：是 s 前缀的单词个数
        for (auto& w : words) {  // 逐个取出候选单词 w
            ans += s.starts_with(w);  // starts_with 返回 bool，为真时相当于加 1，直接累加到答案里
        }  // 结束候选单词的遍历
        return ans;  // 返回统计到的前缀个数
    }  // 结束题解方法
};  // 结束题解类