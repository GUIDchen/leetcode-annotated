// 题目：2739. 总行驶距离（Total Distance Traveled）
// 思路：每消耗 1 升油行驶 10 公里，累计每消耗满 5 升就从备用油里补 1 升回主油箱；用 while 模拟直到主油箱为空。
// 时间复杂度：O(mainTank + additionalTank)，每轮消耗 1 升油；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int distanceTraveled(int mainTank, int additionalTank) {  // mainTank：主油箱现有升数；additionalTank：备用油还能补充的升数
        int ans = 0, cur = 0;  // ans 累计行驶距离（公里）；cur 记录已经消耗的总升数，用于判断是否满 5 升
        while (mainTank > 0) {  // 主油箱还有油就继续行驶
            cur++;  // 又消耗了 1 升油
            ans += 10;  // 每消耗 1 升可以行驶 10 公里
            mainTank--;  // 主油箱减少 1 升
            if (cur % 5 == 0 && additionalTank > 0) {  // 每消耗满 5 升并且备用油还没用完，就补充 1 升
                additionalTank--;  // 备用油减少 1 升
                mainTank++;  // 把补来的 1 升加回主油箱，让循环可以继续
            }  // if 分支体结束
        }  // while 循环体结束
        return ans;  // 主油箱彻底耗尽，返回累计行驶距离
    }  // 方法体结束
};  // 类定义结束