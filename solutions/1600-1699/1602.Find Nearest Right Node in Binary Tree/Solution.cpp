// 题目：1602. 找到二叉树中最近的右侧节点（Find Nearest Right Node in Binary Tree）
// 思路：BFS 按层遍历，处理本层节点时若遇到 u，则同层右侧还有节点就返回队列中的下一个节点，否则返回空。
// 时间复杂度：O(n)，每个节点最多入队出队一次；空间复杂度：O(w)，w 为树的最大层宽。
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
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {  // root 为树根，u 为目标节点
        queue<TreeNode*> q{{root}};  // BFS 队列，用根节点初始化
        while (q.size()) {  // 队列非空说明还有层没处理
            for (int i = q.size(); i; --i) {  // 只处理当前这一层的 i 个节点
                root = q.front();  // 取出队首节点
                q.pop();  // 并把它从队列中弹出
                if (root == u) {  // 找到目标节点 u
                    return i > 1 ? q.front() : nullptr;  // i > 1 说明同层右侧还有节点，即队首；否则 u 是本层最后一个节点
                }  // 目标判断结束
                if (root->left) {  // 左孩子存在才入队
                    q.push(root->left);  // 左孩子加入队尾
                }  // 左孩子判断结束
                if (root->right) {  // 右孩子存在才入队
                    q.push(root->right);  // 右孩子加入队尾
                }  // 右孩子判断结束
            }  // 本层遍历结束
        }  // 层序遍历结束
        return nullptr;  // 没找到 u，或 u 的右侧没有节点
    }  // 方法结束
};  // 类结束