// 题目：426. 将二叉搜索树转化为排序的双向链表（Convert Binary Search Tree to Sorted Doubly Linked List）
// 思路：BST 的中序遍历天然升序，用一个 prev 指针记住前驱，遍历时把当前节点接在前驱之后，最后把首尾相连成循环双向链表。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，h 为树高，来自递归栈。
// 说明：下面是题目自带的 Node 定义（被注释掉，由判题器提供），仅作参考。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {  // LeetCode 题解类
public:  // 方法对外可见
    Node* prev;  // 中序遍历中的前驱节点（dfs 依赖的全局状态）
    Node* head;  // 双向链表的第一个节点，也就是最小值节点

    Node* treeToDoublyList(Node* root) {  // root：BST 的根节点；返回排序循环双向链表的头节点
        if (!root) return nullptr;  // 空树直接返回空，避免下面解引用空指针
        prev = nullptr;  // 每次调用前重置前驱，防止复用上一次调用的状态
        head = nullptr;  // 重置头节点
        dfs(root);  // 中序遍历：按升序把节点串成双向链表
        prev->right = head;  // 遍历结束时 prev 是最大值节点，让它指向头节点
        head->left = prev;  // 头节点的 left 指向最大值节点，闭合成环
        return head;  // 返回链表头，即最小值节点
    }

    void dfs(Node* root) {  // 中序递归：左子树 - 根 - 右子树
        if (!root) return;  // 递归边界：空节点返回
        dfs(root->left);  // 先处理左子树，那里是更小的值
        if (prev) {  // 已经有前驱，说明当前节点不是最小节点
            prev->right = root;  // 前驱的 right 指向当前节点
            root->left = prev;  // 当前节点的 left 指回前驱，保持双向
        } else  // 没有前驱，说明当前节点是最小节点
            head = root;  // 记录链表头
        prev = root;  // 当前节点成为下一轮递归的前驱
        dfs(root->right);  // 再处理右子树，那里是更大的值
    }
};