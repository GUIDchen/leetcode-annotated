// 题目：991. 坏了的计算器（Broken Calculator）
// 思路：反向从 target 退回 startValue：奇数只能 +1、偶数可以 /2；退到不大于起点后，差距全部用 -1 补。
// 时间复杂度：O(log target)，每轮要么减半要么变成偶数；空间复杂度：O(1)，只用几个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int brokenCalc(int startValue, int target) {  // startValue：起始值；target：目标值；返回最少操作次数
        int ans = 0;  // ans 统计已经做过的操作次数
        while (startValue < target) {  // 反向思考：从 target 往 startValue 退，直到 target 不大于 startValue
            if (target & 1) {  // 奇数不可能由乘以 2 得到，只能由「减 1」产生，反向就是 +1
                target++;  // 先把奇数加 1 变成偶数
            } else {  // 否则 target 是偶数，反向可以用除以 2
                target >>= 1;  // 右移一位等价于除以 2，且比除法更快
            }
            ++ans;  // 每做一次反向操作，操作次数加一
        }
        ans += startValue - target;  // 此时 target 已不大于 startValue，剩下的差距只能靠正向「减 1」逐个补
        return ans;  // 返回最少操作次数
    }
};  // 类定义结束