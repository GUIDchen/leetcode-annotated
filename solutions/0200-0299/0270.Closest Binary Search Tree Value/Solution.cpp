// 题目：270. 最接近的二叉搜索树值（Closest Binary Search Tree Value）
// 思路：利用 BST 有序性，从根开始按 target 与当前值的大小关系只沿一条路径下降，边比较边记录差距最小（等距取较小值）的结点值。
// 时间复杂度：O(h)，h 为树高，只走一条从根到叶的链；空间复杂度：O(h)，递归栈深度为树高。
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
 */  // 判题器已提供 TreeNode 定义，这里只是注释说明，无需重复声明
class Solution {  // LeetCode 约定的题解类
public:  // 对外提供 closestValue 方法
    int closestValue(TreeNode* root, double target) {  // root：BST 根结点；target：目标浮点值
        int ans = root->val;  // 答案先取根结点值，保证至少有一个候选
        double diff = INT_MAX;  // diff 记录当前最小差距，先置为极大值
        function<void(TreeNode*)> dfs = [&](TreeNode* node) {  // 递归 lambda：形参是当前结点，[&] 按引用捕获 ans/diff 等外部变量
            if (!node) {  // 空结点是递归边界
                return;  // 直接回溯，避免解引用空指针
            }
            double nxt = abs(node->val - target);  // 当前结点值与 target 的距离
            if (nxt < diff || (nxt == diff && node->val < ans)) {  // 更近，或同样近但值更小（题目要求等距取较小值）
                diff = nxt;  // 记录新的最小差距
                ans = node->val;  // 用当前结点值替换答案
            }
            node = target < node->val ? node->left : node->right;  // target 更小走左子树，否则走右子树，只沿一条路径
            dfs(node);  // 沿选定的子树继续深入
        };  // lambda 体结束
        dfs(root);  // 从根结点开始搜索
        return ans;  // 返回最接近 target 的结点值
    }
};