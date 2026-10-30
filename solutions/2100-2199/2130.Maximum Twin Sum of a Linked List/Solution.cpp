// 题目：2130. 链表最大孪生和（Maximum Twin Sum of a Linked List）
// 核心思路：先把链表所有值按顺序放进数组，再用下标 i 与 n-1-i 配对（孪生对），取最大和。
// 时间复杂度：O(n)，遍历链表与配对各一遍；空间复杂度：O(n)，数组保存所有节点值。
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
    int pairSum(ListNode* head) {  // head 是链表头指针；返回所有孪生和中的最大值
        vector<int> s;  // 用动态数组按链表顺序保存所有节点的值，便于随机访问
        for (; head != nullptr; head = head->next) s.push_back(head->val);  // 单指针遍历链表（head 本身作为游标），把每个节点的值追加进数组
        int ans = 0, n = s.size();  // ans 记录最大孪生和；n 是节点个数（题目保证为偶数）
        for (int i = 0; i < (n >> 1); ++i) ans = max(ans, s[i] + s[n - i - 1]);  // 只枚举前半段 i，其孪生下标是 n-1-i；n >> 1 等价于 n/2
        return ans;  // 返回所有孪生和中的最大值
    }
};