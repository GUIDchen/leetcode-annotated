// 题目：354. 俄罗斯套娃信封问题（Russian Doll Envelopes）
// 思路：按宽度升序、同宽高度降序排序，问题转成高度序列的最长严格递增子序列，用贪心加二分（d 数组）求解。
// 时间复杂度：O(n log n)，排序加 n 次二分；空间复杂度：O(n)，d 数组最多存 n 个高度。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxEnvelopes(vector<vector<int>>& envelopes) {  // envelopes 每项为 [宽, 高]，返回最多能嵌套的信封层数
        sort(envelopes.begin(), envelopes.end(), [](const auto& e1, const auto& e2) {  // 先排序：宽度升序，宽度相同时高度降序，避免同宽信封被误判为可嵌套
            return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);  // 宽度小者在前；宽度相同则高度大者在前
        });  // 排序比较函数结束
        int n = envelopes.size();  // 信封个数
        vector<int> d{envelopes[0][1]};  // d 维护高度序列“最长严格递增子序列”在每个长度下的最小末尾值
        for (int i = 1; i < n; ++i) {  // 从第二个信封开始逐个处理其高度
            int x = envelopes[i][1];  // 当前信封的高度
            if (x > d[d.size() - 1])  // 比当前末尾还大，答案长度可以直接加一
                d.push_back(x);  // 把该高度接到末尾
            else {  // 否则要替换 d 中第一个大于等于 x 的位置
                int idx = lower_bound(d.begin(), d.end(), x) - d.begin();  // 二分找到第一个大于等于 x 的位置
                if (idx == d.size()) idx = 0;  // 源码保留的兜底分支：正常不会取到 size，若出现则回退到下标 0
                d[idx] = x;  // 换成更小的末尾值，后面更容易接上
            }  // 分支结束
        }  // 遍历结束
        return d.size();  // d 的长度就是最多可嵌套的层数
    }  // 方法结束
};  // 类定义结束