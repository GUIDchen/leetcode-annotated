// 题目：1036. 逃离大迷宫（Escape a Large Maze）
// 思路：把二维坐标压成一维长整型键放进哈希集合；从起点与终点各做一次 DFS，若某趟访问的格子数超过障碍能围出的上界 m = k^2/2，说明已冲出包围圈。
// 时间复杂度：O(k^2)，k 为障碍数，每趟 DFS 最多访问 O(k^2) 格；空间复杂度：O(k^2)，用于障碍集合与两个访问集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {  // blocked 是障碍坐标，source 是起点，target 是终点；返回能否逃出
        const int n = 1e6;  // 棋盘边长上限 10^6，合法坐标范围是 [0, n)
        int m = blocked.size() * blocked.size() / 2;  // 关键上界：k 个障碍最多围住约 k^2/2 个格子，搜索超过它即视为已冲出去
        using ll = long long;  // 用 64 位整型保存压缩后的坐标键，避免 int 相乘溢出
        unordered_set<ll> s;  // 哈希集合存放所有障碍点的压缩坐标，便于 O(1) 判断某格是否为障碍
        const int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项 (dirs[k], dirs[k+1]) 组成一个方向，共四个方向
        auto f = [&](int i, int j) {  // lambda：把二维坐标 (i, j) 压缩成一个 long long 键
            return (ll) i * n + j;  // 键 = 行号 * 棋盘边长 + 列号，保证不同格子不会撞键
        };  // 坐标压缩 lambda 结束
        for (const auto& b : blocked) {  // 遍历每一个被封锁的格子
            s.insert(f(b[0], b[1]));  // 把障碍的压缩键插入哈希集合
        }  // 障碍遍历结束
        int sx = source[0], sy = source[1];  // 拆出起点的横纵坐标
        int tx = target[0], ty = target[1];  // 拆出终点的横纵坐标
        unordered_set<ll> vis1, vis2;  // 两趟 DFS 各自的访问集合，互不影响
        auto dfs = [&](this auto&& dfs, int sx, int sy, int tx, int ty, unordered_set<ll>& vis) -> bool {  // 泛型递归 lambda：从 (sx, sy) 搜到 (tx, ty)，vis 记录本趟访问过的格子
            vis.insert(f(sx, sy));  // 标记当前格子已访问，防止重复搜索造成死循环
            if (vis.size() > m) {  // 访问格子数超过上界
                return true;  // 说明已经冲出障碍围成的包围圈，直接判定可以逃出
            }  // 上界判断分支结束
            for (int k = 0; k < 4; ++k) {  // 枚举四个方向
                int x = sx + dirs[k], y = sy + dirs[k + 1];  // 按当前方向算出邻居坐标
                if (x >= 0 && x < n && y >= 0 && y < n) {  // 邻居必须落在棋盘合法范围内
                    if (x == tx && y == ty) {  // 邻居恰好就是目标点
                        return true;  // 直接返回成功
                    }  // 目标判定分支结束
                    auto key = f(x, y);  // 计算邻居的压缩键，供后续判重使用
                    if (!s.contains(key) && !vis.contains(key) && dfs(x, y, tx, ty, vis)) {  // 邻居不是障碍、没被访问过，且从它继续递归能成功
                        return true;  // 整条路径可行，向上返回成功
                    }  // 递归判定分支结束
                }  // 棋盘范围判定结束
            }  // 四方向枚举结束
            return false;  // 四个方向都走不通，说明被困住
        };  // DFS lambda 结束
        return dfs(sx, sy, tx, ty, vis1) && dfs(tx, ty, sx, sy, vis2);  // 起点能到达终点，且终点也能反向逃出包围圈，两者同时成立才算 escaped
    }  // 方法结束
};  // 类结束