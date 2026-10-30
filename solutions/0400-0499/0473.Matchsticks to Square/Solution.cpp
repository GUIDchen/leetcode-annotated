// 题目：473. 火柴拼正方形（Matchsticks to Square）
// 思路：总和必须能被 4 整除且最长火柴不超过边长；把火柴降序排序后用 DFS 逐根尝试放进 4 条边，并跳过等长的重复边做剪枝。
// 时间复杂度：O(4^n) 最坏（n 为火柴数，降序加剪枝后远快于此）；空间复杂度：O(n)，递归栈深度等于火柴数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool makesquare(vector<int>& matchsticks) {  // matchsticks 是每根火柴的长度
        int s = 0, mx = 0;  // s 记录总长度，mx 记录最长的一根火柴
        for (int& v : matchsticks) {  // 遍历所有火柴，一次求出总和与最大值
            s += v;  // 累加总长度
            mx = max(mx, v);  // 更新最长火柴
        }
        int x = s / 4, mod = s % 4;  // x 是正方形边长，mod 是总长对 4 的余数
        if (mod != 0 || x < mx) return false;  // 总长不是 4 的倍数，或最长火柴超过边长，都无法拼成正方形
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());  // 降序排序：先放长火柴，能更早触发剪枝
        vector<int> edges(4);  // edges[i] 记录第 i 条边当前已放火柴的长度
        return dfs(0, x, matchsticks, edges);  // 从第 0 根火柴开始回溯搜索
    }

    bool dfs(int u, int x, vector<int>& matchsticks, vector<int>& edges) {  // u 是当前火柴下标，x 是目标边长，edges 是四条边的当前长度
        if (u == matchsticks.size()) return true;  // 所有火柴都放完了，说明四条边都凑齐
        for (int i = 0; i < 4; ++i) {  // 尝试把当前火柴放进 4 条边中的某一条
            if (i > 0 && edges[i - 1] == edges[i]) continue;  // 若前一条边与当前边长度相同就跳过，避免重复枚举等价的边
            edges[i] += matchsticks[u];  // 先放进去，更新该边长度
            if (edges[i] <= x && dfs(u + 1, x, matchsticks, edges)) return true;  // 不超过边长且后续也能成功，则整体可行
            edges[i] -= matchsticks[u];  // 回溯：撤销这一步的放置
        }
        return false;  // 4 条边都放不下，说明当前分支无解
    }
};