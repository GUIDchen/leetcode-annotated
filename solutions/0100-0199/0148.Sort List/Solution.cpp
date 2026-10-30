// 题目：148. 排序链表（Sort List）
// 思路：归并排序——快慢指针找到中点把链表断开，递归排好两段，再用哑节点做二路归并。
// 时间复杂度：O(n log n)，每层归并 O(n)、共 log n 层；空间复杂度：O(log n)，递归栈深度。
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
class Solution {  // 题目要求的题解类
public:  // 对外提供 sortList 方法
    ListNode* sortList(ListNode* head) {  // 先找中点拆成两段，分别递归排序后合并
        if (!head || !head->next) {  // 空链表或只有一个节点：已经有序
            return head;  // 直接返回
        }
        ListNode* slow = head;  // 慢指针，最终落在左半段的最后一个节点
        ListNode* fast = head->next;  // 快指针从 head->next 出发，保证偶数个节点时中点偏左
        while (fast && fast->next) {  // 快指针每次走两步，走到末尾时慢指针在中点
            slow = slow->next;  // 慢指针走一步
            fast = fast->next->next;  // 快指针走两步
        }
        ListNode* l1 = head;  // 左半段：head 到 slow
        ListNode* l2 = slow->next;  // 右半段：slow->next 到链表末尾
        slow->next = nullptr;  // 断开两段，否则递归无法终止
        l1 = sortList(l1);  // 递归排序左半段
        l2 = sortList(l2);  // 递归排序右半段
        ListNode* dummy = new ListNode();  // 合并用的哑节点，省去第一次接入时的判空
        ListNode* tail = dummy;  // tail 指向合并结果链表的末尾
        while (l1 && l2) {  // 两段都还有节点时，比较各自头节点的大小
            if (l1->val <= l2->val) {  // 左段头节点更小（取等号让排序保持稳定）
                tail->next = l1;  // 接上左段节点
                l1 = l1->next;  // 左段头指针后移
            } else {  // 右段头节点更小
                tail->next = l2;  // 接上右段节点
                l2 = l2->next;  // 右段头指针后移
            }
            tail = tail->next;  // 合并结果末尾后移
        }
        tail->next = l1 ? l1 : l2;  // 接上剩余还没走完的那一段
        return dummy->next;  // 哑节点之后就是合并结果的头节点
    }  // sortList 方法结束
};  // Solution 类定义结束
