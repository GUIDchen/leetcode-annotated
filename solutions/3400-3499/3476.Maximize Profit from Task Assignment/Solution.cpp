// 3476. Maximize Profit from Task Assignment / 3476. 最大化任务分配的利润
// 核心思路：按技能分组用大根堆存利润，每个工人取本技能最高利润任务，最后再补一个剩余任务中的全局最高利润。
// 复杂度：时间 O((n + m) log m)，空间 O(m)。

class Solution {  // LeetCode 题解统一使用 Solution 类
public:  // 公有接口
    long long maxProfit(vector<int>& workers, vector<vector<int>>& tasks) {  // 返回最多能获得的利润总和
        unordered_map<int, priority_queue<int>> d;  // 每个技能对应一个利润大根堆
        for (const auto& t : tasks) {  // 遍历所有任务
            d[t[0]].push(t[1]);  // 按技能 t[0] 把利润 t[1] 入堆
        }  // 任务入堆结束
        long long ans = 0;  // 累计利润，用 long long 防止溢出
        for (int skill : workers) {  // 依次为每个工人分配任务
            if (d.contains(skill)) {  // 该工人技能还有可分配的任务
                auto& pq = d[skill];  // 取出该技能对应的大根堆
                ans += pq.top();  // 累加本技能的最高利润
                pq.pop();  // 该任务已被消耗，弹出堆顶
                if (pq.empty()) {  // 该技能任务已耗尽
                    d.erase(skill);  // 删除空堆，避免后续访问空堆
                }  // 判空分支结束
            }  // 可分配分支结束
        }  // 工人遍历结束
        int mx = 0;  // 记录剩余任务中的最大利润
        for (const auto& [_, pq] : d) {  // 遍历所有仍有剩余任务的技能
            mx = max(mx, pq.top());  // 用堆顶更新最大利润
        }  // 剩余任务遍历结束
        ans += mx;  // 最多再额外完成一个剩余任务
        return ans;  // 返回最大利润总和
    }  // 方法结束
};  // 类定义结束
