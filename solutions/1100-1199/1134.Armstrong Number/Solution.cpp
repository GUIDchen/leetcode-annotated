// 题目：1134. 阿姆斯特朗数（Armstrong Number）
// 思路：先求出 n 的十进制位数 k，再逐位取出数字累加其 k 次方，最后判断该和是否等于 n 本身。
// 时间复杂度：O(log n)，需要遍历 n 的每一位；空间复杂度 O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 接口对外可见
    bool isArmstrong(int n) {  // n：待判断的整数；返回它是否为阿姆斯特朗数
        int k = to_string(n).size();  // k：n 的十进制位数，也是每位要取的幂次
        int s = 0;  // s：各位数字的 k 次方之和
        for (int x = n; x; x /= 10) {  // 逐位取出数字，x 每次除以 10
            s += pow(x % 10, k);  // 累加最低位的 k 次方，pow 返回 double 会自动转成 int
        }  // 逐位循环结束
        return s == n;  // 各位幂次之和等于原数才是阿姆斯特朗数
    }  // 方法结束
};  // 类定义结束