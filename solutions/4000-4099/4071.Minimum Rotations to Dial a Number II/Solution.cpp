// 4071. 拨号的最少旋转次数 II（Minimum Rotations to Dial a Number II）
// 核心思路：先求相邻数字距离之和 total，再枚举反转后缀的起点 k：k = 0 时整串反转，k >= 1 时去掉被跳过的那条边、改为 pre 直接连到末位数字。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // 题解类
public:  // 对外接口
    int minRotations(int n, string s) {  // 允许至多反转一次某个后缀，返回拨号的最少旋转总次数
        int total = 0;  // 原串中相邻两位数字的圆盘距离之和
        for (int i = 1; i < n; ++i) {  // 累加相邻两位之间的距离
            int diff = abs(s[i] - s[i - 1]);  // 相邻两位字符的编码差
            total += min(diff, 10 - diff);  // 顺时针、逆时针取较小值累加
        }  // 循环结束

        char first = s[0];  // 字符串首位数字
        char last = s[n - 1];  // 字符串末位数字
        int toFirst = min(first - '0', 10 - (first - '0'));  // 指针 0 到首位的距离，作为反转后缀（k >= 1）时的起步代价
        int ans = total + min(last - '0', 10 - (last - '0'));  // k = 0 即反转整个串：0 -> last -> ... -> first，代价为 total 加上 0 到 last 的距离

        for (int i = 1; i < n; ++i) {  // 枚举反转后缀的起点 k = i（1 <= i <= n - 1）
            char pre = s[i - 1];  // 反转前缀的最后一个数字
            char cur = s[i];  // 被反转后缀的首个数字
            int diff = abs(pre - cur);  // pre 与 cur 的编码差
            int edge = min(diff, 10 - diff);  // 反转后 pre 不再连 cur，这条边的代价被省掉
            diff = abs(pre - last);  // pre（反转后紧跟 last）与 last 的编码差
            int toLast = min(diff, 10 - diff);  // 拼接处 pre -> last 需要的旋转次数
            ans = min(ans, total - edge + toFirst + toLast);  // 用“前缀代价 + 拼接代价 + 后缀内部代价”更新最小值
        }  // 循环结束

        return ans;  // 返回所有方案中的最小旋转总次数
    }  // 方法结束
};  // 类定义结束