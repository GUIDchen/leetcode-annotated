// 题目：2415. 反转二叉树的奇数层（Reverse Odd Levels of Binary Tree）
// 思路：BFS 逐层遍历，层号为奇数时按从左到右把该层节点收集到数组里，再用双指针首尾交换它们的值，完成该层反转。
// 时间复杂度：O(n)，每个节点进出队列各一次、参与交换各一次；空间复杂度：O(n)，队列与临时数组最多各存一层节点。
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
    TreeNode* reverseOddLevels(TreeNode* root) {  // 返回反转奇数层后的树根（原地修改节点值）
        queue<TreeNode*> q{{root}};  // BFS 队列，初始只放入根节点
        for (int i = 0; q.size(); ++i) {  // i 是当前层号（根在第 0 层），队列不空就继续下一层
            vector<TreeNode*> t;  // 只用来存放奇数层节点，便于按序反转
            for (int k = q.size(); k; --k) {  // 先把本层节点个数固定下来，保证一次只处理一层
                TreeNode* node = q.front();  // 取出队首节点
                q.pop();  // 弹出队首
                if (i & 1) {  // 层号为奇数才需要反转，才收集节点
                    t.push_back(node);  // 按从左到右的顺序记录该层节点
                }
                if (node->left) {  // 有左孩子说明还有下一层
                    q.push(node->left);  // 左孩子入队
                    q.push(node->right);  // 右孩子一同入队，保持从左到右的层序
                }
            }
            for (int l = 0, r = t.size() - 1; l < r; ++l, --r) {  // 双指针从两端向中间收缩
                swap(t[l]->val, t[r]->val);  // 交换两端的值，等价于把该层整体反转
            }
        }
        return root;  // 返回原树根，节点结构未变、只有值被交换
    }  // 方法定义结束
};  // 类定义结束