// 3765. 完全质数 / Complete Prime Number
// 核心思路：把 num 转成十进制字符串，分别枚举它的所有前缀与所有后缀，逐个做质数判定。
// 复杂度：时间 O(d·√num)（d 为十进制位数），空间 O(d)。
class Solution {  // 定义解法类
public:  // 公有方法区
    bool completePrime(int num) {  // 判断 num 的所有十进制前缀和所有十进制后缀是否都是质数
        auto isPrime = [&](int x) {  // 定义质数判定 lambda
            if (x < 2) {  // 小于 2 的数不是质数
                return false;  // 直接返回 false
            }
            for (int i = 2; i * i <= x; ++i) {  // 只需试除到 sqrt(x)
                if (x % i == 0) {  // 找到因子说明不是质数
                    return false;  // 返回 false
                }
            }
            return true;  // 没有因子，说明是质数
        };

        string s = to_string(num);  // 转成十进制字符串

        int x = 0;  // 前缀的累加值
        for (char c : s) {  // 从左到右遍历每一位
            x = x * 10 + (c - '0');  // 拼出当前前缀数值
            if (!isPrime(x)) {  // 前缀不是质数则整体失败
                return false;  // 返回 false
            }
        }

        x = 0;  // 重置，用于计算后缀
        int p = 1;  // 后缀的位权
        for (int i = (int) s.size() - 1; i >= 0; --i) {  // 从右到左遍历每一位
            x = p * (s[i] - '0') + x;  // 把该位拼到当前后缀的最前面
            p *= 10;  // 位权乘 10
            if (!isPrime(x)) {  // 后缀不是质数则整体失败
                return false;  // 返回 false
            }
        }

        return true;  // 所有前缀和后缀都是质数
    }  // 方法结束
};  // 类结束
