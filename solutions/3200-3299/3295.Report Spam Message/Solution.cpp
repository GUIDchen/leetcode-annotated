// 题目：3295. 举报垃圾信息（Report Spam Message）
// 思路：把禁用词放进哈希集合，顺序扫描消息，用计数器记录命中的禁用词个数，达到 2 个立即返回真。
// 时间复杂度：O(n + m)，n 为消息单词数、m 为禁用词数；空间复杂度：O(m)，哈希集合保存禁用词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {  // message 是整条消息的单词数组，bannedWords 是禁用词表
        unordered_set<string> s(bannedWords.begin(), bannedWords.end());  // 把禁用词放进哈希集合，使单次查询降到 O(1)
        int cnt = 0;  // 记录已经出现的禁用词个数
        for (const auto& w : message) {  // 逐个单词扫描消息
            if (s.contains(w) && ++cnt >= 2) {  // 命中禁用词后计数器自增，短路求值后达到 2 个即可判定
                return true;  // 至少两个禁用词，判定为垃圾信息
            }  // 未达标则继续扫描下一个单词
        }  // 所有单词扫描完毕
        return false;  // 禁用词不足两个，不是垃圾信息
    }  // reportSpam 方法结束
};  // Solution 类定义结束
