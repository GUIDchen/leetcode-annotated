// 题目：21. 合并两个有序链表（Merge Two Sorted Lists）
// 思路：递归——两个链表头里较小的那个当新头，它的 next 继续与另一个链表递归合并。
// 时间复杂度：O(m+n)，每个结点只被访问一次；空间复杂度：O(m+n)，递归栈的深度。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {  // list1、list2：两个升序链表的头结点
        if (!list1) return list2;  // list1 为空，剩下的全是 list2，直接接上
        if (!list2) return list1;  // list2 为空，剩下的全是 list1，直接接上
        if (list1->val <= list2->val) {  // list1 的头更小，它应当成为合并后的头
            list1->next = mergeTwoLists(list1->next, list2);  // 递归合并 list1 的剩余部分与 list2
            return list1;  // 返回以 list1 为头的结果
        } else {  // list2 的头更小，它应当成为合并后的头
            list2->next = mergeTwoLists(list1, list2->next);  // 递归合并 list2 的剩余部分与 list1
            return list2;  // 返回以 list2 为头的结果
        }
    }
};
