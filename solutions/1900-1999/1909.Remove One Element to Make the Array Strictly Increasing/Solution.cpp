// 题目：1909. 删除一个元素使数组严格递增（Remove One Element to Make the Array Strictly Increasing）
// 思路：先扫描出第一处 nums[i] >= nums[i+1] 的位置，被删元素只可能是 i 或 i+1；用 check 分别验证删掉其中一个后剩余数组是否严格递增。
// 时间复杂度：O(n)，最多两次线性扫描；空间复杂度：O(1)，只使用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool canBeIncreasing(vector<int>& nums) {  // nums：待检查的整数数组，返回能否只删一个元素使其严格递增
        int n = nums.size();  // n：数组长度，供 lambda 与主逻辑共用
        auto check = [&](int k) -> bool {  // 定义局部 lambda check(k)：判断删掉下标 k 后数组是否严格递增
            int pre = 0;  // pre：上一个保留元素的值；初值 0 是合法下界（元素均为正数）
            for (int i = 0; i < n; ++i) {  // 按原顺序遍历每个下标
                if (i == k) {  // 遇到要删除的下标 k
                    continue;  // 跳过该元素，不参与相邻比较
                }
                if (pre >= nums[i]) {  // 出现 pre >= nums[i]，即保留元素之间不再严格递增
                    return false;  // 违反条件，立刻判定这种删法失败
                }
                pre = nums[i];  // 更新 pre，作为下一个保留元素的比较基准
            }
            return true;  // 所有比较都通过，说明删掉下标 k 后严格递增
        };  // lambda 定义结束（末尾分号是语句要求）
        int i = 0;  // i：从头开始、最后一个仍满足严格递增的下标
        while (i + 1 < n && nums[i] < nums[i + 1]) {  // 向后扫描，直到遇到第一处 nums[i] >= nums[i+1]
            ++i;  // 继续后移
        }
        return check(i) || check(i + 1);  // 冲突只可能通过删除 i 或 i+1 修复，任一可行即返回 true
    }  // 方法结束
};  // 类定义结束
