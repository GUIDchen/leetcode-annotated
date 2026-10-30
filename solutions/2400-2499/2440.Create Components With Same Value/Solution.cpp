// 题目：2440. 创建价值相同的连通块（Create Components With Same Value）【困难】
// 思路：总和为 s，若最终切成 k 块则每块价值和必须等于 t = s/k；从 min(n, s/mx) 递减枚举 k，只对 s%k==0 的 k 做一次后序 DFS 自底向上切块，能正好切完就返回 k-1 条被删除的边。
// 时间复杂度：最坏 O(n·min(n, s/mx))，只有 s%k==0 时才做一次 O(n) 的 DFS；空间复杂度：O(n)，邻接表 + 递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {  // nums 是各节点价值，edges 是无向树的边
        int n = nums.size();  // 节点个数，块数 k 的上界之一
        int s = accumulate(nums.begin(), nums.end(), 0);  // 求全部节点价值之和 s
        int mx = *max_element(nums.begin(), nums.end());  // 单节点最大价值 mx，由此得到块数上界 s/mx
        int t = 0;  // 目标块和 t（每块必须恰好等于它），在下面的 k 循环里被重新赋值
        unordered_map<int, vector<int>> g;  // 邻接表：节点 -> 邻居列表（节点编号不保证连续，所以用 map）
        for (auto& e : edges) {  // 逐条边建无向图
            int a = e[0], b = e[1];  // 取出这条边的两个端点
            g[a].push_back(b);  // a 的邻居列表追加 b
            g[b].push_back(a);  // b 的邻居列表追加 a（无向图双向都要加）
        }
        function<int(int, int)> dfs = [&](int i, int fa) -> int {  // 后序 DFS：返回以 i 为根的「未封口」块价值和，-1 表示这种切法不合法
            int x = nums[i];  // 当前块先放入节点 i 自身的价值
            for (int j : g[i]) {  // 遍历 i 的所有邻居
                if (j != fa) {  // 跳过父节点 fa，避免沿树边绕回去
                    int y = dfs(j, i);  // 递归处理子树 j，并把 i 作为它的父节点传入
                    if (y == -1) return -1;  // 子树已判定失败，整棵子树立刻失败上抛
                    x += y;  // 把子树送回来的残留价值和并入当前块
                }
            }
            if (x > t) return -1;  // 当前块和超过目标 t，已经无法补救，返回 -1
            return x < t ? x : 0;  // 正好等于 t 就封口返回 0；不足 t 就把残留 x 交给父节点继续累加
        };
        for (int k = min(n, s / mx); k > 1; --k) {  // 从可能的最大块数开始递减枚举 k；k=1 时不用删边，答案是 0 不必尝试
            if (s % k == 0) {  // 只有总和能被 k 整除，每块才可能分到整数价值和 t
                t = s / k;  // 计算本次尝试的目标块和
                if (dfs(0, -1) == 0) {  // 从 0 号节点出发（父节点记 -1），返回 0 说明整棵树恰好切成 k 块
                    return k - 1;  // k 块之间需要删掉 k-1 条边，这就是答案
                }
            }
        }
        return 0;  // 所有 k 都失败，只能保持一整块，返回 0 条被删边
    }
};
