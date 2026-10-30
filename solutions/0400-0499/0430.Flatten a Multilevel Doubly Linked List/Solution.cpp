// 题目：430. 扁平化多级双向链表（Flatten a Multilevel Doubly Linked List）
// 思路：深度优先遍历链表，遇到 child 就递归展平子链表并把它插到当前节点与 next 之间，返回展平后的尾节点供上一层继续拼接。
// 时间复杂度：O(n)，n 为全部节点数；空间复杂度：O(层级深度)，来自递归栈。
// 说明：下面是题目自带的 Node 定义（被注释掉，由判题器提供），仅作参考。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {  // LeetCode 题解类
public:  // 方法对外可见
    Node* flatten(Node* head) {  // head：多级双向链表头节点；返回展平后的头节点
        flattenGetTail(head);  // 就地展平，返回的尾节点这里用不到
        return head;  // 展平后头节点不变，直接返回
    }

    Node* flattenGetTail(Node* head) {  // 展平以 head 开头的这一层，返回展平后的最后一个节点
        Node* cur = head;  // 当前遍历到的节点
        Node* tail = nullptr;  // 记录已展平部分的尾节点

        while (cur) {  // 沿 next 逐节点前进
            Node* next = cur->next;  // 先保存原 next，因为展平 child 会改写 cur 的 next
            if (cur->child) {  // 当前节点有子链表，需要把它插到 cur 与 next 之间
                Node* child = cur->child;  // 子链表的头节点
                Node* childTail = flattenGetTail(cur->child);  // 递归展平子链表，拿到它的尾节点

                cur->child = nullptr;  // 题目要求展平后 child 指针必须置空
                cur->next = child;  // 把子链表接在当前节点后面
                child->prev = cur;  // 子链表头的 prev 指向当前节点
                childTail->next = next;  // 子链表尾接回原来的 next

                if (next)  // 原 next 可能为空（当前节点是最后一个）
                    next->prev = childTail;  // next 的 prev 改为子链表尾，保持双向一致

                tail = childTail;  // 展平后的尾节点变成子链表的尾
            } else {  // 没有子链表
                tail = cur;  // 当前节点就是展平部分的新尾巴
            }

            cur = next;  // 移动到原链表的下一个节点继续处理
        }  // while 循环结束

        return tail;  // 返回这一层的尾节点，供上一层拼接使用
    }  // 方法结束
};  // 类定义结束