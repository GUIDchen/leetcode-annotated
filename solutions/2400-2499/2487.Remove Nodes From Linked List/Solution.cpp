// 题目：2487. 从链表中移除节点（Remove Nodes From Linked List）
// 思路：保留的结点序列必然单调不增；用单调栈从左往右淘汰「右侧存在更大值」的结点，再按栈内顺序重建链表。
// 时间复杂度：O(n)，每个结点最多入栈出栈一次；空间复杂度：O(n)，数组与栈各存 n 个值。
// 下面是 LeetCode 题面自带的单链表结点定义（仅作说明，不是需要实现的代码）
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
    ListNode* removeNodes(ListNode* head) {  // head：链表头结点；返回删除所有「右侧存在更大值」的结点之后的新头结点
        vector<int> nums;  // 先按原顺序把所有结点值收集到数组，方便用下标做单调栈
        while (head) {  // 遍历链表直到空指针
            nums.emplace_back(head->val);  // 记录当前结点的值
            head = head->next;  // 移动到下一个结点
        }  // 链表遍历结束
        vector<int> stk;  // 单调栈：从底到顶单调不增，栈里的值就是最终保留的结点
        for (int v : nums) {  // 从左到右扫描每个值
            while (!stk.empty() && stk.back() < v) {  // 栈顶比 v 小，说明它右侧存在更大的 v，应当被删除
                stk.pop_back();  // 弹出被删除的结点值
            }  // 清理结束
            stk.push_back(v);  // v 暂时保留，等待右侧更大的值来淘汰它
        }  // 扫描结束
        ListNode* dummy = new ListNode();  // 哑结点，简化尾插时对空链表的判断
        head = dummy;  // head 复用为尾指针，指向当前链表末尾
        for (int v : stk) {  // 按栈内顺序（即答案顺序）重建链表
            head->next = new ListNode(v);  // 新建结点挂到尾部
            head = head->next;  // 尾指针后移
        }  // 重建结束
        return dummy->next;  // 跳过哑结点，返回真正的头结点
    }  // 方法结束
};  // 类定义结束