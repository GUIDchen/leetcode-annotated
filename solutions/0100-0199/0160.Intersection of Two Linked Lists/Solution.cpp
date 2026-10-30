// 题目：160. 相交链表（Intersection of Two Linked Lists）
// 思路：双指针同步前进，走完自己那条链后跳到对方链头，两条指针走过总长度相同，必然同时到达交点或同时到达空。
// 时间复杂度：O(m+n)，两条链各走两遍；空间复杂度：O(1)，只用两个指针。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {  // headA、headB：两条链表的头节点；返回相交的第一个节点，不相交时返回空指针
        ListNode *a = headA, *b = headB;  // 两个游标分别从各自链表头出发
        while (a != b) {  // 指针相同即相遇（交点或同为 nullptr），循环结束
            a = a ? a->next : headB;  // a 走到自己链尾后换到 B 头继续，补齐两链长度差
            b = b ? b->next : headA;  // b 走到自己链尾后换到 A 头继续
        }  // 循环结束
        return a;  // 返回相遇点：相交时是交点，不相交时是 nullptr
    }  // 题解方法结束
};  // 题解类定义结束