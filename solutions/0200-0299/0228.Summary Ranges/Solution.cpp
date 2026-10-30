// 题目：228. 汇总区间（Summary Ranges）
// 思路：双指针。i 指向当前区间起点，j 向右扩展到不再连续为止，把 [i, j] 拼成一个区间字符串，再令 i = j + 1 处理下一段。
// 时间复杂度：O(n)，每个下标只被扫一次；空间复杂度：O(1)，除返回数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<string> summaryRanges(vector<int>& nums) {  // nums 是升序且可能含重复值的数组，返回其中连续区间的字符串表示
        vector<string> ans;  // 保存所有区间字符串，最终按顺序返回
        auto f = [&](int i, int j) {  // 局部 lambda：把闭区间 [i, j] 格式化成题目要求的字符串
            return i == j ? to_string(nums[i]) : to_string(nums[i]) + "->" + to_string(nums[j]);  // 单个元素只写自己；多个元素写成 起点->终点
        };  // lambda 语句结束
        for (int i = 0, j, n = nums.size(); i < n; i = j + 1) {  // i 是当前区间起点、j 是区间终点、n 是长度；每轮把 i 挪到 j 的下一位
            j = i;  // 区间先从单点 i 开始
            while (j + 1 < n && nums[j + 1] == nums[j] + 1) {  // 只要下一个数恰好比当前数大 1，就说明区间还能向右延伸
                ++j;  // 区间终点右移一格
            }
            ans.emplace_back(f(i, j));  // 把 [i, j] 格式化后追加到答案，emplace_back 原地构造节省一次拷贝
        }
        return ans;  // 返回所有区间字符串
    }
};