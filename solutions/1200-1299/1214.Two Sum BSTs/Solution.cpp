// 题目：1214. 查找两棵二叉搜索树之和（Two Sum BSTs）
// 思路：BST 的中序遍历是升序序列，分别把两棵树展开成有序数组后，用左右双指针判定是否存在和为 target 的一对数。
// 时间复杂度：O(n1 + n2)，遍历两棵树与双指针各线性；空间复杂度：O(n1 + n2)，需要保存两个中序序列。
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
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {  // root1、root2：两棵二叉搜索树；target：目标和；判断是否存在 x + y = target
        vector<int> nums[2];  // nums[0]、nums[1] 分别保存两棵树的中序遍历结果（升序）
        function<void(TreeNode*, int)> dfs = [&](TreeNode* root, int i) {  // 递归中序遍历：参数 i 为 0 表示处理第一棵树、1 表示第二棵
            if (!root) {  // 遇到空结点，递归终止
                return;  // 直接回溯到上一层
            }  // 空结点判断结束
            dfs(root->left, i);  // 先递归左子树，保证「左 → 根 → 右」的中序顺序
            nums[i].push_back(root->val);  // 访问根结点；BST 的中序序列因此严格升序
            dfs(root->right, i);  // 再递归右子树
        };  // dfs 递归函数定义结束
        dfs(root1, 0);  // 把第一棵树展开成升序数组 nums[0]
        dfs(root2, 1);  // 把第二棵树展开成升序数组 nums[1]
        int i = 0, j = nums[1].size() - 1;  // 双指针：i 从左端扫 nums[0]，j 从右端扫 nums[1]
        while (i < nums[0].size() && j >= 0) {  // 两个指针都还没越界，就还有候选组合
            int x = nums[0][i] + nums[1][j];  // 当前双指针指向的两数之和
            if (x == target) {  // 和恰好等于目标值
                return true;  // 找到满足条件的一对数，返回真
            }  // 命中判断结束
            if (x < target) {  // 和偏小，需要增大，于是让左数组指针右移
                ++i;  // 取 nums[0] 中更大的元素
            } else {  // 和偏大，需要减小，于是让右数组指针左移
                --j;  // 取 nums[1] 中更小的元素
            }  // 双指针移动分支结束
        }  // 双指针循环结束
        return false;  // 指针相遇仍未命中，说明不存在这样的两数
    }  // twoSumBSTs 方法结束
};  // 题解类定义结束