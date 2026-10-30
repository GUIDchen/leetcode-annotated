// 题目：1557. 可以到达所有点的最少点数目（Minimum Number of Vertices to Reach All Nodes）
// 思路：入度为 0 的点没有别的点能到达它，必须亲自作为起点；而这些点又能通过 DAG 到达其余所有点，所以答案就是全部入度为 0 的点。
// 时间复杂度：O(n + m)，n 为点数、m 为边数；空间复杂度：O(n)，入度数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {  // n：节点个数（编号 0..n-1）；edges：有向边列表，每条边形如 [u, v]
        vector<int> cnt(n);  // cnt[i] 记录节点 i 的入度，默认初始化成 0
        for (auto& e : edges) {  // 逐条边累加终点入度
            ++cnt[e[1]];  // e[1] 是边的终点，入度加一
        }  // 左花括号结束循环体
        vector<int> ans;  // 保存答案：所有入度为 0 的节点
        for (int i = 0; i < n; ++i) {  // 按编号从小到大扫描每个节点，保证答案有序
            if (cnt[i] == 0) {  // 入度为 0 说明没有入边，它不可能被别的点到达
                ans.push_back(i);  // 只能把它自己选作起点，收进答案
            }  // 右花括号
        }  // 右花括号
        return ans;  // 返回最少的点集：恰好是所有入度为 0 的点
    }  // 方法结束
};  // 类定义结束