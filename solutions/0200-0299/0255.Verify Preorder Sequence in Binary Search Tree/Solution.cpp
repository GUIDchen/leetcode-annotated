// 题目：255. 验证二叉搜索树的前序遍历序列（Verify Preorder Sequence in Binary Search Tree）
// 思路：单调栈。用 last 记录已经回溯过的祖先最大值作为下界；当前值必须 ≥ last，遇到更大的值时不断弹栈并更新 last，从而模拟「右移」的过程。
// 时间复杂度：O(n)，每个元素入栈、出栈各一次；空间复杂度：O(n)，栈深度最坏为 n。

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool verifyPreorder(vector<int>& preorder) {  // preorder：待验证的前序遍历序列
        stack<int> stk;  // 单调栈：保存从根到当前节点的路径，值从栈底到栈顶递减
        int last = INT_MIN;  // last：已经完成出栈的祖先中的最大值，即当前节点值的下界
        for (int x : preorder) {  // 按前序顺序逐个处理节点值
            if (x < last) return false;  // 比下界还小，说明它落在某个祖先的右子树里却不够大，非法
            while (!stk.empty() && stk.top() < x) {  // 当前值比栈顶大：栈顶节点的左子树结束，回到其右子树
                last = stk.top();  // 栈顶节点成为新的下界
                stk.pop();  // 弹出已经处理完的祖先
            }
            stk.push(x);  // 当前节点入栈，表示继续深入它的左子树
        }
        return true;  // 所有元素都满足约束，序列合法
    }  // 结束方法
};  // 结束类