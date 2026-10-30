// 3969. Valid Subarrays With Matching Sum Digits I | 求和后首尾数字相同的有效子数组 I（中等）
// 核心思路：这里 n 很小，直接枚举所有子数组，用 long long 边累加区间和边判断：区间和末位等于 x，且区间和首位也与 x 相同（把和转成字符串取第 0 位）时答案加一。
// 复杂度：时间 O(n^2 · log S)，S 为区间和的量级（每对 (l, r) 一次求和与一次 to_string）；空间 O(1)，只用了常数个变量。
class Solution {  // 定义题解类
public:  // 公有接口
    int countValidSubarrays(vector<int>& nums, int x) {  // 返回“区间和首位与末位都等于 x”的子数组个数
        int n = nums.size();  // 数组长度
        int ans = 0;  // 符合条件的子数组计数

        for (int l = 0; l < n; ++l) {  // 枚举子数组左端点 l
            long long s = 0;  // 以 l 为起点的区间和，累加过程中要用 long long 防溢出
            for (int r = l; r < n; ++r) {  // 枚举子数组右端点 r，区间即 [l, r]
                s += nums[r];  // 把 nums[r] 并入当前区间和
                if (s % 10 == x && to_string(s)[0] - '0' == x) {  // 末位由 s % 10 得到；首位把 s 转成字符串后取下标 0，再减去 '0' 还原成数字
                    ++ans;  // 首位与末位都等于 x，计数加一
                }  // if 结束
            }  // 右端点枚举结束
        }  // 左端点枚举结束

        return ans;  // 返回满足条件的子数组总数
    }  // 方法结束
};  // 类定义结束