// 题目：1882. 使用服务器处理任务（Process Tasks Using Servers）
// 思路：用两个小根堆分别维护「空闲服务器（权重, 下标）」与「忙碌服务器（空闲时刻, 权重, 下标）」，按下标推进时间并逐个分配任务。
// 时间复杂度：O((n + m) log n)，每次堆操作都是对数级；空间复杂度：O(n + m)，两个堆加上答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {  // servers 是服务器权重，tasks 是每个任务的耗时
        using pii = pair<int, int>;  // 空闲堆元素类型：{权重, 服务器下标}
        using arr3 = array<long long, 3>;  // 忙碌堆元素类型：{释放时刻, 权重, 服务器下标}
        priority_queue<pii, vector<pii>, greater<pii>> idle;  // 空闲堆：权重小的优先，权重相同则下标小的优先
        priority_queue<arr3, vector<arr3>, greater<arr3>> busy;  // 忙碌堆：最早释放的服务器优先
        for (int i = 0; i < servers.size(); ++i) {  // 初始时全部服务器都空闲
            idle.push({servers[i], i});  // 把第 i 台服务器按 (权重, 下标) 入空闲堆
        }
        int m = tasks.size();  // 任务总数
        vector<int> ans(m);  // 答案数组：ans[j] 是处理第 j 个任务的服务器下标
        for (int j = 0; j < m; ++j) {  // 按下标顺序处理任务，j 同时也是当前时刻
            int t = tasks[j];  // 当前任务需要占用服务器的时长
            while (!busy.empty() && busy.top()[0] <= j) {  // 把此刻已经忙完的服务器全部搬回空闲堆
                auto [_, s, i] = busy.top();  // 取出最早释放的那台（下划线是占位，忽略释放时刻）
                busy.pop();  // 从忙碌堆中弹出
                idle.push({(int) s, (int) i});  // 以空闲身份重新入堆，键仍是 (权重, 下标)
            }

            if (!idle.empty()) {  // 还有空闲服务器，可以直接分配
                auto [s, i] = idle.top();  // 取权重最小、权重相同则下标最小的空闲服务器
                idle.pop();  // 出堆，标记为即将忙碌
                ans[j] = i;  // 记录它负责第 j 个任务
                busy.push({(long long) j + t, s, i});  // 它要到 j + t 时刻才重新空闲
            } else {  // 没有空闲服务器，只能等最早释放的那台继续干
                auto [w, s, i] = busy.top();  // w 就是它最早释放的时刻
                busy.pop();  // 先出堆再续占
                ans[j] = (int) i;  // 第 j 个任务仍然交给这台服务器
                busy.push({w + t, s, i});  // 释放时刻在 w 的基础上顺延 t
            }
        }
        return ans;  // 返回每个任务对应的服务器下标
    }
};
