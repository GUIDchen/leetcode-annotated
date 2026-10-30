// 题目：2806. 取整购买后的账户余额（Account Balance After Rounded Purchase）
// 思路：把 0~100 间所有 10 的倍数逐个与 purchaseAmount 比较，取差值最小且数值最大（并列时向上取整）的那个。
// 时间复杂度：O(1)，最多循环 11 次；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int accountBalanceAfterPurchase(int purchaseAmount) {  // purchaseAmount：购买金额，返回支付后的账户余额
        int diff = 100, x = 0;  // diff：当前最小差值（初值取最大可能值 100）；x：对应的取整金额
        for (int y = 100; y >= 0; y -= 10) {  // 从 100 递减到 0 枚举所有 10 的倍数，降序保证并列时保留更大的 y
            int t = abs(y - purchaseAmount);  // t：取整金额 y 与实际金额之间的差值
            if (t < diff) {  // 严格小于才更新，因此差值相等时保留先遇到的较大 y
                diff = t;  // 更新最小差值
                x = y;  // 记录当前最优的取整金额
            }
        }
        return 100 - x;  // 从 100 中扣除取整后的金额，得到余额
    }
};