// 题目：1575. 统计所有可行路径（Count All Possible Routes）
// 思路：记忆化搜索，状态为「当前城市 i + 剩余油量 k」，先剪掉连直达终点都不够的分支，再枚举下一座城市累加方案数并取模。
// 时间复杂度：O(n^2 * fuel)，共 n*(fuel+1) 个状态、每状态枚举 n 个城市；空间复杂度：O(n * fuel)，记忆化表规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {  // locations：城市坐标数组；start/finish：起点与终点下标；fuel：初始油量
        int n = locations.size();  // 城市数量，也是状态表第一维的大小
        int f[n][fuel + 1];  // 记忆化表：f[i][k] 表示当前在城市 i、还剩 k 油量时的可行路径数
        memset(f, -1, sizeof(f));  // 用 -1 标记「尚未计算」，以便和合法的答案 0 区分
        const int mod = 1e9 + 7;  // 取模常量，防止路径总数溢出
        function<int(int, int)> dfs = [&](int i, int k) -> int {  // 递归函数 dfs(i, k)：当前在城市 i、剩余油量 k 时的方案数，用 lambda 捕获外部变量
            if (k < abs(locations[i] - locations[finish])) {  // 剩余油量连直达终点都不够，这条分支不可能到达终点
                return 0;  // 该分支贡献 0 条路径
            }  // 剪枝判断结束
            if (f[i][k] != -1) {  // 该状态之前算过，直接复用记忆化结果
                return f[i][k];  // 返回已缓存的值
            }  // 缓存判断结束
            int ans = i == finish;  // 只要当前就在终点，停留即算一条合法路径（起点就是终点时的那条空路径也计入）
            for (int j = 0; j < n; ++j) {  // 枚举下一步要去的城市 j
                if (j != i) {  // 不能原地停留，必须跳到别的城市
                    ans = (ans + dfs(j, k - abs(locations[i] - locations[j]))) % mod;  // 花掉两城距离的油量后递归求解，累加并取模
                }  // if 分支结束
            }  // for 循环结束
            return f[i][k] = ans;  // 把结果写回记忆化表后再返回
        };  // lambda 定义结束
        return dfs(start, fuel);  // 从起点、满油状态开始搜索
    }  // 方法结束
};  // 题解类结束