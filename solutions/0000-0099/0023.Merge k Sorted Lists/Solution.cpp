// 题目：23. 合并 K 个升序链表（Merge k Sorted Lists）
// 思路：小根堆保存每条链表的当前头结点，每次弹出全局最小值接到答案尾部，再把该结点的后继入堆。
// 时间复杂度：O(N log k)，N 为结点总数，每结点入堆/出堆各一次；空间复杂度：O(k)，堆中最多 k 个结点。
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {  // lists：k 条升序链表的头结点数组
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };  // 比较器用「大于」模拟小根堆（priority_queue 默认是大根堆）
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq;  // 存放各链表当前头结点的最小堆
        for (auto head : lists) {  // 遍历每条链表
            if (head) {  // 跳过空链表，否则后面取 val 会空指针
                pq.push(head);  // 把非空链表的头结点入堆
            }
        }
        ListNode* dummy = new ListNode();  // 答案链表的哑结点，便于尾部追加
        ListNode* cur = dummy;  // cur 始终指向答案链表的尾结点
        while (!pq.empty()) {  // 只要堆里有结点就还没合并完
            ListNode* node = pq.top();  // 取出当前全局最小值
            pq.pop();  // 从堆中移除它
            if (node->next) {  // 该结点所属链表还有后续结点
                pq.push(node->next);  // 后继入堆，参与后续比较
            }
            cur->next = node;  // 把最小值挂到答案尾部
            cur = cur->next;  // 尾指针后移
        }
        return dummy->next;  // 返回真正的答案头结点
    }
};
