// 题目：992. K 个不同整数的子数组（Subarrays with K Different Integers）
// 思路：滑动窗口。恰好 k 个 = 至多 k-1 个的起点数 - 至多 k 个的起点数，两次窗口统计相减。
// 时间复杂度：O(n)，左右指针各自最多移动 n 步；空间复杂度：O(n)，计数数组与每个右端点的结果数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int subarraysWithKDistinct(vector<int>& nums, int k) {  // nums：输入数组；k：要求的「不同整数个数」；返回满足条件的子数组数量
        vector<int> left = f(nums, k);  // left[i]：以 i 结尾、不同整数个数不超过 k 的最左起点
        vector<int> right = f(nums, k - 1);  // right[i]：以 i 结尾、不同整数个数不超过 k-1 的最左起点
        int ans = 0;  // 答案累加器
        for (int i = 0; i < nums.size(); ++i) {  // 逐个右端点统计贡献
            ans += right[i] - left[i];  // 恰好 k 个的起点个数 = right[i] - left[i]
        }
        return ans;  // 返回子数组总数
    }

    vector<int> f(vector<int>& nums, int k) {  // 滑动窗口：对每个右端点 i，求不同整数个数不超过 k 时的最左起点 j
        int n = nums.size();  // n 为数组长度
        vector<int> pos(n);  // pos[i] 记录以 i 结尾时窗口的最左起点
        int cnt[n + 1];  // cnt[v] 统计值 v 在窗口内出现的次数（值域 0..n，用变长数组即可）
        memset(cnt, 0, sizeof(cnt));  // 计数器清零
        int s = 0;  // s 是窗口内不同整数的个数
        for (int i = 0, j = 0; i < n; ++i) {  // i 是右端点，j 是左端点，初始窗口为空
            if (++cnt[nums[i]] == 1) {  // 把 nums[i] 计入窗口；它首次出现时不同整数个数要加一
                ++s;  // 新出现的值使不同整数个数增加
            }
            for (; s > k; ++j) {  // 不同整数个数超过 k 时，从左侧不断移出元素
                if (--cnt[nums[j]] == 0) {  // 移出 nums[j]；它出现次数归零时不同整数个数减一
                    --s;  // 该值在窗口内已完全消失
                }
            }
            pos[i] = j;  // 记录当前右端点对应的合法最左起点
        }
        return pos;  // 返回每个右端点对应的最左起点数组
    }
};  // 类定义结束