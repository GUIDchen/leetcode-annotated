// 题目：314. 二叉树的垂直遍历（Binary Tree Vertical Order Traversal）
// 思路：DFS 记录每个节点的列偏移与深度，按列分组（map 天然有序），同列再按深度升序输出，保证自上而下。
// 时间复杂度：O(n log n)，主要是每列内部排序；空间复杂度：O(n)，保存全部节点信息。
// 下面这段块注释是题目给出的二叉树节点定义（判题器已提供）
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
using pii = pair<int, int>;  // 别名：pii 表示 (深度, 节点值) 这样的二元组

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    map<int, vector<pii>> d;  // 列偏移 → [(深度, 节点值)]，map 保证列偏移从小到大有序

    vector<vector<int>> verticalOrder(TreeNode* root) {  // root：二叉树根节点
        dfs(root, 0, 0);  // 先序遍历，收集每个节点所属的列与深度
        vector<vector<int>> ans;  // 按列从左到右存放结果
        for (auto& [_, v] : d) {  // 按列偏移升序遍历每一列，_ 是占位的列偏移
            sort(v.begin(), v.end(), [&](pii& a, pii& b) {  // 同一列内按深度升序排序，保证同列节点自上而下
                return a.first < b.first;  // 只比较深度（first 就是深度）
            });
            vector<int> t;  // 存放当前列的节点值
            for (auto& x : v) {  // 遍历该列排好序的 (深度, 值)
                t.push_back(x.second);  // 只取二元组中的节点值
            }
            ans.push_back(t);  // 把这一列加入结果
        }
        return ans;  // 返回按列分组、自上而下的遍历结果
    }

    void dfs(TreeNode* root, int depth, int offset) {  // depth：深度（行号）；offset：列偏移，根节点为 0
        if (!root) return;  // 空节点直接返回
        d[offset].push_back({depth, root->val});  // 记录「列偏移 → (深度, 节点值)」
        dfs(root->left, depth + 1, offset - 1);  // 左孩子：深度加一，列偏移减一
        dfs(root->right, depth + 1, offset + 1);  // 右孩子：深度加一，列偏移加一
    }
};