// 3810. Minimum Operations to Reach Target Array | 变成目标数组的最少操作次数
// 核心思路：一次操作可以把所有等于某个值的元素同时加一，因此同一数值的所有错位元素可以一次搞定；答案就是“nums[i] != target[i]”位置上 nums[i] 的去重个数。
// 复杂度：时间 O(n)（一次扫描 + 哈希插入）；空间 O(n)（去重集合）。
class Solution {  // 定义题解类
public:  // 公有接口
    int minOperations(vector<int>& nums, vector<int>& target) {  // 返回把 nums 变成 target 所需的最少操作次数
        unordered_set<int> s;  // 记录需要被修改的 nums 值（同一数值一次操作即可全部抬升）
        for (int i = 0; i < nums.size(); ++i) {  // 逐位置比较
            if (nums[i] != target[i]) {  // 该位置与目标不同，必须被操作覆盖到
                s.insert(nums[i]);  // 按数值去重后插入集合
            }  // 结束不等判断
        }  // 扫描结束
        return s.size();  // 不同数值的个数就是最少操作次数
    }  // 方法结束
};  // 类定义结束
