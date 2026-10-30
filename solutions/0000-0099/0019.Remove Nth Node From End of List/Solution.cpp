// 题目：19. 删除链表的倒数第 N 个结点（Remove Nth Node From End of List）
// 思路：加哑结点后，快指针先走 n 步，再与慢指针同步前进；快指针到尾时慢指针正好停在待删结点的前驱。
// 时间复杂度：O(L)，L 为链表长度，只遍历一遍；空间复杂度：O(1)，只用了几个指针。
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {  // head：链表头；n：要删除的倒数第 n 个结点
        ListNode* dummy = new ListNode(0, head);  // 哑结点指向 head，这样删除头结点时也有前驱可用
        ListNode* fast = dummy;  // 快指针从哑结点出发
        ListNode* slow = dummy;  // 慢指针也从哑结点出发
        while (n--) {  // 快指针先走 n 步，与慢指针拉开 n 个位置
            fast = fast->next;  // 快指针前进一步
        }
        while (fast->next) {  // 快指针还没到尾结点时继续同步前进
            slow = slow->next;  // 慢指针前进一步
            fast = fast->next;  // 快指针前进一步，两者间距始终保持 n
        }
        slow->next = slow->next->next;  // 此时 slow 是待删结点的前驱，跳过它就是删除
        return dummy->next;  // 返回可能已被更新的真正头结点
    }
};
