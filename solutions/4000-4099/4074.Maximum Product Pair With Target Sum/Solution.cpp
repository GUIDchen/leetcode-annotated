// 4074. 和为目标值的最大乘积对（Maximum Product Pair With Target Sum）
// 核心思路：一次遍历并用哈希表记录每个数值最新下标；对当前值 x 查互补值 y = target - x 是否出现过，在满足两值不等的条件下最大化乘积。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution {  // 题解类
public:  // 对外接口
    vector<int> maxProductPair(vector<int>& nums, int target) {  // 求和为 target 且乘积最大的下标对，数值较大者对应的下标放在前面
        unordered_map<int, int> pos;  // 记录每个数值最后一次出现的下标
        int mx = INT_MIN;  // 当前的最大乘积，初始为整型最小值
        vector<int> ans = {-1, -1};  // 答案下标对，找不到时保持 {-1, -1}
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右遍历数组
            int x = nums[i], y = target - x;  // x 为当前值，y 为与之配对的互补值
            if (x != y && x * y > mx && pos.contains(y)) {  // 两值不相等（需满足 nums[i] > nums[j]）、乘积更优且互补值已经出现过
                int j = pos[y];  // 取出互补值此前出现的下标
                mx = x * y;  // 更新最大乘积
                ans = x > y ? vector<int>{i, j} : vector<int>{j, i};  // 数值较大者的下标放在前面，保证 nums[ans[0]] > nums[ans[1]]
            }  // 条件分支结束
            pos[x] = i;  // 记录当前值最新的下标
        }  // 遍历结束
        return ans;  // 返回最优下标对，无解时为 {-1, -1}
    }  // 方法结束
};  // 类定义结束