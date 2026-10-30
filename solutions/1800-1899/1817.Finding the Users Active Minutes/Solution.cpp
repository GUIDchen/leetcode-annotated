// 题目：1817. 查找用户活跃分钟数（Finding the Users Active Minutes）
// 思路：用哈希表记录每个用户去重后的活跃分钟集合，集合大小即该用户的 UAM，最后按 UAM 统计人数。
// 时间复杂度：O(n)，每条日志只插入一次；空间复杂度：O(n)，哈希表保存所有 (用户, 分钟) 去重结果。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findingUsersActiveMinutes(vector<vector<int>>& logs, int k) {  // logs：{用户ID, 分钟} 列表；k：UAM 上限
        unordered_map<int, unordered_set<int>> d;  // 哈希表：键是用户 ID，值是该用户活跃的分钟集合（自动去重）
        for (auto& log : logs) {  // 遍历每条日志
            int i = log[0], t = log[1];  // i 是用户 ID，t 是活跃分钟
            d[i].insert(t);  // 把分钟插入该用户的集合，重复的自动忽略
        }
        vector<int> ans(k);  // 答案数组，ans[j] 表示 UAM 恰好为 j+1 的用户数
        for (auto& [_, ts] : d) {  // 遍历每个用户的分钟集合
            ++ans[ts.size() - 1];  // 集合大小即 UAM，UAM 为 s 的用户计入下标 s-1
        }
        return ans;  // 返回按 UAM 分组的人数
    }
};  // 结束 Solution 类定义