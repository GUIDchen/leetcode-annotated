// 题目：2181. 合并零之间的节点（Merge Nodes in Between Zeros）
// 思路：用哨兵节点串联结果链表，顺序扫描原链表，累加两个 0 之间的节点值，遇到非首段的 0 就把累加和接到结果尾部。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(1)，只用了常数个额外指针（新建节点属于返回结果本身）。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* mergeNodes(struct ListNode* head) {  // head 是原链表首节点（题目保证其值为 0），返回合并后的结果链表头
    struct ListNode dummy;  // 栈上的哨兵节点，它的 next 指向结果链表第一个节点
    struct ListNode* cur = &dummy;  // cur 是结果链表的尾指针，初始指向哨兵
    int sum = 0;  // 累加器：当前这一段（两个 0 之间）的节点值之和
    while (head) {  // 顺序遍历原链表，head 变成 NULL 时结束
        if (head->val == 0 && sum != 0) {  // 遇到 0 且之前已经累加出非零和，说明一段刚好结束
            cur->next = malloc(sizeof(struct ListNode));  // 为这一段的和分配一个新节点
            cur->next->val = sum;  // 新节点的值就是这一段的和
            cur->next->next = NULL;  // 新节点暂时作为结果链表尾，next 先置空
            cur = cur->next;  // 尾指针后移到新节点
            sum = 0;  // 清零累加器，准备统计下一段
        }
        sum += head->val;  // 把当前节点值累加进 sum（当前值为 0 时不会改变 sum）
        head = head->next;  // 指针后移，处理下一个节点
    }
    return dummy.next;  // 返回哨兵后面串起来的整条结果链表
}
