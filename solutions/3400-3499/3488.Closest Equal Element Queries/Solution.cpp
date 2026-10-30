// 3488. 距离最小相等元素查询 / Closest Equal Element Queries
// 核心思路：把数组首尾相接复制成两倍长度，从左、从右各扫一遍求出每个位置到最近相等元素的距离，再把后半段的结果合并回前半段，查询时距离达到 n 即表示不存在其它相等元素。
// 复杂度：时间 O(n + q)，空间 O(n)。
class Solution {  // 定义题解类
public:  // 公有接口
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {  // 主函数：对每个查询返回该位置到最近相等元素的距离
        int n = nums.size();  // 原数组长度
        int m = n * 2;  // 数组复制一遍，长度变为两倍以处理环形
        vector<int> d(m, m);  // d[i] 记录位置 i 到最近相等元素的距离，先初始化为 m（表示无穷大）

        unordered_map<int, int> left;  // 记录每个值上一次（左侧最近）出现的下标
        for (int i = 0; i < m; i++) {  // 从左往右扫描两倍数组
            int x = nums[i % n];  // 取环形意义下的元素
            if (left.count(x)) {  // 左侧出现过相同元素
                d[i] = min(d[i], i - left[x]);  // 用左侧最近距离更新
            }  // 结束左侧判断
            left[x] = i;  // 更新该值最近出现的下标
        }  // 结束从左扫描

        unordered_map<int, int> right;  // 记录每个值下一次（右侧最近）出现的下标
        for (int i = m - 1; i >= 0; i--) {  // 从右往左扫描两倍数组
            int x = nums[i % n];  // 取环形意义下的元素
            if (right.count(x)) {  // 右侧出现过相同元素
                d[i] = min(d[i], right[x] - i);  // 用右侧最近距离更新
            }  // 结束右侧判断
            right[x] = i;  // 更新该值最近出现的下标
        }  // 结束从右扫描

        for (int i = 0; i < n; i++) {  // 把后半段的答案合并回前半段
            d[i] = min(d[i], d[i + n]);  // 跨越首尾边界的距离也可能更小
        }  // 结束合并

        vector<int> ans;  // 存放每个查询的答案
        for (int query : queries) {  // 逐个处理查询
            ans.push_back(d[query] >= n ? -1 : d[query]);  // 距离达到 n 说明没有其它相等元素，返回 -1
        }  // 结束查询循环
        return ans;  // 返回所有答案
    }  // 结束 solveQueries
};  // 结束 Solution 类
