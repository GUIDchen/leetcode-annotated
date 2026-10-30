// 题目：3217. 从链表中移除在数组中存在的节点（Delete Nodes From Linked List Present in Array）
// 思路：先把 nums 装进哈希集合，再用哑结点从头遍历链表，命中集合就删掉当前后继节点。
// 时间复杂度：O(n + m)，n 为数组长度、m 为链表长度；空间复杂度：O(n)，哈希集合存放数组中的全部值。
// 下面是 LeetCode 判题器预置的单链表节点定义，以注释形式给出，不属于本题代码
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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {  // nums：需要删除的值；head：原链表头结点
        unordered_set<int> s(nums.begin(), nums.end());  // 把待删除的值全部放进哈希集合，单次查询 O(1)
        ListNode* dummy = new ListNode(0, head);  // 哑结点指向原头结点，这样「头结点也要删」的情况无需特殊处理
        for (ListNode* pre = dummy; pre->next;) {  // pre 是待检查节点的前驱；pre->next 为空表示链表已到末尾
            if (s.count(pre->next->val)) {  // 后继节点的值在黑名单里，需要把它删掉
                pre->next = pre->next->next;  // 让前驱直接指向后继的后继，完成删除；pre 不动，因为新的后继还要继续检查
            } else {  // 后继节点需要保留
                pre = pre->next;  // 前驱后移一位，继续检查下一个节点
            }
        }
        return dummy->next;  // 哑结点的后继就是删除后的新头结点
    }
};