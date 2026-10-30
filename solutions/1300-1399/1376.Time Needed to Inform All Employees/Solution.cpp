// 题目：1376. 通知所有员工所需的时间（Time Needed to Inform All Employees）
// 思路：按 manager 数组建出「上级 → 下级」的树，从总负责人 headID 做一次 DFS，取所有根到叶路径耗时的最大值。
// 时间复杂度：O(n)，建图与遍历都只处理 n 个结点；空间复杂度：O(n)，邻接表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {  // n 是员工数，headID 是总负责人，manager 记录上级，informTime 记录该员工通知下级所需时间
        vector<vector<int>> g(n);  // 邻接表：g[i] 存放员工 i 的直接下级
        for (int i = 0; i < n; ++i) {  // 遍历每个员工，建立「上级 → 下级」的边
            if (manager[i] >= 0) {  // 总负责人 manager 为 -1 没有上级；其余员工的上级都有效
                g[manager[i]].push_back(i);  // 把员工 i 挂到他的上级 manager[i] 的下级列表里
            }  // 根结点判断结束
        }  // 建图循环结束
        function<int(int)> dfs = [&](int i) -> int {  // 递归 DFS：返回从员工 i 开始通知他整棵子树所需的时间
            int ans = 0;  // 记录以 i 为根的子树中最慢的那条链的耗时
            for (int j : g[i]) {  // 逐个处理员工 i 的直接下级
                ans = max(ans, dfs(j) + informTime[i]);  // 下级 j 的子树耗时要加上 i 通知下级所需的 informTime[i]，取最大值
            }  // 下级循环结束
            return ans;  // 返回该子树的最长耗时
        };  // lambda 定义结束
        return dfs(headID);  // 从总负责人出发，DFS 的结果就是通知全体员工所需的时间
    }  // 方法结束
};  // 类定义结束
