// 题目：646. 最长数对链（Maximum Length of Pair Chain）
// 思路：先按右端点升序排序，再贪心扫描：只要当前数对的左端点严格大于上一个已选数对的右端点，就把它接在链尾。
// 时间复杂度：O(n log n)，排序占主导；空间复杂度：O(1)，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findLongestChain(vector<vector<int>>& pairs) {  // pairs 是输入的数对数组，返回最长数对链的长度
        ranges::sort(pairs, {}, [](const auto& p) { return p[1]; });  // C++20 范围排序：以 p[1] 为投影键，即按右端点升序
        int ans = 0, pre = INT_MIN;  // ans 记录链长；pre 记录已选链最后一个右端点，初值取负无穷表示尚未选任何数对
        for (const auto& p : pairs) {  // 按右端点从小到大依次考察每个数对
            if (pre < p[0]) {  // 当前数对左端点严格大于链尾右端点，说明可以接在链上
                pre = p[1];  // 链尾右端点更新为当前数对的右端点
                ++ans;  // 链长加一
            }
        }
        return ans;  // 返回统计出的最长链长度
    }
};
