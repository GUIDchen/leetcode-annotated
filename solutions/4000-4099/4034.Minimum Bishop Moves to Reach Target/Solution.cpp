// 题目：4034. 象到达目标格子的最少移动步数 / Minimum Bishop Moves to Reach Target
// 核心思路：象每一步都保持所在格子的颜色不变，先用行列和的奇偶判断可达性，再看两点是否共对角线决定用 1 步还是 2 步
// 复杂度：时间复杂度 O(1)，空间复杂度 O(1)
class Solution {  // 定义 LeetCode 题解类
public:  // 公有接口
    int minBishopMoves(vector<int>& source, vector<int>& target) {  // 返回象从 source 到 target 的最少移动步数
        int sr = source[0], sc = source[1];  // 取起点行号 sr 与列号 sc
        int tr = target[0], tc = target[1];  // 取终点行号 tr 与列号 tc
        if ((sr + sc) % 2 != (tr + tc) % 2) {  // 每步移动都保持行列和奇偶性不变，奇偶不同则永远无法到达
            return -1;  // 不可达时返回 -1
        }  // 结束可达性判断
        if (abs(sr - tr) == abs(sc - tc)) {  // 两个方向的行列距离相等说明两点在同一条对角线上
            return 1;  // 一次移动即可到达
        }  // 结束一步可达判断
        return 2;  // 其余可达情况至多两步：先走到两条对角线交点再拐一次
    }  // 结束方法
};  // 结束类定义
