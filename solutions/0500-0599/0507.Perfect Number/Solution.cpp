// 题目：507. 完美数（Perfect Number）
// 思路：1 一定是真因子先累加；从 2 枚举到 sqrt(num)，遇到因子就成对累加 i 与 num/i，最后判断因子和是否等于自身。
// 时间复杂度：O(sqrt(num))；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool checkPerfectNumber(int num) {  // num：待判断的正整数
        if (num == 1) {  // 1 的真因子为空集，和为 0，肯定不是完美数
            return false;  // 直接返回 false
        }  // 分支结束
        int s = 1;  // 1 一定是真因子，先累加进来；s 用于累计真因子之和
        for (int i = 2; i <= num / i; ++i) {  // 只枚举到 sqrt(num)，写 num/i 可避免 i*i 溢出
            if (num % i == 0) {  // i 是 num 的因子
                s += i;  // 累加较小的因子 i
                if (i != num / i) {  // 两个配对因子不相等时，才需要累加较大的那个
                    s += num / i;  // 累加与 i 配对的因子 num/i
                }  // 配对因子处理结束
            }  // 因子判断结束
        }  // 枚举结束，s 就是所有真因子之和
        return s == num;  // 真因子之和等于自身即为完美数
    }  // 方法结束
};  // 类定义结束
