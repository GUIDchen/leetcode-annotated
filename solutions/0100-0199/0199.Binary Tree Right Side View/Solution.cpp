// 题目：199. 二叉树的右视图（Binary Tree Right Side View）
// 思路：层序遍历（BFS）。每层先把右孩子入队、再入左孩子，于是队首始终是该层最右侧的节点，取走后再整层出队。
// 时间复杂度：O(n)，每个节点只进出队列一次；空间复杂度：O(n)，队列最坏保存一整层的节点。
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
    vector<int> rightSideView(TreeNode* root) {  // root：二叉树根节点；返回从右侧能看到的每层最右节点值，自上而下排列
        vector<int> ans;  // 收集每层最右侧节点的值
        if (!root) {  // 空树没有可见节点
            return ans;  // 直接返回空数组
        }
        queue<TreeNode*> q{{root}};  // BFS 队列，初始只放入根节点
        while (q.size()) {  // 队列非空说明还存在未处理的一层
            ans.push_back(q.front()->val);  // 因为入队顺序是「先右后左」，队首恰好是本层最右节点，先把它记入答案
            for (int k = q.size(); k; --k) {  // 循环次数预先固定为本层节点数，保证一次刚好处理完一整层
                auto node = q.front();  // 取出当前层的队首节点
                q.pop();  // 从队列中移除该节点
                if (node->right) {  // 右孩子先入队，才能成为下一层的队首（下一层的右视图来源）
                    q.push(node->right);  // 把右孩子压入队列
                }
                if (node->left) {  // 再处理左孩子
                    q.push(node->left);  // 把左孩子压入队列
                }
            }
        }
        return ans;  // 返回每层最右侧的值
    }
};
