// 3898. 统计每个顶点的度 / Find the Degree of Each Vertex
// 核心思路：无向图以邻接矩阵给出，逐行求和即得到每个顶点连出的边数，也就是该顶点的度。
// 复杂度：时间 O(n^2)，空间 O(1)（不计返回数组）。
class Solution {  // 定义题解类
public:  // 公有接口
    vector<int> findDegrees(vector<vector<int>>& matrix) {  // matrix 为邻接矩阵，返回每个顶点的度
        int n = matrix.size();  // 顶点个数
        vector<int> ans(n);  // 存放各顶点的度，初值为 0
        for (int i = 0; i < n; ++i) {  // 逐个顶点统计
            for (int x : matrix[i]) {  // 遍历该顶点在邻接矩阵中的整行
                ans[i] += x;  // 累加该行元素即得到度数
            }  // 本行累加结束
        }  // 本顶点统计结束
        return ans;  // 返回每个顶点的度
    }  // findDegrees 结束
};  // 类定义结束
