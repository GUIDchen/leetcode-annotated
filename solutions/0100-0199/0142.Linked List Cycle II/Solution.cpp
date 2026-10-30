// 题目：142. 环形链表 II（Linked List Cycle II）
// 思路：快慢指针先判环，相遇后让一个指针回到头部、两指针同速前进，再次相遇的位置就是环的入口。
// 时间复杂度：O(n)，快指针最多走两轮；空间复杂度：O(1)，只用了常数个指针。
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
    ListNode* detectCycle(ListNode* head) {  // head：链表头；返回入环的第一个节点，无环时返回 nullptr
        ListNode* fast = head;  // 快指针一次走两步
        ListNode* slow = head;  // 慢指针一次走一步
        while (fast && fast->next) {  // 快指针能走满两步，才有可能追上慢指针
            slow = slow->next;  // 慢指针前进一格
            fast = fast->next->next;  // 快指针前进两格
            if (slow == fast) {  // 两指针相遇，说明链表有环
                ListNode* ans = head;  // ans 重新从头节点出发
                while (ans != slow) {  // 两个指针同速前进，直到相遇
                    ans = ans->next;  // ans 每次走一步
                    slow = slow->next;  // slow 也每次走一步，二者必然在环入口相遇
                }  // 同速前进结束：相遇点即入口
                return ans;  // 返回环的入口节点
            }  // 相遇分支结束
        }  // 判环循环结束
        return nullptr;  // 快指针走到表尾，说明没有环
    }
};  // 题解类定义结束