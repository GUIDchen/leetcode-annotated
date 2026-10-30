// 题目：3063. 链表频率（Linked List Frequency）
// 思路：先用哈希表统计每个值出现的次数，再用头插法把「各不相同的次数」建成一条新链表返回。
// 时间复杂度：O(n)，两次线性遍历；空间复杂度：O(n)，哈希表与新链表各占 O(n)。
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
    ListNode* frequenciesOfElements(ListNode* head) {  // head 是原链表头，返回只含各值出现次数的新链表
        unordered_map<int, int> cnt;  // 哈希表：键是原链表中的值，值是它出现的次数
        for (; head; head = head->next) {  // 顺序遍历原链表
            cnt[head->val]++;  // 当前值计数加一；键不存在时 operator[] 会先默认构造 0 再加一
        }  // 移动到下一个节点
        ListNode* dummy = new ListNode();  // 哑节点，它的 next 用来挂结果链表，省去头插时的空指针判断
        for (auto& [_, val] : cnt) {  // 结构化绑定遍历哈希表：键（原值）用不到的 _ 占位，val 是出现次数
            dummy->next = new ListNode(val, dummy->next);  // 头插法：把新节点接到 dummy 之后，实现结果链表逆序拼接
        }  // 本次插入结束
        return dummy->next;  // 返回哑节点的下一个节点，即真正的结果链表头
    }  // 方法结束
};  // 类定义结束