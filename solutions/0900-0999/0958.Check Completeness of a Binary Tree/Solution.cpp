// 题目：958. 二叉树的完全性检验（Check Completeness of a Binary Tree）
// 思路：层序遍历时把空儿子也入队，第一次取到空节点后继续扩展，最后检查队列里是否还剩真实节点；只要有一个真实节点就不是完全二叉树。
// 时间复杂度：O(n)，每个节点最多入队一次；空间复杂度：O(n)，队列最坏存下一整层的节点。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isCompleteTree(TreeNode* root) {  // root：二叉树根节点，返回这棵树是否为完全二叉树
        queue<TreeNode*> q{{root}};  // 层序遍历队列，先放入根节点
        while (q.front()) {  // 只要队首不是空节点就继续扩展；第一次取到空节点说明开始出现缺口
            root = q.front();  // 取出队首节点作为当前节点
            q.pop();  // 队首出队，避免死循环
            q.push(root->left);  // 左儿子入队，即使是空节点也要入队，用来占住它的位置
            q.push(root->right);  // 右儿子入队，同样允许为空
        }
        while (!q.empty() && !q.front()) q.pop();  // 缺口之后剩下的空节点全部丢掉，只保留可能存在的真实节点
        return q.empty();  // 队列已空说明缺口后面没有真实节点，是完全二叉树
    }  // 方法结束
};  // 类定义结束