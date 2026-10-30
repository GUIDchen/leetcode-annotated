// 题目：2543. 判断一个点是否可以到达（Check if Point Is Reachable）
// 思路：题目允许的操作只会在坐标上叠加/减去彼此、并整体除 2，因此两点坐标的最大公约数中除 2 以外的质因子无法消除；gcd 是 2 的幂即可达。
// 时间复杂度：O(log min(targetX, targetY))，只做一次 gcd；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isReachable(int targetX, int targetY) {  // 判断目标点 (targetX, targetY) 能否从 (1, 1) 变换得到
        int x = gcd(targetX, targetY);  // 求两坐标的最大公约数，所有可达性判断都归结到它上面
        return (x & (x - 1)) == 0;  // x & (x - 1) 会把最低位的 1 清零；结果为 0 说明 x 是 2 的幂，即不含奇质因子，可达
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，保持原样）