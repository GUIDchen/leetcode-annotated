// 题目：61. 旋转链表（Rotate List）
// 思路：先求链长 n 并把 k 对 n 取模；再用快慢指针找到倒数第 k 个结点的前一位，在那里断开，把后段接到头前面。
// 时间复杂度：O(n)，两次遍历链表；空间复杂度：O(1)，只用几个指针。
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
    ListNode* rotateRight(ListNode* head, int k) {  // head：链头；k：向右旋转的步数
        if (!head || !head->next) {  // 空链表或只有一个结点，怎么旋转都不变
            return head;  // 原样返回
        }
        ListNode* cur = head;  // 遍历指针，用来统计结点个数
        int n = 0;  // 链长计数
        while (cur) {  // 走一遍链表
            ++n;  // 每经过一个结点长度加一
            cur = cur->next;  // 移动到下一个结点
        }
        k %= n;  // 旋转 n 次回到原样，所以只需要真正转 k % n 步
        if (k == 0) {  // 取模后为 0，等于不旋转
            return head;  // 直接返回原链表
        }
        ListNode* fast = head;  // 快指针，先走 k 步，于是与慢指针相隔 k 个结点
        ListNode* slow = head;  // 慢指针，之后与快指针同步走
        while (k--) {  // 快指针先前进 k 步
            fast = fast->next;  // 前进一个结点
        }
        while (fast->next) {  // 快指针一直走到尾结点为止，此时快慢相距 k 个结点
            fast = fast->next;  // 快指针继续前进
            slow = slow->next;  // 慢指针同步前进，最终停在倒数第 k+1 个结点（断点前一位）
        }
        ListNode* ans = slow->next;  // 慢指针的下一结点就是旋转后的新头结点
        slow->next = nullptr;  // 在新头之前断开，原来的前半段成为尾段
        fast->next = head;  // 把原来的前半段接到尾结点后面，完成旋转
        return ans;  // 返回新的头结点
    }
};
