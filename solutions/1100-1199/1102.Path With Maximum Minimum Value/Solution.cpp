// 题目：1102. 得分最高的路径（Path With Maximum Minimum Value）
// 思路：把格子按值从大到小逐个「激活」，用并查集合并已激活的相邻格子；左上与右下首次连通时的值就是答案。
// 时间复杂度：O(mn log(mn))，主要是排序；空间复杂度：O(mn)，并查集与访问数组各 O(mn)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumMinimumPath(vector<vector<int>>& grid) {  // grid 是权值矩阵
        int m = grid.size(), n = grid[0].size();  // m 行 n 列
        vector<tuple<int, int, int>> q;  // q 用于按格子值排序，元素是 (值, 行, 列)
        vector<int> p(m * n);  // 并查集父节点，把二维坐标压平成一维
        iota(p.begin(), p.end(), 0);  // iota 初始化：每个格子先各自成一个集合
        for (int i = 0; i < m; ++i) {  // 枚举每一行
            for (int j = 0; j < n; ++j) {  // 枚举每一列
                q.emplace_back(grid[i][j], i, j);  // 把 (值, 行, 列) 放入待排序数组
            }  // for 结束
        }  // for 结束
        function<int(int)> find = [&](int x) {  // 带路径压缩的 find lambda
            return p[x] == x ? x : p[x] = find(p[x]);  // 递归找根并压缩路径
        };  // lambda 定义结束
        sort(q.begin(), q.end(), greater<tuple<int, int, int>>());  // 按值从大到小排序，便于后面「从高到低」加点
        int ans = 0;  // ans 记录当前已加入的最小值
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四方向偏移，dirs[k] 与 dirs[k+1] 两两配对成上下左右
        bool vis[m][n];  // 访问标记数组（长度由运行时变量决定）
        memset(vis, false, sizeof(vis));  // 全部初始化为未访问
        for (auto& [v, i, j] : q) {  // 按值降序，逐个激活格子
            vis[i][j] = true;  // 标记为已访问，等价于把它加入集合
            ans = v;  // 记录当前加入的值，答案就是两端首次连通那一刻的值
            for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 计算相邻格子的坐标
                if (x >= 0 && x < m && y >= 0 && y < n && vis[x][y]) {  // 邻居在界内且已被激活，才可能与当前格子连通
                    p[find(x * n + y)] = find(i * n + j);  // 合并当前格子与邻居所在的集合
                }  // if 结束
            }  // for 结束
            if (find(0) == find(m * n - 1)) {  // 左上角与右下角已经连通，说明找到了一条可行路径
                break;  // 提前结束，此时 ans 就是所有路径「最小值」中的最大者
            }  // if 结束
        }  // for 结束
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束