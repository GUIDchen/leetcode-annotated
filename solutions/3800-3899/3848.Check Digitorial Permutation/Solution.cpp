// 3848. 阶数数字排列 / Check Digitorial Permutation（中等）
// 核心思路：预处理 0~9 的阶乘，求 n 各位数字阶乘之和，再比较该和与 n 的数字多重集是否相同。
// 复杂度：时间 O(log n)，空间 O(1)。
class Solution {  // 解题类：LeetCode 判题器约定的类名
public:  // 公有接口
    bool isDigitorialPermutation(int n) {  // 判断 n 与它各位数字的阶乘之和是否互为数字排列
        static int f[10];  // 静态缓存 0~9 的阶乘
        static bool initialized = false;  // 标记阶乘表是否已经初始化

        if (!initialized) {  // 首次调用时构建阶乘表
            f[0] = 1;  // 0 的阶乘为 1
            for (int i = 1; i < 10; i++) {  // 递推计算 1! 到 9!
                f[i] = f[i - 1] * i;  // 阶乘递推式
            }  // 阶乘表构建结束
            initialized = true;  // 标记已初始化，后续调用直接复用
        }  // 初始化判断结束

        int x = 0;  // x 累加各位数字的阶乘
        int y = n;  // y 是 n 的副本，用于逐位拆解

        while (y > 0) {  // 逐位取出 n 的十进制数字
            x += f[y % 10];  // 加上当前最低位的阶乘
            y /= 10;  // 去掉最低位
        }  // 拆位结束

        string a = to_string(x);  // 阶乘和转成字符串
        string b = to_string(n);  // 原数转成字符串

        sort(a.begin(), a.end());  // 对阶乘和的数字排序
        sort(b.begin(), b.end());  // 对原数的数字排序

        return a == b;  // 排序后相同即互为数字排列
    }  // isDigitorialPermutation 方法结束
};  // 解题类定义结束
