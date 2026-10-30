// 题目：589. N 叉树的前序遍历（N-ary Tree Preorder Traversal）
// 思路：递归 DFS，先记录根节点的值，再按顺序对每个孩子递归（前序 = 根 → 各子树）。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，答案数组与递归栈（最坏 n 层）。
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
    vector<int> preorder(Node* root) {  // root 是 N 叉树的根节点
        vector<int> ans;  // 存放前序遍历结果
        function<void(Node*)> dfs = [&](Node* root) {  // 递归 lambda，按引用捕获 ans，方便不断追加结果
            if (!root) {  // 空节点直接返回
                return;  // 递归出口
            }
            ans.push_back(root->val);  // 前序：先记录根节点的值
            for (auto& child : root->children) {  // 再依次遍历每个孩子
                dfs(child);  // 对孩子递归，保持「根先于子树」的访问顺序
            }
        };
        dfs(root);  // 从根节点开始执行递归
        return ans;  // 返回遍历结果
    }
};
