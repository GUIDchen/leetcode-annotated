// 题目：632. 最小区间（Smallest Range Covering Elements from K Lists）
// 思路：把 k 个列表的元素合并成按值排序的 (值, 所属列表) 数组，用滑动窗口统计窗口覆盖了哪些列表；k 个列表全部被覆盖时收缩左端点并尝试更新答案。
// 时间复杂度：O(N log N)，N 为元素总数，排序主导；空间复杂度：O(N)，存放合并数组与计数表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> smallestRange(vector<vector<int>>& nums) {  // nums 是 k 个升序列表，返回覆盖每个列表至少一个数的最小区间
        int n = 0;  // n 用来累计元素总数，先清零
        for (auto& v : nums) n += v.size();  // 遍历每个列表，把长度累加得到元素总数
        vector<pair<int, int>> t(n);  // 合并数组：first 是元素值，second 是它来自哪个列表
        int k = nums.size();  // k 是列表个数，窗口必须覆盖全部 k 个列表
        for (int i = 0, j = 0; i < k; ++i) {  // i 遍历每个列表，j 是写入合并数组的下标
            for (int v : nums[i]) {  // 遍历第 i 个列表中的每个元素
                t[j++] = {v, i};  // 把 (值, 列表下标) 写入合并数组，同时让 j 后移
            }  // 内层遍历结束
        }  // 外层遍历结束
        sort(t.begin(), t.end());  // 按元素值升序排序（值相同再按列表下标），窗口的最值才有单调性
        int j = 0;  // 滑动窗口的左端点
        unordered_map<int, int> cnt;  // cnt 记录窗口内每个列表贡献了多少个元素
        vector<int> ans = {-1000000, 1000000};  // 答案初值取足够大的区间，保证第一次命中一定能被更新
        for (int i = 0; i < n; ++i) {  // 右端点 i 从左到右扩张，此时窗口最大值是 t[i].first
            int b = t[i].first;  // b 是当前窗口的最大元素值
            int v = t[i].second;  // v 是该元素所属的列表下标
            ++cnt[v];  // 把该元素计入它所属列表的计数
            while (cnt.size() == k) {  // 窗口已覆盖全部 k 个列表，可以尝试收缩左端点
                int a = t[j].first;  // a 是当前窗口的最小元素值
                int w = t[j].second;  // w 是左端点元素所属的列表下标
                int x = b - a - (ans[1] - ans[0]);  // x 是与当前最优区间的长度差：小于 0 表示更短，等于 0 表示等长
                if (x < 0 || (x == 0 && a < ans[0])) {  // 更短，或等长但左端点更小（题目要求起点最小）
                    ans[0] = a;  // 更新答案的左端点
                    ans[1] = b;  // 更新答案的右端点
                }  // 答案更新结束
                if (--cnt[w] == 0) {  // 左端点元素移出窗口；该列表计数归零说明即将不再被覆盖
                    cnt.erase(w);  // 删除该列表的计数，使 cnt.size() 减小，从而跳出 while
                }  // 计数清理结束
                ++j;  // 左端点右移一格
            }  // 收缩循环结束
        }  // 右端点扩张循环结束
        return ans;  // 返回最终的覆盖最小区间
    }  // 方法结束
};  // 类定义结束