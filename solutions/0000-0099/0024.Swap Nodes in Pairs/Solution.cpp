// 题目：24. 两两交换链表中的节点（Swap Nodes in Pairs）
// 思路：递归——把前两个结点交换位置，第二个结点成为新头，它的 next 指向「剩余部分两两交换」的结果。
// 时间复杂度：O(n)，每个结点处理一次；空间复杂度：O(n)，递归栈深度约为 n/2。
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
    ListNode* swapPairs(ListNode* head) {  // head：待处理的链表头
        if (!head || !head->next) {  // 空链表或只剩一个结点，没有成对的结点可交换
            return head;  // 原样返回
        }
        ListNode* t = swapPairs(head->next->next);  // 先递归处理第 3 个结点之后的部分，得到交换后的后半段
        ListNode* p = head->next;  // p 是原来的第二个结点，交换后要当这段的新头
        p->next = head;  // 让第二个结点指向第一个结点
        head->next = t;  // 原第一个结点（现在是这段的尾）接到后半段上
        return p;  // 返回交换后的新头
    }
};
