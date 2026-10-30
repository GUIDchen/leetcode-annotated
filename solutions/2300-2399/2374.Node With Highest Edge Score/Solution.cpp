// 题目：2374. 边积分最高的节点（Node With Highest Edge Score）
// 思路：每条边 i -> edges[i] 把起点编号 i 累加到终点 edges[i] 的分数上，边遍历边维护最高分节点（同分取编号小）。
// 时间复杂度：O(n)，只扫描一遍边数组；空间复杂度：O(n)，cnt 数组记录每个节点的边积分。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int edgeScore(vector<int>& edges) {  // edges[i] 表示一条从 i 指向 edges[i] 的有向边
        int n = edges.size();  // 节点个数，也等于边的条数
        vector<long long> cnt(n);  // cnt[j] 是终点为 j 的所有边的起点编号之和；用 long long 防溢出
        int ans = 0;  // 当前边积分最高的节点，初始为 0 号节点
        for (int i = 0; i < n; ++i) {  // 逐条处理边，i 既是下标也是该边的起点
            int j = edges[i];  // 这条边的终点
            cnt[j] += i;  // 把起点编号 i 计入终点 j 的边积分
            if (cnt[ans] < cnt[j] || (cnt[ans] == cnt[j] && j < ans)) {  // 分数更高，或同分但编号更小
                ans = j;  // 更新答案
            }
        }
        return ans;  // 返回边积分最高（同分取最小编号）的节点
    }
};
