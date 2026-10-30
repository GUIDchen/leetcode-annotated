// 题目：780. 到达终点（Reaching Points）
// 思路：正向变换 (x,y)→(x+y,y)/(x,x+y) 会指数爆炸，于是从终点反向回退：每步让较大的坐标减去较小的坐标（连续减多次用一次取模代替），退到不能再退时检查能否正好落在起点上。
// 时间复杂度：O(log max(tx,ty))，取模相当于欧几里得算法；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool reachingPoints(int sx, int sy, int tx, int ty) {  // sx、sy：起点坐标；tx、ty：终点坐标；返回能否从起点走到终点
        while (tx > sx && ty > sy && tx != ty) {  // 反向回退：两个坐标都严格大于起点且互不相等时才继续（相等时相减会得到 0，无法回退）
            if (tx > ty)  // tx 更大，说明最后一步只能是 (tx-ty, ty) 加上 ty 得到的
                tx %= ty;  // 连续减多次 ty 等价于对 ty 取模，一步退到小于 ty 的位置
            else  // 否则 ty 更大，最后一步来自 (tx, ty-tx)
                ty %= tx;  // 同理连续减多次 tx，用取模一步到位
        }
        if (tx == sx && ty == sy) return true;  // 恰好退成起点，说明可达
        if (tx == sx) return ty > sy && (ty - sy) % tx == 0;  // 横坐标已相等：之后只能让纵坐标每次加 tx=SX，故差值必须是 SX 的正整数倍
        if (ty == sy) return tx > sx && (tx - sx) % ty == 0;  // 纵坐标已相等：之后只能让横坐标每次加 ty=SY，故差值必须是 SY 的正整数倍
        return false;  // 其余情况都无法退到起点，不可达
    }  // reachingPoints 方法结束
};  // Solution 类定义结束