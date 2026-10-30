// 题目：257. 二叉树的所有路径（Binary Tree Paths）
// 思路：DFS 回溯。用数组 t 记录根到当前节点的路径，遇到叶子时用 join 拼成 "a->b->c" 存入答案，回溯时弹出最后一个元素。
// 时间复杂度：O(n^2)，每条路径的拼接代价与其长度成正比；空间复杂度：O(n)，递归栈与路径数组。

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
    vector<string> binaryTreePaths(TreeNode* root) {  // root：二叉树根节点
        vector<string> ans;  // 结果集：保存所有根到叶子的路径字符串
        vector<string> t;  // 回溯路径：当前路径上各节点值的字符串形式
        function<void(TreeNode*)> dfs = [&](TreeNode* root) {  // 内层递归函数：深度优先遍历以 root 为根的子树
            if (!root) {  // 空节点直接返回，作为递归边界
                return;  // 不做任何处理
            }
            t.push_back(to_string(root->val));  // 把当前节点值转成字符串后压入路径
            if (!root->left && !root->right) {  // 左右孩子都为空，说明当前节点是叶子
                ans.push_back(join(t));  // 用 "->" 把整条路径拼起来放入结果集
            } else {  // 否则还有孩子，需要继续向下递归
                dfs(root->left);  // 递归处理左子树
                dfs(root->right);  // 递归处理右子树
            }
            t.pop_back();  // 回溯：离开当前节点前把它从路径中弹出
        };  // 结束内层递归 lambda 的定义
        dfs(root);  // 从根节点开始遍历
        return ans;  // 返回所有根到叶子的路径
    }  // 结束方法

    string join(vector<string>& t, string sep = "->") {  // 辅助函数：用分隔符 sep 把路径数组连接成一个字符串
        string ans;  // 累积最终字符串
        for (int i = 0; i < t.size(); ++i) {  // 依次拼接每个节点值
            if (i > 0) {  // 除第一个元素外，前面都要补分隔符
                ans += sep;  // 追加分隔符 "->"
            }
            ans += t[i];  // 追加当前节点值
        }
        return ans;  // 返回拼接好的路径字符串
    }  // 结束辅助函数
};  // 结束类