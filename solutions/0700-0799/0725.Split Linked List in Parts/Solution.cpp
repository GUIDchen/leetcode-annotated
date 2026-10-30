// 题目：725. 分隔链表（Split Linked List in Parts）
// 思路：先求链表长度 n，则前 n%k 段各长 n/k+1，其余各长 n/k；再按段长边走边断开，空段留空指针。
// 时间复杂度：O(n + k)，需先遍历一次求长度；空间复杂度：O(k)，保存 k 个段头指针。
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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {  // head：链表头；k：要分成的段数
        int n = 0;  // 链表总长度
        for (ListNode* cur = head; cur != nullptr; cur = cur->next) {  // 遍历链表统计节点个数
            ++n;  // 长度加一
        }  // for 循环结束
        int cnt = n / k, mod = n % k;  // 每段至少 cnt 个节点，前 mod 段各多 1 个
        vector<ListNode*> ans(k, nullptr);  // 结果数组长度固定为 k，不足的段保持空指针
        ListNode* cur = head;  // 当前待分配的节点
        for (int i = 0; i < k && cur != nullptr; ++i) {  // 逐段切分；链表用完就提前停止，后面的段留空
            ans[i] = cur;  // 本段的头节点
            int m = cnt + (i < mod ? 1 : 0);  // 本段节点数：前 mod 段多一个
            for (int j = 1; j < m; ++j) {  // 从段头走 m-1 步，停在本段最后一个节点上
                cur = cur->next;  // 前进一步
            }  // for 循环结束
            ListNode* nxt = cur->next;  // 记下下一段的起点
            cur->next = nullptr;  // 断开本段尾部，使其成为独立链表
            cur = nxt;  // 转到下一段
        }  // for 循环结束
        return ans;  // 返回各段的头指针
    }  // 方法结束
};  // 类定义结束