// 题目：234. 回文链表（Palindrome Linked List）
// 思路：快慢指针找到左半段末尾，把右半段原地反转，再让反转后的右半段与左半段逐值比较。
// 时间复杂度：O(n)，找中点、反转、比较各扫一遍；空间复杂度：O(1)，只用了几个指针。
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
    bool isPalindrome(ListNode* head) {  // head 是链表头结点，返回整条链表是否是回文
        ListNode* slow = head;  // 慢指针：最终停在左半段的最后一个结点
        ListNode* fast = head->next;  // 快指针从第二个结点出发，让奇数长度时左半段更短、右半段更长，比较时刚好对齐
        while (fast && fast->next) {  // 快指针每次走两步，走到头时慢指针正好在中点
            slow = slow->next;  // 慢指针走一步
            fast = fast->next->next;  // 快指针走两步
        }  // 找中点结束
        ListNode* pre = nullptr;  // 反转后右半段的头指针，初始为空
        ListNode* cur = slow->next;  // 从 mid 的下一个结点开始反转右半段
        while (cur) {  // 逐个结点头插，完成右半段的反转
            ListNode* t = cur->next;  // 先保存后继，防止改指针后断链找不到
            cur->next = pre;  // 让当前结点反向指向 pre，完成一次反转
            pre = cur;  // pre 前进到当前结点
            cur = t;  // cur 前进到原来的后继
        }  // 反转结束
        while (pre) {  // 反转后的右半段从头开始，与左半段逐值比较
            if (pre->val != head->val) return false;  // 出现不同的值，立刻判定不是回文
            pre = pre->next;  // 右半段指针后移
            head = head->next;  // 左半段指针同步后移
        }  // 比较结束
        return true;  // 全部相等，是回文链表
    }  // 方法结束
};  // 题解类结束