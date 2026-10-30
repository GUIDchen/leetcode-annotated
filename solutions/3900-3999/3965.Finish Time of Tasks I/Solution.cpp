// 3965. 任务完成时间 I / Finish Time of Tasks I
// 核心思路：建出以 0 为根的树后自底向上 DFS 求每个任务的完成时间：叶子取 baseTime[i]，
//          非叶子先求子任务完成时间的最小值 earliest 与最大值 latest，自身耗时 = (latest-earliest) + baseTime[i]，完成时间为 latest + 自身耗时。
// 复杂度：时间 O(n)（每个任务只访问一次），空间 O(n)（邻接表与递归栈）。

class Solution {
public:
    long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime) {  // 返回根任务 0 的完成时间
        vector<vector<int>> g(n);  // 邻接表，g[u] 存放任务 u 的所有子任务

        for (auto& e : edges) {  // 遍历每条父子边
            g[e[0]].push_back(e[1]);  // 记录任务 e[0] 的子任务是 e[1]
        }

        auto dfs = [&](this auto&& dfs, int i) -> long long {  // 递归求任务 i 的完成时间
            if (g[i].empty()) {  // 叶子任务没有子任务
                return baseTime[i];  // 叶子完成时间就是自身耗时
            }

            long long earliest = LLONG_MAX / 4;  // 子任务完成时间的最小值，初值为足够大的数
            long long latest = -LLONG_MAX / 4;  // 子任务完成时间的最大值，初值为足够小的数

            for (int j : g[i]) {  // 遍历任务 i 的每个子任务
                long long a = dfs(j);  // 递归得到子任务 j 的完成时间
                earliest = min(earliest, a);  // 更新最早的子任务完成时间
                latest = max(latest, a);  // 更新最晚的子任务完成时间
            }

            long long own_duration = (latest - earliest) + baseTime[i];  // 自身耗时：等待跨度加上基础耗时
            return latest + own_duration;  // 完成时间 = 最晚子任务完成时间 + 自身耗时
        };

        return dfs(0);  // 从根任务 0 开始计算并返回其完成时间
    }
};
