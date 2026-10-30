// 题目：444. 序列重建（Sequence Reconstruction）
// 思路：把每个 sequences 里相邻的二元关系建成有向图，做拓扑排序；只有每一步候选入度为 0 的点都恰好一个（队列长度始终为 1），最短超序列才唯一。
// 复杂度：时间复杂度 O(n + 所有序列长度之和)，建图加拓扑排序各扫一遍；空间复杂度 O(n + 边数)。
class Solution {  // 题解类：判断 nums 是否是 sequences 的唯一最短超序列
public:  // 公开部分
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {  // nums 是候选的完整排列（1..n），sequences 是一些短子序列
        int n = nums.size();  // n 同时也是元素种类数
        vector<int> indeg(n);  // 每个点的入度，初始全为 0
        vector<int> g[n];  // 邻接表，g[a] 存放下标 a 的所有后继
        for (auto& seq : sequences) {  // 遍历每个子序列，把相邻的两个元素变成一条有向边
            for (int i = 1; i < seq.size(); ++i) {  // 从第二个元素开始，与它的前一个元素连边
                int a = seq[i - 1] - 1, b = seq[i] - 1;  // 值 1..n 映射成下标 0..n-1
                g[a].push_back(b);  // 记录有向边 a -> b
                ++indeg[b];  // b 的入度加一
            }  // 当前子序列的边建完了
        }  // 所有子序列处理完毕
        queue<int> q;  // BFS 队列：存放入度为 0 的点
        for (int i = 0; i < n; ++i) {  // 先把所有入度为 0 的点入队作为初始候选
            if (indeg[i] == 0) {  // 该点没有前驱
                q.push(i);  // 可以作为序列的开头
            }  // 闭合 if
        }  // 初始化结束
        while (q.size() == 1) {  // 队列里始终恰好一个点，才说明每一步选择唯一，拓扑序唯一
            int i = q.front();  // 取出唯一的候选点
            q.pop();  // 出队
            for (int j : g[i]) {  // 遍历它的所有后继
                if (--indeg[j] == 0) {  // 后继入度减一，减到 0 才能入队
                    q.push(j);  // 新的候选点入队
                }  // 闭合 if
            }  // 后继处理完毕
        }  // 一旦队列长度不是 1（0 或大于 1）就退出循环
        return q.empty();  // 队列为空说明所有点都被唯一地依次取出，拓扑序唯一
    }  // sequenceReconstruction 方法结束
};  // Solution 类定义结束