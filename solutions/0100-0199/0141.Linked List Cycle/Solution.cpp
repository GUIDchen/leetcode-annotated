// 题目：141. 环形链表（Linked List Cycle）
// 思路：遍历时把走过的节点地址放进哈希集合，再次遇到同一地址就说明指针绕回来了，即存在环。
// 时间复杂度：O(n)，每个节点最多访问一次；空间复杂度：O(n)，集合最多保存 n 个节点指针。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */  // 以上是 LeetCode 题面给出的链表节点定义（只作注释展示），实际由判题器提供
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool hasCycle(ListNode* head) {  // head：链表头节点；返回链表中是否存在环
        unordered_set<ListNode*> s;  // 集合记录已经访问过的节点，按节点地址区分
        for (; head; head = head->next) {  // 顺着 next 一路走，走到空指针就表示到达表尾
            if (s.contains(head)) {  // 当前节点之前访问过
                return true;  // 地址重复说明成环，立即返回真
            }
            s.insert(head);  // 第一次见到的节点记入集合，供后续判重
        }
        return false;  // 无环，正常走到了 nullptr
    }
};  // 题解类定义结束