// 题目：1666. 改变二叉树的根节点（Change the Root of a Binary Tree）
// 思路：从 leaf 沿 parent 指针一路翻转到 root，边翻转边把原父节点中指向自己的孩子指针置空，最后断开 leaf 的 parent。
// 时间复杂度：O(h)，h 为 leaf 到 root 的路径长度；空间复杂度：O(1)，只用了常数个指针。
/*
// Definition for a Node->
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    Node* flipBinaryTree(Node* root, Node* leaf) {  // root：原根节点；leaf：即将成为新根的节点，返回新的根
        Node* cur = leaf;  // cur：当前要向上翻转的节点，从新根 leaf 出发
        Node* p = cur->parent;  // p：cur 的原父节点，翻转后会成为 cur 的左孩子
        while (cur != root) {  // 沿 parent 链一路翻转，直到处理完原根为止
            Node* gp = p->parent;  // 先记下祖父节点，它是下一轮要当作父节点的那个节点
            if (cur->left) {  // cur 原本有左孩子
                cur->right = cur->left;  // 把原左孩子挪到右孩子位置，因为新树里 cur 的左侧要留给原父节点
            }  // 左孩子搬移结束
            cur->left = p;  // 原父节点变成 cur 的左孩子
            p->parent = cur;  // 同步维护方向相反的 parent 指针
            if (p->left == cur) {  // 原树中 cur 曾是 p 的左孩子
                p->left = nullptr;  // 断开 p 指向 cur 的旧左指针，避免残留环
            } else if (p->right == cur) {  // 否则再判断 cur 是否曾是 p 的右孩子
                p->right = nullptr;  // 断开 p 指向 cur 的旧右指针
            }  // 旧指针清理结束
            cur = p;  // 向上推进：原父节点成为下一个待翻转的节点
            p = gp;  // p 也随之向上移动一层
        }  // 翻转循环结束
        leaf->parent = nullptr;  // 新根节点没有父节点
        return leaf;  // 返回翻转后的新根
    }  // 方法结束
};  // 类定义结束