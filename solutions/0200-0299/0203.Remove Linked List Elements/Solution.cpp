// 题目：203. 移除链表元素（Remove Linked List Elements）
// 思路：建一个哑节点接在原头节点前，用指针 p 指向「已确认保留」的最后一个节点，向后扫描并跳过值等于 val 的节点。
// 时间复杂度：O(n)，每个节点最多检查一次；空间复杂度：O(1)，只用了哑节点和一个指针。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    ListNode* removeElements(ListNode* head, int val) {  // head：链表头节点；val：要删除的值；返回删除后链表的新头节点
        ListNode* dummy = new ListNode();  // 哑节点，让「删除头节点」与「删除中间节点」共用同一套逻辑，不必单独判空
        dummy->next = head;  // 把哑节点接到原链表前面
        ListNode* p = dummy;  // p 指向已确认保留部分的最后一个节点，从哑节点开始
        while (p->next) {  // 只要后面还有节点待检查
            if (p->next->val == val) {  // 下一个节点正是要删除的值
                p->next = p->next->next;  // 让 p 越过它，p 本身不动，这样连续多个待删节点也能逐个跳过
            } else {  // 下一个节点需要保留
                p = p->next;  // 指针后移，把它纳入已确认保留的部分
            }
        }
        return dummy->next;  // 哑节点的 next 就是新的头节点（原头节点可能已被删除）
    }
};