// 题目：662. 二叉树最大宽度（Maximum Width of Binary Tree）
// 核心思路：BFS 给节点按满二叉树编号，每层宽度 = 最右编号 - 最左编号 + 1。
// 时间复杂度：O(n)，每个节点进出队一次；空间复杂度：O(n)，队列最多存一层节点。
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
public:
    int widthOfBinaryTree(TreeNode* root) {  // 求所有层中最大的宽度（层内最左与最右非空节点之间的编号跨度）
        queue<pair<TreeNode*, int>> q;  // 队列元素：节点指针 + 它在满二叉树中的编号
        q.push({root, 1});  // 根节点编号从 1 开始
        int ans = 0;  // ans 记录各层宽度的最大值
        while (!q.empty()) {  // 逐层处理，队列不空就继续
            ans = max(ans, q.back().second - q.front().second + 1);  // 本层最右编号 - 最左编号 + 1 就是本层宽度
            int i = q.front().second;  // 记下本层最左编号，用于把下一层编号整体平移
            for (int n = q.size(); n; --n) {  // 循环次数固定为当前层节点数，从而只弹出这一层
                auto p = q.front();  // 取出队头元素
                q.pop();  // 立即弹出，避免与后续入队混淆
                root = p.first;  // 拆出节点指针
                int j = p.second;  // 拆出该节点的满二叉树编号
                if (root->left) q.push({root->left, (j << 1) - (i << 1)});  // 左孩子编号 2j，减去 2i 做平移，避免编号指数增长溢出
                if (root->right) q.push({root->right, (j << 1 | 1) - (i << 1)});  // 右孩子编号 2j+1，同样减去 2i 做平移
            }
        }
        return ans;  // 返回最大宽度
    }
};  // 题解类定义结束