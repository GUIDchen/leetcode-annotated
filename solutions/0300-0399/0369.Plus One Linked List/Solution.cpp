// 题目：369. 给单链表加一（Plus One Linked List）
// 思路：加哑结点后一趟扫描找到「最右侧不等于 9 的结点」作为加一位置，该位置加一并把它后面的 9 全部置 0；若哑结点被加一说明整体进位，返回 dummy。
// 时间复杂度：O(n)，两趟线性扫描；空间复杂度：O(1)，只用常数个指针。
// 下列 block comment 是 LeetCode 题面自带的单链表结点定义说明，原样保留
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
    ListNode* plusOne(ListNode* head) {  // head：非空单链表，按高位到低位表示一个非负整数
        ListNode* dummy = new ListNode(0, head);  // 加哑结点：让「整条链全是 9」的进位情况也能统一处理
        ListNode* target = dummy;  // target 指向稍后要加一的位置，先指向哑结点
        for (; head; head = head->next) {  // 用 head 当游标遍历整条链
            if (head->val != 9) {  // 只要不等于 9，加一后就不会向它产生进位
                target = head;  // 记住最右侧的这个非 9 结点
            }  // if 分支闭合
        }  // 遍历结束，target 就是唯一需要 +1 的位置
        target->val++;  // 该位置加一（它原本必然小于 9，不会溢出）
        for (target = target->next; target; target = target->next) {  // 从 target 的下一个结点开始，把它后面的 9 全部改成 0
            target->val = 0;  // 原地清零
        }  // 清零循环闭合
        return dummy->val ? dummy : dummy->next;  // 哑结点被加一说明最高位也进位，结果长度加一；否则跳过哑结点
    }  // 方法结束
};  // 类定义结束