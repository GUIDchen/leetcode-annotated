// 题目：558. 四叉树交集（Logical OR of Two Binary Grids Represented as Quad-Trees）
// 核心思路：递归对两棵四叉树做逻辑或，叶子节点按位或合并；四个子节点若都是同值叶子则可合并成一个叶子。
// 时间复杂度：O(n)，只访问两棵树中对应位置必要的节点；空间复杂度：O(h)，递归栈深度为树高。
/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    Node* intersect(Node* quadTree1, Node* quadTree2) {  // 两个四叉树的根，返回它们按位或之后的四叉树根
        return dfs(quadTree1, quadTree2);  // 交给递归函数处理
    }  // 方法结束

    Node* dfs(Node* t1, Node* t2) {  // t1、t2 是当前要合并的两个子节点
        if (t1->isLeaf && t2->isLeaf) return new Node(t1->val || t2->val, true);  // 都是叶子：直接按位或得到新叶子，值相同或不同都只需一个节点
        if (t1->isLeaf) return t1->val ? t1 : t2;  // t1 是叶子：t1 若为 1 则整块都是 1，结果就是 t1；否则那块结果等于 t2
        if (t2->isLeaf) return t2->val ? t2 : t1;  // t2 是叶子：对称处理，t2 为 1 时结果即 t2，否则等于 t1
        Node* res = new Node();  // 两者都是内部节点：新建一个节点，等待填充四个孩子
        res->topLeft = dfs(t1->topLeft, t2->topLeft);  // 左上子区域递归合并
        res->topRight = dfs(t1->topRight, t2->topRight);  // 右上子区域递归合并
        res->bottomLeft = dfs(t1->bottomLeft, t2->bottomLeft);  // 左下子区域递归合并
        res->bottomRight = dfs(t1->bottomRight, t2->bottomRight);  // 右下子区域递归合并
        // 判断四个孩子是否全为叶子：只有全为叶子才可能把内部节点压平
        bool isLeaf = res->topLeft->isLeaf && res->topRight->isLeaf && res->bottomLeft->isLeaf && res->bottomRight->isLeaf;
        // 判断四个孩子的值是否一致：一致才能用一个叶子代替这棵子树
        bool sameVal = res->topLeft->val == res->topRight->val && res->topRight->val == res->bottomLeft->val && res->bottomLeft->val == res->bottomRight->val;
        if (isLeaf && sameVal) res = res->topLeft;  // 四个孩子都是叶子且值相同，说明整块同值，可以合并回一个叶子节点
        return res;  // 返回合并后的子树根
    }  // 递归函数结束
};  // 类定义结束