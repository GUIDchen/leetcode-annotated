// 题目：1483. 树节点的第 K 个祖先（Kth Ancestor of a Tree Node）
// 核心思路：倍增法预处理 p[i][j] 表示节点 i 向上 2^j 步的祖先，查询时把 k 拆成二进制逐位跳跃。
// 时间复杂度：预处理 O(n log n)，单次查询 O(log n)；空间复杂度：O(n log n)，存放倍增表。
class TreeAncestor {  // 题解类：构造时预处理，之后支持 O(log k) 查询第 k 个祖先
public:  // 构造与查询方法对外可见
    TreeAncestor(int n, vector<int>& parent) {  // n：节点数；parent[i] 是 i 的父亲（根节点的父亲为 -1）
        p = vector<vector<int>>(n, vector<int>(18, -1));  // p[i][j] 表示节点 i 向上 2^j 步的祖先，-1 表示不存在，18 位足够覆盖 n ≤ 5*10^4
        for (int i = 0; i < n; ++i) {  // 先填写 j = 0 这一层（2^0 = 1 步）
            p[i][0] = parent[i];  // 向上一步就是直接父亲
        }  // for 循环体结束
        for (int j = 1; j < 18; ++j) {  // 倍增递推：由 2^(j-1) 推出 2^j
            for (int i = 0; i < n; ++i) {  // 对每个节点求第 2^j 个祖先
                if (p[i][j - 1] == -1) {  // 中间祖先不存在
                    continue;  // 该项保持 -1，直接跳过
                }  // if 分支结束
                p[i][j] = p[p[i][j - 1]][j - 1];  // 先跳 2^(j-1) 步到中间节点，再跳 2^(j-1) 步，合计 2^j 步
            }  // 内层循环结束
        }  // 外层循环结束
    }  // 构造函数结束

    int getKthAncestor(int node, int k) {  // node：起点；k：向上步数；返回第 k 个祖先，不存在返回 -1
        for (int i = 17; ~i; --i) {  // 从最高位 17 枚举到 0，~i 等价于 i >= 0
            if (k >> i & 1) {  // k 的第 i 个二进制位为 1，需要跳 2^i 步
                node = p[node][i];  // 一次向上跳 2^i 步
                if (node == -1) {  // 已经跳出根，说明第 k 个祖先不存在
                    break;  // 提前结束跳跃
                }  // if (node == -1) 分支结束
            }  // if (k >> i & 1) 分支结束
        }  // for 循环结束
        return node;  // 返回祖先编号，-1 表示不存在
    }  // getKthAncestor 方法结束

private:  // 私有成员区：倍增表不对外暴露
    vector<vector<int>> p;  // 倍增表：p[i][j] 存节点 i 的第 2^j 个祖先
};  // TreeAncestor 类定义结束

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */