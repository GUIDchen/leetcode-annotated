// 3828. Final Element After Subarray Deletions | 3828. 删除子数组后的最终元素
// 核心思路：脑筋急转弯——Alice 首手可删掉中间整段只留一端，而 Bob 总能删掉她想保住的中间元素，故答案为两端较大者
// 复杂度：时间 O(1)，空间 O(1)
class Solution {
public:
    int finalElement(vector<int>& nums) {  // 求双方最优策略下最终剩下的元素
        return max(nums[0], nums.back());  // 首元素与尾元素的较大值即为答案
    }
};
