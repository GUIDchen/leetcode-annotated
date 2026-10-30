// 题目：554. 砖墙（Brick Wall）
// 核心思路：统计每一行的内部砖缝坐标，被最多行共享的那条竖直缝隙穿过的砖最少。
// 时间复杂度：O(m*n)，m 为行数、n 为每行砖数；空间复杂度：O(砖缝总数)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int leastBricks(vector<vector<int>>& wall) {  // wall：二维数组，wall[i] 是第 i 行各块砖的宽度
        unordered_map<long long, int> cnt;  // 哈希表：键为砖缝的水平坐标，值为该砖缝在多少行中出现
        for (const auto& row : wall) {  // 逐行统计每一行内部的砖缝位置
            long long s = 0;  // 当前行已累加的宽度，也就是下一道砖缝的坐标
            for (int i = 0; i + 1 < row.size(); ++i) {  // 跳过每行最后一块砖，因为墙的右边界不算可穿透的缝隙
                s += row[i];  // 累加当前砖宽，得到这块砖右边缘（即一道砖缝）的坐标
                cnt[s]++;  // 该坐标的砖缝计数加一
            }  // 本行遍历结束
        }  // 所有行统计完成
        int mx = 0;  // 记录同一坐标砖缝出现的最大行数
        for (const auto& [_, x] : cnt) {  // 结构化绑定遍历哈希表，键用 _ 占位，x 是该砖缝的行数
            mx = max(mx, x);  // 更新最大值
        }  // 遍历结束
        return wall.size() - mx;  // 总行数减去被穿过的最大行数，就是必须穿过的砖块数
    }  // 方法结束
};  // 类定义结束
