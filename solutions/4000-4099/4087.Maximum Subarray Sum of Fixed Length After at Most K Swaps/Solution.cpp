// 题目：4087. 最多交换 K 次后固定长度子数组的最大和（Maximum Subarray Sum of Fixed Length After at Most K Swaps）
// 核心思路：枚举每一个长度为 length 的窗口，把窗口内元素升序、窗口外元素降序；一次交换就是用窗口外的最大值换掉窗口内的最小值，按「外面第 j 大 vs 里面第 j 小」成对尝试，收益一旦不为正就停止。可用交换次数受 k、窗口长度与窗口外元素个数共同限制。
// 复杂度：时间 O((n-length+1) * n log n)，每个窗口都要对窗口内外两段排序；空间 O(n)，用于暂存临时数组。
class Solution {  // LeetCode 约定的题解类
public:  // 公开接口
    long long maxSum(vector<int>& nums, int length, int k) {  // 返回至多 k 次交换后、长度为 length 的子数组能取得的最大和
        int n = nums.size();  // n 为数组长度
        int maxSwaps = min(k, min(length, n - length));  // 有效交换次数上限：不超过 k，也不超过窗口内/外的元素个数
        long long ans = LLONG_MIN;  // ans 记录所有窗口中的最大和，初始取最小的 long long 值
        for (int i = 0; i <= n - length; ++i) {  // 枚举子数组的左端点 i
            vector<int> internal(nums.begin() + i, nums.begin() + i + length);  // 拷贝出窗口内的元素
            vector<int> external(nums.begin(), nums.begin() + i);  // 拷贝出窗口左侧的元素
            external.insert(external.end(), nums.begin() + i + length, nums.end());  // 再接上窗口右侧的元素，拼成窗口外的全部元素
            sort(internal.begin(), internal.end());  // 窗口内升序，便于依次取出最小的元素
            sort(external.rbegin(), external.rend());  // 窗口外降序（用反向迭代器），便于依次取出最大的元素
            long long total = accumulate(internal.begin(), internal.end(), 0LL);  // total 为窗口当前和，0LL 保证以 long long 累加
            for (int j = 0; j < maxSwaps; ++j) {  // 最多尝试 maxSwaps 次交换，第 j 大换第 j 小
                long long gain = (long long) external[j] - internal[j];  // 用外面第 j 大的元素换掉里面第 j 小元素的收益
                if (gain <= 0) {  // 收益不为正，后面的交换只会更差
                    break;  // 提前结束本窗口的交换尝试
                }  // 收益判断结束
                total += gain;  // 累加本次交换带来的收益
            }  // 交换尝试结束
            ans = max(ans, total);  // 用当前窗口的和更新全局最大值
        }  // 窗口枚举结束
        return ans;  // 返回所有窗口中的最大子数组和
    }  // maxSum 结束
};  // Solution 类结束
