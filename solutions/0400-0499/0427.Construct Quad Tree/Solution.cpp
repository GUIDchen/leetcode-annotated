// 题目：427. 建立四叉树（Construct Quad Tree）
// 思路：递归处理子矩阵，先扫描判断该区域是否只含一种值：是则返回叶子节点，否则四等分后递归构造四个子节点再合并。
// 时间复杂度：O(n^2 log n)，每层扫描 O(n^2) 共 log n 层；空间复杂度：O(log n)，递归栈深度。
// 说明：下面是题目自带的 QuadTree Node 定义（被注释掉，由判题器提供），仅作参考。
/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {  // LeetCode 题解类
public:  // 方法对外可见
    Node* construct(vector<vector<int>>& grid) {  // grid：由 0/1 组成的 n x n 方阵，返回四叉树的根节点
        return dfs(0, 0, grid.size() - 1, grid[0].size() - 1, grid);  // 从整个矩阵（左上角到右下角）开始递归构造
    }

    Node* dfs(int a, int b, int c, int d, vector<vector<int>>& grid) {  // 处理行区间 [a, c]、列区间 [b, d] 这块子矩阵
        int zero = 0, one = 0;  // 标记这块区域里是否出现过 0 和 1
        for (int i = a; i <= c; ++i) {  // 枚举行
            for (int j = b; j <= d; ++j) {  // 枚举列
                if (grid[i][j])  // 当前格子是 1
                    one = 1;  // 记录出现过 1
                else  // 当前格子是 0
                    zero = 1;  // 记录出现过 0
            }
        }
        bool isLeaf = zero + one == 1;  // 只出现过一种值，说明区域同色，可以作为叶子
        bool val = isLeaf && one;  // 叶子的值：全为 1 取 true，全为 0 取 false
        Node* node = new Node(val, isLeaf);  // 按（值，是否叶子）创建节点
        if (isLeaf) return node;  // 叶子节点无需继续分裂，直接返回
        node->topLeft = dfs(a, b, (a + c) / 2, (b + d) / 2, grid);  // 左上子块：行 [a, mid]、列 [b, mid]
        node->topRight = dfs(a, (b + d) / 2 + 1, (a + c) / 2, d, grid);  // 右上子块：行 [a, mid]、列 [mid+1, d]
        node->bottomLeft = dfs((a + c) / 2 + 1, b, c, (b + d) / 2, grid);  // 左下子块：行 [mid+1, c]、列 [b, mid]
        node->bottomRight = dfs((a + c) / 2 + 1, (b + d) / 2 + 1, c, d, grid);  // 右下子块：行 [mid+1, c]、列 [mid+1, d]
        return node;  // 返回合并后的内部节点
    }  // dfs 结束
};  // 类定义结束