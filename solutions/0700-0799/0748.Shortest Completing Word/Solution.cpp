// 题目：748. 最短补全词（Shortest Completing Word）
// 核心思路：先统计 licensePlate 中字母（统一小写、忽略数字与空格）的词频，再遍历 words 用词频校验覆盖关系，保留最短的一个。
// 时间复杂度：O(L + Σ|w| · 26)，L 为牌照长度；空间复杂度：O(1)，两个长度 26 的计数数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string shortestCompletingWord(string licensePlate, vector<string>& words) {  // licensePlate：含字母与数字/空格的牌照；words：候选单词表
        int cnt[26]{};  // 牌照的字母词频表，花括号保证 26 个元素都初始化为 0
        for (char& c : licensePlate) {  // 遍历牌照的每个字符
            if (isalpha(c)) {  // 只统计字母，跳过数字和空格
                ++cnt[tolower(c) - 'a'];  // 统一转小写后映射到 0..25 的下标并累加
            }  // 结束字母判断
        }  // 结束牌照统计
        string ans;  // 保存当前最短的补全词，空串表示还没有找到
        for (auto& w : words) {  // 逐个候选词检查
            if (ans.size() && ans.size() <= w.size()) {  // 已有答案且不严格更短，就不可能是题目要求的最短，直接剪枝
                continue;  // 跳过当前单词
            }  // 结束剪枝判断
            int t[26]{};  // 当前候选词的小写字母词频表
            for (char& c : w) {  // 统计候选词的每个字符
                ++t[c - 'a'];  // 单词只含小写字母，直接映射成下标累加
            }  // 结束候选词统计
            bool ok = true;  // 先假设当前单词能补全牌照
            for (int i = 0; i < 26; ++i) {  // 逐字母核对是否覆盖牌照所需的全部数量
                if (cnt[i] > t[i]) {  // 某个字母数量不够，说明不满足补全条件
                    ok = false;  // 标记为不满足
                    break;  // 已经确定不满足，提前结束核对
                }  // 结束数量比较
            }  // 结束 26 个字母的核对
            if (ok) {  // 是合格的补全词
                ans = w;  // 前面已剪掉更长的情况，这里的 w 严格更短，直接替换答案
            }  // 结束合格处理
        }  // 结束单词遍历
        return ans;  // 返回最短补全词（题目保证一定存在）
    }  // 结束 shortestCompletingWord 方法
};  // 结束 Solution 类