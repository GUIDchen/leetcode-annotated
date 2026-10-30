// 题目：2295. 替换数组中的元素（Replace Elements in an Array）
// 思路：用哈希表维护「值 → 下标」，每次替换靠它 O(1) 定位，并让新值接管旧下标。
// 时间复杂度：O(n + m)，n 为数组长度、m 为操作次数；空间复杂度：O(n)，哈希表存 n 个值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {  // nums：初始数组；operations：依次执行的「把 x 换成 y」；返回执行完所有操作后的数组
        unordered_map<int, int> d;  // 哈希表：值 → 该值当前在 nums 中的下标
        for (int i = 0; i < nums.size(); ++i) {  // 先给初始数组建立「值 → 下标」索引
            d[nums[i]] = i;  // 记录每个值所在的位置，之后可以 O(1) 定位
        }
        for (auto& op : operations) {  // 依次执行每一次替换操作
            int x = op[0], y = op[1];  // 本次要把 x 替换成 y
            nums[d[x]] = y;  // 借助哈希表找到 x 的位置，原地改写成 y
            d[y] = d[x];  // y 接管 x 原来的下标，后续针对 y 的操作才能继续定位
        }
        return nums;  // 所有操作执行完毕后返回结果数组
    }
};