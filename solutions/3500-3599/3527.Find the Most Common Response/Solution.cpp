// 题目：3527. 找到最常见的回答（Find the Most Common Response）
// 思路：每天的相同回答只算一次，用集合去重后累计每个回答出现的天数；再遍历计数表，按「天数最多、同天数取字典序最小」选答案。
// 时间复杂度：O(L)，L 为所有回答的总字符数（哈希与集合操作均摊线性）；空间复杂度：O(U)，U 为不同回答个数。
class Solution {  // LeetCode 约定的题解类
public:  // 判题器只调用 public 区的方法
    string findCommonResponse(vector<vector<string>>& responses) {  // responses 是每天的回答列表，返回出现天数最多的回答
        unordered_map<string, int> cnt;  // cnt[w] 记录回答 w 出现在多少天里
        for (const auto& ws : responses) {  // 逐天取出当天的回答列表
            unordered_set<string> s;  // 当天用过的回答，用来按天去重
            for (const auto& w : ws) {  // 遍历当天的每条回答
                if (s.insert(w).second) {  // 插入成功说明这是当天第一次见到该回答
                    ++cnt[w];  // 该回答出现的天数加一
                }  // if 结束
            }  // 当天遍历结束
        }  // 所有天遍历结束
        string ans = responses[0][0];  // 任意取一个候选作为初始答案
        for (const auto& e : cnt) {  // 遍历所有出现过的回答
            const string& w = e.first;  // 回答内容
            int v = e.second;  // 它出现的天数
            if (cnt[ans] < v || (cnt[ans] == v && w < ans)) {  // 天数更多，或天数相同但字典序更小
                ans = w;  // 更新最优回答
            }  // if 结束
        }  // 遍历结束
        return ans;  // 返回出现天数最多且字典序最小的回答
    }  // 方法结束
};  // 类定义结束