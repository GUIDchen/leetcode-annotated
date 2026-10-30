// 题目：86. 分隔链表（Partition List）
// 思路：建两条带头结点的临时链表，小于 x 的结点接到左链、其余接到右链，最后把右链拼到左链尾部。
// 时间复杂度：O(n)，原链表只遍历一次；空间复杂度：O(1)，只用了两个哑结点和几个指针。

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
    ListNode* partition(ListNode* head, int x) {  // head：原链表头；x：分界值，小于 x 的排在前面
        ListNode* l = new ListNode();  // 左链的哑结点：存放所有 < x 的结点
        ListNode* r = new ListNode();  // 右链的哑结点：存放所有 >= x 的结点
        ListNode* tl = l;  // tl 是左链的尾指针，负责接新结点
        ListNode* tr = r;  // tr 是右链的尾指针，负责接新结点
        for (; head; head = head->next) {  // 遍历原链表，head 每次前进一位
            if (head->val < x) {  // 当前结点属于左链
                tl->next = head;  // 挂到左链尾部
                tl = tl->next;  // 左链尾指针前移
            } else {  // 当前结点属于右链
                tr->next = head;  // 挂到右链尾部
                tr = tr->next;  // 右链尾指针前移
            }
        }
        tr->next = nullptr;  // 右链尾部收口，防止接到原链表残留结点形成环
        tl->next = r->next;  // 左链尾部接上右链的第一个真实结点
        return l->next;  // 左链哑结点的下一个就是结果链表头
    }
};
