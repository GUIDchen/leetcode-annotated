// 题目：1290. 二进制链表转整数（Convert Binary Number in a Linked List to Integer）
// 核心思路：遍历链表，每读一位先把结果左移一位，再把该位或进去，等价于按二进制位从高位到低位累积。
// 时间复杂度：O(n)，遍历链表一趟；空间复杂度：O(1)，只用到常数个变量。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// 上面是判题器提供的单链表结点结构说明；本题的链表头结点即二进制最高位
int getDecimalValue(struct ListNode* head) {  // 头结点代表二进制最高位，返回整条链表对应的十进制整数
    int ans = 0;  // ans 存放累加结果，初值为 0
    struct ListNode* cur = head;  // cur 是遍历指针，从头结点开始
    while (cur) {  // 链表不为空就继续读下一位
        ans = (ans << 1) | cur->val;  // 结果左移一位腾出最低位，再把当前结点的 0/1 或进去，等价于边读边累加二进制
        cur = cur->next;  // 指针后移，处理下一位
    }  // 遍历结束
    return ans;  // 返回算出的十进制值
}  // 函数结束