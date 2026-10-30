// 题目：697. 数组的度（Degree of an Array）
// 思路：先统计每个元素出现的次数（度）以及它第一次、最后一次出现的位置；再挑出出现次数等于数组度的元素，取「末次减首次加一」最小的区间长度。
// 时间复杂度：O(n)，三次线性扫描；空间复杂度：O(n)，三张哈希表最多各存 n 个不同元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findShortestSubArray(vector<int>& nums) {  // nums 是输入数组，返回与整体度相同的最短连续子数组长度
        unordered_map<int, int> cnt;  // 记录每个元素出现的次数
        unordered_map<int, int> left;  // 记录每个元素第一次出现的下标
        unordered_map<int, int> right;  // 记录每个元素最后一次出现的下标
        int degree = 0;  // 数组的度：任意元素出现次数的最大值
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右扫一遍数组
            int v = nums[i];  // 当前元素的值
            degree = max(degree, ++cnt[v]);  // 先把该元素计数加一，再用它更新整体的度
            if (!left.count(v)) {  // 判断是不是第一次遇到这个值
                left[v] = i;  // 只有第一次出现才记录左端点
            }
            right[v] = i;  // 每遇到一次就刷新右端点，循环结束后即最后一次的位置
        }
        int ans = 1e6;  // 用一个足够大的数初始化最短长度
        for (int v : nums) {  // 再扫一遍数组，挑出达到度的元素
            if (cnt[v] == degree) {  // 只考虑出现次数等于数组度的值
                int t = right[v] - left[v] + 1;  // 该值全部出现位置被包住所需的区间长度
                if (ans > t) {  // 若这个区间更短
                    ans = t;  // 更新最短长度
                }
            }
        }
        return ans;  // 返回满足条件的最短子数组长度
    }
};
