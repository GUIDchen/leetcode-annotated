// 题目：817. 链表组件（Linked List Components）
// 思路：先把 nums 放进哈希集合，再顺链表扫描：跳过一段「不在集合里」的节点后，若紧接着还有属于集合的节点，就计为一个组件，如此反复。
// 时间复杂度：O(n + m)，n 为链表长度、m 为 nums 长度；空间复杂度：O(m)，哈希集合最多存 m 个值。
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
    int numComponents(ListNode* head, vector<int>& nums) {  // head：链表头指针；nums：能组成组件的取值集合
        unordered_set<int> s(nums.begin(), nums.end());  // 把 nums 全部放进哈希集合，做到 O(1) 判断某个值是否属于「组件取值」
        int ans = 0;  // ans：统计到的组件个数
        while (head) {  // 外层循环：链表还没走完就继续寻找下一段组件
            while (head && !s.count(head->val)) head = head->next;  // 先跳过所有不在集合里的节点，head 停在属于集合的节点（或 nullptr）
            ans += head != nullptr;  // 若确实停在集合内的节点上，说明刚找到一个新的组件，计数加一
            while (head && s.count(head->val)) head = head->next;  // 再把这一段连续属于集合的节点整体跳过，避免同一个组件被重复统计
        }  // 一次「找组件」结束，回到外层循环继续扫描
        return ans;  // 返回组件总数
    }  // numComponents 方法结束
};  // Solution 类结束