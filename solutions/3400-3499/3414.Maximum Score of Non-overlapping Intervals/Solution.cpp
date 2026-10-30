// 3414. 不重叠区间的最大得分 / Maximum Score of Non-overlapping Intervals
// 核心思路：按起点排序后二分求每个区间的后继，再从后往前 DP 选至多 4 个区间，同分时取下标序列字典序最小者。
// 复杂度：时间复杂度 O(n log n + 4n)，空间复杂度 O(4n)。
class Solution {  // 题解类定义
public:  // 公有接口
    vector<int> maximumWeight(vector<vector<int>>& intervals) {  // 选出至多 4 个不重叠区间，使总分最大且下标序列字典序最小
        int n = intervals.size();  // 区间数量
        vector<array<int, 4>> arr(n);  // 把区间连同原始下标打包成四元组
        for (int i = 0; i < n; ++i) {  // 逐个打包
            arr[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};  // {起点, 终点, 权重, 原下标}
        }  // 结束打包循环
        ranges::sort(arr);  // 按起点升序排序
        vector<int> nxt(n);  // nxt[i]：与区间 i 不重叠的下一个区间的下标
        for (int i = 0; i < n; ++i) {  // 对每个区间二分查找
            int l = i + 1, r = n;  // 二分区间 [i+1, n)
            while (l < r) {  // 二分循环
                int mid = (l + r) >> 1;  // 取中点
                if (arr[mid][0] > arr[i][1]) {  // 中点的起点严格大于区间 i 的终点
                    r = mid;  // 答案落在左半部分
                } else {  // 否则
                    l = mid + 1;  // 答案落在右半部分
                }  // 结束二分判断
            }  // 结束二分循环
            nxt[i] = l;  // 记录后继下标
        }  // 结束 nxt 计算
        vector<vector<long long>> f(n + 1, vector<long long>(5));  // f[i][k]：从区间 i 起选 k 个区间的最大得分
        vector<vector<vector<int>>> g(n + 1, vector<vector<int>>(5));  // g[i][k]：对应得分下字典序最小的下标序列
        for (int i = n - 1; i >= 0; --i) {  // 从后向前递推
            for (int k = 1; k < 5; ++k) {  // 枚举选取个数 1..4
                long long s1 = f[i + 1][k];  // 不选区间 i 的得分
                vector<int> a1 = g[i + 1][k];  // 不选区间 i 的下标序列
                long long s2 = f[nxt[i]][k - 1] + arr[i][2];  // 选区间 i 的得分（接上 nxt[i] 处选 k-1 个）
                vector<int> a2 = g[nxt[i]][k - 1];  // 选区间 i 时对应下标序列
                a2.insert(ranges::lower_bound(a2, arr[i][3]), arr[i][3]);  // 把下标 i 按序插入序列
                if (s2 > s1 || (s2 == s1 && a2 < a1)) {  // 得分更大，或得分相同但序列字典序更小
                    f[i][k] = s2;  // 采用选择区间 i 的方案得分
                    g[i][k] = move(a2);  // 采用选择区间 i 的方案序列
                } else {  // 否则
                    f[i][k] = s1;  // 采用不选区间 i 的方案得分
                    g[i][k] = move(a1);  // 采用不选区间 i 的方案序列
                }  // 结束方案比较
            }  // 结束个数枚举
        }  // 结束递推
        return g[0][4];  // 答案为从头选 4 个区间的下标序列
    }  // 结束 maximumWeight
};  // 结束题解类
