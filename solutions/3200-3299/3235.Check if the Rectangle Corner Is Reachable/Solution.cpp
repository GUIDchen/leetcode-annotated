// 题目：3235. 判断矩形的两个角落是否可达（Check if the Rectangle Corner Is Reachable）
// 思路：把圆看作障碍，若相交的圆从矩形的「左边或上边」连成一条链通到「右边或下边」，就把起点与终点隔开；用 DFS 判断这种阻断链是否存在。
// 时间复杂度：O(n^2)，每个圆只被搜索一次、每次枚举 n 个邻居；空间复杂度：O(n)，vis 数组与递归栈。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canReachCorner(int xCorner, int yCorner, vector<vector<int>>& circles) {  // 起点角 (0,0)、终点角 (xCorner,yCorner)；circles 每个元素是 {圆心 x, 圆心 y, 半径}
        using ll = long long;  // 统一用 long long，避免 (x-cx)^2 这类运算在 int 上溢出
        // 用捕获引用的 lambda 封装，方便直接读取外层变量
        auto inCircle = [&](ll x, ll y, ll cx, ll cy, ll r) {  // 判断点 (x, y) 是否落在圆 (cx, cy, r) 内或圆上
            return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;  // 平方距离 <= r^2 即点在圆内（含边界），不用开方也就没有精度问题
        };  // inCircle lambda 结束
        auto crossLeftTop = [&](ll cx, ll cy, ll r) {  // 判断圆是否与矩形的「左边或上边」相交：这两条边是起点角的邻边
            bool a = abs(cx) <= r && (cy >= 0 && cy <= yCorner);  // 条件 a：圆心到左边界 x=0 的距离 <= r，且交点的 y 落在 [0, yCorner] 内
            bool b = abs(cy - yCorner) <= r && (cx >= 0 && cx <= xCorner);  // 条件 b：圆心到上边界 y=yCorner 的距离 <= r，且交点的 x 落在 [0, xCorner] 内
            return a || b;  // 与左边或上边任一相交，就说明它切住了起点一侧
        };  // crossLeftTop lambda 结束
        auto crossRightBottom = [&](ll cx, ll cy, ll r) {  // 判断圆是否与矩形的「右边或下边」相交：这两条边是终点角的邻边
            bool a = abs(cx - xCorner) <= r && (cy >= 0 && cy <= yCorner);  // 条件 a：圆心到右边界 x=xCorner 的距离 <= r，且交点的 y 落在 [0, yCorner] 内
            bool b = abs(cy) <= r && (cx >= 0 && cx <= xCorner);  // 条件 b：圆心到下边界 y=0 的距离 <= r，且交点的 x 落在 [0, xCorner] 内
            return a || b;  // 与右边或下边任一相交，就说明它切住了终点一侧
        };  // crossRightBottom lambda 结束

        int n = circles.size();  // 圆的个数，下面多次用到
        vector<bool> vis(n);  // vis：DFS 中标记圆是否已被访问，防止在相交环上重复搜索
        // C++23 的显式 this 参数写法，让 lambda 可以递归调用自身
        auto dfs = [&](this auto&& dfs, int i) -> bool {  // 从第 i 个圆出发 DFS，判断能否沿相交的圆一路连到「右边或下边」
            auto c = circles[i];  // 取出当前圆
            ll x1 = c[0], y1 = c[1], r1 = c[2];  // 拆出圆心坐标与半径，全部用 long long
            if (crossRightBottom(x1, y1, r1)) {  // 当前圆已经碰到右边或下边：起点侧到终点侧的阻断链被打通了
                return true;  // 返回 true 表示这条链成立
            }  // if 结束
            vis[i] = true;  // 标记已访问，避免重复进入
            for (int j = 0; j < n; ++j) {  // 枚举所有其他圆，找与当前圆相交的邻居
                if (vis[j]) {  // 已经访问过的圆不必再搜
                    continue;  // 跳过
                }  // if 结束
                auto c2 = circles[j];  // 取出候选邻居圆
                ll x2 = c2[0], y2 = c2[1], r2 = c2[2];  // 拆出它的圆心与半径
                if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) > (r1 + r2) * (r1 + r2)) {  // 圆心距的平方大于半径和的平方，说明两圆相离
                    continue;  // 相离就不可能连通，跳过这个邻居
                }  // if 结束
                // 只用「朝右下推进」的圆链，避免圆心落在矩形外时的几何误判
                if (x1 * r2 + x2 * r1 < (r1 + r2) * xCorner && y1 * r2 + y2 * r1 < (r1 + r2) * yCorner  // 1) 加权圆心 x 坐标必须小于 (r1+r2)*xCorner，保证接触点在这条边之内
                    && dfs(j)) {  // 2) 加权圆心 y 坐标同样要在 (r1+r2)*yCorner 之内，然后递归检查邻居能否继续连到右下边界
                    return true;  // 邻居也能连通终点侧，整条链成立
                }  // if 结束
            }  // for 结束
            return false;  // 所有邻居都试过仍未连通，返回 false
        };  // dfs lambda 结束

        for (int i = 0; i < n; ++i) {  // 枚举每个圆：先判角点是否被覆盖，再尝试从它开始做阻断链搜索
            auto c = circles[i];  // 取出当前圆
            ll x = c[0], y = c[1], r = c[2];  // 拆出圆心坐标与半径
            if (inCircle(0, 0, x, y, r) || inCircle(xCorner, yCorner, x, y, r)) {  // 起点角或终点角若落在某个圆内，两个角落直接不可达
                return false;  // 角点被覆盖，返回 false
            }  // if 结束
            if (!vis[i] && crossLeftTop(x, y, r) && dfs(i)) {  // 圆心碰到左边/上边，且从它 DFS 能连到右边/下边
                return false;  // 存在完整阻断链，起点到不了终点
            }  // if 结束
        }  // for 结束
        return true;  // 没有任何阻断链，起点可以到达终点
    }  // 方法结束
};  // 类结束
