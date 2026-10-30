// 题目：2905. 找出满足差值条件的下标 II（Find Indices With Index and Value Difference II）
// 思路：与 I 相同，边扫描边维护满足下标差要求的前缀最小值与最大值下标，对每个 i 检查「当前值减前缀最小」和「前缀最大减当前值」两种情况。
// 时间复杂度：O(n)，与放大的数据范围相匹配；空间复杂度：O(1)，只用了常数个下标变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {  // nums：输入数组；indexDifference：下标差下界；valueDifference：值差下界
        int mi = 0, mx = 0;  // mi/mx：当前前缀中最小值、最大值的下标
        for (int i = indexDifference; i < nums.size(); ++i) {  // i 作为较大的下标，从 indexDifference 开始才能找到合法的较小下标
            int j = i - indexDifference;  // j 是刚进入候选前缀、满足下标差条件的较小下标
            if (nums[j] < nums[mi]) {  // 新进入的元素比当前最小值更小
                mi = j;  // 更新最小值下标
            }  // if 语句结束
            if (nums[j] > nums[mx]) {  // 新进入的元素比当前最大值更大
                mx = j;  // 更新最大值下标
            }  // if 语句结束
            if (nums[i] - nums[mi] >= valueDifference) {  // 情况一：当前值减去前缀最小值，差是否达到 valueDifference
                return {mi, i};  // 满足就返回这对下标（mi 是较小下标，i 是较大下标）
            }  // if 语句结束
            if (nums[mx] - nums[i] >= valueDifference) {  // 情况二：前缀最大值减去当前值，差是否达到 valueDifference
                return {mx, i};  // 满足就返回这对下标
            }  // if 语句结束
        }  // for 循环结束
        return {-1, -1};  // 扫描完毕仍无解，按题目要求返回 [-1, -1]
    }  // 方法结束
};  // 类定义结束