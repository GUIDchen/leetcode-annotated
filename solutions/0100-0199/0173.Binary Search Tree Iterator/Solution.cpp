// 题目：173. 二叉搜索树迭代器（Binary Search Tree Iterator）
// 思路：中序遍历二叉搜索树得到升序数组，构造时一次性存好；next 返回下标 cur 处的值并后移，hasNext 判断 cur 是否越界。
// 时间复杂度：构造 O(n)，next 与 hasNext 均为 O(1)；空间复杂度：O(n)，保存全部节点值。
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
class BSTIterator {  // 二叉搜索树迭代器：按中序（升序）依次返回节点值
public:  // 对外公开的接口
    vector<int> vals;  // 中序遍历结果，对二叉搜索树来说天然升序
    int cur;  // 下一个要返回的元素下标
    BSTIterator(TreeNode* root) {  // 构造函数：初始化下标并完成一次中序遍历
        cur = 0;  // 从第一个元素开始
        inorder(root);  // 遍历整棵树，把节点值按升序填进 vals
    }  // 构造函数结束

    int next() {  // 返回下一个最小值
        return vals[cur++];  // 先取当前下标的元素，再让下标自增，为下一次调用做准备
    }  // next 结束

    bool hasNext() {  // 是否还有未访问的节点
        return cur < vals.size();  // 下标没有越界就说明还有元素
    }  // hasNext 结束

    void inorder(TreeNode* root) {  // 递归中序遍历：左子树 → 根 → 右子树
        if (root) {  // 空指针直接返回
            inorder(root->left);  // 先遍历左子树，保证更小的值先入数组
            vals.push_back(root->val);  // 访问根节点，把值追加到结果数组
            inorder(root->right);  // 再遍历右子树
        }  // if 结束
    }  // inorder 结束
};  // 类定义结束

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */