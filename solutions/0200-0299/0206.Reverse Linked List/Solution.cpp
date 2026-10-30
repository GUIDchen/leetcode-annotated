// 题目：206. 反转链表（Reverse Linked List）
// 思路：哑节点 + 头插法，边遍历边把当前节点插到 dummy 之后，走完一遍链表就完成了反转。
// 时间复杂度：O(n)，每个节点只处理一次；空间复杂度：O(1)，只额外申请了一个哑节点。
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
public:  // 解题接口对外可见
    ListNode* reverseList(ListNode* head) {  // head 是原链表头节点，返回反转后的新头节点
        ListNode* dummy = new ListNode();  // 哑节点：用它的 next 挂住已经反转好的那部分链表
        ListNode* curr = head;  // curr 指向当前待处理的节点，从头节点开始
        while (curr) {  // 沿着原链表一直走到空指针
            ListNode* next = curr->next;  // 先保存后继节点，否则改完 next 就找不回后面的链表
            curr->next = dummy->next;  // 头插法：当前节点的 next 指向已反转部分的头
            dummy->next = curr;  // 哑节点改指向当前节点，当前节点成为新的反转链头
            curr = next;  // 指针后移，继续处理原链表的下一个节点
        }  // 原链表遍历结束，反转完成
        return dummy->next;  // 哑节点的 next 就是反转后的头节点
    }  // 方法结束
};  // 类定义结束（源文件末尾没有换行符，此处保持原样）