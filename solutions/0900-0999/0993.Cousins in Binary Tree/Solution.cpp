// 题目：993. 二叉树的堂兄弟节点（Cousins in Binary Tree）
// 思路：BFS 分层遍历，记录 x、y 各自的深度与父结点；深度相同且父结点不同即为堂兄弟。
// 时间复杂度：O(n)，每个结点入队出队各一次；空间复杂度：O(n)，队列最多保存一层结点。
// 下面是题目给出的二叉树结点定义，实际判题时由 LeetCode 提供，无需自己写。
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
    bool isCousins(TreeNode* root, int x, int y) {  // root：二叉树根；x、y：要找的两个结点值；返回二者是否为堂兄弟
        queue<pair<TreeNode*, TreeNode*>> q;  // 队列元素是 (当前结点, 它的父结点)，根的父亲记为空指针
        q.push({root, nullptr});  // 根结点先入队
        int d1 = 0, d2 = 0;  // d1、d2 分别记录 x、y 所在的深度
        TreeNode *p1 = nullptr, *p2 = nullptr;  // p1、p2 分别记录 x、y 的父结点
        for (int depth = 0; q.size(); ++depth) {  // 逐层 BFS：depth 是当前层深度，队列非空就继续
            for (int n = q.size(); n; --n) {  // 只处理当前这一层的 n 个结点，保证同层结点的 depth 一致
                auto [node, parent] = q.front();  // 取出队首结点及其父结点（C++17 结构化绑定）
                q.pop();  // 弹出队首
                if (node->val == x) {  // 命中 x：记下它的深度与父结点
                    d1 = depth;  // 保存 x 的深度
                    p1 = parent;  // 保存 x 的父结点
                } else if (node->val == y) {  // 否则再看是不是 y
                    d2 = depth;  // 保存 y 的深度
                    p2 = parent;  // 保存 y 的父结点
                }  // x、y 的判定分支结束
                if (node->left) {  // 左孩子存在就连同当前结点作为父亲一起入队
                    q.push({node->left, node});  // 入队时把当前结点记为左孩子的父亲
                }  // 左孩子处理结束
                if (node->right) {  // 右孩子同理
                    q.push({node->right, node});  // 入队时把当前结点记为右孩子的父亲
                }  // 右孩子处理结束
            }  // 本层结点处理完毕
        }  // 层数加一，进入下一层
        return d1 == d2 && p1 != p2;  // 堂兄弟：深度相同且父结点不同
    }  // isCousins 函数结束
};  // 类定义结束