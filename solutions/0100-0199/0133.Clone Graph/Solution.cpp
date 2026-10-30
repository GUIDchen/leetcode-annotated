// 题目：133. 克隆图（Clone Graph）
// 思路：DFS 深拷贝。用哈希表记录“原节点 → 克隆节点”，先登记当前节点再递归邻居，这样环形结构也不会无限递归。
// 时间复杂度：O(V + E)，每个点、每条边只处理一次；空间复杂度：O(V)，哈希表与递归栈。
// 说明：紧接着的块注释是 LeetCode 题面预先给出的 Node 定义。
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    Node* cloneGraph(Node* node) {  // 返回 node 的深拷贝；node 为空指针时也返回空指针
        unordered_map<Node*, Node*> g;  // 哈希表 g：键是原图节点，值是它对应的克隆节点，同时充当“是否已克隆”的标记
        auto dfs = [&](this auto&& dfs, Node* node) -> Node* {  // C++23 的显式对象参数写法，让 lambda 能递归调用自身
            if (!node) {  // 空图直接返回
                return nullptr;  // 空指针表示空图
            }
            if (g.contains(node)) {  // 这个节点已经克隆过了（环上的边会让同一个节点被走到多次）
                return g[node];  // 直接复用已有的副本，保证一个原节点只对应一个克隆对象
            }
            Node* cloned = new Node(node->val);  // 新建一个值相同的节点
            g[node] = cloned;  // 先登记再递归：这样邻居里出现指向自己的边时，不会又新建一个节点导致死循环
            for (auto& nxt : node->neighbors) {  // 遍历原节点的所有邻居
                cloned->neighbors.push_back(dfs(nxt));  // 递归克隆邻居，并把它挂到克隆节点的邻接表上
            }
            return cloned;  // 返回当前节点对应的克隆
        };  // 递归 lambda 定义结束
        return dfs(node);  // 从入口节点开始克隆整张连通图
    }
};
