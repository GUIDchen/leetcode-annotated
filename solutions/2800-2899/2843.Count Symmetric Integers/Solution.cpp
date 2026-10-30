// 题目：2843. 统计对称整数的数目（Count Symmetric Integers）
// 思路：对区间内每个整数转成十进制字符串，位数为偶数时比较前后两半的数字和是否相等，相等就计入答案。
// 时间复杂度：O((high - low) * log high)，每个数最多 O(log high) 位；空间复杂度：O(log high)，用于存放字符串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSymmetricIntegers(int low, int high) {  // low / high：闭区间上下界，统计其中对称整数的个数
        int ans = 0;  // 计数器：满足「前半数字和 == 后半数字和」的整数个数
        auto f = [](int x) {  // 局部 lambda：判断单个整数 x 是否对称，返回 0 或 1
            string s = to_string(x);  // 转成十进制字符串，方便按下标逐位取数
            int n = s.size();  // 数位个数
            if (n & 1) {  // 位数为奇数时无法平均分成两半，必然不对称
                return 0;  // 直接判为不对称
            }
            int a = 0, b = 0;  // a 累加前半段数字和，b 累加后半段数字和
            for (int i = 0; i < n / 2; ++i) {  // 只遍历一半长度，i 同时可以索引到前后两段
                a += s[i] - '0';  // 字符减 '0' 得到数值，累加到前半段和
                b += s[n / 2 + i] - '0';  // 累加后半段中与 i 对应的那一位
            }
            return a == b ? 1 : 0;  // 两半数字和相等即对称，返回 1，否则返回 0
        };
        for (int x = low; x <= high; ++x) {  // 枚举 [low, high] 内的每个整数
            ans += f(x);  // 对称就 +1，不对称 +0
        }
        return ans;  // 返回区间内对称整数的总个数
    }
};