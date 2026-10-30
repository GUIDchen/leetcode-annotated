// 题目：2. 两数相加（Add Two Numbers）
// 思路：哑结点串起结果链表，同步遍历两个链表逐位相加，carry 保存进位；循环条件里带上 carry，处理最高位产生的进位。
// 时间复杂度：O(max(m, n))，m、n 为两链表长度；空间复杂度：O(max(m, n))，用于新建结果链表（不计返回值为 O(1)）。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {  // l1、l2 是两个逆序存数的链表头，返回相加后的新链表头
    struct ListNode* dummy = (struct ListNode*) malloc(sizeof(struct ListNode));  // 哑结点：让尾插法不必特判结果链表的第一个结点
    dummy->val = 0;  // 哑结点的值只是占位，不会被返回
    dummy->next = NULL;  // 初始化 next，避免野指针
    struct ListNode* curr = dummy;  // curr 始终指向结果链表的尾结点
    int carry = 0;  // 进位，取值只能是 0 或 1

    while (l1 != NULL || l2 != NULL || carry != 0) {  // 任一链表还有位、或还留着进位，就继续算一位
        int sum = carry;  // 本位和先加上低位来的进位
        if (l1 != NULL) {  // 第一个加数还有位
            sum += l1->val;  // 累加该位数字
            l1 = l1->next;  // 指针后移，处理更高位
        }
        if (l2 != NULL) {  // 第二个加数还有位
            sum += l2->val;  // 累加该位数字
            l2 = l2->next;  // 指针后移
        }

        carry = sum / 10;  // 整除 10 得到向高位的进位
        int val = sum % 10;  // 对 10 取余得到本位保留的数字

        struct ListNode* newNode = (struct ListNode*) malloc(sizeof(struct ListNode));  // 为本位申请一个新结点
        newNode->val = val;  // 写入本位数字
        newNode->next = NULL;  // 新结点作为新的尾结点，next 置空
        curr->next = newNode;  // 把新结点挂到结果链表尾部
        curr = curr->next;  // 尾指针后移
    }

    struct ListNode* result = dummy->next;  // 结果链表真正的头结点是哑结点的后继
    free(dummy);  // 哑结点只是辅助，释放掉以免内存泄漏
    return result;  // 返回结果链表头
}
