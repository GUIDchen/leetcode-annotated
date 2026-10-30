// 题目：1302. 层数最深叶子节点的和（Deepest Leaves Sum）
// 思路：层序遍历（BFS）。每处理完一层就把累加和清零，循环结束时留下的正是最深一层的叶子节点之和。
// 时间复杂度：O(n)，每个节点进出队列一次；空间复杂度：O(n)，队列最多存一层节点。
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
    int deepestLeavesSum(TreeNode* root) {  // root：二叉树根节点
        int ans = 0;  // 当前这一层所有节点的值之和
        queue<TreeNode*> q{{root}};  // 层序遍历队列，初始只有根节点
        while (!q.empty()) {  // 队列非空说明还存在下一层
            ans = 0;  // 进入新的一层先清零，最后留下的就是最深层的和
            for (int k = q.size(); k; --k) {  // 用当前队列长度固定次数，只弹出本层节点
                TreeNode* node = q.front();  // 取出队首节点
                q.pop();  // 弹出队首
                ans += node->val;  // 累加该节点的值
                if (node->left) {  // 有左孩子就入队
                    q.push(node->left);  // 左孩子成为下一层节点
                }
                if (node->right) {  // 有右孩子就入队
                    q.push(node->right);  // 右孩子成为下一层节点
                }
            }
        }
        return ans;  // 循环结束时 ans 累加的就是最深叶子层的和
    }
};
