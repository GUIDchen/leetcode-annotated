// 题目：2948. 交换得到字典序最小的数组（Make Lexicographically Smallest Array by Swapping Elements）
// 思路：先把所有下标按元素值升序排序；排序后值相差不超过 limit 的连续一段构成互相可达的连通块，块内元素可任意换位。于是把块内原下标升序、元素值升序一一对应填回，就能让较小的值落到较小的下标上。
// 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，下标数组、临时数组与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {  // nums 为输入数组，limit 为允许交换的两个元素的最大差值
        int n = nums.size();  // 数组长度
        vector<int> idx(n);  // idx 保存「按元素值升序排列后」对应的原始下标
        iota(idx.begin(), idx.end(), 0);  // 用 0..n-1 填充索引数组
        sort(idx.begin(), idx.end(), [&](int i, int j) {  // 按元素值给下标排序，而不是直接破坏性地排序元素本身
            return nums[i] < nums[j];  // 比较器：值小的下标排在前面（值相等时顺序无关）
        });
        vector<int> ans(n);  // 存放最终答案
        for (int i = 0; i < n;) {  // 逐个处理排序后的连通块，i 是当前块的起点
            int j = i + 1;  // j 从 i 的下一个位置开始试探
            while (j < n && nums[idx[j]] - nums[idx[j - 1]] <= limit) {  // 相邻两值之差不超过 limit，说明它们可互相交换，块可以继续向右扩
                ++j;  // 把 j 纳入当前块
            }
            vector<int> t(idx.begin() + i, idx.begin() + j);  // 取出该连通块内元素对应的原始下标
            sort(t.begin(), t.end());  // 把块内原始下标升序排列，让较小的位置拿到较小的值
            for (int k = i; k < j; ++k) {  // 按下标从小到大依次回填
                ans[t[k - i]] = nums[idx[k]];  // 第 k 小的值放到第 t[k-i] 小的下标上：块内元素可以任意重排
            }
            i = j;  // 跳到下一个连通块
        }
        return ans;  // 返回字典序最小的结果数组
    }
};