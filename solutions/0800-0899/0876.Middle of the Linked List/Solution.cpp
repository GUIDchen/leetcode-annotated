// 题目：876. 链表的中间结点（Middle of the Linked List）
// 核心思路：快慢指针，快指针每次走两步、慢指针每次走一步，快指针到尾时慢指针正好在中间结点上。
// 时间复杂度：O(n)，只遍历一次链表；空间复杂度：O(1)，只用了两个指针。
// 下面这段块注释是 LeetCode 题面给出的单链表结构体定义，属于题面而非题解代码
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
    ListNode* middleNode(ListNode* head) {  // head：链表头节点；返回中间结点（偶数个结点时返回后一个）
        ListNode *slow = head, *fast = head;  // 慢、快两个指针同时从头节点出发
        while (fast && fast->next) {  // 快指针还能走两步时继续，保证 fast->next->next 不会解引用空指针
            slow = slow->next;  // 慢指针前进一步
            fast = fast->next->next;  // 快指针前进两步
        }  // 快指针走到头，循环结束
        return slow;  // 返回中间结点
    }  // middleNode 结束
};  // Solution 类结束