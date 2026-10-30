// 题目：3215. 用偶数异或设置位计数三元组 II（Count Triplets with Even XOR Set Bits II）
// 思路：三个数异或后的设置位个数奇偶性等于三者设置位个数奇偶性之和的奇偶性，因此只按奇偶统计各数组元素个数，再枚举 2×2×2 种奇偶组合相乘累加。
// 时间复杂度：O(|a| + |b| + |c|)，只需线性扫一遍；空间复杂度：O(1)，仅两个计数的常量数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long tripletCount(vector<int>& a, vector<int>& b, vector<int>& c) {  // a、b、c：三个整数数组
        int cnt1[2]{};  // cnt1[0] / cnt1[1]：a 中设置位个数为偶数 / 奇数的元素个数
        int cnt2[2]{};  // cnt2[0] / cnt2[1]：b 中设置位个数为偶数 / 奇数的元素个数
        int cnt3[2]{};  // cnt3[0] / cnt3[1]：c 中设置位个数为偶数 / 奇数的元素个数
        for (int x : a) {  // 统计 a 中元素的奇偶性分布
            ++cnt1[__builtin_popcount(x) & 1];  // 设置位个数的最低位即奇偶性，直接作为下标计数
        }
        for (int x : b) {  // 统计 b 中元素的奇偶性分布
            ++cnt2[__builtin_popcount(x) & 1];  // 设置位个数的最低位即奇偶性，直接作为下标计数
        }
        for (int x : c) {  // 统计 c 中元素的奇偶性分布
            ++cnt3[__builtin_popcount(x) & 1];  // 设置位个数的最低位即奇偶性，直接作为下标计数
        }
        long long ans = 0;  // 三元组数量最多可达 10^15 级别，用 long long 存储
        for (int i = 0; i < 2; ++i) {  // 枚举 a 中元素设置位个数的奇偶性
            for (int j = 0; j < 2; ++j) {  // 枚举 b 中元素设置位个数的奇偶性
                for (int k = 0; k < 2; ++k) {  // 枚举 c 中元素设置位个数的奇偶性
                    if ((i + j + k) % 2 == 0) {  // 异或后设置位个数为偶数，等价于三者奇偶性之和为偶数
                        ans += 1LL * cnt1[i] * cnt2[j] * cnt3[k];  // 该奇偶组合下三数组元素的所有搭配都满足条件
                    }
                }
            }
        }
        return ans;  // 返回满足条件的三元组总数
    }
};