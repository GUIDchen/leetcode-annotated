// 题目：2816. 翻倍以链表形式表示的数字（Double a Number Represented as a Linked List）
// 思路：链表高位在前，无法直接进位，于是先反转成低位在前，从个位开始乘以 2 并保留进位，最后把结果再反转回高位在前。
// 时间复杂度：O(n)，反转两次加一次遍历共 3 趟；空间复杂度：O(n)，结果链表需要 n 到 n+1 个新节点。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */  // 以上是判题器提供的单链表节点定义，无需修改
class Solution {  // 题解类
public:  // 题解方法对外可见
    ListNode* doubleIt(ListNode* head) {  // head：高位在前的数字链表；返回翻倍后的链表头
        head = reverse(head);  // 第一步先就地反转，让低位在前，方便从个位开始做乘法
        ListNode* dummy = new ListNode();  // 结果链表的虚拟头结点，省去处理空链表的特判
        ListNode* cur = dummy;  // cur 指向结果链表的尾部，用尾插法逐步追加节点
        int mul = 2, carry = 0;  // mul 是乘数（翻倍固定为 2），carry 是上一位算出的进位
        while (head) {  // 遍历原链表的每一位（此时是从个位到最高位）
            int x = head->val * mul + carry;  // 当前位的结果 = 原数字位 × 2 + 低位进位
            carry = x / 10;  // 新的进位：超过 10 的部分留给下一位
            cur->next = new ListNode(x % 10);  // 当前位只保留个位数字，新建节点接到结果链表尾部
            cur = cur->next;  // 尾指针后移
            head = head->next;  // 继续处理下一位
        }
        if (carry) {  // 最高位算完后如果还有进位，需要再多加一个节点（例如 99 × 2 = 198）
            cur->next = new ListNode(carry);  // 补上最高位的进位
        }
        return reverse(dummy->next);  // 结果现在低位在前，再反转一次恢复成高位在前
    }

    ListNode* reverse(ListNode* head) {  // 辅助函数：用头插法就地反转单链表，返回新的头结点
        ListNode* dummy = new ListNode();  // 虚拟头结点，统一处理插到链表头部的情况
        ListNode* cur = head;  // 从原链表头部开始遍历
        while (cur) {  // 逐个摘取节点
            ListNode* next = cur->next;  // 先保存下一个节点，否则改完指针就找不到后续链表了
            cur->next = dummy->next;  // 头插：把当前节点接到虚拟头结点的后继位置
            dummy->next = cur;  // 虚拟头结点指向新的链表头
            cur = next;  // 继续处理原链表的下一个节点
        }
        return dummy->next;  // 虚拟头结点的后继就是反转后的新头结点
    }
};