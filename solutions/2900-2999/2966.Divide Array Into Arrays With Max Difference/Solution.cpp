// 题目：2966. 划分数组并满足最大差限制（Divide Array Into Arrays With Max Difference）
// 思路：先排序，再每 3 个连续元素贪心分成一组；排序后相邻元素最接近，只要某组首尾差大于 k 就说明无解，返回空数组。
// 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(log n)，排序递归栈（不计返回的结果数组）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> divideArray(vector<int>& nums, int k) {  // nums：输入数组（长度是 3 的倍数）；k：每组内最大值与最小值之差的上限
        sort(nums.begin(), nums.end());  // 排序后相邻元素最接近，按每 3 个一组贪心划分才能让组内极差尽量小
        vector<vector<int>> ans;  // 存放划分结果，每个元素是一个三元组
        int n = nums.size();  // 缓存数组长度
        for (int i = 0; i < n; i += 3) {  // 步长 3 遍历，每 3 个元素分成一组
            vector<int> t = {nums[i], nums[i + 1], nums[i + 2]};  // 取出连续三个元素作为一组（排序后它们之间的差最小）
            if (t[2] - t[0] > k) {  // 排序后 t[0] 最小、t[2] 最大，t[2]-t[0] 就是组内极差
                return {};  // 极差超过 k 说明按当前划分无解，返回空数组
            }  // if 结束
            ans.emplace_back(t);  // 该组合法，追加进结果数组
        }  // for 结束
        return ans;  // 返回划分方案
    }  // 方法结束
};  // 类定义结束