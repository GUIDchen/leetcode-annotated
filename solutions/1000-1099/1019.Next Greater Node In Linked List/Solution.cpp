// 题目：1019. 链表中的下一个更大节点（Next Greater Node In Linked List）
// 思路：先把链表的值摊平成数组，再从右往左扫描并用单调栈维护「右侧尚未被更大值淘汰的候选」，栈顶即当前元素的下一个更大值。
// 时间复杂度：O(n)，每个元素最多入栈出栈各一次；空间复杂度：O(n)，数组、栈与答案数组各占 O(n)。
// 以下是判题器给定的单链表节点定义（以注释形式给出，无需重复声明）
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
// LeetCode 约定的题解类
class Solution {
public:  // 题解方法对外可见
    vector<int> nextLargerNodes(ListNode* head) {  // head：单链表头结点
        vector<int> nums;  // 先把链表的值按顺序摊平成数组，便于用下标做单调栈
        for (; head; head = head->next) {  // 沿 next 指针遍历，直到链表末尾
            nums.push_back(head->val);  // 依次收集每个结点的值
        }
        stack<int> stk;  // 单调栈：栈底到栈顶保持单调不升，存放还没找到下一个更大值的元素
        int n = nums.size();  // 数组长度，也就是链表结点个数
        vector<int> ans(n);  // 答案数组，默认值 0 表示右侧不存在更大的结点
        for (int i = n - 1; ~i; --i) {  // 从右往左扫描，右侧元素的信息已经齐备
            while (!stk.empty() && stk.top() <= nums[i]) {  // 栈顶不大于当前值，它不可能成为当前元素的答案
                stk.pop();  // 弹出这些更小或相等的元素
            }
            if (!stk.empty()) {  // 栈非空说明栈顶就是右侧第一个比当前值大的元素
                ans[i] = stk.top();  // 记录它的值
            }
            stk.push(nums[i]);  // 当前值入栈，供左边的元素继续比较
        }
        return ans;  // 返回每个结点的下一个更大值，没有则为 0
    }
};