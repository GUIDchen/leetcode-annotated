// 题目：3572. 选择不同 X 值三元组使 Y 值之和最大（Maximize Y‑Sum by Picking a Triplet of Distinct X‑Values）
// 思路：把 (x, y) 打包成二元组并按 y 降序排序，从头贪心扫描：同一个 x 只取 y 最大的那一次，累计到 3 个不同的 x 就立刻返回当前和；不同 x 不足 3 个则返回 -1。
// 时间复杂度：O(n log n)，排序为主，扫描 O(n)；空间复杂度：O(n)，存放二元组与去重集合。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSumDistinctTriplet(vector<int>& x, vector<int>& y) {  // x：每个元素的 X 值；y：每个元素的 Y 值；选出 3 个 X 互不相同的元素使 Y 之和最大，返回该和，凑不齐 3 个则返回 -1
        int n = x.size();  // 元素个数
        vector<array<int, 2>> arr(n);  // 把 x、y 打包成 n 个二元组，便于按 Y 排序
        for (int i = 0; i < n; ++i) {  // 逐元素打包
            arr[i] = {x[i], y[i]};  // 存入第 i 个元素对应的 (X, Y)
        }  // 打包结束
        ranges::sort(arr, [](auto& a, auto& b) {  // 按 Y 从大到小排序
            return b[1] < a[1];  // Y 更大的元素排在前面，等价于降序
        });  // 排序调用结束
        int ans = 0;  // 记录选中的 Y 之和
        unordered_set<int> vis;  // 记录已经选过的 X 值，用于去重
        for (int i = 0; i < n; ++i) {  // 从 Y 最大的元素开始贪心扫描
            int a = arr[i][0], b = arr[i][1];  // 取出当前的 X 与 Y
            if (vis.insert(a).second) {  // insert 返回的 second 为真，说明这个 X 之前没有出现过
                ans += b;  // 同一 X 中当前是最大的 Y，把它累加进答案
                if (vis.size() == 3) {  // 已经凑齐 3 个互不相同的 X
                    return ans;  // 当前和就是最大和，立即返回
                }  // 数量判断结束
            }  // 去重判断结束
        }  // 扫描结束
        return -1;  // 不同的 X 不足 3 个，无解
    }  // 方法结束
};  // 类定义结束
