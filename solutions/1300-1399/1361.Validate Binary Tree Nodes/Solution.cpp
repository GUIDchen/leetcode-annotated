// 题目：1361. 验证二叉树（Validate Binary Tree Nodes）
// 思路：并查集 + 入度标记。每个孩子最多一个父亲（vis 判重），连边不能成环（find 相同即为环），最终连通分量必须恰好为 1。
// 时间复杂度：O(n α(n))，并查集近似常数；空间复杂度：O(n)，父数组与 vis 数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {  // n：节点数；leftChild/rightChild：每个节点的左右孩子下标，-1 表示没有孩子
        int p[n];  // 并查集父数组，p[x] 是 x 当前所在集合的父指针
        iota(p, p + n, 0);  // 初始时每个节点各自成集合（p[i] = i）
        bool vis[n];  // 标记某个节点是否已经被父亲认领（入度是否已达 1）
        memset(vis, 0, sizeof(vis));  // 初始没有任何节点被认领
        function<int(int)> find = [&](int x) {  // 递归 lambda：查找 x 所在集合的根，并在回溯时做路径压缩
            return p[x] == x ? x : p[x] = find(p[x]);  // 若 x 已是根就返回；否则把 p[x] 直接指向根
        };  // lambda 定义结束
        for (int i = 0, m = n; i < m; ++i) {  // 遍历每个节点 i；m 保存原始节点数，因为后面 n 会被自减
            for (int j : {leftChild[i], rightChild[i]}) {  // 依次取出 i 的左孩子与右孩子
                if (j != -1) {  // -1 表示该孩子不存在，跳过
                    if (vis[j] || find(i) == find(j)) {  // 孩子已被认领（入度≥2）或 i 与 j 已连通（再连边会成环）
                        return false;  // 违反二叉树定义，立刻返回 false
                    }  // 非法情况判断结束
                    p[find(i)] = find(j);  // 合并集合：把 i 的根挂到 j 的根下，表示 i 是 j 的父亲
                    vis[j] = true;  // 标记 j 已经有父亲
                    --n;  // 每成功连一条边，连通分量数减一
                }  // if (j != -1) 结束
            }  // 左右孩子遍历结束
        }  // 节点遍历结束
        return n == 1;  // 连通分量恰好为 1 才是合法二叉树
    }  // 方法结束
};  // 类定义结束