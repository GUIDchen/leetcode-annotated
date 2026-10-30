// 3622. Check Divisibility by Digit Sum and Product（3622. 判断整除性）
// 核心思路：逐位拆解 n，累加数位和 s、累乘数位积 p，最后判断 n 能否被 (s + p) 整除。
// 复杂度：时间 O(log n)（数的位数），空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有成员，供判题器调用
    bool checkDivisibility(int n) {  // 判断 n 是否能被“数位和 + 数位积”整除
        int s = 0, p = 1;  // s 为数位和，p 为数位积（乘积单位元为 1）
        int x = n;  // 用副本 x 逐位拆解，保留 n 本身
        while (x != 0) {  // 逐位处理直到 x 为 0
            int v = x % 10;  // 取出最低位数字
            x /= 10;  // 去掉最低位
            s += v;  // 累加数位和
            p *= v;  // 累乘数位积
        }
        return n % (s + p) == 0;  // 余数为 0 说明可以整除
    }
};