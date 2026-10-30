// 题目：1265. 逆序打印不可变链表（Print Immutable Linked List in Reverse）
// 思路：先递归深入后继节点，再在回溯时调用 printValue，利用函数调用栈天然得到逆序输出，全程只使用 getNext/printValue 两个接口。
// 时间复杂度：O(n)，每个节点恰好打印一次；空间复杂度：O(n)，递归调用栈深度等于链表长度。
/**
 * // This is the ImmutableListNode's API interface.
 * // You should not implement it, or speculate about its implementation.
 * class ImmutableListNode {
 * public:
 *    void printValue(); // print the value of the node.
 *    ImmutableListNode* getNext(); // return the next node.
 * };
 */

class Solution {  // 题解类
public:  // 题解方法对外可见
    void printLinkedListInReverse(ImmutableListNode* head) {  // head 是不可变链表的头节点，只能调用其 API，不能修改指针
        if (head) {  // 空节点直接返回，作为递归的终止条件
            printLinkedListInReverse(head->getNext());  // 先递归处理后继节点，保证链表更靠后的值先被打印
            head->printValue();  // 回溯阶段打印当前节点的值，从而形成逆序输出
        }  // 结束非空判断
    }  // 结束 printLinkedListInReverse
};  // 结束题解类