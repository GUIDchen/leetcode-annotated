// 题目：2049. 统计最高分的节点数目（Count Nodes With the Highest Score）
// 思路：先按 parents 建立孩子表，再用一次后序 DFS 求出每棵子树大小；删掉节点 i 后，各连通块大小是「每个孩子子树大小」和「n - 子树大小」，得分就是它们的乘积，边算边更新最大值与计数。
// 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，孩子表与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countHighestScoreNodes(vector<int>& parents) {  // parents[i] 是节点 i 的父节点（根节点 0 的父节点为 -1）；返回得分最高的节点个数
        int n = parents.size();  // 节点总数
        vector<int> g[n];  // 邻接表：g[i] 保存节点 i 的所有孩子
        for (int i = 1; i < n; ++i) {  // 0 号是根，从 1 号开始把每个节点挂到父节点下
            g[parents[i]].push_back(i);  // 把 i 加入它的父节点的孩子列表
        }  // 结束建树循环
        int ans = 0;  // ans：得分最高的节点个数
        long long mx = 0;  // mx：当前记录到的最高得分，得分是乘积，用 long long 防止溢出
        function<int(int, int)> dfs = [&](int i, int fa) {  // 后序 DFS：返回以 i 为根的子树的节点数；fa 是父节点，用于跳过回边
            long long score = 1;  // 节点 i 的得分：删掉它以后各连通块大小的乘积，初值为 1
            int cnt = 1;  // 子树大小，先把自己算进去
            for (int j : g[i]) {  // 遍历 i 的所有孩子
                if (j != fa) {  // 跳过父节点，避免沿着边往回走
                    int t = dfs(j, i);  // 递归求出这个孩子的子树大小
                    cnt += t;  // 把自己之外的这部分累加进子树大小
                    score *= t;  // 每个孩子子树都是一个独立连通块，大小乘进得分
                }  // 结束孩子判断
            }  // 结束孩子遍历
            if (n - cnt) {  // 父节点那一侧也是一个连通块，大小为 n - cnt
                score *= n - cnt;  // 把上方连通块的大小也乘进得分
            }  // 结束上方连通块处理
            if (mx < score) {  // 出现比当前最高分更高的得分
                mx = score;  // 更新最高分
                ans = 1;  // 计数重置为 1，只保留当前这个节点
            } else if (mx == score) {  // 得分与当前最高分相同
                ++ans;  // 计数加一
            }  // 结束得分比较
            return cnt;  // 把子树大小返回给父节点使用
        };  // lambda 定义结束
        dfs(0, -1);  // 从根节点开始后序遍历整棵树
        return ans;  // 返回得分最高的节点个数
    }  // 方法结束
};  // 题解类结束
