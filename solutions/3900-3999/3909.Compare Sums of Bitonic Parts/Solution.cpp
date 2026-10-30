// 3909. 比较双调部分的和（Compare Sums of Bitonic Parts）
// 思路：先把总和作为右段初值，再从左往右把上升部分的元素并入左段并从右段移除，直到出现下降为止，最后比较两段和的大小。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int compareBitonicSums(vector<int>& nums) {  // 比较双调序列左段与右段的和
        long long l = nums[0], r = 0;  // l：左段和；r：右段和，两者只在峰值处重叠
        for (int x : nums) {  // 先用总和作为右段初值
            r += x;  // 累加全部元素得到总和
        }  // 求和结束
        for (int i = 1; i < nums.size(); ++i) {  // 从第二个元素开始向右寻找峰值
            if (nums[i - 1] > nums[i]) {  // 出现下降，说明峰值已过
                break;  // 停止扩展左段
            }  // 峰值判断结束
            l += nums[i];  // 峰值元素并入左段
            r -= nums[i - 1];  // 该元素不再算入右段
        }  // 分段结束
        if (l == r) {  // 两段和相等
            return -1;  // 返回 -1
        }  // 相等判断结束
        return l > r ? 0 : 1;  // 左段更大返回 0，否则返回 1
    }  // 方法结束
};  // 类定义结束
