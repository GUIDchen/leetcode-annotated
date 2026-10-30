// 题目：1506. 找到 N 叉树的根节点（Find Root of N-Ary Tree）
// 思路：把所有结点值以及所有孩子值全部异或起来——非根结点会被异或两次而抵消，最后剩下的就是根的值。
// 时间复杂度：O(N)，遍历结点与全部孩子；空间复杂度：O(1)，只用一个异或累加器。
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    Node* findRoot(vector<Node*> tree) {  // tree：N 叉树的全部结点（顺序任意）；返回根结点
        int x = 0;  // 异或累加器：根的值只出现一次，其余结点的值出现两次会互相抵消
        for (Node* node : tree) {  // 遍历所有结点
            x ^= node->val;  // 每个结点自身的值先异或一次
            for (Node* child : node->children) {  // 再遍历它的全部孩子
                x ^= child->val;  // 作为孩子被异或第二次，于是只剩根的值留下
            }
        }
        for (int i = 0;; ++i) {  // 找出值等于 x 的结点即为根；题目保证存在，循环上界可以省略
            if (tree[i]->val == x) {  // 题目保证结点值唯一，所以可以直接按值比较
                return tree[i];  // 找到根，返回该结点
            }
        }
    }
};