// 题目：2847. 给定数字乘积的最小数字（Smallest Number With Given Digit Product）
// 思路：从大到小用 9..2 贪心分解 n，尽量用大因子使数位最少；再把因子按升序拼接，得到数值最小的答案。
// 时间复杂度：O(9 * log n)，因子分解近似对数级；空间复杂度：O(1)，只用到长度 10 的计数数组与结果串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string smallestNumber(long long n) {  // n：给定的数位乘积（用 long long 防止溢出）
        int cnt[10]{};  // cnt[d] 记录因子 d 用了多少次，下标 0..9
        for (int i = 9; i > 1; --i) {  // 从 9 递减到 2，优先用大因子
            while (n % i == 0) {  // 只要 n 还能被 i 整除就继续拆
                n /= i;  // 把因子 i 从 n 中除掉
                ++cnt[i];  // 因子 i 的使用次数加一
            }
        }
        if (n > 1) {  // 除剩下的 n 大于 1，说明含大于等于 11 的质因子，无法由单个数字拼出
            return "-1";  // 无解，按题目要求返回 "-1"
        }
        string ans;  // 拼接出的答案串
        for (int i = 2; i < 10; ++i) {  // 从小到大排列因子，使数值最小
            ans += string(cnt[i], '0' + i);  // 把 cnt[i] 个数字 i 追加到答案末尾
        }
        return ans == "" ? "1" : ans;  // 空串表示 n 的初始作用等价于 1，此时答案为 1
    }
};