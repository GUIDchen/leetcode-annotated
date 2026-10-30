// 题目：2046. 给按照绝对值排序的链表排序（Sort Linked List Already Sorted Using Absolute Values）
// 思路：链表已按绝对值升序，负数只能出现在前半段且彼此逆序；顺序扫描，遇到负节点就把它从原位置摘下、头插到链表最前面，扫描结束即得升序链表。
// 时间复杂度：O(n)，每个节点只被访问一次；空间复杂度：O(1)，只用几个指针。
// 下面是题目给定的单链表节点定义（原题面注释，保持原样）
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
class Solution {  // 题目给定结构体定义的注释块结束
public:  // LeetCode 约定的题解类
    ListNode* sortLinkedList(ListNode* head) {  // 题解方法对外可见
        ListNode* prev = head;  // head：按绝对值升序排列的链表头；返回按值升序排列的链表头
        ListNode* curr = head->next;  // prev 始终是 curr 的前驱，方便把 curr 从链表中摘除
        while (curr) {  // curr 是正在扫描的节点，从头节点的下一个开始
            if (curr->val < 0) {  // 沿着链表一直走到末尾
                auto t = curr->next;  // 负数的绝对值排序后应整体排在最前面，所以要把它移到头部
                prev->next = t;  // 先记住后继节点，摘掉 curr 之后还要从这里继续扫描
                curr->next = head;  // 让前驱跳过 curr，把它从原位置摘下来
                head = curr;  // 把 curr 接到当前链表头的前面
                curr = t;  // 头指针前移，curr 成为新的链表头
            } else {  // 从原来的后继继续扫描
                prev = curr;  // 当前节点是非负数，相对顺序已经正确，原地保留
                curr = curr->next;  // 前驱指针后移一位
            }  // 继续扫描下一个节点
        }  // 结束负数的判断分支
        return head;  // 结束链表遍历
    }  // 返回调整后的升序链表头
};  // 方法结束