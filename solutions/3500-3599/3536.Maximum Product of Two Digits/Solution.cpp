// 3536. 两个数字的最大乘积 / Maximum Product of Two Digits
// 核心思路：逐位取出每个数字，维护最大的两个位数字 a、b，最后返回 a * b。
// 复杂度：时间 O(log n)，空间 O(1)。
class Solution {  // 定义题解类
public:  // 公有方法区
    int maxProduct(int n) {  // 返回 n 的各位数字中任取两位的最大乘积
        int a = 0, b = 0;  // a 为最大位数字，b 为次大位数字
        for (; n; n /= 10) {  // 逐位处理，每轮 n 除以 10
            int x = n % 10;  // 取当前最低位数字
            if (a < x) {  // 比当前最大值还大
                b = a;  // 原最大值降为次大值
                a = x;  // 更新最大值
            } else if (b < x) {  // 否则比次大值大
                b = x;  // 更新次大值
            }  // if 语句结束
        }  // 循环结束
        return a * b;  // 最大的两个位数字相乘
    }  // 方法结束
};  // 类定义结束