// 题目：102. 二叉树的层序遍历（Binary Tree Level Order Traversal）
// 思路：BFS。队列里逐层处理，每轮先记下当前层节点数，一次弹出这一层的全部节点并把下一层入队。
// 时间复杂度：O(n)，每个节点入队出队各一次；空间复杂度：O(w)，w 为树的最大宽度，即队列峰值。
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x, left), left(left), right(right) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> levelOrder(TreeNode* root) {  // root：树根，返回按层分组的值（自顶向下、每层自左向右）
        vector<vector<int>> ans;  // 答案：每个元素是某一层的值序列
        if (!root) return ans;  // 空树没有层，返回空答案
        queue<TreeNode*> q{{root}};  // 广度优先队列，先放入根节点
        while (!q.empty()) {  // 队列非空说明还有下一层要处理
            vector<int> t;  // 存放当前这一层的所有节点值
            for (int n = q.size(); n; --n) {  // 先固定当前层的节点个数，只弹出这么多，保证不会混入下一层
                auto node = q.front();  // 取出队首（本层最左未处理的节点）
                q.pop();  // 弹出队首，避免重复处理
                t.push_back(node->val);  // 把该节点的值追加到本层结果中
                if (node->left) {  // 左孩子存在
                    q.push(node->left);  // 左孩子入队，成为下一层的节点
                }
                if (node->right) {  // 右孩子存在
                    q.push(node->right);  // 右孩子入队，保证下一层自左向右的顺序
                }
            }
            ans.push_back(t);  // 本层处理完，整层追加到答案中
        }
        return ans;  // 返回自顶向下按层组织的遍历结果
    }
};