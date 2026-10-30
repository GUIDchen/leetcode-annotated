// 题目：1836. 从未排序的链表中移除重复元素（Remove Duplicates From an Unsorted Linked List）
// 思路：第一遍遍历用哈希表统计每个值出现的次数，第二遍用哑结点加前驱指针扫描，把计数大于 1 的结点原地摘除。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，哈希表最多存 n 个不同取值的计数。
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
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {  // head 为链表头结点，返回删除全部重复值结点后的新头结点
        unordered_map<int, int> cnt;  // 哈希表：键是结点值，值是该值在链表中出现的次数
        for (ListNode* cur = head; cur; cur = cur->next) {  // 第一遍遍历：从头到尾统计每个值出现了多少次
            cnt[cur->val]++;  // 当前结点值的计数加一
        }  // 统计循环结束
        ListNode* dummy = new ListNode(0, head);  // 哑结点指向原头结点，避免单独处理“头结点被删”的边界
        for (ListNode *pre = dummy, *cur = head; cur; cur = cur->next) {  // 第二遍遍历：pre 始终是 cur 的前驱，便于原地删除
            if (cnt[cur->val] > 1) {  // 计数大于 1 说明该值是重复值，所有同值结点都要删掉
                pre->next = cur->next;  // 让前驱跳过 cur，把 cur 从链表中摘除；pre 保持不动
            } else {  // 否则该值唯一，保留当前结点
                pre = cur;  // 前驱前移到当前结点
            }  // 分支结束
        }  // 遍历结束，重复结点已全部摘除
        return dummy->next;  // 哑结点的后继就是新的头结点
    }  // 方法结束
};  // 类定义结束