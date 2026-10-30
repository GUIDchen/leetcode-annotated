// 题目：1490. 克隆 N 叉树（Clone N-ary Tree）
// 核心思路：后序遍历递归，先把所有子节点克隆成新列表，再用原值和新子节点列表构造当前节点的副本。
// 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，新树与递归栈。
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
    Node* cloneTree(Node* root) {  // 返回 root 的深拷贝，原树与新树不共享任何节点
        if (!root) {  // 空节点
            return root;  // 直接返回空指针
        }  // if (!root) 分支结束
        vector<Node*> children;  // 收集克隆后的子节点
        for (Node* child : root->children) {  // 逐个处理原树的子节点
            children.emplace_back(cloneTree(child));  // 递归克隆子节点并加入列表
        }  // for 循环结束
        return new Node(root->val, children);  // 用原值和新子节点列表构造当前节点的副本
    }  // 方法结束
};  // Solution 类定义结束