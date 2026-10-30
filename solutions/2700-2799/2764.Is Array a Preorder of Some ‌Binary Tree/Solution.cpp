// 题目：2764. 数组是否表示某二叉树的前序遍历（Is Array a Preorder of Some Binary Tree）
// 思路：先用 nodes 建出「父 → 子」邻接表，再用全局指针 k 做前序 DFS：每访问一个节点必须等于 nodes[k]，匹配就消费它并递归所有孩子，最后要求所有节点都被消费完。
// 时间复杂度：O(n)，每个节点和每条边各访问一次；空间复杂度：O(n)，邻接表与递归栈的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isPreorder(vector<vector<int>>& nodes) {  // nodes 每行是 [节点值, 父节点值]，已按前序顺序给出；返回它能否对应某棵二叉树的前序遍历
        int k = 0;  // k 是指针，指向当前应当匹配的 nodes 下标（按前序顺序依次消费节点）
        unordered_map<int, vector<int>> g;  // g 是「父节点 → 子节点列表」的邻接表，用来做深度优先搜索
        for (auto& node : nodes) {  // 遍历 nodes，建立父子边
            g[node[1]].push_back(node[0]);  // node[0] 是子节点值，node[1] 是父节点值；按输入顺序挂到父节点下（顺序会影响前序匹配）
        }  // 建图完成
        function<bool(int)> dfs = [&](int i) {  // 定义递归函数 dfs(i)：尝试用 nodes[k...] 这一段匹配以 i 为根的子树，匹配不上返回 false
            if (i != nodes[k][0]) {  // 前序遍历要求当前访问的节点恰好是 i，否则顺序不符
                return false;  // 顺序不符，直接判失败
            }  // 当前节点与前序序列对上了
            ++k;  // 消费掉 nodes[k]，指针后移，准备匹配下一个节点
            for (int j : g[i]) {  // 按输入顺序依次递归匹配每个子节点
                if (!dfs(j)) {  // 某个子节点匹配失败，整棵子树也就失败
                    return false;  // 立即返回失败
                }  // 子节点判断结束
            }  // 所有子节点都匹配成功
            return true;  // 子树匹配成功
        };  // lambda 定义结束，dfs 现在可以递归调用自己
        return dfs(nodes[0][0]) && k == nodes.size();  // 从根节点开始匹配，并且所有节点都必须被消费完（k == 节点个数）序列才合法
    }  // 方法结束
};  // 类定义结束