// 题目：708. 循环有序列表的插入（Insert into a Sorted Circular Linked List）
// 思路：从 head 出发绕环一圈，在「值落在 prev 与 curr 之间」或「跨过最大值到最小值的断点」处插入；空表则让新结点自成一环。
// 时间复杂度：O(n)，最坏绕环一整圈；空间复杂度：O(1)，只新建一个结点。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 对外接口：insert 方法
    Node* insert(Node* head, int insertVal) {  // 把 insertVal 插入循环有序链表中，返回链表头指针
        Node* node = new Node(insertVal);  // 先创建待插入的新结点
        if (!head) {  // 空链表：新结点自己组成一个环
            node->next = node;  // 唯一的结点指向自己，形成自环
            return node;  // 返回这个新结点作为链表头
        }
        Node *prev = head, *curr = head->next;  // prev 与 curr 是相邻的一对游标，curr 从 head->next 开始，便于判断一段区间
        while (curr != head) {  // 绕环扫描，curr 回到 head 说明已经转满一圈，仍未找到就落在 head 前插入
            if ((prev->val <= insertVal && insertVal <= curr->val) || (prev->val > curr->val && (insertVal >= prev->val || insertVal <= curr->val))) break;  // 两个可插入条件：普通升序区间内，或者跨过最大值到最小值的断点处
            prev = curr;  // prev 前移一个结点
            curr = curr->next;  // curr 前移一个结点，两者始终保持相邻
        }
        prev->next = node;  // 把新结点接到 prev 之后
        node->next = curr;  // 新结点的后继是 curr，从而保持环的完整
        return head;  // 头结点不变，返回原 head
    }
};