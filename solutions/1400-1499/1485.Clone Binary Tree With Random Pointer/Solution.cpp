// 题目：1485. 克隆含随机指针的二叉树（Clone Binary Tree With Random Pointer）
// 核心思路：哈希表记录「原节点 → 副本」，先登记再递归，避免 random 指针形成环时重复克隆或无限递归。
// 时间复杂度：O(n)，每个节点只克隆一次；空间复杂度：O(n)，哈希表与递归栈。
/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     Node *left;
 *     Node *right;
 *     Node *random;
 *     Node() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
 *     Node(int x, Node *left, Node *right, Node *random) : val(x), left(left), right(right), random(random) {}
 * };
 */

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    NodeCopy* copyRandomBinaryTree(Node* root) {  // root：原二叉树根；返回深拷贝后新树的根
        unordered_map<Node*, NodeCopy*> seen;  // 已克隆映射：原节点 → 新节点，用于判重与环引用
        auto dfs = [&](this auto&& dfs, Node* root) -> NodeCopy* {  // C++23 显式对象参数，让 lambda 能递归调用自身
            if (!root) {  // 空指针直接返回空
                return nullptr;  // 保持空结构
            }  // if (!root) 分支结束
            if (seen.contains(root)) {  // C++20 contains：该节点已经克隆过（random 指针可能回指祖先）
                return seen[root];  // 直接复用已建好的副本
            }  // if (seen.contains(root)) 分支结束
            NodeCopy* copy = new NodeCopy(root->val);  // 先复制节点值；必须立刻登记，环上的引用才能拿到有效地址
            seen[root] = copy;  // 登记映射，供左右子树和 random 复用
            copy->left = dfs(root->left);  // 递归克隆左子树
            copy->right = dfs(root->right);  // 递归克隆右子树
            copy->random = dfs(root->random);  // 递归克隆 random 指向的节点
            return copy;  // 返回当前节点的副本
        };  // lambda 定义结束
        return dfs(root);  // 从根开始克隆
    }  // 方法结束
};  // Solution 类定义结束
