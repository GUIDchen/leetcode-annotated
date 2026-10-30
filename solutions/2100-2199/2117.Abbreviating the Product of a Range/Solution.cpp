// 题目：2117. 一个区间内所有数乘积的缩写（Abbreviating the Product of a Range）
// 思路：乘积写成 m * 10^c，c 由因子 2 与 5 的较小个数决定；后缀取模保留低位，前缀用 long double 只留约 5 位有效数字。
// 时间复杂度：O((right-left+1) * log right)，每个数剥离因子开销很小；空间复杂度：O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string abbreviateProduct(int left, int right) {  // left..right 闭区间；返回缩写后的乘积字符串
        int cnt2 = 0, cnt5 = 0;  // 分别统计乘积中因子 2 与因子 5 的总个数
        for (int i = left; i <= right; ++i) {  // 第一遍：扫描区间内的每个数
            int x = i;  // 复制一份 i，避免破坏循环变量
            for (; x % 2 == 0; x /= 2) {  // 反复除以 2，统计因子 2
                ++cnt2;  // 因子 2 计数加一
            }  // 因子 2 统计结束
            for (; x % 5 == 0; x /= 5) {  // 反复除以 5，统计因子 5
                ++cnt5;  // 因子 5 计数加一
            }  // 因子 5 统计结束
        }  // 第一遍扫描结束
        int c = min(cnt2, cnt5);  // 每个 2 和 5 配成一个 10，较小的个数就是末尾 0 的个数 c
        cnt2 = cnt5 = c;  // 只保留用于配对的配额，多余的 2 或 5 会留在 suf 里
        long long suf = 1;  // 后缀：用取模维持低位
        long double pre = 1;  // 前缀：用高精度浮点只保留高位有效数字
        bool gt = false;  // 标记乘积是否超过 10 位（需要缩写）
        for (int i = left; i <= right; ++i) {  // 第二遍：累乘，并同步剥离 10 的因子
            for (suf *= i; cnt2 && suf % 2 == 0; suf /= 2) {  // 先乘上 i，再按配额从 suf 中剥离因子 2
                --cnt2;  // 用掉一个 2 的配额
            }  // 因子 2 剥离结束
            for (; cnt5 && suf % 5 == 0; suf /= 5) {  // 按配额从 suf 中剥离因子 5
                --cnt5;  // 用掉一个 5 的配额
            }  // 因子 5 剥离结束
            if (suf >= 1e10) {  // 后缀超过 10 位
                gt = true;  // 标记需要缩写
                suf %= (long long) 1e10;  // 只保留末尾 10 位，防止整数溢出
            }  // 后缀截断完成
            for (pre *= i; pre > 1e5; pre /= 10) {  // 前缀乘上 i 后不断降量级，保持 5 位左右有效数字
            }  // 这里是空循环体：归一化前缀全靠循环头部的 pre /= 10
        }  // 第二遍累乘结束
        if (gt) {  // 乘积过长，需要输出「前 5 位...后 5 位e指数」
            char buf[10];  // 存放后 5 位字符串的缓冲，5 位 + 结束符足够
            snprintf(buf, sizeof(buf), "%0*lld", 5, suf % (int) 1e5);  // 取末 5 位，用 %0*lld 左补 0 到 5 位宽
            return to_string((int) pre) + "..." + string(buf) + "e" + to_string(c);  // 拼成「前缀...后缀e指数」
        }  // 否则走下面的短乘积分支
        return to_string(suf) + "e" + to_string(c);  // 乘积不长，直接输出完整后缀与指数
    }  // abbreviateProduct 方法结束
};  // Solution 类定义结束