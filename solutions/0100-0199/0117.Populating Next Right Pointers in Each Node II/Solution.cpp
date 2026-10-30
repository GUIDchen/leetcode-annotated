// 题目：117. 填充每个节点的下一个右侧节点指针 II（Populating Next Right Pointers in Each Node II）
// 思路：仍然是层序遍历，用 p 记住本层上一个节点，遇到新节点就把 p->next 指向它；BFS 天然按层分组，所以不要求树是完全二叉树。
// 时间复杂度：O(n)，每个节点只入队出队一次；空间复杂度：O(n)，队列最坏保存一整层节点。
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    Node* connect(Node* root) {  // 把每层节点用 next 指针从左到右串起来，返回根节点
        if (!root) {  // 空树直接返回，避免后面访问空指针
            return root;  // 这里返回的就是 nullptr
        }
        queue<Node*> q{{root}};  // BFS 队列，初始只放根节点
        while (!q.empty()) {  // 队列非空说明还有层没处理完
            Node* p = nullptr;  // p 指向本层上一个处理完的节点，初始为空表示还没有
            for (int n = q.size(); n; --n) {  // 一次 for 只处理当前这一整层；先把 q.size() 存下来，避免新入队的子节点干扰本层计数
                Node* node = q.front();  // 取出队头节点
                q.pop();  // 弹出队头
                if (p) {  // 本层已经有前一个节点，就把它和当前节点连起来
                    p->next = node;  // 完成 next 指针赋值
                }
                p = node;  // 当前节点成为本层最后一个节点，供下一个节点连接
                if (node->left) {  // 左孩子存在就入队（孩子可能只有一个，这正是 II 与 I 的区别）
                    q.push(node->left);  // 左孩子入队
                }
                if (node->right) {  // 右孩子存在就入队
                    q.push(node->right);  // 右孩子入队
                }
            }
        }
        return root;  // next 指针已原地填好，返回根节点
    }
};  // 类定义结束