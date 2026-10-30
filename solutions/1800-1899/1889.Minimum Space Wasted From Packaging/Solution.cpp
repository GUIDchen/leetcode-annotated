// 题目：1889. 装包裹的最小浪费空间（Minimum Space Wasted From Packaging）
// 思路：排序包裹后，对每个供应商的箱子也排序；箱子由小到大扫描，用 upper_bound 二分出「当前箱子能装的包裹区间」，按箱子体积乘以数量累加总体积，最后用总体积减去包裹体积和得到浪费。
// 时间复杂度：O(n log n + Σ b_i log n)，n 为包裹数、b_i 为该方案箱子数；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {  // packages：各包裹尺寸；boxes：每种供应商方案可用的箱子尺寸，返回最小浪费空间
        int n = packages.size(), m = boxes.size();  // 记录包裹数与方案数（后续直接用容器接口，未再引用）
        sort(packages.begin(), packages.end());  // 把包裹升序排序，之后才能对每个箱子二分出可容纳的包裹区间
        const int mod = 1e9 + 7;  // 结果按题目要求对 1e9+7 取模
        const long long inf = 1LL << 62;  // 用一个足够大的数表示「暂时还没有可行方案」
        long long ans = inf;  // ans 保存所有可行供应商方案中最小的箱子总体积
        for (auto& box : boxes) {  // 逐个供应商方案尝试
            sort(box.begin(), box.end());  // 该方案的箱子也升序排列，才能贪心地由小到大装包裹
            if (packages.back() > box.back()) {  // 最大的包裹比最大的箱子还大，这个方案必然装不下
                continue;  // 直接跳过该方案
            }  // 结束可行性判断
            int i = 0;  // i 是「尚未装箱的包裹」的起始下标，它左边的包裹都已装好
            long long s = 0;  // s 是当前方案下所有箱子体积之和（含浪费）
            for (auto& b : box) {  // 按箱子从小到大扫描
                int j = upper_bound(packages.begin() + i, packages.end(), b) - packages.begin();  // 二分求第一个大于 b 的位置 j，区间 [i, j) 的包裹都装进这个箱子
                s += 1LL * (j - i) * b;  // 区间内每个包裹各占一个体积 b，用 1LL 防止 int 乘法溢出
                i = j;  // 已装好的包裹不再参与后续箱子，起点右移
            }  // 结束箱子扫描
            ans = min(ans, s);  // 用当前方案的总体积刷新最小值
        }  // 结束方案枚举
        return ans == inf ? -1 : (ans - accumulate(packages.begin(), packages.end(), 0LL)) % mod;  // 总浪费 = 箱子总体积 - 包裹体积和；无解返回 -1，结果取模
    }  // 方法结束
};  // 类定义结束