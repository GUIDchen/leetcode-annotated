// 题目：166. 分数到小数（Fraction to Recurring Decimal）
// 核心思路：符号单独处理，整数部分直接整除，小数部分做长除法；用哈希表记录「余数 → 该位小数位置」，余数重复即为循环节起点。
// 时间复杂度：O(k)，k 为不重复余数的个数（不超过分母）；空间复杂度：O(k)，哈希表最多存 k 个余数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string fractionToDecimal(int numerator, int denominator) {  // 把分数 numerator/denominator 转成小数字符串
        if (numerator == 0) {  // 分子为 0 时结果恒为 "0"，不带负号
            return "0";  // 直接返回
        }
        string ans;  // 结果字符串，边算边拼接
        bool neg = (numerator > 0) ^ (denominator > 0);  // 异或判断符号：一正一负结果才是负数
        if (neg) {  // 结果为负
            ans += "-";  // 先写入负号，之后都按正数计算
        }
        long long a = abs(1LL * numerator), b = abs(1LL * denominator);  // 转成 long long 再取绝对值，避免 INT_MIN 取反溢出
        ans += to_string(a / b);  // 整数部分
        a %= b;  // 余数，作为小数部分长除法的起点
        if (a == 0) {  // 余数为 0 说明可以整除，没有小数部分
            return ans;  // 直接返回整数结果
        }
        ans += ".";  // 加上小数点，准备输出小数位
        unordered_map<long long, int> d;  // 余数 → 该位小数在 ans 中的下标，用于定位循环节
        while (a) {  // 余数非 0 就继续长除法
            d[a] = ans.size();  // 记录当前余数对应的输出位置：若它再次出现，循环节就从这里开始
            a *= 10;  // 余数乘 10，得到这一位的被除数
            ans += to_string(a / b);  // 这一位的小数数字
            a %= b;  // 更新余数，进入下一位
            if (d.contains(a)) {  // C++20 的 contains：该余数之前出现过，说明进入循环
                ans.insert(d[a], "(");  // 在循环节起点插入左括号（插入后其后下标会整体右移）
                ans += ")";  // 末尾补上右括号
                break;  // 循环节已标记完毕，结束长除法
            }
        }
        return ans;  // 返回最终的小数字符串
    }
};