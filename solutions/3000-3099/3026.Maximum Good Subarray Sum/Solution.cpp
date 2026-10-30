// 题目：3026. 最大好子数组和（Maximum Good Subarray Sum）
// 核心思路：边扫描边维护前缀和 s，并用哈希表 p 记录「某个值出现位置之前的最小前缀和」；对当前元素 x，若 x-k 或 x+k 出现过，就用 s 减去对应的最小前缀和更新答案，最后把下一个元素的前缀和按更小值写入表中。
// 时间复杂度：O(n)，每个元素只做常数次哈希查询；空间复杂度：O(n)，哈希表最多保存 n 个不同的值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long maximumSubarraySum(vector<int>& nums, int k) {  // nums：输入数组；k：好子数组首尾元素差的绝对值；返回最大子数组和
        unordered_map<int, long long> p;  // p：值 → 该值出现位置之前的最小前缀和
        p[nums[0]] = 0;  // 第一个元素之前没有元素，前缀和记为 0
        long long s = 0;  // s：当前前缀和（累加到 nums[i] 为止）
        const int n = nums.size();  // n：数组长度
        long long ans = LONG_LONG_MIN;  // ans：目前找到的最大子数组和，先置为最小可能值
        for (int i = 0;; ++i) {  // 逐元素扫描，循环退出条件放在循环体内部判断
            s += nums[i];  // 把当前元素累加进前缀和
            auto it = p.find(nums[i] - k);  // 找与 nums[i] 相差 k 的前一个值
            if (it != p.end()) {  // 找到了，说明能形成长度至少为 2 的好子数组
                ans = max(ans, s - it->second);  // 用当前前缀和减去它的最小前缀和，取较大值更新答案
            }
            it = p.find(nums[i] + k);  // 再查另一个方向：与 nums[i] 相差 k 的值
            if (it != p.end()) {  // 同样也能形成好子数组
                ans = max(ans, s - it->second);  // 同样用两者前缀和之差更新答案
            }
            if (i + 1 == n) {  // 已经处理到最后一个元素
                break;  // 结束扫描
            }
            it = p.find(nums[i + 1]);  // 为下一轮做准备：查下一个元素是否已在表中
            if (it == p.end() || it->second > s) {  // 没出现过，或表中已有的前缀和更大
                p[nums[i + 1]] = s;  // 写入更小的前缀和，使后续算出的子数组和更大
            }
        }
        return ans == LONG_LONG_MIN ? 0 : ans;  // 没找到好子数组返回 0，否则返回最大和
    }
};