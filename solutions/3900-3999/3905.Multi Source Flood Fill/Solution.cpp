// 3905. 多源图像渲染（Multi Source Flood Fill）
// 思路：把所有源点作为第 0 层队列，逐层向相邻的空白格扩散颜色；同一层多个源点染同一格时取颜色较大者。
// 复杂度：时间复杂度 O(n*m)，每个格子最多被染色一次；空间复杂度 O(n*m)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {  // n,m：网格尺寸；sources：多源染色点 {行,列,颜色}
        vector<vector<int>> ans(n, vector<int>(m, 0));  // 结果网格，0 表示尚未染色
        vector<array<int, 3>> q;  // 当前这一轮待扩散的 {行,列,颜色} 队列
        int dirs[] = {-1, 0, 1, 0, -1};  // 四方向偏移量，相邻两项组成一个方向向量
        for (auto& s : sources) {  // 把所有源点先染上各自的颜色
            ans[s[0]][s[1]] = s[2];  // 源点自身的颜色
            q.push_back({s[0], s[1], s[2]});  // 源点入队，作为第 0 轮扩散起点
        }  // 源点初始化完成
        while (!q.empty()) {  // 逐层扩散，直到没有新格子
            unordered_map<long long, int> vis;  // 本轮每个待染色格子收到的最大颜色
            for (auto& curr : q) {  // 遍历上一轮的所有格子
                int r = curr[0], c = curr[1], color = curr[2];  // 取出当前格子的坐标与颜色
                for (int i = 0; i < 4; i++) {  // 枚举四个相邻方向
                    int x = r + dirs[i], y = c + dirs[i + 1];  // 相邻格子的坐标
                    if (x >= 0 && x < n && y >= 0 && y < m && ans[x][y] == 0) {  // 越界或已经被染色的格子跳过
                        long long key = (long long) x * m + y;  // 二维坐标压成一维键，便于哈希
                        if (color > vis[key]) {  // 同一格子被多个源点覆盖时取较大颜色
                            vis[key] = color;  // 记录本轮该格子的最优颜色
                        }  // 颜色比较结束
                    }  // 合法性判断结束
                }  // 四方向枚举结束
            }  // 本轮所有格子扩散结束
            q.clear();  // 清空队列，准备装入下一轮
            for (auto const& [key, color] : vis) {  // 把本轮确定颜色的格子正式染色
                int x = key / m;  // 一维键还原出行号
                int y = key % m;  // 一维键还原出列号
                ans[x][y] = color;  // 写入最终颜色
                q.push_back({x, y, color});  // 新染色的格子作为下一轮扩散起点
            }  // 本轮染色结束
        }  // 扩散结束
        return ans;  // 返回染色后的网格
    }  // 方法结束
};  // 类定义结束
