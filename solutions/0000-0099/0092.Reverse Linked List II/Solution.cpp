// 题目：92. 反转链表 II（Reverse Linked List II）
// 思路：用哨兵结点统一边界，先走 left-1 步定位反转区间前驱，再用「头插」把区间内 right-left+1 个结点原地反转。
// 时间复杂度：O(n)，最多遍历链表一次；空间复杂度：O(1)，只用了常数个指针。
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
    ListNode* reverseBetween(ListNode* head, int left, int right) {  // head 为链表头，left / right 是 1 起算的闭区间
        if (!head->next || left == right) {  // 只有一个结点，或区间长度为 1，都无需反转
            return head;  // 原样返回头结点
        }
        ListNode* dummy = new ListNode(0, head);  // 哨兵结点指向原头，避免 left == 1 时单独处理头结点
        ListNode* pre = dummy;  // pre 用来走到反转区间的前驱结点
        for (int i = 0; i < left - 1; ++i) {  // 前进 left-1 步，停在区间前驱上
            pre = pre->next;  // 一步步向后移动
        }
        ListNode *p = pre, *q = pre->next;  // p 记住前驱；q 记住区间第一个结点（反转后会变成区间尾）
        ListNode* cur = q;  // cur 是当前正在被反转的结点
        for (int i = 0; i < right - left + 1; ++i) {  // 只处理区间内的这些结点，区间外不动
            ListNode* t = cur->next;  // 先保存后继，断链后还能继续往后走
            cur->next = pre;  // 反转指针方向：当前结点指向前驱
            pre = cur;  // pre 前移，成为下一轮的前驱
            cur = t;  // cur 前移，处理下一个结点
        }
        p->next = pre;  // 区间前驱接到反转后的区间头（原区间最后一个结点）
        q->next = cur;  // 原区间第一个结点（现区间尾）接到区间后面的第一个结点
        return dummy->next;  // 哨兵的后继就是真正的头结点
    }
};
