// 题目：582. 杀掉进程（Kill Process）
// 核心思路：用哈希表把 ppid 映射到它的所有子进程，再从 kill 出发做一次 DFS，收集整棵进程子树。
// 时间复杂度：O(n)，建图与遍历都只访问每个进程一次；空间复杂度：O(n)，邻接表与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {  // pid 为进程号，ppid 为父进程号（下标一一对应），kill 为被杀进程
        unordered_map<int, vector<int>> g;  // 邻接表：键是父进程号，值是该父进程的所有子进程
        int n = pid.size();  // 进程总数
        for (int i = 0; i < n; ++i) {  // 逐对处理 (pid[i], ppid[i])
            g[ppid[i]].push_back(pid[i]);  // 把 pid[i] 记到它的父进程 ppid[i] 的子进程列表里
        }  // 建图结束
        vector<int> ans;  // 收集所有被终止的进程号
        function<void(int)> dfs = [&](int i) {  // 递归 DFS：终止进程 i 及其全部后代的进程
            ans.push_back(i);  // 当前进程被终止，加入答案
            for (int j : g[i]) {  // 遍历当前进程的每个子进程
                dfs(j);  // 递归终止子进程及其后代
            }  // 子进程遍历结束
        };  // lambda 定义结束
        dfs(kill);  // 从被 kill 的进程开始递归
        return ans;  // 返回所有被终止的进程号（顺序为 DFS 先序）
    }  // killProcess 结束
};  // 类定义结束
