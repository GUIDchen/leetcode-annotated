// 题目：2962. 统计最大元素出现至少 K 次的子数组（Count Subarrays Where Max Element Appears at Least K Times）
// 思路：先求出整个数组的最大值 mx，再用滑动窗口枚举左端点，右端点单调右移直到窗口内 mx 出现 k 次，累加合法右端点的个数。
// 时间复杂度：O(n)，右端点 j 只增不减，每个下标最多被扫过一次；空间复杂度：O(1)，只用了常数个整型变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countSubarrays(vector<int>& nums, int k) {  // nums：输入数组；k：最大元素至少要出现的次数；返回满足条件的子数组个数
        int mx = *max_element(nums.begin(), nums.end());  // 先求出整个数组的最大值 mx（max_element 返回迭代器，解引用取出元素）
        int n = nums.size();  // 缓存数组长度，后面会反复用到
        long long ans = 0;  // 答案：合法子数组个数最多 O(n^2)，所以用 long long 防止溢出
        int cnt = 0, j = 0;  // cnt：窗口内等于 mx 的元素个数；j：窗口右端点（左闭右开，即当前窗口为 [i, j)）
        for (int x : nums) {  // 枚举左端点 i，x 就是 nums[i]，稍后左端点右移时用它把元素移出窗口
            while (j < n && cnt < k) {  // 右端点一直右移，直到窗口里已有 k 个最大值，或者右端点到达数组末尾
                cnt += nums[j++] == mx;  // nums[j] 等于 mx 时计数加一；无论是否相等 j 都后移一位（先比较再自增）
            }  // 内层 while 结束
            if (cnt < k) {  // 右端点已到末尾但仍不足 k 个：左端点再右移只会让最大值更少，可以直接结束
                break;  // 提前跳出对左端点的枚举
            }  // if 结束
            ans += n - j + 1;  // 窗口 [i, j) 已含 k 个最大值，则右端点取 j-1..n-1 都合法，共 n-(j-1)=n-j+1 个
            cnt -= x == mx;  // 左端点右移一位：若离开窗口的 nums[i]（即 x）是最大值，就从计数中减去
        }  // for 结束
        return ans;  // 返回合法子数组总数
    }  // 方法结束
};  // 类定义结束