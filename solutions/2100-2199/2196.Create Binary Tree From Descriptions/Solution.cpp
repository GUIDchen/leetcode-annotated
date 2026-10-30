// 题目：2196. 根据描述创建二叉树（Create Binary Tree From Descriptions）
// 思路：哈希表把结点值映射到已创建的结点，按描述逐条连接父子并记录所有“孩子”；值从未当过孩子的结点就是根。
// 时间复杂度：O(n)，每条描述只做常数次哈希操作；空间复杂度：O(n)，哈希表最多保存 2n 个结点。
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
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {  // descriptions：每条形如 [父结点值, 子结点值, 是否为左孩子]
        unordered_map<int, TreeNode*> nodes;  // 值到已创建结点的映射
        unordered_set<int> children;  // 记录所有当过孩子（即一定不是根）的结点值
        for (const auto& d : descriptions) {  // 逐条处理描述
            int parent = d[0], child = d[1], isLeft = d[2];  // 拆出父结点值、子结点值与左右标记
            if (!nodes.contains(parent)) {  // 父结点还没有创建过
                nodes[parent] = new TreeNode(parent);  // 新建父结点并登记到哈希表
            }  // if 结束
            if (!nodes.contains(child)) {  // 子结点还没有创建过
                nodes[child] = new TreeNode(child);  // 新建子结点并登记到哈希表
            }  // if 结束
            if (isLeft) {  // 标记为 1 表示是左孩子
                nodes[parent]->left = nodes[child];  // 把子结点挂到父结点的左侧
            } else {  // 否则是右孩子
                nodes[parent]->right = nodes[child];  // 把子结点挂到父结点的右侧
            }  // else 结束
            children.insert(child);  // 孩子结点一定不是根，记录下来
        }  // for 结束
        for (const auto& [k, v] : nodes) {  // 根是唯一没有出现在孩子集合里的结点
            if (!children.contains(k)) {  // 找到根
                return v;  // 返回根结点
            }  // if 结束
        }  // for 结束
        return nullptr;  // 理论上不可达（题面保证能构成合法二叉树），兜底返回空指针
    }  // 方法结束
};  // 类定义结束