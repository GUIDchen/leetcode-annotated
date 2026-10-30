// 题目：328. 奇偶链表（Odd Even Linked List）
// 思路：a 维护奇数位链尾、b 维护偶数位链尾、c 记住偶数链头；每轮把奇数节点接到奇链、偶数节点接到偶链，最后偶链接到奇链尾。
// 时间复杂度：O(n)，每个节点只被访问一次；空间复杂度：O(1)，只用了 a、b、c 等常数个指针。
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
// 上面是 LeetCode 题面给出的单链表节点定义，判题器已提供，此处仅作说明
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    ListNode* oddEvenList(ListNode* head) {  // 把奇数位、偶数位节点分别串成两条链，再把偶链接到奇链尾部，返回 head
        if (!head) {  // 空链表直接返回，避免后面解引用空指针
            return nullptr;  // 没有节点，原样返回
        }  // if 分支结束
        ListNode* a = head;  // a 指向奇数位链表的尾部，初始是第 1 个节点（它也是新链表头）
        ListNode *b = head->next, *c = b;  // b 指向偶数位链表的尾部（第 2 个节点）；c 记住偶数链头，最后要接回去
        while (b && b->next) {  // 偶数位尾后面还有节点，说明后面还存在一个可搬动的奇数位节点
            a->next = b->next;  // 把 b 后面的奇数位节点接到奇数链尾
            a = a->next;  // 奇数链尾后移一位
            b->next = a->next;  // 新的奇数链尾后面的节点是下一个偶数位节点，接到偶数链尾
            b = b->next;  // 偶数链尾后移一位
        }  // 循环结束
        a->next = c;  // 奇数链尾接上偶数链头，拼成完整链表
        return head;  // head 始终没变，作为新链表头返回
    }  // 方法结束
};  // 类结束