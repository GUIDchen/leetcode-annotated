// 题目：3219. 切蛋糕的最小总开销 II（Minimum Cost for Cutting Cake II）
// 思路：与 I 相同的双指针贪心；数据范围更大，累加值可能溢出 int，因此用 long long 并用 1LL 提升乘法。
// 时间复杂度：O(m log m + n log n)，主要是两次排序；空间复杂度：O(1)，只用了双指针与计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {  // m、n 是蛋糕行列数；两个列表分别是横切、竖切的价格
        sort(horizontalCut.rbegin(), horizontalCut.rend());  // 横切价格降序排列，保证先处理贵的切法（原地排序）
        sort(verticalCut.rbegin(), verticalCut.rend());  // 竖切价格降序排列
        long long ans = 0;  // 累计总开销，用 long long 防止超过 int 范围
        int i = 0, j = 0;  // i、j 分别指向横切、竖切数组中还没用过的最大价格
        int h = 1, v = 1;  // h：横切一次要穿过的竖块数；v：竖切一次要穿过的横块数，最初蛋糕只有 1 块
        while (i < m - 1 || j < n - 1) {  // 只要还有切法没用完就继续
            if (j == n - 1 || (i < m - 1 && horizontalCut[i] > verticalCut[j])) {  // 竖切已经用完，或横切单价更高时，选择横切
                ans += 1LL * horizontalCut[i++] * v;  // 1LL 把乘法提升为 64 位，避免单价乘块数时溢出；i 后移
                h++;  // 横切把蛋糕多切出一道边界，以后竖切要穿过的横块数加一
            } else {  // 否则选择竖切
                ans += 1LL * verticalCut[j++] * h;  // 同样用 1LL 保证 64 位乘法；j 后移
                v++;  // 竖切把蛋糕多切出一道边界，以后横切要穿过的竖块数加一
            }
        }
        return ans;  // 所有切法都用完，返回最小总开销
    }
};