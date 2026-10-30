// 题目：2249. 统计圆内格点数目（Count Lattice Points Inside a Circle）
// 思路：坐标全部非负，枚举 [0, maxX] × [0, maxY] 内的每个整点，只要落在任一圆内（dx²+dy² ≤ r²）就计数并跳出内层循环，避免重复计数。
// 时间复杂度：O(maxX·maxY·n)，n 为圆的个数；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countLatticePoints(vector<vector<int>>& circles) {  // circles 的每个元素是 [圆心x, 圆心y, 半径r]
        int mx = 0, my = 0;  // mx/my：所有圆在 x/y 方向能覆盖到的最远坐标，即枚举的上界
        for (auto& c : circles) {  // 先扫一遍所有圆，求出枚举的边界
            mx = max(mx, c[0] + c[2]);  // 圆心 x 加半径，就是该圆在 x 方向的最右端
            my = max(my, c[1] + c[2]);  // 圆心 y 加半径，就是该圆在 y 方向的最上端
        }  // 边界统计结束
        int ans = 0;  // ans：被至少一个圆覆盖的格点个数
        for (int i = 0; i <= mx; ++i) {  // 枚举所有可能的横坐标（坐标非负，所以从 0 开始）
            for (int j = 0; j <= my; ++j) {  // 枚举所有可能的纵坐标，与 i 组合成一个候选格点
                for (auto& c : circles) {  // 逐个圆判断当前格点 (i, j) 是否被覆盖
                    int dx = i - c[0], dy = j - c[1];  // 格点相对圆心的横、纵偏移
                    if (dx * dx + dy * dy <= c[2] * c[2]) {  // 距离平方不超过半径平方，说明该点在圆内
                        ++ans;  // 当前格点被覆盖，计数加一
                        break;  // 已被一个圆覆盖就够了，跳出以免同一个格点被重复计数
                    }  // 结束圆内判定
                }  // 结束圆的遍历
            }  // 结束纵坐标枚举
        }  // 结束横坐标枚举
        return ans;  // 返回被覆盖的格点总数
    }  // 结束题解方法
};  // 结束题解类