// 题目：916. 单词子集（Word Subsets）
// 思路：先把 words2 中每个字母的频次按单词取最大值合并成统一需求，再逐个检查 words1 的单词是否覆盖该需求。
// 时间复杂度：O(L + 26*(|words1| + |words2|))，L 为所有字符总数；空间复杂度：O(26 + 输出空间)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {  // words1：候选单词数组；words2：必须被全部覆盖的约束单词数组
        int cnt[26] = {0};  // cnt[i] 表示所有 words2 中字母 i 出现次数的最大值，即统一需求
        int t[26];  // t 是临时计数桶，存放当前单词的字母频次
        for (auto& b : words2) {  // 先把所有约束单词合并成一个「最严需求」
            memset(t, 0, sizeof t);  // 每换一个单词都先清空计数桶
            for (auto& c : b) {  // 逐个字符统计当前约束单词
                t[c - 'a']++;  // 字符减去 'a' 映射到 0..25 下标，出现次数加一
            }  // 结束本单词的字符统计
            for (int i = 0; i < 26; ++i) {  // 逐字母取最大值：多个约束单词要同时被满足
                cnt[i] = max(cnt[i], t[i]);  // 需求取最大，代表同时满足全部约束单词
            }  // 结束逐字母合并
        }  // 结束约束单词遍历
        vector<string> ans;  // 存放满足全部约束的候选单词
        for (auto& a : words1) {  // 逐个检查候选单词
            memset(t, 0, sizeof t);  // 清空计数桶，准备统计这个候选单词
            for (auto& c : a) {  // 统计候选单词的字母频次
                t[c - 'a']++;  // 同样映射到 0..25 并计数
            }  // 结束候选单词的字符统计
            bool ok = true;  // ok 标记该候选单词是否覆盖了全部需求
            for (int i = 0; i < 26; ++i) {  // 逐字母对比需求与实际拥有的数量
                if (cnt[i] > t[i]) {  // 需求比实际多，说明这个单词不满足
                    ok = false;  // 标记为不满足
                    break;  // 已经失败，无需继续比较
                }  // 结束 if 与 for 语句块
            }  // 结束逐字母检查
            if (ok) {  // 所有字母都满足
                ans.emplace_back(a);  // 收进答案，emplace_back 直接就地构造元素
            }  // 结束 if (ok)
        }  // 结束候选单词遍历
        return ans;  // 返回所有通用单词
    }  // 结束 wordSubsets 方法
};  // 结束 Solution 类