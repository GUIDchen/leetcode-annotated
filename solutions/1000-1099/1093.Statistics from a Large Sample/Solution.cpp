// 题目：1093. 大样本统计（Statistics from a Large Sample）
// 思路：count[k] 是数值 k 的出现次数。一次遍历求出最小/最大值、总和、样本总数与众数；中位数用前缀和定位（find 找第 i 个样本落在哪个值），偶数个时取中间两个的平均。
// 时间复杂度：O(V)，V = 256 为取值个数（find 最多调用两次，每次最坏扫 V 个值）；空间复杂度：O(1)，只用常数额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<double> sampleStats(vector<int>& count) {  // count[k] 是数值 k 的出现次数，返回 [最小值, 最大值, 均值, 中位数, 众数]
        auto find = [&](int i) -> int {  // lambda：返回第 i 个样本（1-based）落在哪个数值上
            for (int k = 0, t = 0;; ++k) {  // k 为数值，t 为累计样本数
                t += count[k];  // 累加数值 k 的出现次数
                if (t >= i) {  // 累计个数已经覆盖到第 i 个样本
                    return k;  // 这个数值就是答案
                }  // 结束判断
            }  // 结束扫描
        };  // 结束 find 的定义
        int mi = 1 << 30, mx = -1;  // mi 先设为足够大的数，mx 为 -1 表示最大值尚未出现
        long long s = 0;  // s 是所有样本之和，用 long long 防止溢出
        int cnt = 0, mode = 0;  // cnt 为样本总数，mode 记录众数的数值
        for (int k = 0; k < count.size(); ++k) {  // 遍历所有可能取值
            if (count[k]) {  // 只统计出现过（次数大于 0）的数值
                mi = min(mi, k);  // 更新最小值
                mx = max(mx, k);  // 更新最大值
                s += 1LL * k * count[k];  // 累加「数值 × 出现次数」，转 long long 防溢出
                cnt += count[k];  // 累加样本总数
                if (count[k] > count[mode]) {  // 出现次数严格大于当前众数的次数
                    mode = k;  // 更新众数；相等时保留较小的数值，符合题目要求
                }  // 结束众数判断
            }  // 结束非零判断
        }  // 结束统计循环
        double median = cnt % 2 == 1 ? find(cnt / 2 + 1) : (find(cnt / 2) + find(cnt / 2 + 1)) / 2.0;  // 中位数：奇数个取第 cnt/2+1 个样本，偶数个取第 cnt/2 与第 cnt/2+1 个样本的平均
        return vector<double>{(double) mi, (double) mx, s * 1.0 / cnt, median, (double) mode};  // 按题目要求顺序返回最小、最大、均值、中位数、众数
    }  // 结束方法体
};  // 类定义结束