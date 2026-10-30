// 题目：107. 二叉树的层序遍历 II（Binary Tree Level Order Traversal II）
// 思路：BFS 按层收集结点值，得到自顶向下的层序，最后把整个结果反转成自底向上。
// 时间复杂度：O(n)，每个结点进出队列一次；空间复杂度：O(n)，队列与结果数组。
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {  // root：树根；返回自底向上的层序遍历结果
        vector<vector<int>> ans;  // 结果容器：每个元素是某一层的结点值
        if (!root) {  // 空树没有层可遍历，直接返回
            return ans;  // 返回空的结果集合
        }  // 空树分支结束
        queue<TreeNode*> q{{root}};  // BFS 队列，先把根结点放进去
        while (!q.empty()) {  // 队列非空就说明还有层没处理
            vector<int> t;  // 收集当前这一层的结点值
            for (int n = q.size(); n; --n) {  // 先记下本层结点数，循环只弹这么多次，从而把层与层分开
                auto node = q.front();  // 取出队首结点
                q.pop();  // 弹出队首结点
                t.push_back(node->val);  // 记录当前结点的值
                if (node->left) {  // 左孩子存在时
                    q.push(node->left);  // 左孩子入队，留给下一层处理
                }  // 左孩子判断结束
                if (node->right) {  // 右孩子存在时
                    q.push(node->right);  // 右孩子入队，留给下一层处理
                }  // 右孩子判断结束
            }  // 本层结点全部处理完
            ans.push_back(t);  // 把这一层的结果追加到答案里
        }  // 层循环结束
        reverse(ans.begin(), ans.end());  // 此时是自顶向下，整体反转就变成自底向上
        return ans;  // 返回最终结果
    }  // 方法结束
};  // 题解类结束