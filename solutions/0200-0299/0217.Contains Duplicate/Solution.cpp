// 题目：217. 存在重复元素（Contains Duplicate）
// 核心思路：先排序，重复元素必然相邻，再线性扫描相邻对即可判断。
// 时间复杂度：O(n log n)，排序为主开销；空间复杂度：O(log n)，sort 的递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    bool containsDuplicate(vector<int>& nums) {  // 判断数组中是否存在重复元素
        sort(nums.begin(), nums.end());  // 先原地升序排序，排序后重复元素必相邻
        for (int i = 0; i < nums.size() - 1; ++i) {  // 遍历到倒数第二个元素为止，每次与后一个元素比较
            if (nums[i] == nums[i + 1]) {  // 相邻两元素相等，说明存在重复
                return true;  // 返回 true
            }  // if 结束
        }  // 循环结束
        return false;  // 没有重复元素
    }  // 方法结束
};  // 类定义结束