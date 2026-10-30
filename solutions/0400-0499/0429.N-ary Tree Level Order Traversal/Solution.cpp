// 题目：429. N 叉树的层序遍历（N-ary Tree Level Order Traversal）
// 思路：BFS 逐层处理，每次先固定当前队列长度（即本层节点数），一次弹出整层并把子节点入队，从而把每层结果单独成组。
// 时间复杂度：O(n)，每个节点进出队列各一次；空间复杂度：O(n)，队列最多同时存一层节点。
// 说明：下面是题目自带的 N 叉树 Node 定义（被注释掉，由判题器提供），仅作参考。
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {  // LeetCode 题解类
public:  // 方法对外可见
    vector<vector<int>> levelOrder(Node* root) {  // 返回按层分组后的节点值
        vector<vector<int>> ans;  // ans[k] 保存第 k 层的所有节点值
        if (!root) {  // 空树
            return ans;  // 直接返回空结果，避免把空指针放进队列
        }
        queue<Node*> q{{root}};  // BFS 队列，初始只有根节点
        while (!q.empty()) {  // 只要还有节点没处理
            vector<int> t;  // 存放当前这一层的节点值
            for (int n = q.size(); n; --n) {  // 先固定本层节点数 n，循环只处理这么多节点
                root = q.front();  // 取出队首节点
                q.pop();  // 弹出队首
                t.push_back(root->val);  // 记录该节点的值
                for (auto& child : root->children) {  // 遍历它的所有子节点
                    q.push(child);  // 子节点入队，属于下一层
                }  // 子节点循环结束
            }  // 本层处理完毕
            ans.push_back(t);  // 把本层结果加入答案
        }
        return ans;  // 返回层序遍历结果
    }  // 方法结束
};  // 类定义结束