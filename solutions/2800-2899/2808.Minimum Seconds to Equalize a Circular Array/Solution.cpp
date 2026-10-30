// 题目：2808. 使循环数组所有元素相等的最少秒数（Minimum Seconds to Equalize a Circular Array）
// 思路：用哈希表按数值收集它出现的所有下标；环形数组中同一数值相邻下标的「最大空档」决定它把整圈同化所需的秒数，对所有数值取最小值。
// 时间复杂度：O(n)，每个下标只被统计与比较常数次；空间复杂度：O(n)，哈希表最多保存 n 个下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumSeconds(vector<int>& nums) {  // nums：环形数组，首尾相邻；返回把数组所有元素变相等的最少秒数
        unordered_map<int, vector<int>> d;  // 哈希表：键是数值，值是它出现的所有下标（随扫描天然升序）
        int n = nums.size();  // 数组长度 n，涉及环形时下标要对 n 取模
        for (int i = 0; i < n; ++i) {  // 一次线性扫描，按下标顺序把每个数归档
            d[nums[i]].push_back(i);  // 把下标 i 追加到数值 nums[i] 自己的列表里
        }
        int ans = 1 << 30;  // 答案初值取足够大的 2^30，方便后面不断取 min
        for (auto& [_, idx] : d) {  // 逐一处理每个数值的下标列表（_ 是数值本身，这里用不到，也不需要拷贝）
            int m = idx.size();  // 该数值在数组中一共出现了 m 次
            int t = idx[0] + n - idx[m - 1];  // 首尾相接的环形空档：从最后一个下标绕一圈回到第一个下标
            for (int i = 1; i < m; ++i) {  // 再枚举同一数值相邻两次出现之间的空档
                t = max(t, idx[i] - idx[i - 1]);  // 取最大空档：它决定这个数值把整圈同化完需要多久
            }
            ans = min(ans, t / 2);  // 每秒空档两端各向外扩散一格，故秒数是空档的一半；换另一个数值方案取更优
        }
        return ans;  // 输入非空，ans 一定被更新过，直接返回最少秒数
    }
};  // 类定义结束