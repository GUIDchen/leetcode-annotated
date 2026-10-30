// 题目：3294. 将双链表转换为数组 II（Convert Doubly Linked List to Array II）
// 思路：先用 prev 指针从任意节点回溯到表头，再沿 next 指针正向遍历收集所有节点的值。
// 时间复杂度：O(n)，两次线性遍历；空间复杂度：O(n)，结果数组需要存 n 个元素。
/**
 * Definition for doubly-linked list.
 * class Node {
 *     int val;
 *     Node* prev;
 *     Node* next;
 *     Node() : val(0), next(nullptr), prev(nullptr) {}
 *     Node(int x) : val(x), next(nullptr), prev(nullptr) {}
 *     Node(int x, Node *prev, Node *next) : val(x), next(next), prev(prev) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> toArray(Node* node) {  // node 是双向链表中的任意一个节点，返回从表头开始的整条链表的值
        while (node && node->prev) {  // 只要还有前驱，就说明当前节点不是表头
            node = node->prev;  // 不断向前回溯，直到表头（prev 为空）
        }  // 此时 node 指向链表的第一个节点
        vector<int> ans;  // ans 存放按链表顺序排列的数组
        for (; node; node = node->next) {  // 从表头开始沿 next 正向遍历，直到空指针
            ans.push_back(node->val);  // 把当前节点的值追加到结果数组
        }  // 本轮遍历结束，node 已移到下一个节点
        return ans;  // 返回按链表顺序排列的数组
    }  // toArray 方法结束
};  // Solution 类定义结束
