// 题目：1344. 时钟指针的夹角（Angle Between Hands of a Clock）
// 思路：分别算出时针、分针相对 12 点方向的角度，作差取绝对值，再与 360 度减去该差值取较小者。
// 时间复杂度：O(1)，只有常数次算术运算；空间复杂度：O(1)，仅用常数个 double 变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double angleClock(int hour, int minutes) {  // hour：小时数（1~12）；minutes：分钟数（0~59）
        double h = 30 * hour + 0.5 * minutes;  // 时针角度：每小时 30 度，另外每分钟再走 0.5 度
        double m = 6 * minutes;  // 分针角度：每分钟 6 度
        double diff = abs(h - m);  // 两针角度的绝对差，可能大于 180 度
        return min(diff, 360 - diff);  // 一圈 360 度，夹角取劣角，即 diff 与 360-diff 中较小的那个
    }  // 方法结束
};  // 类定义结束（源文件末尾无换行，逐字节保持不变）