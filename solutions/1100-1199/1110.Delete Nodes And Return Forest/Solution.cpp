// 题目：1110. 删点成林（Delete Nodes And Return Forest）
// 思路：先用标记数组记下所有待删值，再后序 DFS：递归修好左右子树后，若当前节点待删，就把它暴露出的两个孩子收进结果并返回空。
// 时间复杂度：O(n)，每个节点只被访问一次；空间复杂度：O(n)，标记数组固定 1001 项，递归栈最深为树高。
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
public:  // 对外暴露的解题接口
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {  // root 是原树根，to_delete 是要删除的节点值列表
        bool s[1001];  // 值域标记数组，题目保证节点值都在 1..1000 之间
        memset(s, 0, sizeof(s));  // 全部清零，表示默认所有节点都保留
        for (int x : to_delete) {  // 遍历待删列表
            s[x] = true;  // 标记该值需要删除，后续可用 O(1) 查询
        }
        vector<TreeNode*> ans;  // 收集新森林里每棵树的根
        function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* root) -> TreeNode* {  // 递归 lambda：返回处理后的子树根，节点被删则返回空
            if (!root) {  // 空节点无需处理
                return nullptr;  // 直接返回空指针
            }
            root->left = dfs(root->left);  // 后序遍历：先递归处理左子树，并把新的左孩子接回来
            root->right = dfs(root->right);  // 再递归处理右子树，并把新的右孩子接回来
            if (!s[root->val]) {  // 当前节点不需要删除
                return root;  // 保留当前节点，继续作为父节点的孩子
            }
            if (root->left) {  // 当前节点待删，但它还有左孩子
                ans.push_back(root->left);  // 被断开的左孩子自成新森林的一棵树
            }
            if (root->right) {  // 右孩子同理
                ans.push_back(root->right);  // 被断开的右孩子也自成新树
            }
            return nullptr;  // 当前节点被删除，向父节点报告此处为空
        };
        if (dfs(root)) {  // 从根开始处理；若根节点没有被删除
            ans.push_back(root);  // 原根也是一棵新树的根，需要加入结果
        }
        return ans;  // 返回森林中所有树的根节点
    }
};