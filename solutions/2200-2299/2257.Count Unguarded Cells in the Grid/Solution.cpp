// 题目：2257. 统计网格图中没有被保卫的格子数（Count Unguarded Cells in the Grid）
// 思路：用一张二维标记表（2 表示守卫或墙、1 表示已被保卫、0 表示未保卫），从每个守卫向四个方向直线推进，遇到墙或守卫即停。
// 时间复杂度：O(m * n + g * (m + n))，每个守卫最多沿四个方向各扫一遍；空间复杂度：O(m * n)，标记表与网格同规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {  // m 行 n 列，guards 是守卫坐标、walls 是墙坐标
        int g[m][n];  // 二维标记表：0 未保卫，1 被保卫，2 守卫或墙（变长数组是编译器扩展，判题环境支持）
        memset(g, 0, sizeof(g));  // 全部清零，先把每个格子都当成「未保卫」
        for (auto& e : guards) {  // 遍历所有守卫坐标
            g[e[0]][e[1]] = 2;  // 守卫所在格子标 2：它阻挡视线，也不计入答案
        }
        for (auto& e : walls) {  // 遍历所有墙坐标
            g[e[0]][e[1]] = 2;  // 墙和守卫在「挡视线」上作用相同，统一标成 2
        }
        int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：相邻两项组成 (上、右、下、左) 的行列增量
        for (auto& e : guards) {  // 以每个守卫为扫描起点
            for (int k = 0; k < 4; ++k) {  // 依次处理四个方向
                int x = e[0], y = e[1];  // 当前位置从守卫自身出发
                int a = dirs[k], b = dirs[k + 1];  // 取出当前方向的行、列增量
                while (x + a >= 0 && x + a < m && y + b >= 0 && y + b < n && g[x + a][y + b] < 2) {  // 下一格在界内且不是守卫/墙，就继续朝这个方向推进
                    x += a;  // 行坐标移到下一格
                    y += b;  // 列坐标移到下一格
                    g[x][y] = 1;  // 该格被这个守卫看到，标记为已保卫（重复标记没有副作用）
                }
            }
        }
        int ans = 0;  // 统计结果：整张表中仍为 0 的格子数
        for (auto& row : g) {  // 逐行扫描标记表
            ans += count(row, row + n, 0);  // 数出本行里值为 0 的格子个数并累加
        }
        return ans;  // 返回没有被保卫的格子总数
    }
};