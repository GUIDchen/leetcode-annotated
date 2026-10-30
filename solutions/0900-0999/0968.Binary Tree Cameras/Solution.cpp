// 题目：968. 监控二叉树（Binary Tree Cameras）
// 思路：树形 DP，每个节点返回三种状态的最优值：a=本点放摄像头、b=本点已被覆盖但没放、c=本点未被覆盖，自底向上转移。
// 时间复杂度：O(n)，每个节点只算一次；空间复杂度：O(h)，递归栈深度等于树的高度。
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
struct Status {  // 描述一个节点三种状态的 DP 值
    int a, b, c;  // a：本节点放摄像头；b：本节点被覆盖但没放；c：本节点未被覆盖（留给父节点处理）
};  // 结构体定义结束

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minCameraCover(TreeNode* root) {  // root 是根节点，返回覆盖所有节点所需的最少摄像头数
        auto [a, b, _] = dfs(root);  // 取根节点的前两种状态：根节点没有父节点，不能指望别人来覆盖它
        return min(a, b);  // 在「根节点放摄像头」与「根节点被覆盖」中取较小值
    }  // 方法结束

    Status dfs(TreeNode* root) {  // 树形 DP：返回以 root 为根的子树在三种状态下的最少摄像头数
        if (!root) {  // 空节点：放摄像头无意义（视为无穷大），既不算被覆盖也不算未被覆盖
            return {1 << 29, 0, 0};  // 返回 {无穷大, 0, 0}
        }  // 空节点判断结束
        auto [la, lb, lc] = dfs(root->left);  // 左子树的三种状态
        auto [ra, rb, rc] = dfs(root->right);  // 右子树的三种状态
        int a = 1 + min({la, lb, lc}) + min({ra, rb, rc});  // 状态 a：本节点放摄像头可覆盖孩子，孩子三态任取最小值，再算上自身这 1 个
        int b = min({la + ra, la + rb, lb + ra});  // 状态 b：本节点没放但被覆盖，覆盖必须来自某个孩子放摄像头，三种组合取最小
        int c = lb + rb;  // 状态 c：本节点未被覆盖，要求两个孩子都必须处于「被覆盖」状态
        return {a, b, c};  // 返回本节点的三种状态
    };  // 方法结束
};  // 题解类结束