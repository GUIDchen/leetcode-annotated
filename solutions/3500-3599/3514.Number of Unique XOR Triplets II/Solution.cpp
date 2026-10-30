// 题目：3514. 不同 XOR 三元组的数目 II（Number of Unique XOR Triplets II）
// 思路：先双重循环得到所有二元异或值，再与第三个数异或得到三元异或值，最后统计可达个数；值域上界取最大值左移一位。
// 时间复杂度：O(n^2 + nV)，V 为值域上界；空间复杂度：O(V)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int uniqueXorTriplets(vector<int>& nums) {  // nums：输入的整数数组
        int mx = ranges::max(nums) << 1;  // mx：异或结果的上界，最大值左移一位即可覆盖所有 a^b^c 的取值

        vector<bool> st(mx, false);  // st[x] 标记二元异或值 x 是否可以由某两个数得到
        for (int a : nums) {  // 枚举第一个数 a
            for (int b : nums) {  // 枚举第二个数 b
                st[a ^ b] = true;  // 标记二元异或值 a^b 可达
            }  // 内层枚举结束
        }  // 外层枚举结束

        vector<int> s(mx, 0);  // s[x] 记录三元异或值 x 是否可达
        for (int ab = 0; ab < mx; ab++) {  // 遍历所有可能的二元异或值
            if (st[ab]) {  // 该二元异或值可达时才继续枚举第三个数
                for (int c : nums) {  // 枚举第三个数 c
                    s[ab ^ c] = 1;  // 标记三元异或值 ab^c 可达
                }  // 第三层枚举结束
            }  // 可达性判断结束
        }  // 二元异或值遍历结束

        return accumulate(s.begin(), s.end(), 0);  // 累加 s 得到可达的三元异或值总个数
    }  // 方法结束
};  // 类结束