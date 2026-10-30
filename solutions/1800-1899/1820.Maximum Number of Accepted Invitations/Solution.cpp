// 题目：1820. 最多邀请的个数（Maximum Number of Accepted Invitations）
// 核心思路：男生与女生构成二分图，grid[i][j]=1 表示男生 i 可邀请女生 j；用匈牙利算法为每个男生找一条增广路，能找到增广路的男生数即最多被接受的邀请数。
// 时间复杂度：O(m·E)，最坏 O(m²n)；空间复杂度：O(n) 的 vis/match 数组，外加 O(m) 的递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumInvitations(vector<vector<int>>& grid) {  // grid[i][j] 为 1 表示第 i 个男生愿意邀请第 j 个女生
        int m = grid.size(), n = grid[0].size();  // m：男生（行）数量；n：女生（列）数量
        bool vis[210];  // vis[j]：本轮增广中第 j 个女生是否已被访问，防止同一轮重复搜索
        int match[210];  // match[j]：女生 j 当前匹配的男生编号，-1 表示尚未匹配
        memset(match, -1, sizeof match);  // 初始化：把所有女生都置为未匹配
        int ans = 0;  // ans：匹配成功的男生数量，即最多接受的邀请数
        function<bool(int)> find = [&](int i) -> bool {  // 递归函数 find：为男生 i 寻找增广路，返回是否匹配成功
            for (int j = 0; j < n; ++j) {  // 枚举男生 i 愿意邀请的每一个女生 j
                if (grid[i][j] && !vis[j]) {  // 只有存在边、且本轮还没访问过的女生才值得尝试
                    vis[j] = true;  // 标记女生 j 已访问，避免同一轮内绕回造成死循环
                    if (match[j] == -1 || find(match[j])) {  // 女生 j 空闲，或她的原配男生 find 能改约到别人，则可以让出 j
                        match[j] = i;  // 于是把女生 j 改匹配给男生 i
                        return true;  // 找到一条增广路，立即返回成功
                    }
                }
            }
            return false;  // 所有女生都试过仍不成功，说明男生 i 无法匹配
        };  // 结束 lambda 的函数体
        for (int i = 0; i < m; ++i) {  // 依次为每个男生尝试增广
            memset(vis, 0, sizeof vis);  // 每个男生开始前清空访问标记，重新独立寻找增广路
            ans += find(i);  // find 返回 true 记为 1、false 记为 0，直接累加即匹配数
        }
        return ans;  // 返回最多能接受的邀请数
    }
};