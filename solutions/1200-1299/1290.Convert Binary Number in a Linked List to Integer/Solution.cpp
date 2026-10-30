// 题目：1290. 二进制链表转整数（Convert Binary Number in a Linked List to Integer）
// 核心思路：遍历链表，每读一位先把结果左移一位，再把该位或进去，等价于按二进制位从高位到低位累积。
// 时间复杂度：O(n)，遍历链表一趟；空间复杂度：O(1)，只用到常数个变量。
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
// 上面是判题器提供的单链表结点结构说明；本题的链表头结点即二进制最高位
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int getDecimalValue(ListNode* head) {  // head 是二进制链表的头结点，返回它表示的十进制整数
        int ans = 0;  // ans 存放累加结果，初值为 0
        for (; head; head = head->next) {  // 空初始化 + 条件 head 非空 + 每轮后移指针，一次遍历整条链表
            ans = ans << 1 | head->val;  // 结果左移一位腾出最低位，再把当前结点的 0/1 或进去
        }  // 结束循环
        return ans;  // 返回算出的十进制值
    }  // 结束函数
};  // 结束题解类