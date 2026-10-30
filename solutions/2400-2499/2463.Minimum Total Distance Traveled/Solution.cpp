// 题目：2463. 最小移动总距离（Minimum Total Distance Traveled）
// 思路：机器人与工厂分别排序后，按顺序枚举「当前工厂修几台连续的机器人」，用记忆化搜索求最小总距离。
// 时间复杂度：O(R * F * C)，R 为机器人数、F 为工厂数、C 为最大容量（记忆化后每个状态只算一次）；空间复杂度：O(R * F)。
class Solution {  // LeetCode 题解类
public:  // 判题器通过 public 区调用下面的方法
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {  // robot 是机器人坐标数组，factory 每项为 [工厂坐标, 可维修容量]
        ranges::sort(robot);  // 机器人坐标排序：最优方案中机器人一定按位置顺序依次分配给工厂，不会交叉
        ranges::sort(factory);  // 工厂按坐标排序，这样 DP 可以按顺序决定每个工厂负责哪一段连续的机器人
        using ll = long long;  // 距离总和可能超过 int，用 64 位整数
        vector<vector<ll>> f(robot.size(), vector<ll>(factory.size(), -1));  // 记忆化表：f[i][j] 表示「从第 i 台机器人开始、只用第 j 及之后的工厂」的最小总距离，-1 表示尚未计算

        auto dfs = [&](this auto&& dfs, int i, int j) -> ll {  // C++23 显式对象参数写法：dfs 就是 lambda 自身，可以自递归；i 是待分配的第一台机器人，j 是当前工厂
            if (i == robot.size()) {  // 机器人都已分配完
                return 0;  // 没有剩余距离可加，递归出口
            }  // i 的边界判断结束
            if (j == factory.size()) {  // 还有机器人没分配，但工厂已经用完
                return 1e15;  // 返回一个足够大的数表示不可行，让上层 min 自动排除这条分支
            }  // j 的边界判断结束
            if (f[i][j] != -1) {  // 该状态在之前已经算过
                return f[i][j];  // 直接复用记忆化结果，避免指数级重复搜索
            }  // 查表结束
            ll ans = dfs(i, j + 1);  // 方案一：第 j 个工厂一台都不修，直接跳过它
            ll t = 0;  // t 累加「第 j 个工厂维修前 k+1 台机器人」的总距离
            for (int k = 0; k < factory[j][1]; ++k) {  // 枚举第 j 个工厂维修的台数（下标 k），不能超过它的容量
                if (i + k >= robot.size()) {  // 机器人数量不够再分了
                    break;  // 提前结束台数枚举
                }  // 越界判断结束
                t += abs(robot[i + k] - factory[j][0]);  // 把第 i+k 台机器人交给第 j 个工厂，累加这段距离
                ans = min(ans, t + dfs(i + k + 1, j + 1));  // 方案二：用该工厂修完这 k+1 台后，剩余机器人交给后面的工厂，取更优者
            }  // 台数枚举结束
            f[i][j] = ans;  // 记录该状态的最优值，供后续复用
            return ans;  // 返回当前状态的最小总距离
        };  // lambda 定义结束
        return dfs(0, 0);  // 从第 0 台机器人、第 0 个工厂开始递推求答案
    }  // 方法结束
};  // 类定义结束
