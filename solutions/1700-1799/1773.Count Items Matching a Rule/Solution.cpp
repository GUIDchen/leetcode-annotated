// 题目：1773. 统计匹配检索规则的物品数量（Count Items Matching a Rule）
// 思路：规则键只有 type/color/name 三种，先用首字母确定列下标，再用 count_if 统计该列等于规则值的物品数。
// 时间复杂度：O(n·L)，n 为物品数、L 为字符串比较代价；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {  // items：物品三元组；ruleKey/ruleValue：匹配规则
        int i = ruleKey[0] == 't' ? 0 : (ruleKey[0] == 'c' ? 1 : 2);  // 用规则键首字母确定列号：t 对应 type 列 0，c 对应 color 列 1，否则 name 列 2
        return count_if(items.begin(), items.end(), [&](auto& v) { return v[i] == ruleValue; });  // 统计第 i 列等于规则值的物品个数
    }
};  // 类定义结束