// 题目：2096. 从二叉树一个节点到另一个节点每一步的方向（Step-By-Step Directions From a Binary Tree Node to Another）
// 思路：先求两节点的最近公共祖先，再从祖先分别 DFS 记录到起点、到终点的方向串；起点到祖先一律是 'U'。
// 时间复杂度：O(n)，常数次遍历整棵树；空间复杂度：O(n)，递归栈深度与路径长度。
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
public:  // 对外提供的题解方法
    string getDirections(TreeNode* root, int startValue, int destValue) {  // root：树根；startValue / destValue：起点与终点节点的值
        TreeNode* node = lca(root, startValue, destValue);  // 先求出两个节点的最近公共祖先，路径必然经过它
        string pathToStart, pathToDest;  // 分别保存祖先到起点、祖先到终点的方向串
        dfs(node, startValue, pathToStart);  // 搜索祖先到起点的路径
        dfs(node, destValue, pathToDest);  // 搜索祖先到终点的路径
        return string(pathToStart.size(), 'U') + pathToDest;  // 起点到祖先一律向上走 'U'，再拼上祖先到终点的方向串
    }

private:  // 以下为内部辅助函数
    TreeNode* lca(TreeNode* node, int p, int q) {  // 返回 node 子树中 p、q 的最近公共祖先
        if (node == nullptr || node->val == p || node->val == q) {  // 空节点或命中目标值就返回当前节点作为候选
            return node;  // 命中即作为候选祖先向上返回
        }
        TreeNode* left = lca(node->left, p, q);  // 在左子树里找
        TreeNode* right = lca(node->right, p, q);  // 在右子树里找
        if (left != nullptr && right != nullptr) {  // 左右都找到，说明当前节点就是分叉点（LCA）
            return node;  // 当前节点即为答案
        }
        return left != nullptr ? left : right;  // 只有一侧有结果就继续向上返回该结果
    }

    bool dfs(TreeNode* node, int x, string& path) {  // 在 node 子树中搜索 x，把沿途方向追加到 path
        if (node == nullptr) {  // 走到空节点说明这条路径不通
            return false;  // 回溯失败
        }
        if (node->val == x) {  // 找到目标节点
            return true;  // 成功，此时 path 中就是完整路径
        }
        path.push_back('L');  // 先假设走左子树，压入 'L'
        if (dfs(node->left, x, path)) {  // 左子树搜索成功
            return true;  // 保留路径，直接向上返回成功
        }
        path.back() = 'R';  // 左边不通，把这一位改成 'R' 去试右子树
        if (dfs(node->right, x, path)) {  // 右子树搜索成功
            return true;  // 保留路径，直接向上返回成功
        }
        path.pop_back();  // 两边都不通，撤销这一位方向后回溯
        return false;  // 说明 x 不在当前子树中
    }
};
