// 题目：1721. 交换链表中的节点（Swapping Nodes in a Linked List）难度：中等
// 思路：快指针先走 k-1 步停在正数第 k 个节点 p 上；随后快慢指针同步后移，快指针到末尾时慢指针正好落在倒数第 k 个节点 q 上，
// 最后交换 p、q 两个节点的值即可（题目允许只交换 val，不必改动指针连接）。
// 时间复杂度：O(n)，链表最多遍历两趟；空间复杂度：O(1)，只用了几个指针变量。
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
    ListNode* swapNodes(ListNode* head, int k) {  // head：链表头；k：要交换的、正数与倒数第 k 个节点
        ListNode* fast = head;  // 快指针从头出发，先负责定位正数第 k 个节点
        while (--k) {  // 循环 k-1 次（把 k 自减到 0 为止）
            fast = fast->next;  // 快指针后移一步
        }
        ListNode* slow = head;  // 慢指针重新从头出发，用来定位倒数第 k 个节点
        ListNode* p = fast;  // p 记录正数第 k 个节点
        while (fast->next) {  // 快指针走到尾节点就停下
            fast = fast->next;  // 快指针后移
            slow = slow->next;  // 慢指针同步后移，二者间距恒为 k-1
        }
        ListNode* q = slow;  // q 就是倒数第 k 个节点
        swap(p->val, q->val);  // 只交换两个节点的值，避免修改链表结构
        return head;  // 链表头不变，直接返回
    }  // swapNodes 方法结束
};  // Solution 类结束