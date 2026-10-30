// 题目：1548. 图中最相似的路径（The Most Similar Path in a Graph）
// 思路：按目标路径逐位置做 DP，f[i][j] 表示路径前 i 个位置走完、且第 i 个位置停在点 j 时的最少不同名字数；
// 时间复杂度：O(m·(n+E))（m 目标路径长度、n 点数、E 边数）；空间复杂度：O(m·n)（DP 表 + 前驱表）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> mostSimilar(int n, vector<vector<int>>& roads, vector<string>& names, vector<string>& targetPath) {  // n：节点数；roads：无向边；names：各点名字；targetPath：目标名字序列
        vector<int> g[n];  // 邻接表：g[x] 保存与点 x 直接相连的所有点（n 个桶）
        for (auto& r : roads) {  // 遍历每条无向边
            int a = r[0], b = r[1];  // 拆出这条边连接的两个端点
            g[a].push_back(b);  // 建立 a -> b 的邻接关系
            g[b].push_back(a);  // 建立 b -> a 的邻接关系（无向图两条都要加）
        }
        int m = targetPath.size();  // 目标路径的长度，也就是 DP 的层数
        int f[m][n];  // f[i][j]：前 i+1 个位置走完并停在点 j 时，名字不匹配的最小个数
        int pre[m][n];  // pre[i][j]：f[i][j] 取到最优时，上一个位置 i-1 停留的节点编号（用于回溯）
        memset(f, 0x3f, sizeof(f));  // 把 DP 表初始化为一个足够大的数，表示"暂不可达"
        memset(pre, -1, sizeof(pre));  // 前驱表初始化为 -1，表示还没有前驱
        for (int j = 0; j < n; ++j) {  // 单独处理第 0 层：路径的第一个位置可以落在任意点
            f[0][j] = targetPath[0] != names[j];  // 名字不同记 1 点代价，相同记 0
        }
        for (int i = 1; i < m; ++i) {  // 从第 1 层开始逐层递推（每个位置都要与前一个位置相邻）
            for (int j = 0; j < n; ++j) {  // 枚举第 i 个位置当前停靠的点 j
                for (int k : g[j]) {  // 枚举 j 的所有邻居 k，作为第 i-1 个位置的可能落点
                    int t = f[i - 1][k] + (targetPath[i] != names[j]);  // 上一层的代价 + 本位置名字不匹配的代价
                    if (t < f[i][j]) {  // 若这条转移更优
                        f[i][j] = t;  // 更新第 i 层停在 j 的最小代价
                        pre[i][j] = k;  // 记录最优前驱，供最后还原路径
                    }
                }
            }
        }
        int k = 0;  // k 保存最优终点节点
        int mi = 1 << 30;  // mi 保存当前找到的最小代价，先设为极大值
        for (int j = 0; j < n; ++j) {  // 在所有终点中挑代价最小的那个
            if (f[m - 1][j] < mi) {  // 发现更小的代价
                mi = f[m - 1][j];  // 更新最小代价
                k = j;  // 更新最优终点节点
            }
        }
        vector<int> ans(m);  // 结果数组，长度为目标路径长度，存放逐个位置的节点编号
        for (int i = m - 1; ~i; --i) {  // 从最后一层往前回溯（~i 等价于 i >= 0）
            ans[i] = k;  // 把当前层的节点编号填到答案对应位置
            k = pre[i][k];  // 顺着前驱指针退回到上一层的节点
        }
        return ans;  // 回溯完成，ans 就是与目标路径最相似的节点序列
    }
};