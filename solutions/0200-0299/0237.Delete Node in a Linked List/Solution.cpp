// 题目：237. 删除链表中的节点（Delete Node in a Linked List）
// 思路：只给了待删除结点本身，拿不到前驱，于是把后继的值复制到当前结点，再让当前结点跳过原来的后继，效果等价于删掉了当前的值。
// 时间复杂度：O(1)；空间复杂度：O(1)。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void deleteNode(ListNode* node) {  // node 就是要删除的结点（题目保证它不是尾结点）
        node->val = node->next->val;  // 把后继的值覆盖到当前结点，相当于当前结点原来的值被删除
        node->next = node->next->next;  // 跳过原来的后继，把它从链表中摘除
    }  // 方法结束
};  // 题解类结束