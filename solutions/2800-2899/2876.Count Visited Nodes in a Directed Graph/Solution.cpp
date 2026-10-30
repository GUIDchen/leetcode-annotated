// 题目：2876. 有向图访问计数（Count Visited Nodes in a Directed Graph）
// 思路：函数图每个点出度为 1，从未计算的点出发走步并打时间戳，遇到环先算环长，再回填整条路径。
// 时间复杂度：O(n)，每个点只被标记和回填一次；空间复杂度：O(n)，答案数组与时间戳数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> countVisitedNodes(vector<int>& edges) {  // edges[i] 表示点 i 指向的下一个点
        int n = edges.size();  // 节点个数
        vector<int> ans(n), vis(n);  // ans：每点能访问到的点数；vis：本次模拟走到该点时的步数，0 表示没走过
        for (int i = 0; i < n; ++i) {  // 依次以每个点为起点出发
            if (!ans[i]) {  // 只处理还没算出答案的点
                int cnt = 0, j = i;  // cnt：本路径新标记的点数；j：当前走到的点
                while (vis[j] == 0) {  // 一直走到重复经过（进入环）或碰到已算出答案的点
                    vis[j] = ++cnt;  // 先自增步数，再给 j 打上第 cnt 步的时间戳
                    j = edges[j];  // 沿出边前进一步
                }
                int cycle = 0, total = cnt + ans[j];  // cycle：本路径的环长；total：从起点出发能走过的总点数
                if (ans[j] == 0) {  // ans 为 0 说明 j 是本路径刚走进环的那个点
                    cycle = cnt - vis[j] + 1;  // 环长 = 两次经过同一点的步数差加一
                }
                j = i;  // 回到起点，准备回填
                while (ans[j] == 0) {  // 只回填本路径上还没有答案的点
                    ans[j] = max(total--, cycle);  // 环上的点取环长，环外的点取剩余路径长度
                    j = edges[j];  // 继续沿出边前进
                }
            }
        }
        return ans;  // 返回每个点能访问到的点数
    }
};