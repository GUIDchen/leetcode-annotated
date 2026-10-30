// 题目：1171. 从链表中删去总和值为零的连续节点（Remove Zero Sum Consecutive Nodes from Linked List）
// 思路：两遍扫描。第一遍用哈希表记录每个前缀和最后一次出现的节点；第二遍重扫，把相同前缀和之间的节点段（和为零）整段跳过。
// 时间复杂度：O(n)，两次线性扫描加哈希查询；空间复杂度：O(n)，哈希表最多保存 n 个前缀和。
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
class Solution {  // 题解类
public:
    ListNode* removeZeroSumSublists(ListNode* head) {  // 删除链表中所有和为零的连续节点段，返回新的头节点
        ListNode* dummy = new ListNode(0, head);  // 哨兵节点：值为 0，next 指向真实头节点，避免特判头节点
        unordered_map<int, ListNode*> last;  // 哈希表：记录每个前缀和最后一次出现的节点
        ListNode* cur = dummy;  // 遍历指针从哨兵开始
        int s = 0;  // 前缀和，初值为哨兵的 0
        while (cur) {  // 第一遍：走到链表末尾
            s += cur->val;  // 累加当前节点的值，得到当前位置的前缀和
            last[s] = cur;  // 用「最后一次出现」覆盖，等价于只保留最靠后的位置
            cur = cur->next;  // 指针后移
        }  // while 结束
        s = 0;  // 第二遍：前缀和归零重新扫描
        cur = dummy;  // 指针重新回到哨兵节点
        while (cur) {  // 同样遍历到末尾
            s += cur->val;  // 累加当前节点的值，得到前缀和
            cur->next = last[s]->next;  // 相同前缀和之间的节点段和为零，直接跳过这一段
            cur = cur->next;  // 跳到下一个需要处理的节点
        }  // while 结束
        return dummy->next;  // 返回真正的新头节点（跳过哨兵）
    }  // 方法结束
};  // 类定义结束