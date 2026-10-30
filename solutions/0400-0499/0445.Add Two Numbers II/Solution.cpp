// 题目：445. 两数相加 II（Add Two Numbers II）
// 思路：链表高位在前，先把两条链表的值分别压栈，再从低位到高位逐位相加；用头插法把每一位的结果挂到虚拟头结点之后，得到高位在前的和。
// 复杂度：时间复杂度 O(m + n)，两条链表各遍历一次；空间复杂度 O(m + n)，两个栈加上结果链表。
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
class Solution {  // 题解类：两条链表表示的数相加（高位在前）
public:  // 公开部分
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {  // l1、l2 是高位在前的数字链表，返回同样高位在前的和
        stack<int> s1;  // 存 l1 的各位数字，栈顶是低位，便于从低位开始相加
        stack<int> s2;  // 存 l2 的各位数字
        for (; l1; l1 = l1->next) s1.push(l1->val);  // 顺序压栈，最后入栈的就是最低位
        for (; l2; l2 = l2->next) s2.push(l2->val);  // 同理把 l2 的各位压栈
        ListNode* dummy = new ListNode();  // 虚拟头结点，用头插法按低位到高位收集结果
        int carry = 0;  // 进位，初始为 0
        while (!s1.empty() || !s2.empty() || carry) {  // 只要还有没加完的位或有进位就继续
            int s = carry;  // 本位和先带上进位
            if (!s1.empty()) {  // l1 还有剩余位
                s += s1.top();  // 加上 l1 当前的最低位
                s1.pop();  // 该位用完出栈
            }  // 闭合 if
            if (!s2.empty()) {  // l2 还有剩余位
                s += s2.top();  // 加上 l2 当前的最低位
                s2.pop();  // 该位用完出栈
            }  // 闭合 if
            // ListNode* node = new ListNode(s % 10, dummy->next);  // 等价写法（分两步）：先建好新节点
            // dummy->next = node;  // 第二步：把新节点挂到 dummy 之后，实现头插
            dummy->next = new ListNode(s % 10, dummy->next);  // 一行完成头插：本位数字插到已收集结果的最前面
            carry = s / 10;  // 计算向高位的进位
        }  // 所有位和进位都处理完了
        return dummy->next;  // dummy 之后就是拼接好的结果链表
    }  // addTwoNumbers 方法结束
};  // Solution 类定义结束