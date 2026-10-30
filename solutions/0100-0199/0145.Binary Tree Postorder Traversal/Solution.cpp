// 题目：145. 二叉树的后序遍历（Binary Tree Postorder Traversal）
// 思路：递归 DFS，按「左 → 右 → 根」的次序访问节点，最后才把根的值写入结果数组。
// 时间复杂度：O(n)，每个节点恰好访问一次；空间复杂度：O(h) 递归栈（h 为树高），结果数组另占 O(n)。
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
 */  // 以上是 LeetCode 题面给出的二叉树节点定义（只作注释展示），实际由判题器提供
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> postorderTraversal(TreeNode* root) {  // root：树根；返回后序遍历得到的值序列
        vector<int> ans;  // 存放遍历结果
        function<void(TreeNode*)> dfs = [&](TreeNode* root) {  // 递归 lambda：用 [&] 按引用捕获 ans，直接就地追加避免拷贝
            if (!root) {  // 空节点是递归终止条件
                return;  // 直接返回上一层
            }  // 终止条件判断结束
            dfs(root->left);  // 先后序遍历左子树
            dfs(root->right);  // 再后序遍历右子树
            ans.push_back(root->val);  // 后序：左右都处理完，最后才记录根的值
        };  // lambda 定义结束
        dfs(root);  // 从整棵树的根开始遍历
        return ans;  // 返回收集好的后序序列
    }
};  // 题解类定义结束