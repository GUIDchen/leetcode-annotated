// 题目：802. 找到最终的安全状态（Find Eventual Safe States）
// 思路：反向建图后做拓扑排序，从出度为 0 的节点开始不断剥离，最终出度被削到 0 的节点就是安全节点。
// 时间复杂度：O(n + m)，n 为节点数、m 为边数；空间复杂度：O(n + m)，存反向图与出度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {  // graph：邻接表；返回所有安全节点（按下标升序）
        int n = graph.size();  // 节点个数
        vector<int> indeg(n);  // 每个节点的有效出度，拓扑剥离时会递减到 0
        vector<vector<int>> rg(n);  // 反向图：rg[v] 保存所有指向 v 的起点
        queue<int> q;  // 拓扑队列，存放已确认出度为 0 的节点
        for (int i = 0; i < n; ++i) {  // 遍历每个节点，一次完成建反向图与统计出度
            for (int j : graph[i]) rg[j].push_back(i);  // 原图的边 i → j 反向记到 rg[j] 中
            indeg[i] = graph[i].size();  // 初始出度就是原图中该节点的边数
            if (indeg[i] == 0) q.push(i);  // 出度为 0 说明走不出去，天然安全，直接入队
        }  // 建图结束
        while (!q.empty()) {  // 不断剥离已确认安全的节点
            int i = q.front();  // 取出队头节点
            q.pop();  // 弹出该节点
            for (int j : rg[i])  // 遍历所有指向 i 的前驱 j
                if (--indeg[j] == 0) q.push(j);  // 前驱少掉一条出边，降为 0 时它也安全，入队
        }  // 拓扑循环结束
        vector<int> ans;  // 收集答案
        for (int i = 0; i < n; ++i)  // 按下标从小到大扫描
            if (indeg[i] == 0) ans.push_back(i);  // 出度被削到 0 的节点就是安全节点
        return ans;  // 返回值天然是升序的
    }  // 方法结束
};  // 类定义结束