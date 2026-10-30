// 题目：3218. 切蛋糕的最小总开销 I（Minimum Cost for Cutting Cake I）
// 思路：两种切法各自降序排序后做双指针贪心，每次取当前更贵的切法，代价 = 单价 × 该方向上当前被穿过的块数。
// 时间复杂度：O(m log m + n log n)，主要是两次排序；空间复杂度：O(1)，只用了双指针与计数器。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {  // m、n 是蛋糕行列数；horizontalCut 是 m-1 条横切线的价格，verticalCut 是 n-1 条竖切线的价格
        sort(horizontalCut.rbegin(), horizontalCut.rend());  // 横切价格降序排列，保证先处理贵的切法（原地排序）
        sort(verticalCut.rbegin(), verticalCut.rend());  // 竖切价格降序排列
        int ans = 0;  // 累计的最小总开销
        int i = 0, j = 0;  // i、j 分别指向横切、竖切数组中还没用过的最大价格
        int h = 1, v = 1;  // h：横切一次要穿过的竖块数；v：竖切一次要穿过的横块数，最初蛋糕只有 1 块
        while (i < m - 1 || j < n - 1) {  // 只要还有切法没用完就继续
            if (j == n - 1 || (i < m - 1 && horizontalCut[i] > verticalCut[j])) {  // 竖切已经用完，或横切单价更高时，选择横切
                ans += horizontalCut[i++] * v;  // 横切一次要穿过 v 块，费用是单价乘块数；i 后移准备下一次
                h++;  // 横切把蛋糕多切出一道边界，以后竖切要穿过的横块数加一
            } else {  // 否则选择竖切
                ans += verticalCut[j++] * h;  // 竖切一次要穿过 h 块，费用是单价乘块数；j 后移
                v++;  // 竖切把蛋糕多切出一道边界，以后横切要穿过的竖块数加一
            }
        }
        return ans;  // 所有切法都用完，返回最小总开销
    }
};