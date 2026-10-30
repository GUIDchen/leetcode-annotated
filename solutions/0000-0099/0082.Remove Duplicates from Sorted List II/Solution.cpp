// 题目：82. 删除排序链表中的重复元素 II（Remove Duplicates from Sorted List II）
// 思路：哑结点 + 双指针，先让 cur 走完当前重复段，再用 pre->next == cur 判断这一段是「唯一」还是「重复」，重复就把整段摘除。
// 时间复杂度：O(n)，每个结点最多被访问两次；空间复杂度：O(1)，只用了常数个指针（哑结点记为常数）。

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
    ListNode* deleteDuplicates(ListNode* head) {  // head：升序链表头结点；返回删除所有重复值后的新头结点
        ListNode* dummy = new ListNode(0, head);  // 哑结点指向原头结点，让「原头结点被删除」和普通情况走同一套逻辑
        ListNode* pre = dummy;  // pre 指向最后一个确定要保留的结点（初始为哑结点）
        ListNode* cur = head;  // cur 向右探测，最终停在当前重复段的最后一个结点
        while (cur) {  // 外层循环：一段一段地处理整条链表
            while (cur->next && cur->next->val == cur->val) {  // 后一个值相同就继续右移，把整段重复值走完
                cur = cur->next;  // 跳到下一个重复值
            }
            if (pre->next == cur) {  // pre 的下一结点仍是 cur，说明这一段只有 cur 自己
                pre = cur;  // 该值唯一，保留下来，pre 前移到 cur
            } else {  // 否则 cur 前面的一段（含 cur）出现了至少两次
                pre->next = cur->next;  // 从 pre 后面直接跳过整段重复值，pre 保持不动
            }
            cur = cur->next;  // cur 移到下一段的起点
        }
        return dummy->next;  // 哑结点的下一结点就是结果链表真正的头
    }
};