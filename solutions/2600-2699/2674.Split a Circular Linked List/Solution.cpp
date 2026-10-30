// 题目：2674. 拆分循环链表（Split a Circular Linked List）
// 思路：快慢指针找到中点：慢指针停在第一段末尾，快指针停在第二段末尾；再把两个 next 接回各自头，得到两个循环链表。
// 时间复杂度：O(n)，只遍历一遍链表；空间复杂度：O(1)，只用两个指针和常数个中间变量。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */  // 以上 ListNode 定义由判题器提供，原样保留
class Solution {  // 快慢指针拆分循环链表
public:  // 对外接口
    vector<ListNode*> splitCircularLinkedList(ListNode* list) {  // list 是循环链表的任意入口结点，返回两个新循环链表的头结点
        ListNode* a = list;  // 慢指针：每次走一步，最终停在第一段的最后一个结点
        ListNode* b = list;  // 快指针：每次走两步，最终停在第二段的最后一个结点
        while (b->next != list && b->next->next != list) {  // 快指针再走两步就会回到起点时停下，避免绕完整圈
            a = a->next;  // 慢指针走一步
            b = b->next->next;  // 快指针走两步
        }  // while 结束
        if (b->next != list) {  // 结点个数为偶数时快指针还差一步才到第二段末尾
            b = b->next;  // 把快指针补到第二段末尾
        }  // if 结束
        ListNode* list2 = a->next;  // 第二段的头结点就是第一段末尾的下一个结点
        b->next = list2;  // 先让第二段首尾相接（此时 a->next 仍指向 list2）
        a->next = list;  // 再让第一段首尾相接，得到第一个循环链表
        return {list, list2};  // 返回两个循环链表的头结点
    }  // splitCircularLinkedList 结束
};  // 类定义结束