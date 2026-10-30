// 题目：407. 接雨水 II（Trapping Rain Water II）
// 思路：用小根堆维护「木桶边界」，每次取已知水面最低的边界格向内扩展，逐格结算存水。
// 时间复杂度：O(mn log(mn))，每格入堆出堆各一次；空间复杂度：O(mn)，访问标记加堆的规模。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int trapRainWater(vector<vector<int>>& heightMap) {  // heightMap 是每格柱子的高度，返回能接住的雨水总量
        using tii = tuple<int, int, int>;  // 给三元组起别名：元素依次是（该格水面高度，行号，列号）
        priority_queue<tii, vector<tii>, greater<tii>> pq;  // 小根堆：每次先弹出当前已知水面最低的边界格子
        int m = heightMap.size(), n = heightMap[0].size();  // 矩阵的行数 m 与列数 n
        bool vis[m][n];  // 标记某格是否已进入过木桶边界，防止重复入堆
        memset(vis, 0, sizeof vis);  // 全部初始化为未访问
        for (int i = 0; i < m; ++i) {  // 先遍历所有行
            for (int j = 0; j < n; ++j) {  // 再遍历所有列
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {  // 只有最外圈格子能作为初始边界（水只可能从边界流出）
                    pq.emplace(heightMap[i][j], i, j);  // 外圈格子的水面高度先等于它自身高度
                    vis[i][j] = true;  // 标记外圈已访问，避免之后重复处理
                }  // 内层 if 结束
            }  // 列循环结束
        }  // 行循环结束
        int ans = 0;  // 累计接住的雨水体积
        int dirs[5] = {-1, 0, 1, 0, -1};  // 四邻域方向数组，成对取用即上、右、下、左
        while (!pq.empty()) {  // 从边界逐层向内扩展，堆空说明整个矩阵处理完毕
            auto [h, i, j] = pq.top();  // 取出水面最低的边界格（结构化绑定拆出三个分量）
            pq.pop();  // 弹出这个已处理的格子
            for (int k = 0; k < 4; ++k) {  // 枚举它的四个相邻格子
                int x = i + dirs[k], y = j + dirs[k + 1];  // 相邻格坐标：行加 dirs[k]，列加 dirs[k + 1]
                if (x >= 0 && x < m && y >= 0 && y < n && !vis[x][y]) {  // 坐标合法且尚未访问才处理
                    ans += max(0, h - heightMap[x][y]);  // 邻格比当前水面低时差值是能存的水；否则不存水
                    vis[x][y] = true;  // 标记邻格已访问
                    pq.emplace(max(heightMap[x][y], h), x, y);  // 邻格新水面高度取自身高度与 h 的较大者，入堆继续向外扩展
                }  // 内层 if 结束
            }  // 方向循环结束
        }  // while 结束
        return ans;  // 返回接住的雨水总量
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，此处保持一致）