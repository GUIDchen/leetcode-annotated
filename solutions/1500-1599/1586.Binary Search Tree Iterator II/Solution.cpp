// 题目：1586. 二叉搜索树迭代器 II（Binary Search Tree Iterator II）
// 思路：构造时中序遍历把 BST 的值按升序存入数组，再用下标 i 表示当前位置，next/prev 只是移动下标。
// 时间复杂度：构造 O(n)，四个接口均 O(1)；空间复杂度：O(n)，数组保存全部节点值。
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
class BSTIterator {  // 二叉搜索树迭代器
public:  // 对外接口
    BSTIterator(TreeNode* root) {  // 构造函数：先把整棵树的升序序列准备好
        dfs(root);  // 中序遍历，结果天然升序
        n = nums.size();  // 缓存长度，供 hasNext 使用
    }

    bool hasNext() {  // 是否还能向后移动
        return i < n - 1;  // 下标没到最后一个元素就还有下一个
    }

    int next() {  // 移动到下一个元素并返回它的值
        return nums[++i];  // 先把下标右移，再取该位置的值
    }

    bool hasPrev() {  // 是否还能向前移动
        return i > 0;  // 下标大于 0 才存在前一个元素
    }

    int prev() {  // 移动到前一个元素并返回它的值
        return nums[--i];  // 先把下标左移，再取该位置的值
    }

private:  // 内部数据与辅助函数
    vector<int> nums;  // 中序遍历得到的升序元素
    int i = -1;  // 当前下标，-1 表示还没有开始访问任何元素
    int n;  // 元素总数

    void dfs(TreeNode* root) {  // 中序遍历：左 → 根 → 右
        if (!root) {  // 空节点是递归出口
            return;
        }
        dfs(root->left);  // 先遍历左子树，得到更小的值
        nums.push_back(root->val);  // 再记录根节点的值
        dfs(root->right);  // 最后遍历右子树，得到更大的值
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * bool param_1 = obj->hasNext();
 * int param_2 = obj->next();
 * bool param_3 = obj->hasPrev();
 * int param_4 = obj->prev();
 */