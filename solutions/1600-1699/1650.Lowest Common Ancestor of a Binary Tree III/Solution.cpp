// 题目：1650. 二叉树的最近公共祖先 III（Lowest Common Ancestor of a Binary Tree III）
// 思路：从 p 沿 parent 向上把整条祖先链放入哈希集合，再从 q 沿 parent 向上，第一个命中的节点就是最近公共祖先。
// 时间复杂度：O(h)，h 为树高；空间复杂度：O(h)，集合存放 p 的祖先链。
// 下面的 /* */ 是题目自带的结构体说明，保持原样
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    Node* lowestCommonAncestor(Node* p, Node* q) {  // 返回 p、q 的最近公共祖先（节点带 parent 指针）
        unordered_set<Node*> vis;  // 哈希集合：记录 p 到根路径上的所有节点
        for (Node* node = p; node; node = node->parent) {  // 从 p 开始沿 parent 向上，node 为空表示越过根
            vis.insert(node);  // 把当前节点标记为 p 的祖先
        }  // 祖先链收集结束
        for (Node* node = q;; node = node->parent) {  // 从 q 开始沿 parent 向上；根必在集合中，所以省略终止条件
            if (vis.count(node)) {  // 第一个已经在集合里的节点就是最近公共祖先
                return node;  // 立即返回该祖先
            }  // 条件体结束
        }  // 外层循环结束
    }  // 方法结束
};  // Solution 类定义结束