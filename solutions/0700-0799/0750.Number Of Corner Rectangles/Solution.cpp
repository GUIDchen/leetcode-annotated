// 题目：750. 角矩形的数量（Number Of Corner Rectangles）
// 核心思路：枚举行内每一对列 (i, j)，用 map 记录这两列此前有多少行同时为 1；新的一行两格都为 1 时，能与之前每一行各配成一个角矩形。
// 时间复杂度：O(m · n^2 · log n)，每行两重循环加 map 操作；空间复杂度：O(n^2)，最多保存 n(n-1)/2 个列对的计数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countCornerRectangles(vector<vector<int>>& grid) {  // grid 是 0/1 矩阵，1 表示该位置有一个顶点
        int n = grid[0].size();  // 列数，决定枚举列对的边界
        int ans = 0;  // 角矩形计数
        map<pair<int, int>, int> cnt;  // 键是有序列对 (i, j)，值是此前两列同时为 1 的行数
        for (auto& row : grid) {  // 逐行扫描
            for (int i = 0; i < n; ++i) {  // 枚举左侧列 i
                if (row[i]) {  // 该行第 i 列必须是点，否则构不成矩形的左竖边
                    for (int j = i + 1; j < n; ++j) {  // 枚举右侧列 j，只往右找避免同一列对被重复统计
                        if (row[j]) {  // 第 j 列也是点，这一行才能作为矩形的水平边
                            ans += cnt[{i, j}];  // 与之前每一个两列同为 1 的行配对，各自围成一个角矩形
                            ++cnt[{i, j}];  // 本行也加入该列对的记录，供后续行配对
                        }  // 结束第 j 列判断
                    }  // 结束右侧列枚举
                }  // 结束第 i 列判断
            }  // 结束左侧列枚举
        }  // 结束行遍历
        return ans;  // 返回角矩形总数
    }  // 结束 countCornerRectangles 方法
};  // 结束 Solution 类