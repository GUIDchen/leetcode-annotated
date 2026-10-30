// 题目：3784. 使所有字符相等的最小删除代价（Minimum Deletion Cost to Make All Characters Equal）
// 核心思路：枚举最终保留下来的字符 c，其余字符必须全部删除，代价为总代价减去 c 的代价之和；对所有出现过的字符取最小值。
// 复杂度：时间 O(n)，扫描一遍并遍历至多 26 个字符；空间 O(1)，哈希表最多存 26 项。
class Solution {  // LeetCode 约定的题解类
public:  // public 区的方法供判题器调用
    long long minCost(string s, vector<int>& cost) {  // 可删除任意多个字符，要求剩余串非空且字符全相同，返回最小删除总代价
        long long tot = 0;  // 所有字符的删除代价之和
        unordered_map<char, long long> g;  // g[c] 统计字符 c 的删除代价总和
        for (int i = 0; i < cost.size(); ++i) {  // 遍历每个字符及其删除代价
            tot += cost[i];  // 累加所有字符的总代价
            g[s[i]] += cost[i];  // 把当前字符的代价累加到对应字符的统计里
        }  // 遍历结束
        long long ans = tot;  // 答案先取「把所有字符都删掉」的总代价作为上界，再由每个候选字符修正
        for (auto [_, v] : g) {  // 枚举「最终保留的字符是 c」这一方案
            ans = min(ans, tot - v);  // 保留 c 需删掉其余字符，代价为总代价减去 c 的代价，取最小值
        }  // 枚举结束
        return ans;  // 返回最小删除代价
    }  // 方法结束
};  // 类定义结束
