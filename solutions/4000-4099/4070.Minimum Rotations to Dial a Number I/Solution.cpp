// 4070. 拨号的最少旋转次数 I（Minimum Rotations to Dial a Number I）
// 核心思路：指针从 0 出发按顺序拨号，每一步取圆盘上顺时针与逆时针旋转次数的较小值累加。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // 题解类
public:  // 对外接口
    int minRotations(string s) {  // 按顺序拨出字符串 s 的每一位数字，返回最少旋转总次数
        int ans = 0;  // 累计的最少旋转次数
        int pre = 0;  // 指针当前指着的数字，初始指向 0
        for (int i = 0; i < s.size(); ++i) {  // 逐位拨出字符串中的每个数字
            int cur = s[i] - '0';  // 当前要拨到的数字（字符转整数）
            int diff = abs(cur - pre);  // 两个数字在圆盘上的直线距离
            ans += min(diff, 10 - diff);  // 顺时针、逆时针两个方向取较小值累加
            pre = cur;  // 指针移到当前数字，作为下一次拨号的起点
        }  // 循环结束
        return ans;  // 返回拨完全部数字的最少旋转次数
    }  // 方法结束
};  // 类定义结束