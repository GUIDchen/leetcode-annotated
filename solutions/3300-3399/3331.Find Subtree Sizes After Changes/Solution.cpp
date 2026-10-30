// 题目：3331. 修改后子树的大小（Find Subtree Sizes After Changes）
// 思路：按 parent 建树后 DFS，用 26 个栈记录每个字母最近的祖先；回溯时把子树大小累加到“最近的同字母祖先”（没有则累加到原父亲），即完成父子关系改变后的合并。
// 时间复杂度：O(n)，每个节点进出栈各一次；空间复杂度：O(n)，邻接表、字母栈与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {  // parent 是每个节点的父节点，s 是每个节点的字符；返回调整后的子树大小
        int n = s.size();  // 节点总数
        vector<int> g[n];  // 邻接表：g[u] 存放 u 的所有孩子（变长数组是 GCC 扩展）
        vector<int> d[26];  // d[c] 是字符 c 在 DFS 路径上的节点栈，栈顶是离当前节点最近的同字母祖先
        for (int i = 1; i < n; ++i) {  // 0 是根节点，从 1 开始挂接孩子
            g[parent[i]].push_back(i);  // 把 i 挂到它的父亲 parent[i] 下面
        }  // 建树结束
        vector<int> ans(n);  // ans[i] 最终保存以 i 为根的子树大小
        auto dfs = [&](this auto&& dfs, int i, int fa) -> void {  // 递归 lambda：i 是当前节点，fa 是它在原树中的父亲
            ans[i] = 1;  // 子树至少包含节点自己
            int idx = s[i] - 'a';  // 把字符映射到 0..25，方便索引字母栈 d
            d[idx].push_back(i);  // 当前节点入栈，此后它的后代能找到它作为最近的同字母祖先
            for (int j : g[i]) {  // 先递归处理所有孩子，孩子子树大小会先算好
                dfs(j, i);  // 继续往孩子方向 DFS
            }  // 孩子处理完毕
            int k = d[idx].size() > 1 ? d[idx][d[idx].size() - 2] : fa;  // 栈里除自己外还有同字母节点就取次栈顶作为新父亲，否则沿用原父亲 fa
            if (k >= 0) {  // fa 为 -1 表示根节点没有父亲，无处累加
                ans[k] += ans[i];  // 把当前子树大小累加到新父亲，等价于完成改接后的合并
            }  // 累加结束
            d[idx].pop_back();  // 回溯：当前节点离开 DFS 路径，出栈
        };  // 递归 lambda 结束
        dfs(0, -1);  // 从根节点 0 开始 DFS，父亲的哨兵值为 -1
        return ans;  // 返回每个节点的子树大小
    }  // 方法结束
};  // 类定义结束
