// 题目：876. 链表的中间结点（Middle of the Linked List）
// 核心思路：快慢指针，快指针每次走两步、慢指针每次走一步，快指针走到表尾时慢指针正好停在中间结点。
// 时间复杂度：O(n)，只遍历一次链表；空间复杂度：O(1)，只用了两个指针。
// 下面这段块注释是 LeetCode 题面给出的单链表结构体定义，属于题面而非题解代码
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* middleNode(struct ListNode* head) {  // head：链表头节点；返回中间结点（结点数为偶数时返回后一个）
    struct ListNode* fast = head;  // 快指针，每次前进两步
    struct ListNode* slow = head;  // 慢指针，每次前进一步
    while (fast && fast->next) {  // 快指针还能走两步时继续，保证 fast->next->next 不会解引用空指针
        fast = fast->next->next;  // 快指针前进两步
        slow = slow->next;  // 慢指针前进一步
    }  // 快指针走到头，慢指针恰好落在中间结点
    return slow;  // 返回中间结点
}  // middleNode 结束