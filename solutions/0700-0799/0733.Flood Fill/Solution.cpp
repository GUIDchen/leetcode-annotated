// 题目：733. 图像渲染（Flood Fill）
// 思路：从 (sr, sc) 出发做深度优先搜索，把与起始像素同色且四连通的格子全部改成 color；起始色与目标色相同直接返回，避免死循环。
// 时间复杂度：O(m·n)，每个格子最多访问一次；空间复杂度：O(m·n)，递归栈最坏深度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {  // image 是像素矩阵，sr、sc 是起点行列，color 是目标颜色
        int m = image.size(), n = image[0].size();  // m、n 分别是矩阵的行数与列数
        int oc = image[sr][sc];  // 记下起点原来的颜色，搜索时用它判断是否属于同一连通块
        if (oc == color) {  // 起始颜色与目标颜色相同时，再染色会无限递归，直接返回原图
            return image;  // 无需改动，直接返回
        }  // if 结束
        const int dirs[5] = {-1, 0, 1, 0, -1};  // 方向数组：连续两两组成上、右、下、左四个方向
        auto dfs = [&](this auto&& dfs, int i, int j) -> void {  // C++23 的推导 this 写法：让 lambda 能在内部调用自身
            image[i][j] = color;  // 进入格子先染成目标颜色，代替额外的 visited 标记
            for (int k = 0; k < 4; ++k) {  // 枚举四个相邻方向
                int x = i + dirs[k], y = j + dirs[k + 1];  // 按方向数组取出邻居坐标（dirs[k] 是行偏移，dirs[k+1] 是列偏移）
                if (x >= 0 && x < m && y >= 0 && y < n && image[x][y] == oc) {  // 邻居在边界内，且仍是原来的颜色，才继续扩散
                    dfs(x, y);  // 递归处理该邻居
                }  // if 结束
            }  // for 循环结束
        };  // lambda 定义结束
        dfs(sr, sc);  // 从起点开始搜索染色
        return image;  // 返回染色后的图像
    }  // floodFill 方法结束
};  // Solution 类定义结束
