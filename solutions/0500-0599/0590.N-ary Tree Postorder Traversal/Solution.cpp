// 题目：590. N 叉树的后序遍历（N-ary Tree Postorder Traversal）
// 思路：递归 DFS，先按顺序对每个孩子递归，最后才记录根节点的值（后序 = 各子树 → 根）。
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
    vector<int> postorder(Node* root) {  // root 是 N 叉树的根节点
        vector<int> ans;  // 存放后序遍历结果
        function<void(Node*)> dfs = [&](Node* root) {  // 递归 lambda，按引用捕获 ans，方便不断追加结果
            if (!root) {  // 空节点直接返回
                return;  // 递归出口
            }
            for (auto& child : root->children) {  // 后序：先把所有孩子都处理完
                dfs(child);  // 对孩子递归，保证子树的结果先于根节点写入
            }
            ans.push_back(root->val);  // 最后才记录根节点的值
        };
        dfs(root);  // 从根节点开始执行递归
        return ans;  // 返回遍历结果
    }
};
