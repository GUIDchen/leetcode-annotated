// 题目：2521. 数组乘积中的不同质因数数目（Distinct Prime Factors of Product of Array）
// 核心思路：乘积的质因数集合等于各元素质因数集合的并集，所以逐个元素试除分解质因数，把质因子放进哈希集合去重，集合大小即答案。
// 时间复杂度：O(n * √m)，m 为元素最大值；空间复杂度：O(p)，p 为不同质因数的个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解接口对外可见
    int distinctPrimeFactors(vector<int>& nums) {  // nums：输入数组；返回所有元素乘积中不同质因数的个数
        unordered_set<int> s;  // 哈希集合存放出现过的质因数，天然去重
        for (int& n : nums) {  // 逐个元素分解质因数（按引用遍历，下面会直接修改 n）
            for (int i = 2; i <= n / i; ++i) {  // 只需试除到 √n，用 i <= n / i 可避免 i * i 溢出
                if (n % i == 0) {  // i 能整除 n，说明 i 是质因子
                    s.insert(i);  // 把它加入集合，重复出现也只记一次
                    while (n % i == 0) {  // 把 n 中所有因子 i 除干净，避免同一质因子重复统计
                        n /= i;  // 继续除，直到 i 不再是因子
                    }  // 结束内层 while
                }  // 结束 if
            }  // 结束 for
            if (n > 1) {  // 剩下的 n > 1，说明它本身就是最后一个质因数
                s.insert(n);  // 把它也加入集合
            }  // 结束 if
        }  // 结束外层 for
        return s.size();  // 集合大小就是不同质因数的个数
    }  // 结束 distinctPrimeFactors
};  // 结束 Solution 类