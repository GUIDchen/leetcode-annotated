// 题目：382. 链表随机节点（Linked List Random Node）
// 思路：蓄水池抽样，遍历链表时第 n 个节点以 1/n 的概率替换答案，最终每个节点被返回的概率都是 1/链表长度。
// 时间复杂度：getRandom 为 O(n)，n 是链表长度；空间复杂度：O(1)，只用了几个计数变量（构造时仅保存头指针）。
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
class Solution {  // 题解类：构造函数保存链表头，getRandom 会被判题器反复调用
public:  // 对外公开的接口
    ListNode* head;  // 成员变量记录链表头，遍历时不能把它挪走

    Solution(ListNode* head) {  // 构造函数：判题器通过 new Solution(head) 调用
        this->head = head;  // 形参与成员同名，this->head 取成员，右侧 head 取形参
    }

    int getRandom() {  // 等概率返回链表中某个节点的值
        int n = 0, ans = 0;  // n 是已遍历的节点数，ans 是当前被抽中的节点值
        for (ListNode* node = head; node != nullptr; node = node->next) {  // 单次遍历整条链表，不额外申请节点数组
            n += 1;  // 现在访问到第 n 个节点
            int x = 1 + rand() % n;  // 在 [1, n] 上等概率取整数，取到 n 的概率正好是 1/n
            if (n == x) ans = node->val;  // 命中就用当前节点替换答案，于是第 k 个节点留到最后的概率是 1/k
        }
        return ans;  // 每个节点被返回的概率都是 1/链表长度
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */