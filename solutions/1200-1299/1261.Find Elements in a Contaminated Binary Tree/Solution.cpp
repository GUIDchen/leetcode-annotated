// 题目：1261. 在受污染的二叉树中查找元素（Find Elements in a Contaminated Binary Tree）
// 思路：按完全二叉树编号规则（左孩子 2x+1、右孩子 2x+2）从根值 0 开始 DFS 还原所有节点，并全部放入哈希集合；find 时 O(1) 查表。
// 时间复杂度：构造 O(n)、find O(1)；空间复杂度：O(n)，集合存全部节点值，DFS 递归深度为树高。
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
class FindElements {  // 题解类：构造时一次性还原整棵树，之后只做查询
public:  // 构造函数：root 是节点值被污染的树根（原值全部无效）
    FindElements(TreeNode* root) {  // 题目规定受污染前根节点的值就是 0，直接写回
        root->val = 0;  // 从根开始深度优先还原每个节点的真实值
        dfs(root);  // 结束构造函数
    }

    bool find(int target) {  // 查询 target 是否出现在还原后的树中
        return s.contains(target);  // C++20 的 contains：集合中是否存在该值，均摊 O(1)
    }  // 结束 find

private:
    unordered_set<int> s;  // 哈希集合，存放所有还原出来的节点值，便于 O(1) 查询

    void dfs(TreeNode* root) {  // 递归还原以 root 为根的子树
        s.insert(root->val);  // 当前节点的值已经正确，先收进集合
        if (root->left) {  // 存在左孩子时继续还原
            root->left->val = root->val * 2 + 1;  // 左孩子的编号规则：2 * 父值 + 1
            dfs(root->left);  // 递归处理左子树
        }  // 结束左孩子分支
        if (root->right) {  // 存在右孩子时继续还原
            root->right->val = root->val * 2 + 2;  // 右孩子的编号规则：2 * 父值 + 2
            dfs(root->right);  // 递归处理右子树
        }  // 结束右孩子分支
    };  // 结束 dfs 的定义（此处分号是作者原样写法，不影响编译）
};  // 结束题解类

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */