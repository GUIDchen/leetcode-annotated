// 题目：797. 所有可能的路径（All Paths From Source to Target）
// 思路：从节点 0 出发做深度优先搜索，用 path 记录当前路径；走到终点 n-1 就把路径存进答案，回溯时弹栈继续尝试其他分支。
// 时间复杂度：O(n·2^n)，无环图的路径最多指数条且每条长度 O(n)；空间复杂度：O(n)，递归栈与单条路径。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> graph;  // 成员变量保存图，避免 dfs 每次传参
    vector<vector<int>> ans;  // 收集所有从 0 到 n-1 的路径

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {  // graph：有向无环图的邻接表
        this->graph = graph;  // 备份到成员变量，供 dfs 递归访问
        vector<int> path;  // 当前正在走的路径
        path.push_back(0);  // 起点 0 先入路径
        dfs(0, path);  // 从节点 0 开始深搜
        return ans;  // 返回全部合法路径
    }  // allPathsSourceTarget 结束

    void dfs(int i, vector<int> path) {  // i：当前节点；path：已走过的路径（按值传递，回溯互不影响）
        if (i == graph.size() - 1) {  // 走到终点 n-1
            ans.push_back(path);  // 记录这条完整路径
            return;  // 终点没有后继，直接返回
        }  // 终点判断结束
        for (int j : graph[i]) {  // 枚举当前节点的所有邻居
            path.push_back(j);  // 邻居加入路径
            dfs(j, path);  // 递归深入
            path.pop_back();  // 回溯：撤销邻居，尝试下一个分支
        }  // 邻居枚举结束
    }  // dfs 结束
};  // 类定义结束