// 题目：513. 找树左下角的值（Find Bottom Left Tree Value）
// 思路：BFS 按层遍历，每层的第一个节点就是该行的最左节点，逐层覆盖记录，遍历结束时留下的就是最后一层最左值。
// 时间复杂度：O(n)，每个节点进出队各一次；空间复杂度：O(n)，队列最多保存一层节点。
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
    int findBottomLeftValue(TreeNode* root) {  // root：二叉树根节点；返回最后一行的最左值
        queue<TreeNode*> q{{root}};  // BFS 队列，初始只放根节点
        int ans = 0;  // 保存每行最左边的值，最后一层覆盖后即为答案
        while (!q.empty()) {  // 队列非空说明还有层没处理
            ans = q.front()->val;  // 当前层的队首就是本行最左节点，先记下它的值
            for (int i = q.size(); i; --i) {  // 只弹出当前层的 q.size() 个节点，保证按层处理
                TreeNode* node = q.front();  // 取出队首节点
                q.pop();  // 把它从队列中移除
                if (node->left) q.push(node->left);  // 有左孩子就入队，成为下一层的节点
                if (node->right) q.push(node->right);  // 有右孩子就入队
            }  // 当前这一层处理完毕
        }  // 所有层都处理完毕
        return ans;  // 返回最后一层最左边的值
    }  // 方法结束
};  // 类定义结束