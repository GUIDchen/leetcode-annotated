// 题目：841. 钥匙和房间（Keys and Rooms）
// 思路：房间是节点、钥匙是有向边；从 0 号房间做 DFS 标记所有可达房间，最后看可达数是否等于房间总数。
// 时间复杂度：O(n + e)，n 为房间数、e 为钥匙总数；空间复杂度：O(n)，vis 数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canVisitAllRooms(vector<vector<int>>& rooms) {  // rooms[i] 保存进入房间 i 后能拿到的所有钥匙；返回能否访问全部 n 个房间
        int n = rooms.size();  // 房间总数，也就是最终需要访问的个数
        int cnt = 0;  // 计数器：已经访问过的房间数量
        bool vis[n];  // vis[i] 标记房间 i 是否已访问；长度依赖运行时变量 n，是编译器支持的变长数组
        memset(vis, false, sizeof(vis));  // 初始时一个房间都没访问过，全部置为 false
        function<void(int)> dfs = [&](int i) {  // 定义递归函数 dfs：从房间 i 出发，把能走到的房间都标记为已访问
            if (vis[i]) {  // 如果房间 i 已经访问过，就没必要再搜一遍
                return;  // 直接返回，避免在环路里无限递归
            }  // 已访问分支结束
            vis[i] = true;  // 把房间 i 标记为已访问
            ++cnt;  // 访问计数加一
            for (int j : rooms[i]) {  // 遍历房间 i 里拿到的每把钥匙，钥匙 j 能打开房间 j
                dfs(j);  // 从新房间 j 继续深度优先搜索
            }  // 房间 i 的所有钥匙处理完毕
        };  // lambda 定义结束，此时 dfs 已能递归调用自身
        dfs(0);  // 从 0 号房间出发；0 号房间初始就是打开的，不需要钥匙
        return cnt == n;  // 只有访问数等于房间总数时，才算能进入所有房间
    }  // 方法结束
};  // 类定义结束
