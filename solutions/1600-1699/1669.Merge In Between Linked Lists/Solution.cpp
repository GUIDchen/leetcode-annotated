// 题目：1669. 合并两个链表（Merge In Between Linked Lists）
// 思路：双指针分别停在第 a-1 个节点 p 与第 b 个节点 q，把 list2 接到 p 之后，再把 list2 的尾巴接到 q->next。
// 时间复杂度：O(n + m)，n 为 list1 长度、m 为 list2 长度；空间复杂度：O(1)，只用了常数个指针。
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
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {  // 删掉 list1 中下标 [a, b] 的节点并把 list2 接进去，返回原头节点 list1
        auto p = list1, q = list1;  // p 用于定位第 a-1 个节点，q 用于定位第 b 个节点
        while (--a) {  // 前移 a-1 步，让 p 停在 a-1 号节点（a 会被递减到 0 而退出）
            p = p->next;  // 指针前移
        }  // p 定位完成
        while (b--) {  // 前移 b 步，让 q 停在 b 号节点
            q = q->next;  // 指针前移
        }  // q 定位完成
        p->next = list2;  // 把 list2 的头接到 p 后面
        while (p->next) {  // 一路走到 list2 的最后一个节点
            p = p->next;  // 指针前移
        }  // list2 尾部定位完成
        p->next = q->next;  // 把 list2 的尾巴接到 b 号节点之后的那段链表
        q->next = nullptr;  // 断开 q 之后原来的链接，避免残留多余节点
        return list1;  // 返回合并后的链表头
    }  // 方法结束
};  // 类定义结束