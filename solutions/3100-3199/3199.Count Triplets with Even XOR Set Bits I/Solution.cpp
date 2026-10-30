// 3199. 用偶数异或设置位计数三元组 I（Count Triplets with Even XOR Set Bits I）
// 核心思路：x^y^z 的 popcount 奇偶性等于三者 popcount 奇偶性的异或；分别统计 a、b、c 中 popcount 为奇/偶的个数，再枚举三种奇偶性的组合做乘法原理求和。
// 复杂度：时间 O(|a|+|b|+|c|)，空间 O(1)

class Solution {  // 定义题解类
public:  // 公开接口
    int tripletCount(vector<int>& a, vector<int>& b, vector<int>& c) {  // 返回满足 x^y^z 的二进制 1 的个数为偶数的三元组数量
        int cnt1[2]{};  // 统计 a 中 popcount 为偶(=0)/奇(=1) 的元素个数
        int cnt2[2]{};  // 统计 b 中 popcount 奇偶性的元素个数
        int cnt3[2]{};  // 统计 c 中 popcount 奇偶性的元素个数
        for (int x : a) {  // 遍历 a
            ++cnt1[__builtin_popcount(x) & 1];  // 按 popcount 的奇偶性累加计数
        }  // 结束遍历 a
        for (int x : b) {  // 遍历 b
            ++cnt2[__builtin_popcount(x) & 1];  // 按 popcount 的奇偶性累加计数
        }  // 结束遍历 b
        for (int x : c) {  // 遍历 c
            ++cnt3[__builtin_popcount(x) & 1];  // 按 popcount 的奇偶性累加计数
        }  // 结束遍历 c
        int ans = 0;  // 满足条件的三元组数量
        for (int i = 0; i < 2; ++i) {  // 枚举 a 中元素 popcount 的奇偶性
            for (int j = 0; j < 2; ++j) {  // 枚举 b 中元素 popcount 的奇偶性
                for (int k = 0; k < 2; ++k) {  // 枚举 c 中元素 popcount 的奇偶性
                    if ((i + j + k) % 2 == 0) {  // 三者奇偶性之和为偶数，等价于异或结果中 1 的个数为偶数
                        ans += cnt1[i] * cnt2[j] * cnt3[k];  // 乘法原理：三类元素任取其一都能组成合法三元组
                    }  // 结束奇偶性判断
                }  // 结束 k 循环
            }  // 结束 j 循环
        }  // 结束 i 循环
        return ans;  // 返回结果
    }  // 方法结束
};  // 类定义结束