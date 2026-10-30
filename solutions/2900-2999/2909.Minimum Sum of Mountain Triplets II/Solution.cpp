// 题目：2909. 元素和最小的山形三元组 II（Minimum Sum of Mountain Triplets II）
// 核心思路：与 2908 同题不同数据规模，用后缀最小值数组配合滚动前缀最小值，枚举峰值 i 并检查两侧是否都存在更小的元素。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，后缀最小值数组 right。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumSum(vector<int>& nums) {  // nums 是输入数组，返回最小山形三元组的元素和
        int n = nums.size();  // 数组长度
        const int inf = 1 << 30;  // 用一个足够大的数当“无穷大”，保证三数相加也不溢出 int
        int right[n + 1];  // right[i] 存放 nums[i..n-1] 的最小值，多开一位便于处理右边界
        right[n] = inf;  // 空后缀的最小值设为 inf，方便统一用 min 递推
        for (int i = n - 1; ~i; --i) {  // ~i 等价于 i >= 0，从右往左递推后缀最小值
            right[i] = min(right[i + 1], nums[i]);  // 后缀最小值 = min(右侧后缀最小值, 当前元素)
        }  // 后缀预处理结束
        int ans = inf, left = inf;  // ans 记录答案；left 记录 nums[0..i-1] 的最小值（前缀最小值）
        for (int i = 0; i < n; ++i) {  // 正序枚举山形三元组的峰值位置 i
            if (left < nums[i] && right[i + 1] < nums[i]) {  // 左右两侧的最小值都要严格小于 nums[i] 才构成山形
                ans = min(ans, left + nums[i] + right[i + 1]);  // 用 left + nums[i] + right[i+1] 更新最小和
            }  // if 结束
            left = min(left, nums[i]);  // 把当前元素并入前缀最小值，供下一个位置使用
        }  // 枚举结束
        return ans == inf ? -1 : ans;  // 没有找到合法三元组时返回 -1
    }  // 方法结束
};  // 类定义结束