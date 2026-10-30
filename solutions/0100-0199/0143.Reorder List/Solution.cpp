// 题目：143. 重排链表（Reorder List）
// 思路：快慢指针找到中点并断开，反转后半段，再把两段链表交替合并，原地完成重排。
// 时间复杂度：O(n)，找中点、反转、合并各一趟；空间复杂度：O(1)，只用了若干指针变量。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */  // 以上是 LeetCode 题面给出的链表节点定义（只作注释展示），实际由判题器提供
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void reorderList(ListNode* head) {  // head：链表头；原地重排所以返回 void
        ListNode* fast = head;  // 快指针，用来把慢指针带到中点
        ListNode* slow = head;  // 慢指针，最终停在前半段的最后一个节点
        while (fast->next && fast->next->next) {  // 快指针还能跳两格就继续，保证 slow 指向前半段末尾
            slow = slow->next;  // 慢指针走一步
            fast = fast->next->next;  // 快指针走两步
        }  // 找中点结束，middle 为 slow

        ListNode* cur = slow->next;  // cur 指向后半段的第一个节点
        slow->next = nullptr;  // 断开前后两段，避免反转时互相干扰

        ListNode* pre = nullptr;  // pre 是反转后链表的头，初始为空
        while (cur) {  // 逐节点反转后半段
            ListNode* t = cur->next;  // 先保存后继，防止断链后丢失
            cur->next = pre;  // 当前节点反向指向前一个节点
            pre = cur;  // pre 前移，成为新的反转链头
            cur = t;  // cur 继续处理原来的后继
        }  // 反转结束，pre 是后半段新的头
        cur = head;  // cur 回到整条链表头部，准备做合并

        while (pre) {  // pre 非空说明后半段还有节点待插入
            ListNode* t = pre->next;  // 保存后半段的下一个节点备用
            pre->next = cur->next;  // pre 先接上 cur 原本的后继，保证链表不断
            cur->next = pre;  // cur 后面接上 pre，完成一次交替插入
            cur = pre->next;  // cur 跳到下一个待插入位置（原前半段的下一个节点）
            pre = t;  // pre 推进到后半段的下一个节点
        }  // 合并完成，链表已按要求交错重排
    }
};  // 题解类定义结束