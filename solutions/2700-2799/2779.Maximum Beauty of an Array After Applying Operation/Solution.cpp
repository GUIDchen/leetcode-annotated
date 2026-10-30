// 题目：2779. 数组的最大美丽值（Maximum Beauty of an Array After Applying Operation）
// 思路：每个元素 x 最多变成区间 [x - k, x + k] 里的任意值，能变成同一个值就等价于这些区间有公共交点；用差分数组在数值轴上统计区间覆盖数，前缀和的最大值就是答案。
// 时间复杂度：O(n + m)，m 为数值轴长度（与最大值和 k 成正比）；空间复杂度：O(m)，差分数组大小为 m。
class Solution {  // LeetCode 约定的题解类
public:  // 对外暴露的解题方法
    int maximumBeauty(vector<int>& nums, int k) {  // nums 是输入数组，k 是每个元素最多可加/减的次数
        int m = *max_element(nums.begin(), nums.end()) + k * 2 + 2;  // 数值轴长度：覆盖到最大值 + k*2 之后再多留 2 格，防止越界
        vector<int> d(m);  // 差分数组：d[v] 记录数值 v 处区间覆盖数的增量
        for (int x : nums) {  // 把每个元素可取值域 [x - k, x + k] 的贡献打到差分数组上
            d[x]++;  // 区间左端点：覆盖数从 x 处开始加一
            d[x + k * 2 + 1]--;  // 区间右端点再后一格：覆盖数在此处减一，区间长度为 2k + 1
        }
        int ans = 0, s = 0;  // ans 记录最大重叠数；s 是差分数组的前缀和，即当前数值处的覆盖数
        for (int x : d) {  // 从左到右对差分数组求前缀和
            s += x;  // 累加增量，得到该数值处被多少个区间覆盖
            ans = max(ans, s);  // 覆盖数最大的位置就能放下最多的相同值
        }
        return ans;  // 返回数组的最大美丽值
    }
};