// 3424. 将数组变相同的最小代价 / Minimum Cost to Make Arrays Identical
// 核心思路：方案一直接累加逐位绝对差；方案二先花 k 把 arr 任意重排，排序后与 brr 排序对齐即最优，再累加绝对差；两者取小
// 复杂度：时间 O(n·log n)（两次排序），空间 O(1) 额外空间（原地排序）
class Solution {  // 定义题解类
public:  // 公有方法区
    long long minCost(vector<int>& arr, vector<int>& brr, long long k) {  // 求把 arr 变成 brr 所需的最小代价
        auto calc = [&](vector<int>& arr, vector<int>& brr) {  // 定义辅助 lambda：计算两个数组按位绝对差之和
            long long ans = 0;  // 代价累加器
            for (int i = 0; i < arr.size(); ++i) {  // 遍历每一位下标
                ans += abs(arr[i] - brr[i]);  // 累加这一位的绝对差
            }  // 循环结束
            return ans;  // 返回逐位绝对差之和
        };  // lambda 定义结束
        long long c1 = calc(arr, brr);  // 方案一：不重排，直接对齐求差
        ranges::sort(arr);  // 方案二的第一步：花 k 的代价后，把 arr 排序
        ranges::sort(brr);  // 对应地把 brr 也排序
        long long c2 = calc(arr, brr) + k;  // 排序对齐后的逐位差之和，再加上重排代价 k
        return min(c1, c2);  // 两种方案取较小值返回
    }  // 方法结束
};  // 类定义结束
