// 题目：2849. 判断能否在给定时间到达单元格（Determine if a Cell Is Reachable at a Given Time）
// 核心思路：每步可横、竖或斜走一格，最少步数是横纵坐标差的较大者（切比雪夫距离）；只有起点等于终点且 t == 1 时需要特判。
// 时间复杂度：O(1)；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 对外公开的接口区域
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {  // 参数依次是起点行、列，终点行、列，以及限定时间 t
        if (sx == fx && sy == fy) {  // 起点与终点重合，是唯一违背「最少步数 = 距离」直觉的特殊情况
            return t != 1;  // 1 秒内无法离开原点再走回来，故 t == 1 不可达；t 为 0 或大于 1 都可达
        }  // 结束重合分支
        int dx = abs(fx - sx), dy = abs(fy - sy);  // dx、dy 分别是行列方向需要跨越的距离绝对值
        return max(dx, dy) <= t;  // 允许斜走，所以最少步数取两个差值的较大者；不超过 t 就能在限时内到达
    }  // 结束方法
};  // 结束类定义