// 3878. 统计好子数组（Count Good Subarrays）
// 核心思路：用单调栈分别求出每个位置 i 左侧第一个「按位包含 nums[i] 的值」的下标 l[i] 和右侧第一个满足条件的位置 r[i]，则以 i 为「唯一代表」的好子数组数量为 (i - l[i]) * (r[i] - i)，累加即为答案。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)。
class Solution {  // 题解类
public:  // 公有成员
    long long countGoodSubarrays(vector<int>& nums) {  // 返回所有好子数组的数量
        int n = nums.size();  // 数组长度

        vector<int> l(n, -1);  // l[i]：左侧第一个满足条件的位置，不存在时为 -1
        vector<int> stk;  // 单调栈，保存下标

        for (int i = 0; i < n; i++) {  // 从左往右扫描
            int x = nums[i];  // 当前元素
            while (!stk.empty() && nums[stk.back()] < x && (nums[stk.back()] | x) == x) {  // 栈顶更小且其二进制位被 x 完全包含时弹出
                stk.pop_back();  // 栈顶被 x 支配，不可能再作为边界
            }  // 弹栈结束
            l[i] = stk.empty() ? -1 : stk.back();  // 栈顶即左侧最近的支配点
            stk.push_back(i);  // 当前下标入栈
        }  // 左侧边界计算结束

        vector<int> r(n, n);  // r[i]：右侧第一个满足条件的位置，不存在时为 n
        stk.clear();  // 清空栈，复用为从右往左的单调栈

        for (int i = n - 1; i >= 0; i--) {  // 从右往左扫描
            while (!stk.empty() && (nums[stk.back()] | nums[i]) == nums[i]) {  // 栈顶的二进制位被 nums[i] 完全包含时弹出
                stk.pop_back();  // 栈顶被 nums[i] 支配，不可能再作为边界
            }  // 弹栈结束
            r[i] = stk.empty() ? n : stk.back();  // 栈顶即右侧最近的支配点
            stk.push_back(i);  // 当前下标入栈
        }  // 右侧边界计算结束

        long long ans = 0;  // 答案累加器（子数组数量可能很大，用 64 位整数）
        for (int i = 0; i < n; i++) {  // 枚举每个位置作为代表元素
            ans += 1LL * (i - l[i]) * (r[i] - i);  // 左端点有 i-l[i] 种选择，右端点有 r[i]-i 种选择
        }  // 累加结束
        return ans;  // 返回好子数组总数
    }  // 方法结束
};  // 类结束
