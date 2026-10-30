// 4075. 最长有韧性的子数组 I（Longest Resilient Subarray I）
// 核心思路：同一段内元素必须模 k 同余，段长 cnt 的整段删掉任一元素后剩余和模 k 为 x * (cnt - 1)，为 0 时该段即为有韧性子数组，扫描时维护最长长度。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(1)。
class Solution {  // 题解类
public:  // 对外接口
    int resilientSubarray(vector<int>& nums, int k) {  // 返回最长的“有韧性”子数组长度：删掉其中任意一个元素后，剩余元素之和仍能被 k 整除
        int ans = 0, cnt = 0;  // ans 记录最长长度，cnt 记录当前同余连续段的长度
        for (int i = 0; i < nums.size(); i++) {  // 从左到右扫描数组
            int x = nums[i] % k;  // 当前元素模 k 的余数
            if (i > 0 && nums[i - 1] % k == x) {  // 前一个元素与当前元素同余，可以并入同一段
                cnt++;  // 段长加一
            } else {  // 否则同余段在此断开
                cnt = 1;  // 以当前元素为新的起点
            }  // 分支结束
            if (x * (cnt - 1) % k == 0) {  // 删掉该段任一元素后剩余和模 k 为 x * (cnt - 1)，为 0 即满足韧性条件
                ans = max(ans, cnt);  // 更新最长长度
            }  // 条件分支结束
        }  // 扫描结束
        return ans;  // 返回最长有韧性子数组的长度
    }  // 方法结束
};  // 类定义结束
