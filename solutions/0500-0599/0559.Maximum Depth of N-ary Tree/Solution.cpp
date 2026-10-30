// 题目：559. N 叉树的最大深度（Maximum Depth of N-ary Tree）
// 核心思路：深搜每个孩子，取所有子树深度的最大值再加一（本层）。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高。
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
*/

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxDepth(Node* root) {  // root：N 叉树根节点，返回从根到最深叶子的节点数
        if (!root) {  // 空树深度为 0，是递归的终止条件
            return 0;  // 空节点没有层数
        }  // 判断结束
        int mx = 0;  // 记录所有孩子子树中的最大深度
        for (Node* child : root->children) {  // 逐个孩子递归求深度
            mx = max(mx, maxDepth(child));  // 用较大者更新最大子树深度
        }  // 孩子遍历结束
        return mx + 1;  // 最深的子树深度加上当前这一层
    }  // 方法结束
};  // 类定义结束
