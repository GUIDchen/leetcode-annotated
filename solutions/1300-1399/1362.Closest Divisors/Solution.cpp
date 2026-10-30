// 题目：1362. 最接近的因数（Closest Divisors）
// 思路：答案一定来自 num+1 或 num+2；从平方根向下找第一个因子，此时这对因数最接近，两候选再比差值取更小者。
// 时间复杂度：O(√num)，两次枚举到平方根；空间复杂度：O(1)，不计返回的两个数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> closestDivisors(int num) {  // num：题目给定的正整数
        auto f = [](int x) {  // 辅助 lambda：求 x 的一对最接近的因数
            for (int i = sqrt(x);; --i) {  // 从 √x 向下枚举，越接近平方根的两个因数差值越小
                if (x % i == 0) {  // 找到 x 的一个因子 i
                    return vector<int>{i, x / i};  // 立即返回这对因数：i 与配对的 x/i
                }  // if 结束
            }  // for 结束（i=1 时必定整除，所以无需写循环上界）
        };  // lambda 定义结束
        vector<int> a = f(num + 1);  // 候选一：num+1 的最接近因数对
        vector<int> b = f(num + 2);  // 候选二：num+2 的最接近因数对
        return abs(a[0] - a[1]) < abs(b[0] - b[1]) ? a : b;  // 比较两对因数的差值，返回更接近的那一对
    }  // 方法结束
};  // 类定义结束