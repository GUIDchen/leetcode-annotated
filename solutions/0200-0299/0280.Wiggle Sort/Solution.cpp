// 题目：280. 摆动排序（Wiggle Sort）🔒
// 思路：从左到右扫描，按位置奇偶强制 nums[奇数] > 相邻、nums[偶数] < 相邻；一次交换即可修复局部逆序，且不会破坏已成立的左侧关系。
// 时间复杂度：O(n)，只扫一遍；空间复杂度：O(1)，原地交换。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    void wiggleSort(vector<int>& nums) {  // nums：待原地调整的数组，返回后需满足摆动序列
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始，逐个修复与前一个元素的大小关系
            if ((i % 2 == 1 && nums[i] < nums[i - 1]) || (i % 2 == 0 && nums[i] > nums[i - 1])) {  // 奇数下标应大于前驱、偶数下标应小于前驱，违反其一就交换
                swap(nums[i], nums[i - 1]);  // 交换后当前位置满足摆动要求，且不会破坏之前已修好的部分
            }
        }
    }
};