// 题目：1474. 删除链表 M 个节点之后的 N 个节点（Delete N Nodes After M Nodes of a Linked List）
// 思路：指针 pre 反复「先走 m-1 步停在保留段的最后一个节点，再从它出发跳 n 步找到被删段的末尾，然后接上剩余链表」；保留段不足 m 个或已到末尾就结束。
// 时间复杂度：O(L)，L 为链表长度，每个节点最多被访问一次；空间复杂度：O(1)，只用常数个指针。
// 下面是 LeetCode 题面给出的单链表节点定义（原文件自带的说明性注释块）
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
    ListNode* deleteNodes(ListNode* head, int m, int n) {  // head：链表头；m：每段保留个数；n：每段删除个数
        auto pre = head;  // pre 指向「当前保留段的最后一个节点」的候选位置，从头开始
        while (pre) {  // 只要还没走到链表末尾就继续处理下一段
            for (int i = 0; i < m - 1 && pre; ++i) {  // 先走 m-1 步，让 pre 停在要保留的 m 个节点的最后一个上
                pre = pre->next;  // 向后移动一步
            }
            if (!pre) {  // 剩余节点不足 m 个，后面没有需要删除的节点了
                return head;  // 保留段已到链尾，直接返回原头节点
            }
            auto cur = pre;  // cur 从保留段末尾出发，用来跳过接下来要删除的 n 个节点
            for (int i = 0; i < n && cur; ++i) {  // 最多跳 n 步，跳过 n 个待删节点
                cur = cur->next;  // 向后移动一步
            }
            pre->next = cur ? cur->next : nullptr;  // 把保留段末尾直接连到被删段之后的节点（没有则为空）
            pre = pre->next;  // pre 移到下一段的起点，准备处理下一轮
        }
        return head;  // 全部处理完毕，返回链表头
    }
};