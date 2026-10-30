// 题目：25. K 个一组翻转链表（Reverse Nodes in k-Group）
// 思路：哑结点保持头不变；每轮从 pre 往后数 k 个结点，够 k 个就截断这一段、就地反转、再接回剩余部分，最后不足 k 个保持原序。
// 时间复杂度：O(n)，每个结点至多被扫描和反转各常数次；空间复杂度：O(1)，只用了固定几个指针。
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
    ListNode* reverseKGroup(ListNode* head, int k) {  // head：链表头；k：每组结点数
        ListNode* dummy = new ListNode(0, head);  // 哑结点指向 head，便于统一处理第一组
        ListNode* pre = dummy;  // pre 始终是「当前组的前驱」，初始为哑结点

        while (pre != nullptr) {  // 反复处理每一组，直到指针失效
            ListNode* cur = pre;  // cur 用来从 pre 往后数 k 个结点，定位当前组的尾结点
            for (int i = 0; i < k; i++) {  // 数 k 步
                cur = cur->next;  // 前进一步
                if (cur == nullptr) {  // 不足 k 个，剩余的保持原顺序不再翻转
                    return dummy->next;  // 直接返回答案
                }
            }

            ListNode* node = pre->next;  // node 是当前组的第一个结点，反转后会变成这组的尾
            ListNode* nxt = cur->next;  // nxt 是先记录下来、留给下一组的后继结点
            cur->next = nullptr;  // 把当前组从原链表上断开，才能安全地整段反转
            pre->next = reverse(node);  // 反转当前组，并把它接到 pre 之后
            node->next = nxt;  // 反转后的尾（原第一个结点）接回后面没处理的结点
            pre = node;  // 下一组的前驱就是这一组的尾结点
        }
        return dummy->next;  // 返回真正的答案头结点
    }

private:  // 辅助函数不对外暴露
    ListNode* reverse(ListNode* head) {  // 反转一条以 head 开头的链表，返回新的头
        ListNode* dummy = new ListNode();  // 哑结点，用头插法收集反转后的结点
        ListNode* cur = head;  // 从原链表头开始逐个摘取
        while (cur != nullptr) {  // 原链表还没走完
            ListNode* nxt = cur->next;  // 先保存后继，避免改指针后丢失
            cur->next = dummy->next;  // 把 cur 插到已有结果的头部（头插法即反转）
            dummy->next = cur;  // 哑结点指向新的头
            cur = nxt;  // 继续处理原链表的下一个结点
        }
        return dummy->next;  // 返回反转后的链表头
    }
};
