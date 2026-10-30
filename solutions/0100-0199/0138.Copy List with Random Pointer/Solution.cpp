// 题目：138. 随机链表的复制（Copy List with Random Pointer）
// 思路：用哈希表建立「原节点 → 新节点」的映射，第一趟复制 next 方向搭出新链，第二趟按映射补全 random 指针。
// 时间复杂度：O(n)，两趟遍历都是线性的；空间复杂度：O(n)，哈希表与深拷贝出的新链表各占 O(n)。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/  // 以上是 LeetCode 题面给出的 Node 定义（只作注释展示），字段为 val、next、random

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    Node* copyRandomList(Node* head) {  // head：原链表头节点；返回深拷贝后新链表的头节点
        Node* dummy = new Node(0);  // 哨兵节点：让新链表第一个节点的挂接不需要特判空链表
        Node* tail = dummy;  // tail 始终指向新链表的尾节点，方便 O(1) 追加
        unordered_map<Node*, Node*> d;  // 哈希表：键是原节点地址，值是对应的新节点地址
        for (Node* cur = head; cur; cur = cur->next) {  // 第一趟：沿原链表的 next 指针复制每个节点
            Node* node = new Node(cur->val);  // 用原节点的值新建一个节点，random 暂时留空
            tail->next = node;  // 把新节点挂到新链表尾部
            tail = node;  // 尾指针后移，保持指向最后一个节点
            d[cur] = node;  // 记录映射关系，第二趟查 random 时要用到
        }  // 第一趟结束：新链表的骨架（val 与 next）已经建好
        for (Node* cur = head; cur; cur = cur->next) {  // 第二趟：再走一遍原链表，把 random 指针也复制过去
            d[cur]->random = cur->random ? d[cur->random] : nullptr;  // 原节点 random 非空就映射成新节点，为空则新节点也置空
        }  // 第二趟结束：新链表的 random 指针全部补齐
        return dummy->next;  // 跳过哨兵节点，返回真正的新链表头节点
    }
};  // 题解类定义结束
