// 题目：2. 两数相加（Add Two Numbers）
// 思路：哑结点串起结果链表，两个链表指针同步前进逐位相加，carry 保存进位，缺位时按 0 处理。
// 时间复杂度：O(max(m, n))，m、n 为两链表长度；空间复杂度：O(max(m, n))，为结果链表新申请的结点。
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {  // l1、l2：两个逆序存数的链表；返回相加后的链表头
        ListNode dummy;  // 栈上的哑结点，next 默认 nullptr，省去特判头结点
        int carry = 0;  // 进位，0 或 1
        ListNode* cur = &dummy;  // 结果链表的尾指针，初始指向哑结点
        while (l1 || l2 || carry) {  // 两个链表还有结点或仍有进位时继续
            int s = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;  // 本位和：短链表缺位按 0 算，再加进位
            carry = s / 10;  // 新的进位
            cur->next = new ListNode(s % 10);  // 本位数字建成结点接到尾部
            cur = cur->next;  // 尾指针后移
            l1 = l1 ? l1->next : nullptr;  // l1 未走完则后移，否则保持空指针
            l2 = l2 ? l2->next : nullptr;  // l2 同理后移
        }
        return dummy.next;  // 哑结点的后继就是结果的头结点（dummy 在栈上，无需 delete）
    }
};