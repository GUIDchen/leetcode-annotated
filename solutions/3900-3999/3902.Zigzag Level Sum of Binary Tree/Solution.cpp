// 3902. 二叉树的 Z 字形层级和 / Zigzag Level Sum of Binary Tree
// 核心思路：BFS 逐层遍历，第 1 层从左到右、第 2 层从右到左交替扫描本层节点，遇到缺少对应方向孩子的节点立即停止并结算本层和。
// 复杂度：时间 O(n)，空间 O(n)。
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
class Solution {  // 定义题解类
public:  // 公有接口
    vector<long long> zigzagLevelSum(TreeNode* root) {  // 返回 Z 字形逐层处理后的各层和
        vector<long long> ans;  // 保存每一层的和
        vector<TreeNode*> q = {root};  // 当前层的节点，初始只有根节点
        bool left = true;  // 本层方向：true 表示从左到右（第 1 层）
        while (!q.empty()) {  // 逐层遍历（BFS）
            vector<TreeNode*> nq;  // 收集下一层的节点
            for (TreeNode* node : q) {  // 按左、右顺序收集本层节点的孩子
                if (node->left != nullptr) {  // 有左孩子
                    nq.push_back(node->left);  // 左孩子加入下一层
                }  // 左孩子判断结束
                if (node->right != nullptr) {  // 有右孩子
                    nq.push_back(node->right);  // 右孩子加入下一层
                }  // 右孩子判断结束
            }  // 本层孩子收集结束
            int m = q.size();  // 本层节点个数
            long long s = 0;  // 本层计入答案的和
            for (int i = 0; i < m; i++) {  // 按指定方向顺序处理本层节点
                TreeNode* node = left ? q[i] : q[m - i - 1];  // 从左往右取，或从右往左取
                TreeNode* child = left ? node->left : node->right;  // 检查该方向上必需的孩子
                if (child == nullptr) {  // 命中停止条件
                    break;  // 立即停止本层处理
                }  // 停止条件判断结束
                s += node->val;  // 该节点计入本层和
            }  // 本层处理结束
            ans.push_back(s);  // 记录本层的和
            left = !left;  // 下一层方向翻转
            q = nq;  // 进入下一层
        }  // 遍历结束
        return ans;  // 返回各层的和
    }  // zigzagLevelSum 结束
};  // 类定义结束
