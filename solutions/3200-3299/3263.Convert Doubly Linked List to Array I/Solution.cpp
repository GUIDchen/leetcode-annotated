// 题目：3263. 将双链表转换为数组 I（Convert Doubly Linked List to Array I）🔒
// 思路：从双向链表的头结点出发，沿 next 指针顺序遍历，把每个结点的值依次追加进数组即可（prev 指针在这道题里无需用到）。
// 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(n)，结果数组存放 n 个值（不计输出为 O(1)）。
/**
 * Definition for doubly-linked list.
 * class Node {
 *     int val;
 *     Node* prev;
 *     Node* next;
 *     Node() : val(0), next(nullptr), prev(nullptr) {}
 *     Node(int x) : val(x), next(nullptr), prev(nullptr) {}
 *     Node(int x, Node *prev, Node *next) : val(x), next(next), prev(prev) {}
 * };
 */
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外公开
    vector<int> toArray(Node* head) {  // head 为双向链表头结点；返回从头结点开始的正序数组
        vector<int> ans;  // ans 依次收集链表各结点的值
        for (; head; head = head->next) {  // 从 head 出发沿 next 指针遍历，直到链表结束
            ans.push_back(head->val);  // 把当前结点的值追加到结果数组
        }  // 循环体结束，head 已在 for 的步进中前进到下一个结点
        return ans;  // 返回转换得到的数组
    }  // 方法结束
};  // 类定义结束
