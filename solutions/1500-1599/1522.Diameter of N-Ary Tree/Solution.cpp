// 题目：1522. N 叉树的直径（Diameter of N-Ary Tree）🔒
// 核心思路：DFS 返回以当前节点为顶端向下延伸的最长链；在每个节点处把「最长链 + 次长链」当作经过它的路径来更新直径。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高（递归栈）。
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/  // 题目自带的 Node 结构说明（整段是块注释）到此结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int ans;  // 成员变量：记录当前找到的最大直径，dfs 过程中不断更新

    int diameter(Node* root) {  // root：N 叉树根节点，返回树的直径（任意两节点间最长路径的边数）
        ans = 0;  // 直径初值为 0
        dfs(root);  // 从根开始后序 DFS，过程中会刷新 ans
        return ans;  // 返回最大直径
    }  // 方法结束

    int dfs(Node* root) {  // 返回以 root 为顶端、向下延伸的最长链长度（边数）
        if (!root) return 0;  // 空节点没有链，返回 0
        int m1 = 0, m2 = 0;  // m1 是当前最长孩子链，m2 是次长孩子链
        for (Node* child : root->children) {  // 遍历所有孩子
            int t = dfs(child);  // 递归求出该孩子子树向下的最长链
            if (t > m1) {  // 比当前最长还长
                m2 = m1;  // 原来的最长降为次长
                m1 = t;  // 刷新最长
            } else if (t > m2)  // 否则若比次长更长
                m2 = t;  // 刷新次长（if/else 之间没有花括号，缩进就是语句体）
        }  // 孩子遍历结束
        ans = max(ans, m1 + m2);  // 经过当前节点最长的路径 = 最长链 + 次长链，用它更新直径
        return 1 + m1;  // 向上返回：当前节点自身这条边 + 最长孩子链
    }  // 方法结束
};  // 类定义结束
