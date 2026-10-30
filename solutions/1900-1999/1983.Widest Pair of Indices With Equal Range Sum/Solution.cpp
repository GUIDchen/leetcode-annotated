// 题目：1983. 范围和相等的最宽索引对（Widest Pair of Indices With Equal Range Sum）
// 思路：区间 (i, j] 内两数组和相等，等价于差数组的前缀和 prefix[i] == prefix[j]；哈希表记录每个前缀和首次出现的下标，取最远距离即可。
// 时间复杂度：O(n)，每个元素只做一次哈希操作；空间复杂度：O(n)，哈希表最多存 n+1 个前缀和。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int widestPairOfIndices(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2：等长的两个数组
        unordered_map<int, int> d;  // 哈希表：键是前缀差，值是它最早出现的下标
        d[0] = -1;  // 空前缀的前缀差为 0，虚拟下标记为 -1，这样从下标 0 开始的区间也能被统计
        int ans = 0, s = 0;  // ans：目前最宽的区间长度；s：当前前缀差
        int n = nums1.size();  // 数组长度，下面按下标遍历
        for (int i = 0; i < n; ++i) {  // 逐个下标扫描
            s += nums1[i] - nums2[i];  // 累加两个数组同位置元素的差，得到到 i 为止的前缀差
            if (d.count(s)) {  // 这个前缀差以前出现过，说明两数组在 (d[s], i] 这段区间内的和相等
                ans = max(ans, i - d[s]);  // 用区间长度更新答案；保留最早出现的下标才能得到最宽区间
            } else {  // 第一次出现这个前缀差
                d[s] = i;  // 记下下标，作为后续区间的左端点
            }  // 分支结束
        }  // 扫描结束
        return ans;  // 返回最宽区间长度，找不到这样的区间时就是初始值 0
    }  // 方法结束
};  // 类定义结束