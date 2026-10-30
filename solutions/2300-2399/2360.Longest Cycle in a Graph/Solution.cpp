// 题目：2360. 图中的最长环（Longest Cycle in a Graph）
// 思路：每个点出度至多为 1，每个连通块形如“链 + 环”；从每个未访问点沿出边走到无路或撞到已访问点，再在本次路径中定位环并取最长。
// 时间复杂度：O(n)，每个点至多被访问一次；空间复杂度：O(n)，访问标记数组与路径数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int longestCycle(vector<int>& edges) {  // edges：每个点唯一的出边，-1 表示没有出边；返回最长环的长度
        int n = edges.size();  // n 为节点总数
        vector<bool> vis(n);  // 访问标记，保证每个点只被走一次
        int ans = -1;  // 没有环时按题目要求返回 -1
        for (int i = 0; i < n; ++i) {  // 依次枚举尚未访问的点作为起点
            if (vis[i]) {  // 已经访问过，说明属于之前处理过的链或环，直接跳过
                continue;  // 跳过当前点
            }  // 跳过判断结束
            int j = i;  // 从 i 开始沿出边前进
            vector<int> cycle;  // 记录本次走过的点（按访问顺序）
            for (; j != -1 && !vis[j]; j = edges[j]) {  // 一直走到无出边（j == -1）或遇到已访问点为止
                vis[j] = true;  // 标记当前点已访问，之后不会再重复处理
                cycle.push_back(j);  // 把当前点按顺序记入本次路径
            }  // 路径遍历结束
            if (j == -1) {  // 走到链尾：没有形成环
                continue;  // 本连通块没有环，继续处理下一个起点
            }  // 走到这里说明遇到了已访问点，可能成环
            for (int k = 0; k < cycle.size(); ++k) {  // 在本次路径中查找 j 的位置，它之后的部分就是环
                if (cycle[k] == j) {  // 找到了环的入口 j
                    ans = max(ans, (int) cycle.size() - k);  // 环长 = 路径总长减去环入口前的链长
                    break;  // 只记录一次即可退出
                }  // 环入口判断结束
            }  // 查找环长结束
        }  // 起点枚举结束
        return ans;  // 返回最长环的长度
    }  // 方法结束
};  // 类定义结束