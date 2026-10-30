// 题目：918. 环形子数组的最大和（Maximum Sum Circular Subarray）
// 思路：环形最大和 = max(普通最大子段和, 总和 - 非空最小子段和)，用前缀和的最小/最大值一次扫描求出。
// 时间复杂度：O(n)，只扫描一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSubarraySumCircular(vector<int>& nums) {  // nums 是环形数组（首尾相连）
        const int inf = 1 << 30;  // inf 表示「正无穷」，1<<30 足够大且与真实值相加不易溢出
        int pmi = 0, pmx = -inf;  // pmi：此前出现过的最小前缀和；pmx：此前的最大前缀和
        int ans = -inf, s = 0, smi = inf;  // ans：不跨越边界的最大子段和；s：当前前缀和；smi：非空最小子段和
        for (int x : nums) {  // 从左到右遍历，边扫描边更新
            s += x;  // 累加得到当前前缀和
            ans = max(ans, s - pmi);  // 以当前位置结尾的最大子段和 = 当前前缀和 - 此前最小前缀和
            smi = min(smi, s - pmx);  // 以当前位置结尾的最小子段和 = 当前前缀和 - 此前最大前缀和
            pmi = min(pmi, s);  // 更新最小前缀和，供后续位置使用
            pmx = max(pmx, s);  // 更新最大前缀和，供后续位置使用
        }  // 结束遍历
        return max(ans, s - smi);  // 取「不环形」与「环形取反」两种情况的较大者
    }  // 结束 maxSubarraySumCircular 方法
};  // 结束 Solution 类