// 题目：2181. 合并零之间的节点（Merge Nodes in Between Zeros）
// 思路：跳过开头的 0 从第二个节点开始遍历，遇到非零值累加，遇到 0 就把累加和接成新节点挂到结果链表尾部。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(1)，额外只用了哨兵与尾指针（新节点即返回结果）。
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
    ListNode* mergeNodes(ListNode* head) {  // head：原链表头（其值为 0）；返回合并后的链表头
        ListNode* dummy = new ListNode();  // 哨兵节点，dummy->next 指向结果链表第一个节点
        ListNode* tail = dummy;  // tail 是结果链表尾指针，初始指向哨兵
        int s = 0;  // 累加器：当前段（两个 0 之间）的节点值之和
        for (ListNode* cur = head->next; cur; cur = cur->next) {  // 跳过开头那个 0，从首段内部开始遍历
            if (cur->val) {  // 当前值非零，属于某一段内部
                s += cur->val;  // 累加进当前段的和
            } else {  // 当前值为 0，说明前面一段结束
                tail->next = new ListNode(s);  // 用该段的和新建节点并接到结果链表尾部
                tail = tail->next;  // 尾指针后移到新节点
                s = 0;  // 清零累加器，准备统计下一段
            }
        }
        return dummy->next;  // 返回哨兵后面的结果链表
    }
};
