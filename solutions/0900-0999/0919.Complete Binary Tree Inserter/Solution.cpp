// 题目：919. 完全二叉树插入器（Complete Binary Tree Inserter）
// 思路：BFS 把完全二叉树按层序存进数组，插入位置由 (size-1)/2 直接定位，左孩子空就补左、否则补右。
// 时间复杂度：构造 O(n)，insert 均摊 O(1)，get_root O(1)；空间复杂度：O(n)，保存层序节点。
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
class CBTInserter {  // 完全二叉树的插入器类
public:  // 构造与插入接口对外可见
    CBTInserter(TreeNode* root) {  // 构造函数：把已有完全二叉树按层序展开成一维数组
        queue<TreeNode*> q{{root}};  // BFS 队列，初始只放入根节点
        while (q.size()) {  // 队列非空就继续向下扩展
            for (int i = q.size(); i; --i) {  // 固定当前层节点数并逐个弹出，保证按层序写入数组
                auto node = q.front();  // 取出队首节点
                q.pop();  // 弹出队首
                tree.push_back(node);  // 按层序存入数组，下标即完全二叉树的编号
                if (node->left) {  // 存在左孩子才入队
                    q.push(node->left);  // 左孩子入队，等待后续处理
                }  // 结束左孩子分支
                if (node->right) {  // 存在右孩子才入队
                    q.push(node->right);  // 右孩子入队
                }  // 结束右孩子分支
            }  // 结束本层遍历
        }  // 结束 BFS
    }  // 结束构造函数

    int insert(int val) {  // 插入新值，返回新节点父节点的值
        auto p = tree[(tree.size() - 1) / 2];  // 层序下标从 0 开始，新节点的父节点下标为 (size-1)/2
        auto node = new TreeNode(val);  // 为新值创建节点
        tree.push_back(node);  // 新节点追加到层序数组末尾
        if (!p->left) {  // 父节点左孩子为空就先补左孩子
            p->left = node;  // 挂到左孩子
        } else {  // 否则挂到右孩子
            p->right = node;  // 挂到右孩子
        }  // 结束 if/else
        return p->val;  // 返回父节点的值
    }  // 结束 insert 方法

    TreeNode* get_root() {  // 取根节点
        return tree[0];  // 层序数组第 0 个元素就是根节点
    }  // 结束 get_root 方法

private:  // 私有成员：只对本类可见
    vector<TreeNode*> tree;  // 按层序保存所有节点，便于 O(1) 定位插入位置
};  // 结束 CBTInserter 类

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */