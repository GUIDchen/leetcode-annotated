// 题目：1606. 找到处理最多请求的服务器（Find Servers That Handled Most Number of Requests）
// 思路：用有序集合维护空闲服务器、小根堆维护忙碌服务器的忙完时刻；每个请求先归还已空闲的，再从 i%k 起环形找第一台空闲服务器。
// 时间复杂度：O((n + k) log k)，每次插入/删除/查找都是对数级；空间复杂度：O(k)，空闲集合、堆与计数数组。
class Solution {  // 题解类
public:  // 对外接口
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {  // k 为服务器个数；arrival[i] 是第 i 个请求的到达时间，load[i] 是它的处理耗时
        set<int> free;  // 空闲服务器集合（按编号有序），用于按环形规则挑选服务器
        for (int i = 0; i < k; ++i) free.insert(i);  // 初始时 k 台服务器全部空闲
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> busy;  // 小根堆：按「忙完时刻」排序，堆顶是最早空闲的服务器
        vector<int> cnt(k);  // cnt[i] 记录第 i 台服务器处理过的请求数
        for (int i = 0; i < arrival.size(); ++i) {  // 按时间顺序处理每一个请求
            int start = arrival[i], end = start + load[i];  // 本请求的开始时刻与预计忙完时刻
            while (!busy.empty() && busy.top().first <= start) {  // 把所有在本请求到达前（含同一时刻）已空闲的服务器还回空闲集合
                free.insert(busy.top().second);  // 该服务器重新空闲
                busy.pop();  // 已处理完，从堆中弹出
            }  // 归还循环结束
            if (free.empty()) continue;  // 一台空闲服务器都没有，本请求只能丢弃
            auto p = free.lower_bound(i % k);  // 环形规则：从 i % k 开始，找编号不小于它的最小空闲服务器
            if (p == free.end()) p = free.begin();  // 后面已无空闲服务器，回绕到编号最小的那台
            int server = *p;  // 选中的服务器编号
            ++cnt[server];  // 该服务器处理的请求数加一
            busy.emplace(end, server);  // 把「忙完时刻, 服务器编号」压入小根堆，等待之后归还
            free.erase(server);  // 该服务器进入忙碌状态，从空闲集合中移除
        }  // 请求处理循环结束
        int mx = *max_element(cnt.begin(), cnt.end());  // 所有服务器中的最大处理请求数
        vector<int> ans;  // 保存答案：处理了最多请求的服务器编号
        for (int i = 0; i < k; ++i)  // 从小到大遍历服务器编号
            if (cnt[i] == mx)  // 处理数恰好等于最大值
                ans.push_back(i);  // 记录该服务器编号
        return ans;  // 返回结果（题目要求编号升序）
    }
};