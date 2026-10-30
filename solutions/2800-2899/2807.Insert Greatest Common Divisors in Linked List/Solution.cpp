// 题目：2807. 在链表中插入最大公约数（Insert Greatest Common Divisors in Linked List）
// 思路：一次遍历，用前驱 pre 与当前 cur 两个节点值的最大公约数新建节点，插到 pre 与 cur 之间。
// 时间复杂度：O(n log V)，n 为节点数、V 为节点值，每次求 gcd 为对数级；空间复杂度：O(1) 额外指针（新节点属于答案所需）。
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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {  // head：链表头节点，返回插入完成后的头节点
        ListNode* pre = head;  // pre：已经处理完的前一个节点，初始为头节点
        for (ListNode* cur = head->next; cur; cur = cur->next) {  // cur：当前节点，从第二个节点开始逐个向后走
            int x = gcd(pre->val, cur->val);  // x：相邻两个节点值的最大公约数（std::gcd，C++17 起可用）
            pre->next = new ListNode(x, cur);  // 新建值为 x 的节点，插在 pre 与 cur 之间
            pre = cur;  // 前驱推进到 cur，作为下一轮的左端点
        }
        return head;  // 头节点本身不变，直接返回 head
    }
};